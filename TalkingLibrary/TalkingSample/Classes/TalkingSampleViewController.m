//
//  TalkingSampleViewController.m
//  TalkingSample
//
//  Created by Mario on 11. 1. 10..
//  Copyright 2011 Vanilla Breeze. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "TalkingSampleViewController.h"
#import "EAGLView.h"

/******************예외처리필요******************/
//입력중단
void TalkingEventInputEventInterrupt(void* userReference) {
}

//입력방식바뀔때
void TalkingEventInputEventRouteChange(void* userReference, TalkingRouteType oldRoute, TalkingRouteType newRoute) {
}

//입력가능여부
void TalkingEventInputEventAvailable(void* userReference, bool isAvailable) {
}

/******************비쥬얼라이제이션******************/
//사운드 녹음여부를 체크하는 성량데이터 받아오는 콜백
void TalkingEventMeter(void* userReference, unsigned long channelNum, float* averagePower, float* peakPower) {
	TalkingSampleViewController* vc = userReference;
	vc->avrPower[1] = *averagePower * 0.01 + 1.0;
	vc->avrPower[3] = *averagePower * 0.01 + 1.0;
	vc->peakPower[1] = *peakPower * 0.01 + 1.0;
	vc->peakPower[3] = *peakPower * 0.01 + 1.0;
}

//사운드 FFT변환(이퀄라이징) 데이터 콜백
void TalkingEventEqualizer(void *userReference, unsigned long dataLength, float *data) {
	TalkingSampleViewController* vc = userReference;
	float* vtx = vc->vtxFFT;
	for(int i = 0; i < FFT_SIZE; i++) {
		vtx++;
		*vtx = data[i] * 100.0 + 0.5;
		vtx++;
	}
}

/******************녹음상태이벤트******************/
//녹음시작 콜백
void TalkingEventStartTalking(void *userReference) {
}

//녹음 종료 콜백
void TalkingEventEndTalking(void *userReference) {
	TalkingSampleViewController* vc = userReference;
	float* vtx = vc->vtxFFT;
	for(int i = 0; i < FFT_SIZE; i++) {
		vtx++;
		*vtx = 0.5;
		vtx++;
	}
	vc->avrPower[1] = 0.5;
	vc->avrPower[3] = 0.5;
	vc->peakPower[1] = 0.5;
	vc->peakPower[3] = 0.5;
	
	//녹음 종료후 사운드 플레이
	TalkingPlay(vc->talking);
}


/******************변형이벤트******************/
//사운드 변환 할수 있는 콜백(녹음시 들어옴):샘플코드에는 일단 콜백걸지 않았음
//출력 데이터 변형을 위한 콜백(실시간 변형이기 때문에 텀이 없지만 연산을 많이 할경우 속도가 느려지고 전체적인 변형이 되지 않는다)
void TalkingEventExtensionTalking(void *userReference, unsigned long* outputDataLength, signed long** outputData) {
}

//플레이전에 녹음된 파일경로 리턴(녹음 데이터의 전체적인 변형을 위해:플레이 전에 하기때문에 약간 중간에 텀이 있을수 있음)
void TalkingEventExtensionFilePathTalking(void* userReference, char* recordFilePath) {
}

/******************플레이상태이벤트******************/
//사운드 플레이 콜백
void TalkingEventPlayTalking(void *userReference) {
}

//사운드 플레이 종료 콜백
void TalkingEventPlayEndedTalking(void *userReference) {
	TalkingSampleViewController* vc = userReference;
	float* vtx = vc->vtxFFT;
	for(int i = 0; i < FFT_SIZE; i++) {
		vtx++;
		*vtx = 0.5;
		vtx++;
	}
	vc->avrPower[1] = 0.5;
	vc->avrPower[3] = 0.5;
	vc->peakPower[1] = 0.5;
	vc->peakPower[3] = 0.5;
	
	//사운드 플레이 종료시 녹음대기 상태로 진입
	TalkingRecord(vc->talking);
}


// Uniform index.
enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

@interface TalkingSampleViewController ()
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
- (BOOL)loadShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;
@end

@implementation TalkingSampleViewController

@synthesize animating, context, displayLink;

- (void)awakeFromNib
{
    EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    if (!aContext)
    {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    }
    
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
    
	self.context = aContext;
	[aContext release];
	
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
    
    if ([context API] == kEAGLRenderingAPIOpenGLES2)
        [self loadShaders];
    
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
	
	float* vtxPtr = vtx; 
	for(int i = 0; i < FFT_SIZE; i++) {
		*vtxPtr = 2.0 * ((float)i / FFT_SIZE);
		vtxPtr++;
		vtxPtr++;
	}
	avrPower[0] = avrPowerVtx[0] = 0.0;
	avrPower[0] = avrPowerVtx[2] = 2.0;
	peakPower[0] = peakPowerVtx[0] = 0.0;
	peakPower[0] = peakPowerVtx[2] = 2.0;
	
	//토킹 라이브러리 생성
	talking = TalkingInit([[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) 
							 objectAtIndex:0] 
							stringByAppendingString:@"/record"] 
						   UTF8String],//write가 가능한 임시 도큐먼트 파일 경로
						  
						  TalkingEventInit(self,
										   TalkingEventMeter,//빨간수평선과 초록수평선데이터 콜백
										   TalkingEventEqualizer, //하얀 오디오 데이터 콜백
										   TalkingEventStartTalking, //레코드 시작 콜백
										   TalkingEventEndTalking, //레코드 종료 콜백
										   NULL,	//TalkingEventExtensionTalking, 
										   //입력 오디오 변환 콜백:여기다가는 NULL을 넣을수 있음 
										   //출력 데이터 변형을 위한 콜백(실시간 변형이기 때문에 속도는 느리지 않지만 전체적인 변형이 되지 않는다)
										   TalkingEventExtensionFilePathTalking,//플레이전에 녹음된 파일경로 리턴(녹음 데이터의 전체적인 변형을 위해:플레이 전에 하기때문에 약간 중간에 텀이 있을수 있음)
										   TalkingEventPlayTalking, //사운드 플레이 콜백
										   TalkingEventPlayEndedTalking, //사운드 종료시
										   TalkingEventInputEventInterrupt, //입력이 일반적이지 않게 중단되었을떄
										   TalkingEventInputEventRouteChange, //오디오 입출력 기기가 바뀌었을때
										   TalkingEventInputEventAvailable //오디오 입력여부가 바뀌었을때
										   ),
						  
						  FFT_SIZE,//이퀄라이징시 나오는 데이커 갯수
						  //되도록 종료시점은 시작지점보다 높으면 안되요!
						  0.8, //사운드 녹음시작지점(녹색선):0.0으로 하면 사용안함
						  0.8, //사운드 녹음종료지점(녹색선):0.0으로 하면 사용안함
						  0.0, //사운드 녹음시작지점(빨간선):0.0으로 하면 사용안함
						  0.0, //사운드 녹음종료지점(빨간선):0.0으로 하면 사용안함  -> 되도록 사용하지마세요
						  //녹음 시작후 종료시점이 어느정도 텀이 있어야 올바르게 작동함그러므로 4번째값은 사용을 피하여야 함
						  20.0, //사운드 최대 녹음시간
						  0.7 //사운드녹음속도(낮을수록 빨라짐)
						  );
	
	TalkingRecord(talking);
	//토킹 라이브러리 시작(녹음대기상태로 진입)
}

- (void)dealloc
{
	//토킹하이브러리 해제
	TalkingFree(&talking);
	
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }
    
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    
    [super dealloc];
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }

    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        
        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        TalkingSetIsAwake(talking, true);
        
        CADisplayLink *aDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawFrame)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
        
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        TalkingSetIsAwake(talking, false);
        
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)drawFrame
{
    [(EAGLView *)self.view setFramebuffer];
    
    // Replace the implementation of this method to do your own custom drawing.
    static const GLfloat squareVertices[] = {
        -0.5f, -0.33f,
        0.5f, -0.33f,
        -0.5f,  0.33f,
        0.5f,  0.33f,
    };
    
    static const GLubyte squareColors[] = {
        255, 255,   0, 255,
        0,   255, 255, 255,
        0,     0,   0,   0,
        255,   0, 255, 255,
    };
    
    static float transY = 0.0f;
    
    if ([context API] == kEAGLRenderingAPIOpenGLES2)
    {
        // Use shader program.
        glUseProgram(program);
        
        // Update uniform value.
        glUniform1f(uniforms[UNIFORM_TRANSLATE], (GLfloat)transY);
        transY += 0.075f;	
        
        // Update attribute values.
        glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
        glEnableVertexAttribArray(ATTRIB_VERTEX);
        glVertexAttribPointer(ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, 1, 0, squareColors);
        glEnableVertexAttribArray(ATTRIB_COLOR);
        
        // Validate program before drawing. This is a good check, but only really necessary in a debug build.
        // DEBUG macro must be defined in your debug configurations if that's not already the case.
#if defined(DEBUG)
        if (![self validateProgram:program])
        {
            NSLog(@"Failed to validate program: %d", program);
            return;
        }
#endif
    }
    else
    {
		
		//오디오 이퀄라이저 데이터
		float* _vtx = vtx;
		float* _vtxFFT = vtxFFT;
		for(int i = 0; i < FFT_SIZE; i++) {
			_vtx++;
			_vtxFFT++;
			*_vtx += (*_vtxFFT - *_vtx) * 0.2;
			_vtx++;
			_vtxFFT++;
		}
		
		//오디오 성량 데이터
		avrPowerVtx[1] += (avrPower[1] - avrPowerVtx[1]) * 0.2;
		avrPowerVtx[3] += (avrPower[3] - avrPowerVtx[3]) * 0.2;
		
		peakPowerVtx[1] += (peakPower[1] - peakPowerVtx[1]) * 0.2;
		peakPowerVtx[3] += (peakPower[3] - peakPowerVtx[3]) * 0.2;
		
		static float r, g, b, a;
		
		//토킹라이브러리의 상태에 따라서 배경색 바꾸어줌
		if(talking->status == TalkingStatus_Play){
			r += (0.5 - r) * 0.075;
			g += (0.0 - g) * 0.075;
			b += (0.5 - b) * 0.075;
			a += (1.0 - a) * 0.075;
		} else if(talking->status == TalkingStatus_Recording) {
			r += (0.0 - r) * 0.075;
			g += (0.5 - g) * 0.075;
			b += (0.5 - b) * 0.075;
			a += (1.0 - a) * 0.075;
		} else {
			r += (0.0 - r) * 0.075;
			g += (0.0 - g) * 0.075;
			b += (0.0 - b) * 0.075;
			a += (1.0 - a) * 0.075;
		}
		glClearColor(r, g, b, a);
		
		
		glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glTranslatef(-1.0, -1.0, 0);
        glVertexPointer(2, GL_FLOAT, 0, avrPowerVtx);
		glColor4f(1.0, 0.5, 0.0, 1.0);
		glDrawArrays(GL_LINES, 0, 2);
        glVertexPointer(2, GL_FLOAT, 0, peakPowerVtx);
		glColor4f(0.5, 1.0, 0.0, 1.0);
		glDrawArrays(GL_LINES, 0, 2);
        glVertexPointer(2, GL_FLOAT, 0, vtx);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glDrawArrays(GL_LINE_STRIP, 0, FFT_SIZE);
		glPopMatrix();
    }
    
    
    [(EAGLView *)self.view presentFramebuffer];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load vertex shader");
        return FALSE;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(*shader);
        return FALSE;
    }
    
    return TRUE;
}

- (BOOL)linkProgram:(GLuint)prog
{
    GLint status;
    
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0)
        return FALSE;
    
    return TRUE;
}

- (BOOL)validateProgram:(GLuint)prog
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0)
        return FALSE;
    
    return TRUE;
}

- (BOOL)loadShaders
{
    GLuint vertShader, fragShader;
    NSString *vertShaderPathname, *fragShaderPathname;
    
    // Create shader program.
    program = glCreateProgram();
    
    // Create and compile vertex shader.
    vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"vsh"];
    if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname])
    {
        NSLog(@"Failed to compile vertex shader");
        return FALSE;
    }
    
    // Create and compile fragment shader.
    fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"fsh"];
    if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname])
    {
        NSLog(@"Failed to compile fragment shader");
        return FALSE;
    }
    
    // Attach vertex shader to program.
    glAttachShader(program, vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(program, fragShader);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(program, ATTRIB_VERTEX, "position");
    glBindAttribLocation(program, ATTRIB_COLOR, "color");
    
    // Link program.
    if (![self linkProgram:program])
    {
        NSLog(@"Failed to link program: %d", program);
        
        if (vertShader)
        {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (program)
        {
            glDeleteProgram(program);
            program = 0;
        }
        
        return FALSE;
    }
    
    // Get uniform locations.
    uniforms[UNIFORM_TRANSLATE] = glGetUniformLocation(program, "translate");
    
    // Release vertex and fragment shaders.
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);
    
    return TRUE;
}

@end

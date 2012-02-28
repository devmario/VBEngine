#import "GLVIEW.h"
#import "GLCheck.h"
#import "trackball.h"
#import "drawinfo.h"

@implementation GLVIEW

@synthesize comboBox;

double x = 0.0;
double y = 0.0;
double z = -415.0;
double dx = 0.0;
double dy = 0.0;
double dz = -415.0;

+ (NSOpenGLPixelFormat*) basicPixelFormat
{
    NSOpenGLPixelFormatAttribute attributes [] = {
        NSOpenGLPFAWindow,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16,
        (NSOpenGLPixelFormatAttribute)nil
    };
    return [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];
}


- (void)animationTimer:(NSTimer *)timer
{
	[self drawRect:[self bounds]];
}

-(void)keyDown:(NSEvent *)theEvent
{
    NSString *characters = [theEvent characters];
    if ([characters length]) {
        unichar character = [characters characterAtIndex:0];
	}
}

- (void)mouseDown:(NSEvent *)theEvent
{
    if ([theEvent modifierFlags] & NSControlKeyMask)
		[self rightMouseDown:theEvent];
	else if ([theEvent modifierFlags] & NSAlternateKeyMask)
		[self otherMouseDown:theEvent];
	else {
		NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
		dx = location.x;
		dy = location.y;
	}
}

- (void)rightMouseDown:(NSEvent *)theEvent // pan
{
	NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}

- (void)otherMouseDown:(NSEvent *)theEvent //dolly
{
	NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
}

- (void)mouseUp:(NSEvent *)theEvent
{ 
	if ([theEvent modifierFlags] & NSControlKeyMask) {
		[self rightMouseDown:theEvent];
	} else if ([theEvent modifierFlags] & NSAlternateKeyMask) {
	} else {
		NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
		x -= (dx - location.x);
		y -= (dy - location.y);
		dx = location.x;
		dy = location.y;
        VBCamera2D* c = VBDisplay2DGetCamera(display);
        VBCamera2DSetPosition(c, VBVector2DCreate(x, y));
        VBCamera2DSetZoom(c, z);
	}
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
	[self mouseUp:theEvent];
}

- (void)otherMouseUp:(NSEvent *)theEvent
{
	[self mouseUp:theEvent];
}


- (void)mouseDragged:(NSEvent *)theEvent
{
	NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	x -= (dx - location.x);
	y -= (dy - location.y);
	dx = location.x;
	dy = location.y;
    VBCamera2D* c = VBDisplay2DGetCamera(display);
    VBCamera2DSetPosition(c, VBVector2DCreate(x, y));
    VBCamera2DSetZoom(c, z);
}

- (void)scrollWheel:(NSEvent *)theEvent
{
	float wheelDelta = [theEvent deltaX] +[theEvent deltaY] + [theEvent deltaZ];
	z += wheelDelta * 2;
    VBCamera2D* c = VBDisplay2DGetCamera(display);
    VBCamera2DSetPosition(c, VBVector2DCreate(x, y));
    VBCamera2DSetZoom(c, z);
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
	[self mouseDragged: theEvent];
}

- (void)otherMouseDragged:(NSEvent *)theEvent
{
	[self mouseDragged: theEvent];
}

- (void) drawRect:(NSRect)rect
{	
    [[self openGLContext] makeCurrentContext];
    if(display == NULL) {
        VBEngineStart([[[NSBundle mainBundle] resourcePath] UTF8String], [[[NSBundle mainBundle] resourcePath] UTF8String], 1024,1024, 1024, 1024);
        display = VBDisplay2DInit(VBDisplay2DAlloc());
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    
    VBDisplay2DUpdate(display, 1.0/60);
    VBDisplay2DDraw(display);
	[[self openGLContext] flushBuffer];
}

- (void) prepareOpenGL
{
    long swapInt = 1;
	
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

- (void)dealloc {
	
	[super dealloc];
}

- (void) update
{
	[super update];
	
}

-(id) initWithFrame: (NSRect) frameRect
{
	NSOpenGLPixelFormat * pf = [GLVIEW basicPixelFormat];
    
	
	self = [super initWithFrame: frameRect pixelFormat: pf];
    return self;
}

- (BOOL)acceptsFirstResponder
{
	return YES;
}

- (BOOL)becomeFirstResponder
{
	return  YES;
}

- (BOOL)resignFirstResponder
{
	return YES;
}

- (void) awakeFromNib
{
	timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize
}


char *replaceAll(char *s, const char *olds, const char *news) {
    char *result, *sr;
    size_t i, count = 0;
    size_t oldlen = strlen(olds); if (oldlen < 1) return s;
    size_t newlen = strlen(news);
    
    
    if (newlen != oldlen) {
        for (i = 0; s[i] != '\0';) {
            if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
            else i++;
        }
    } else i = strlen(s);
    
    
    result = (char *) malloc(i + 1 + count * (newlen - oldlen));
    if (result == NULL) return NULL;
    
    
    sr = result;
    while (*s) {
        if (memcmp(s, olds, oldlen) == 0) {
            memcpy(sr, news, newlen);
            sr += newlen;
            s  += oldlen;
        } else *sr++ = *s++;
    }
    *sr = '\0';
    
    return result;
}


- (IBAction)loadObj:(id)sender {
	int i; // Loop counter.
	
	// Create the File Open Dialog class.
	NSOpenPanel* openDlg = [NSOpenPanel openPanel];
	
	// Enable the selection of files in the dialog.
	[openDlg setCanChooseFiles:YES];
	
	
	// Enable the selection of directories in the dialog.
	[openDlg setCanChooseDirectories:NO];
	
	// Display the dialog.  If the OK button was pressed,
	// process the files.
	if ( [openDlg runModalForDirectory:nil file:nil] == NSOKButton )
	{
		// Get an array containing the full filenames of all
		// files and directories selected.
		NSArray* files = [openDlg filenames];
		
		// Loop through all the files and process them.
		for( i = 0; i < [files count]; i++ )
		{
			NSString* fileName = [files objectAtIndex:i];
			
            VBString* _str = VBStringInitWithCString(VBStringAlloc(), [fileName UTF8String]);
            obj = VBObjectFile2DInitAndLoad(VBObjectFile2DAlloc(), _str);
            
            char tmp_path[256] = {0,};
            strcpy(tmp_path, VBStringGetCString(_str));
            VBStringFree(&_str);
            
            char* image_path = replaceAll(tmp_path, "obj", "png");
            printf("image_path : %s\n", image_path);
            
            _str = VBStringInitWithCString(VBStringAlloc(), image_path);
            tex = VBTextureInitAndLoadWithImagePath(VBTextureAlloc(), _str);
            
			[comboBox removeAllItems];
			
            id _id = nil;
            for(int _i = 0; _i < VBObjectFile2DGetLibraryNameIDLength(obj); _i++) {
                VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameAt(obj, _i);
                VBString* _str = VBObjectFile2DLibraryNameIDGetName(_library_name_id);
                //printf("[%d] _library_name_id: %s\n", _i, VBStringGetCString(_str));
                NSString* mystr = [[NSString alloc]initWithFormat:@"%s",VBStringGetCString(_str)];
                if(_i == 0)
                    _id = mystr;
                [comboBox addItemWithObjectValue:mystr];
            }
            
            if (_id) {
                [comboBox selectItemWithObjectValue:_id];
                [self addLibraryModel:comboBox];
            }
		}
	}
}

//- (void)IFplay:(Model*)m {
//	ModelAllLoopPlay(m);
//}


- (IBAction)addLibraryModel:(id)sender {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    
    NSComboBox* _comboBox = (NSComboBox*)sender;
    NSString* str = (NSString*)[_comboBox objectValueOfSelectedItem];
    
    VBString* _str = VBStringInitWithCString(VBStringAlloc(), [str UTF8String]);
    VBObjectFile2DLibraryNameID* _library_name_id = VBObjectFile2DGetLibraryNameIDByName(obj, _str);
    VBStringFree(&_str);
    
    if (model) {
        VBModel2DRemoveChildModel(VBDisplay2DGetTopModel(display), model);
        model = nil;
    }
    
    model = VBModel2DInitWithLibraryNameIDAndTexture(VBModel2DAlloc(), obj, _library_name_id, tex, true);
    VBModel2DSetPosition(model, VBVector2DCreate(1024/2-200, 1024/2-200));
    VBModel2DAddChildModel(VBDisplay2DGetTopModel(display), model);
    
    //	if(self->model) {
    //		ModelRemove(tutorial->topModel, self->model);
    //		ObjectFileMadeMovieClipFree(&self->model);
    //	}
    //	NSComboBox* comboBox = (NSComboBox*)sender;
    //	NSString* str = (NSString*)[comboBox objectValueOfSelectedItem];
    //	if(str) {
    //		self->model = ObjectFileMakeModelWithLibraryName(tutorial->of, (char*)[str UTF8String]);
    //		ModelAdd(tutorial->topModel, self->model);
    //		[self IFplay:self->model];
    //	}
}

- (IBAction)setBackgroundColor:(id)sender {
	NSColorWell* cw = (NSColorWell*)sender;
    //	ModelManagerSetClearColor(tutorial->manager, ColorRGBAInit((unsigned char)(0xFF*[[cw color] redComponent]), 
    //																(unsigned char)(0xFF*[[cw color] greenComponent]), 
    //																(unsigned char)(0xFF*[[cw color] blueComponent]), 
    //																			   0xFF));
}

- (IBAction)setLineVisible:(id)sender {
	NSButton* checkBox = (NSButton*)sender;
	isLine = [checkBox state];
}
- (IBAction)setLineColor:(id)sender {
	NSColorWell* cw = (NSColorWell*)sender;
    //	lineR = (unsigned char)(0xFF*[[cw color] redComponent]);
    //	lineG = (unsigned char)(0xFF*[[cw color] greenComponent]);
    //	lineB = (unsigned char)(0xFF*[[cw color] blueComponent]);
}


@end

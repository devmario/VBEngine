#include "Tutorial.h"
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
		CameraSetDetailValue(tutorial->camera, Vector3DInit(x, y, z), Vector3DInit(x, y, tutorial->camera->center->z), *tutorial->camera->up);
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
	CameraSetDetailValue(tutorial->camera, Vector3DInit(x, y, z), Vector3DInit(x, y, tutorial->camera->center->z), *tutorial->camera->up);
}

- (void)scrollWheel:(NSEvent *)theEvent
{
	float wheelDelta = [theEvent deltaX] +[theEvent deltaY] + [theEvent deltaZ];
	z += wheelDelta * 2;
	CameraSetDetailValue(tutorial->camera, Vector3DInit(x, y, z), Vector3DInit(x, y, tutorial->camera->center->z), *tutorial->camera->up);
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
	renderTutorial(isLine);
	[[self openGLContext] flushBuffer];
}

- (void) prepareOpenGL
{
    long swapInt = 1;
	
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
	
	initTutorial([[[NSBundle mainBundle] resourcePath] UTF8String], 800, 600);
	
	lineR = 0xFF;
	lineG = 0xFF;
	lineB = 0xFF;
	
}

- (void)dealloc {
	
	if(self->model) {
		ModelRemove(tutorial->topModel, self->model);
		ObjectFileMadeMovieClipFree(&self->model);
	}
	
	if(tutorial->of)
		ObjectFileFree(&tutorial->of);
	freeTutorial();
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
			
			if(self->model) {
				ModelRemove(tutorial->topModel, self->model);
				ObjectFileMadeMovieClipFree(&self->model);
			}
			//리소스 로드
			if(tutorial->of)
				ObjectFileFree(&tutorial->of);
			tutorial->of = ObjectFileLoad([fileName UTF8String]); 
			
			[comboBox removeAllItems];
			
			id _id = nil;
			for(int i = 0; i < tutorial->of->library_name_id->length; i++) {
				_NameID* nameID = ArrayObjectAtIndex(tutorial->of->library_name_id, i);
				NSString* mystr = [[NSString alloc]initWithFormat:@"%s",nameID->name];
				if(i == 0)
					_id = mystr;
				[comboBox addItemWithObjectValue:mystr];
			}
			
			if(_id) {
				[comboBox selectItemWithObjectValue:_id];
				[self addLibraryModel:comboBox];
			}
		}
	}
}

- (void)IFplay:(Model*)m {
	ModelAllLoopPlay(m);
}

- (IBAction)addLibraryModel:(id)sender {
	if(self->model) {
		ModelRemove(tutorial->topModel, self->model);
		ObjectFileMadeMovieClipFree(&self->model);
	}
	NSComboBox* comboBox = (NSComboBox*)sender;
	NSString* str = (NSString*)[comboBox objectValueOfSelectedItem];
	if(str) {
		self->model = ObjectFileMakeModelWithLibraryName(tutorial->of, (char*)[str UTF8String]);
		ModelAdd(tutorial->topModel, self->model);
		[self IFplay:self->model];
	}
}

- (IBAction)setBackgroundColor:(id)sender {
	NSColorWell* cw = (NSColorWell*)sender;
	ModelManagerSetClearColor(tutorial->manager, ColorRGBAInit((unsigned char)(0xFF*[[cw color] redComponent]), 
																(unsigned char)(0xFF*[[cw color] greenComponent]), 
																(unsigned char)(0xFF*[[cw color] blueComponent]), 
																			   0xFF));
}

- (IBAction)setLineVisible:(id)sender {
	NSButton* checkBox = (NSButton*)sender;
	isLine = [checkBox state];
}
- (IBAction)setLineColor:(id)sender {
	NSColorWell* cw = (NSColorWell*)sender;
	lineR = (unsigned char)(0xFF*[[cw color] redComponent]);
	lineG = (unsigned char)(0xFF*[[cw color] greenComponent]);
	lineB = (unsigned char)(0xFF*[[cw color] blueComponent]);
}


@end

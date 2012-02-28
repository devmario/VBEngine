#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#import <OpenGL/glu.h>
#import "VBEngine.h"

@interface GLVIEW : NSOpenGLView
{
	NSTimer* timer;
	NSComboBox* comboBox;
	
    VBDisplay2D* display;
    VBModel2D* model;
    VBObjectFile2D* obj;
    VBTexture* tex;
	bool isLine;
}

@property (nonatomic, assign) IBOutlet NSComboBox* comboBox;

+ (NSOpenGLPixelFormat*) basicPixelFormat;

- (void)animationTimer:(NSTimer *)timer;

- (void)keyDown:(NSEvent *)theEvent;

- (void) mouseDown:(NSEvent *)theEvent;
- (void) rightMouseDown:(NSEvent *)theEvent;
- (void) otherMouseDown:(NSEvent *)theEvent;
- (void) mouseUp:(NSEvent *)theEvent;
- (void) rightMouseUp:(NSEvent *)theEvent;
- (void) otherMouseUp:(NSEvent *)theEvent;
- (void) mouseDragged:(NSEvent *)theEvent;
- (void) scrollWheel:(NSEvent *)theEvent;
- (void) rightMouseDragged:(NSEvent *)theEvent;
- (void) otherMouseDragged:(NSEvent *)theEvent;

- (void) drawRect:(NSRect)rect;

- (void) prepareOpenGL;
- (void) update;		// moved or resized

- (BOOL) acceptsFirstResponder;
- (BOOL) becomeFirstResponder;
- (BOOL) resignFirstResponder;

- (id) initWithFrame: (NSRect) frameRect;
- (void) awakeFromNib;





- (IBAction)loadObj:(id)sender;

- (IBAction)addLibraryModel:(id)sender;

- (IBAction)setBackgroundColor:(id)sender;

- (IBAction)setLineVisible:(id)sender;
- (IBAction)setLineColor:(id)sender;

- (IBAction)setLibraryVisible:(id)sender;
- (IBAction)setLibraryColor:(id)sender;

- (IBAction)setInstanceVisible:(id)sender;
- (IBAction)setInstanceColor:(id)sender;

- (IBAction)setGuideVisible:(id)sender;
- (IBAction)setGuideColor:(id)sender;

@end

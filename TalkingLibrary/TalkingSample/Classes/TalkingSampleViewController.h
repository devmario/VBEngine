//
//  TalkingSampleViewController.h
//  TalkingSample
//
//  Created by Mario on 11. 1. 10..
//  Copyright 2011 Vanilla Breeze. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "Talking.h"

#define FFT_SIZE 0xFF

@interface TalkingSampleViewController : UIViewController
{
	@public
    EAGLContext *context;
    GLuint program;
    
    BOOL animating;
    NSInteger animationFrameInterval;
    CADisplayLink *displayLink;
	
	float vtx[FFT_SIZE * 2];
	float vtxFFT[FFT_SIZE * 2];
	
	float avrPowerVtx[2 * 2];
	float peakPowerVtx[2 * 2];
	float avrPower[2 * 2];
	float peakPower[2 * 2];
	
	Talking* talking;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

@end

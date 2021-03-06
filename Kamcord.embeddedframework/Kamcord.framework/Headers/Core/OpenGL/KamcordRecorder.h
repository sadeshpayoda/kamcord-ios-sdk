//
//  KamcordRecorder.h
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <QuartzCore/QuartzCore.h>

@interface KamcordRecorder : NSObject

/*
 *
 * OpenGL setup. Should be called once before any OpenGL rendering
 * is done.
 */
+ (BOOL)initWithEAGLContext:(EAGLContext *)context
                      layer:(CAEAGLLayer *)layer;

/*
 *
 * Call this method to create framebuffers if you don't use MSAA.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer;

/*
 *
 * Call this method to create framebuffers if you use MSAA.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
           msaaFramebuffer:(GLuint)msaaFramebuffer;

/*
 *
 * Call this method to create framebuffers without MSAA.
 * The resulting video will be cropped to the given boundaries.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
                boundaries:(CGRect)boundaries;

/*
 *
 * Call this method to create framebuffers with MSAA.
 * The resulting video will be cropped to the given boundaries.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
           msaaFramebuffer:(GLuint)msaaFramebuffer
                boundaries:(CGRect)boundaries;

/*
 *
 * Call this alongside any code you have that deletes your framebuffers.
 *
 */
+ (void)deleteFramebuffers;


/*
 *
 * Call every render loop before [context presentRenderbuffer:GL_RENDERBUFFER].
 * Pass the OpenGL framebuffer to which the renderbuffer you are presenting
 * is attached.  Returns NO on failure or if Kamcord is disabled.
 *
 */
+ (BOOL)beforePresentRenderbuffer:(GLuint)framebuffer;

/*
 *
 * Call every render loop after [context presentRenderbuffer:GL_RENDERBUFFER].
 *
 */
+ (BOOL)afterPresentRenderbuffer;

/*
 *
 * Call to capture a frame of video before the call to beforePresentRenderbuffer.
 * For instance if the game has a HUD, call captureFrame before drawing the HUD;
 * the HUD will not appear in the final video.
 *
 */
+ (BOOL)captureFrame;

/*
 *
 * Anywhere in your OpenGL code where you would normally bind your defaultFramebuffer,
 * instead bind [KamcordRecorder kamcordFramebuffer].
 *
 */
+ (GLuint)kamcordFramebuffer;

/*
 *
 * Takes a snapshot of the current screen and returns an UIImage.
 *
 */
+ (UIImage *)snapshot;

/*!
 *
 * Set the target video FPS. The default value is 30 FPS.
 *
 * Valid values are 30 or 60. Only newer devices can typically handle 60 FPS.
 *
 */
+ (void)setTargetVideoFPS:(NSUInteger)fps;
+ (NSUInteger)targetVideoFPS;

@end

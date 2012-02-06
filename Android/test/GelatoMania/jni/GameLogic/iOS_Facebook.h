#import <Foundation/Foundation.h>
#import "PlatformFunctions.h"
#import "Facebook.h"

@interface FacebookDelegate : NSObject <FBSessionDelegate, FBRequestDelegate, FBDialogDelegate> {
    Facebook* facebook;
    
    PlatformCallback callback;
    
    BOOL isOperating;
    
    NSMutableData* data;
}

- (id)initWithCallback:(PlatformCallback)_callback;

- (BOOL)setCallback:(PlatformCallback)_callback;
- (PlatformCallback)getCallback;

- (Facebook*)getFacebook;

- (BOOL)getIsOperating;

- (BOOL)logIn;
- (BOOL)logOut;

- (BOOL)requestWithGraphPath:(PlatformFacebookGraphPath)_path;

- (BOOL)appRequestWithMessege:(const char*)_messege withTo:(const char*)_to withNotificationText:(const char*)_notificationText;

- (BOOL)feedWithName:(const char*)_name withCaption:(const char*)_caption withDescription:(const char*)_description withPicture:(const char*)_picture withLink:(const char*)_link;

@end
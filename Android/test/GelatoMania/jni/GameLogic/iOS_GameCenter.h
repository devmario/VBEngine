#import <Foundation/Foundation.h>
#import "PlatformFunctions.h"
#import "cJSON.h"

@interface GameCenter : NSObject {
    BOOL hasAPI;
    
    PlatformCallback callback;
    
    BOOL isOperating;
}

- (id)initWithCallback:(PlatformCallback)_callback;

- (BOOL)setCallback:(PlatformCallback)_callback;
- (PlatformCallback)getCallback;

- (BOOL)isLogIn;

- (BOOL)logIn;

- (BOOL)getIsOperating;

@end

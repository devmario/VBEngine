//
//  TalkingSampleAppDelegate.h
//  TalkingSample
//
//  Created by Mario on 11. 1. 10..
//  Copyright 2011 Vanilla Breeze. All rights reserved.
//

#import <UIKit/UIKit.h>

@class TalkingSampleViewController;

@interface TalkingSampleAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    TalkingSampleViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet TalkingSampleViewController *viewController;

@end


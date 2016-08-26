//
//  AppDelegate.m
//  QYLiveStaticSDKDemo
//
//  Created by Zeaple Choi on 16/8/22.
//  Copyright © 2016年 KingSoft. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import <QYLiveSDK/QYLiveSDK.h>

#define QYLIVE_AK       @"ae0aad8448c8d159ad46055eb9236fe4"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    _window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    _window.backgroundColor = [UIColor whiteColor];
    _window.tintColor = [UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00];
    
    ViewController *viewConttroller = [[ViewController alloc] init];
    UINavigationController *navtionController = [[UINavigationController alloc] initWithRootViewController:viewConttroller];
    navtionController.navigationBar.translucent = NO;
    _window.rootViewController = navtionController;
    
    
    [_window makeKeyAndVisible];
    
    [[QYLiveEngine sharedInstance] initWithAppKey:QYLIVE_AK andObject:nil];

    [[QYLiveEngine sharedInstance] connectWithToken:nil error:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
        
        if (code == QYErrOk) {
            
            QYUserProfile *userProfile = [[QYUserProfile alloc] init];
            userProfile.uid = @"asdfghjkl";
            userProfile.nickName = @"贝吉塔";
            userProfile.profileIcon = @"http://test-huzilong.kss.ksyun.com/ObjectPrefix/201606071506258791";
            
            [[QYLiveEngine sharedInstance] syncUserProfile:userProfile error:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
                
                if (code != QYErrOk) {
                    
                    NSLog(@"syncUserProfile error is %@",extra);
                    
                }else {
                    NSLog(@"syncUserProfile success");
                }
            }];
        }else {
            
            NSLog(@"connect error is %@",extra);
        }
        
    }];


    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end

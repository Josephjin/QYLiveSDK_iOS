//
//  ViewController.m
//  QYLiveStaticSDKDemo
//
//  Created by Zeaple Choi on 16/8/22.
//  Copyright © 2016年 KingSoft. All rights reserved.
//

#import "ViewController.h"
#import "LogInViewController.h"
#import <QYLiveSDK/QYLiveSDK.h>


@interface ViewController ()<QYStatusChangeDelegate>

@property (nonatomic, assign) BOOL  isReady;
@end

@implementation ViewController

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.navigationBar.hidden = NO;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"QYLiveSDK Demo";
    
    UIButton *rightBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [rightBtn setTitle:@"充值" forState:UIControlStateNormal];
    [rightBtn setTitleColor:[UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00] forState:UIControlStateNormal];
    rightBtn.frame = CGRectMake(0, 0, 60, 30);
    [rightBtn addTarget:self action:@selector(leftBtnEvent) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *rightButtonItem = [[UIBarButtonItem alloc] initWithCustomView:rightBtn];
    self.navigationItem.rightBarButtonItem = rightButtonItem;

    
    [[QYLiveEngine sharedInstance] setStatusChangeDelegate:self];
    
    [QYLiveEngine sharedInstance].shouldLogin = ^(){
        
        LogInViewController *loginVC = [[LogInViewController alloc] init];
        UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:loginVC];
        [[QYLiveEngine sharedInstance].topViewController presentViewController:nav animated:YES completion:nil];
    };
    
    UIViewController *liveViewController = [[QYLiveEngine sharedInstance] enterScene:@{kQYLiveEngineViewController : @(QYMainViewController)}];
    
    if (liveViewController) {
        [self.view addSubview:liveViewController.view];
        NSLog(@"viewDidLoad enterScene");
        liveViewController.view.frame = self.view.bounds;
        [QYLiveEngine sharedInstance].target = self;

    }



}

- (void)leftBtnEvent
{
    UIViewController *rechargeController = [[QYLiveEngine sharedInstance] enterScene:@{kQYLiveEngineViewController : @(QYReChargeViewController)}];

    [self.navigationController pushViewController:rechargeController animated:YES];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}

#pragma QYEngeDelegate

- (void)connectTokenStatusChanged:(QYErrCode)status
{
    if (status == QYErrOk) {
        
        UIViewController *liveViewController = [[QYLiveEngine sharedInstance] enterScene:@{kQYLiveEngineViewController : @(QYMainViewController)}];

        if (liveViewController) {
            [self.view addSubview:liveViewController.view];
            NSLog(@"delegate enterScene");
            liveViewController.view.frame = self.view.bounds;
            [QYLiveEngine sharedInstance].target = self;
            
        }

    }
}


@end

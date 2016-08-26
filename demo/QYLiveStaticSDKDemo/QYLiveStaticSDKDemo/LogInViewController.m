//
//  LogInViewController.m
//  QYLiveStaticSDKDemo
//
//  Created by Zeaple Choi on 16/8/23.
//  Copyright © 2016年 KingSoft. All rights reserved.
//

#import "LogInViewController.h"
#import <QYLiveSDK/QYLiveSDK.h>

#define QYLIVE_TOKEN    @"CqQc0ZYfxxtPhMfvdQAMNen5jMM="

typedef void (^LoginSuccess)(NSString *token);
typedef void (^LoginError)(NSError *error);

@interface LogInViewController ()<QYStatusChangeDelegate>

@end

@implementation LogInViewController

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:QYPlayerWillReloadNotification object:nil];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"登录";
    self.view.backgroundColor = [UIColor grayColor];
    
    
    UIButton *leftBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [leftBtn setTitle:@"返回" forState:UIControlStateNormal];
    [leftBtn setTitleColor:[UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00] forState:UIControlStateNormal];
    leftBtn.frame = CGRectMake(0, 0, 60, 30);
    [leftBtn addTarget:self action:@selector(leftBtnEvent) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *leftButtonItem = [[UIBarButtonItem alloc] initWithCustomView:leftBtn];
    self.navigationItem.leftBarButtonItem = leftButtonItem;

    
    UILabel *userNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 80, 60, 40)];
    userNameLabel.text = @"用户名:";
    userNameLabel.textColor = [UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00];
    [self.view addSubview:userNameLabel];
    
    UILabel *passWordLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 120, 60, 40)];
    passWordLabel.text = @"密码:";
    passWordLabel.textColor = [UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00];
    [self.view addSubview:passWordLabel];

    UIButton *logInButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [logInButton setTitle:@"登录" forState:UIControlStateNormal];
    [logInButton setTitleColor:[UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00] forState:UIControlStateNormal];
    [logInButton.layer setBorderColor:[[UIColor colorWithRed:0.314 green:0.890 blue:0.761 alpha:1.00] CGColor]];
    [logInButton.layer setBorderWidth:1];
    logInButton.layer.masksToBounds = YES;
    logInButton.layer.cornerRadius = 6;
    [logInButton addTarget:self action:@selector(login) forControlEvents:UIControlEventTouchUpInside];
    [logInButton setFrame:CGRectMake(20, 200, self.view.frame.size.width - 40, 40)];
    [self.view addSubview:logInButton];

    [[QYLiveEngine sharedInstance] setStatusChangeDelegate:self];

    
}

- (void)leftBtnEvent
{
    [self dismissViewControllerAnimated:YES completion:nil];
}
- (void)login
{

    [[QYLiveEngine sharedInstance] connectWithToken:QYLIVE_TOKEN error:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
        
        if (code == QYErrOk) {
            
            QYUserProfile *userProfile = [[QYUserProfile alloc] init];
            userProfile.uid = @"";
            userProfile.nickName = @"服务端返回来的用户昵称";      //服务端返回来的用户昵称
            userProfile.profileIcon = @"服务端返回来的头像";       //服务端返回来的用户头像
            
            [[QYLiveEngine sharedInstance] syncUserProfile:userProfile error:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
                
                if (code != QYErrOk) {
                    
                    NSLog(@"syncUserProfile error is %@",extra);
                    
                }else {
                    [[NSNotificationCenter defaultCenter] postNotificationName:QYPlayerWillReloadNotification object:nil];
                    [self dismissViewControllerAnimated:YES completion:nil];
                }
            }];
        }else {
            
            NSLog(@"connect error is %@",extra);
        }
        
    }];

}

- (void)loginWithSuccess:(LoginSuccess)success failure:(LoginError)failure
{
    
}


- (void)playerUserStatusChanged:(QYPlayerUserStatus)status
{
    NSLog(@"userStatus is %@",@(status));
    
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

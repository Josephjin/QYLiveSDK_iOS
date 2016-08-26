//
//  QYLiveEngine.h
//  SaaSPrj
//
//  Created by 张俊 on 7/14/16.
//  Copyright © 2016 ksyun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QYTypeDef.h"
#import "QYUserProfile.h"

NS_ASSUME_NONNULL_BEGIN
/**
 *  QYLiveEngine 作为QYLiveSDK对外的接口类，使用者可以很方便的接入直播服务
 */
NS_CLASS_AVAILABLE_IOS(7_0) @interface QYLiveEngine : NSObject

+(instancetype)sharedInstance;
/*
 *  @param ak         ak用于标识客户身份，必填， 请联系金山云获取
 *  @param object     功能模块配置参数，保留
 */
-(void)initWithAppKey:(NSString *)ak andObject:(nullable id)object;

/**
 *  connect之前需要调用initWithAppKey
 *
 *  @param token      用于连接QYServer的token
 *                    token == nil，游客身份
 *                    token != nil，用户身份
 *  @param errorBlock 连接返回的block
 */
-(void)connectWithToken:(nullable NSString *)token error:(QYStatusBlock)errorBlock;

/**
 *  为了获得更好的用户体验，必须使用该接口同步用户信息(非重要信息, 头像、昵称、性别等)到QYServer
 * 该函数必须在connect成功之后调用才生效
 *  @param userProfile 用户信息
 *  @param errorBlock  同步信息block
 *
 */
-(void)syncUserProfile:(QYUserProfile *)userProfile
                 error:(QYStatusBlock)errorBlock;

/*!
    进入sdk中指定界面
    @param context context类型为NSDictionary, 支持的key的类型定义在QYTypeDef.h中
                    比如要跳转到 充值页面，需指定key为kQYLiveEngineViewController， value暂时支持QYViewControllerType的跳转
    @return 返回对应的ViewController
    @description  
            客户可以通过present或者modal的方式进入直播场景页，但需注意：通过modal方式进入场景直播页时，
            需要在直播场景页外包装一个UINavigationController，否则会影响后续界面跳转，示例代码如下：
            UIViewController *liveViewController = [[QYLiveEngine sharedInstance] enterScene:nil];
            UINavigationController *naviViewController = [[UINavigationController alloc] initWithRootViewController:liveViewController];
            [self presentViewController:naviViewController animated:YES completion:nil];
 */

-(UIViewController *)enterScene:(id)context;

/**
 *  与SDK断连，登出时候调用，清空一切信息，用户再次调用SDK的时候需要重新connect 并 syncUserProfile
 */
- (void)disConnect;

/**
 *  用于监听sdk的连接状态
 *
 *  @param delegate 消息接收者
 */
-(void)setStatusChangeDelegate:(id<QYStatusChangeDelegate>)delegate;

/**
 *  QYLiveSDK可以处理直播相关的推送服务，当接收到推送后调用该方法即可
 *  sdk目前支持的推送包括
 *       1.关注开播消息提醒
 *       2.被关注的消息提醒
 *  @param message 推送消息
 */
-(void)dispatchPushMessage:(NSDictionary *)message;

/**
 *  是否开启log，暂不支持release版本的接口设置
 *
 *  @param isOn TRUE 开启 FALSE 关闭
 */
-(void)setLog:(BOOL)isOn;

//@property(nonatomic, copy)NSString *token;

/**
 *  客户需要设置该属性，以便接收分享事件
 */
@property(copy) QYShareBlock share;

#pragma mark -- 高级功能
/**
 *  内部测试使用
 *  如果客户集成了第三方推送，无需调用该接口
 *  设置推送的标识符号
 *
 *  @param identifier 设备标识符
 */
-(void)setPushIdentifier:(NSString *)identifier;

/**
 *  内部测试使用
 *  第三方登录事件回调
 */
@property(copy) QYThirdPartyLoginBlock thirdPartyLogin;

/*！
    当用户身份为游客时，使用sdk内部的某些功能必须登入方可使用，
 sdk提供登入的事件回调， sdk使用者可以接收该事件完成app的登录过程，然后重连，即重新调用connectWithToken方法
 */
@property(nonatomic, copy) QYShouldLoginBlock shouldLogin;

/**
 *  登出的block,在sdk内部调用
 */
@property(copy) QYLogOutBlock logOut;

/**
 *  用于推出playViewController 的target.如果开发者直接加载enterScene返回的controller的view，target不能为空.
 */
@property (nonatomic, weak) UIViewController *target;

/**
 *  SDK 内部的顶层控制器，用于pressent 其他controller
 */
@property(nonatomic, readonly, strong) UIViewController *topViewController;
@end

NS_ASSUME_NONNULL_END




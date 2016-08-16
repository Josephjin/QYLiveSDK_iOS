# QYLiveSDK
##阅读对象
本文档面向所有使用该SDK的开发人员, 测试人员等, 要求读者具有一定的iOS编程开发经验.
##QYLiveSDK简介
QYLiveSDK（以下简称SDK） 是金山云为广大iOS开发者提供的集视频推流播放为一体的，直播/播放组件。SDK提供了可配置化的UI支持。提供了播放列表，直播间，送礼，关注，主播信息简介等UI实现，开发者集成之后，可一键进入直播，实现直播功能

##集成环境
* 1、目前SDK只支持iOS8.0以上。
* 2、SDK支持bitcode
* 3、SDK支持HTTP，HTTPS协议

##集成步骤
* 1、使用CocoaPods 导入 SDK.
pod 'QYLiveSDK', '~> 1.0.0',之后pod install，成功导入之后即可使用。
* 2、直接下载SDK手动导入

##添加依赖库
SDK中引入了一些常用的第三方库，如果开发者的工程中包含以下的某个第三方库，不必要重复导入，如果没有请导入。
以下是需要依赖的第三方库列表：

* AFNetworking
* SDWebImage
* Masonry
* RongCloudIMLib
* MJRefresh
* KSYGPULive_iOS
* SSZipArchive
* FMDB
* pop
* MOBFoundation

这些库可以通过CocoaPods导入，也可以下载下来，手动导入SDK

##快速集成
###1、关键类说明
* QYLiveEngine 	：SDK 核心类，提供了用户调用SDK的接口。
* QYTypeDef		：宏定义文件
* QYUserProfile：用户信息类

###2、接口说明

```
1、初始化SDK，启用SDK的时候第一个需要调用的方法

/*
 *  @param ak         ak用于标识客户身份，必填， 请联系金山云获取
 *  @param object     功能模块配置参数，保留。字典类型，可配置主题颜色等信息。主题色值对应的key值
 *  "SS_AppSkinColor"
 */ 
-(void)initWithAppKey:(NSString *)ak andObject:(nullable id)object;
```

```
2、连接金山云Server，connect之前需要调用initWithAppKey。如果是登录的用户需要在登录成功之后调用
/**
 *
 *  @param token      用于连接QYServer的token
 *                    token == nil，游客身份
 *                    token != nil，用户身份
 *  @param errorBlock 连接返回的block
 */

-(void)connectWithToken:(nullable NSString *)token error:(QYStatusBlock)errorBlock;

```
```
3、同步用户信息
/**
 *  为了获得更好的用户体验，必须使用该接口同步用户信息(非重要信息, 头像、昵称、性别等)到QYServer
 * 该函数必须在connect成功之后调用才生效
 *  @param userProfile 用户信息
 *  @param errorBlock  同步信息block
 *
 */
-(void)syncUserProfile:(QYUserProfile *)userProfile
                 error:(QYStatusBlock)errorBlock;

```
```
4、 进入sdk中指定界面
/*!
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

```
```
5、设置监听代理(可选)
/**
 *  用于监听sdk的连接状态
 *
 *  @param delegate 消息接收者
 */
-(void)setStatusChangeDelegate:(id<QYStatusChangeDelegate>)delegate;

```
```
6、推送设置(可选)
/**
 *  QYLiveSDK可以处理直播相关的推送服务，当接收到推送后调用该方法即可
 *  sdk目前支持的推送包括
 *       1.关注开播消息提醒
 *       2.被关注的消息提醒
 *  @param message 推送消息
 */
-(void)dispatchPushMessage:(NSDictionary *)message;

```
```
7、提示用户登录事件回调，用于游客身份
/*！
    当用户身份为游客时，使用sdk内部的某些功能必须登入方可使用，
 sdk提供登入的事件回调， sdk使用者可以接收该事件完成app的登录过程，然后重连，即重新调用connectWithToken方法
 */
@property(nonatomic, copy) QYShouldLoginBlock shouldLogin;

```

###3、SDK启用示例
 在需要使用SDK的类中，import相关的头文件

* 引入头文件 <QYLiveSDK/QYLiveSDK.h> 

* 开发者从金山云获取AppKey，AppKey用于标识用户身份，必填。
* andObject所带参数是字典类型，可动态配置SDK的状态，传空是默认状态。
* 用AppKey初始化 SDK，开发者APP中只初始化一次token就可以。

```
[[QYLiveEngine sharedInstance] initWithAppKey:QYLIVE_AK andObject:@{@"SS_AppSkinColor":@"#50E3C2"}]
```
* 初始化AppKey成功之后，调用connect方法，连接金山云Server,获取openid
* 如果是登录状态，传入token值。如果传空是未登录状态，用户是游客状态。

```
    [[QYLiveEngine sharedInstance] connectWithToken:@"token" :^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
        
        if (code == QYShareSuccess) {
        
        }else {
        
            NSLog(@"connect error is %@",extra);
        }
    }];


```
* connect成功之后，在connect的成功回调中同步用户信息到金山云Server

```
    [[QYLiveEngine sharedInstance] connectWithToke:nil :^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
        
        if (code == QYShareSuccess) {
        
        	//开发者需自己设置用户信息
            QYUserProfile *userProfile = [[QYUserProfile alloc] init];
            userProfile.uid = @"asdfghjkl";	//设置用户id，可选
            userProfile.nickName = @"傲娇盟主"; //设置用户名
            userProfile.profileIcon = @"http://test-huzilong.kss.ksyun.com/ObjectPrefix/201606071506258791";							//设置用户头像

				//同步用户信息
            [[QYLiveEngine sharedInstance] syncUserProfile:userProfile error:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
                
                if (code != QYShareSuccess) {
                    
                    NSLog(@"syncUserProfile error is %@",extra);

                }
            }];
        }else {
        
            NSLog(@"connect error is %@",extra);
        }
    }];


```
* 在需要进入SDK页面的时候调用enterScene方法，一键进入直播列表页/充值页

```
	NSDiction *context = context = @{kQYLiveEngineViewController : @(QYMainViewController)};
	
    UIViewController *liveViewController = [[QYLiveEngine sharedInstance] enterScene:context];
    UINavigationController *navigationVc = [[UINavigationController alloc] initWithRootViewController:liveViewController];
    [self presentViewController:navigationVc animated:YES completion:nil];

```

* 若按照以上步骤集成仍然出现问题，请及时联系我们，我们将竭诚为您服务！

###4、注意事项
* 如果用户最初是以游客状态进入的，后来转成以登录后的用户身份进来的，需要在登录成功之后调用connectWithToken方法，并在connectWithToken的成功回调之后调用syncUserProfile方法同步用户信息到金山云server。















[1]: http://183.131.21.162:8001/tt-sdk/zxc.jpg


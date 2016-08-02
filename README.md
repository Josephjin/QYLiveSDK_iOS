# QYLiveSDK
##阅读对象
本文档面向所有使用该SDK的开发人员, 测试人员等, 要求读者具有一定的iOS编程开发经验.
##QYLiveSDK简介
QYLiveSDK（以下简称SDK） 是金山云为广大iOS开发者提供的集视频推流播放为一体的，直播/播放组件。SDK提供了可配置化的UI支持。提供了播放列表，直播间，送礼，关注，主播信息简介等UI实现，开发者集成之后，可一键进入直播，实现直播功能

## SDK业务流程
![业务流程图][1]

##集成环境
* 1、目前SDK只支持iOS8.0以上。
* 2、SDK目前暂时不支持bitcode。请在xcodeproj-->BuildSetting-->Build Options 的Enable Bitcode 设置成NO。
* 3、SDK目前暂时不支持HTPPS，请在工程的info.plist中添加App Transport Security Settings,并在之下添加Allow Arbitrary Loads，并设置成YES。

##集成步骤（三选一）
* 1、使用CocoaPods 导入 动态SDK: pod 'QYLiveSDK_Dynamic', '~> 0.3.1',之后pod install，成功导入之后即可使用。
* 2、使用CocoaPods 导入 动态SDK: pod 'QYLiveSDK_Static', '~> 0.3.1',之后pod install，成功导入之后即可使用。
* 3、直接下载SDK手动导入

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


###2、SDK启用
在需要使用SDK的类中，import相关的头文件

 #import <QYLiveSDK/QYLiveSDK.h> 

* 开发者从金山云Server获得Token。
* 用Token初始化 SDK，开发者APP中只初始化一次token就可以。

```
[[QYLiveEngine sharedInstance] initWithToken:QYLIVE_TOKEN];
```
* 初始化Token成功之后，调用connect方法，连接金山云Server,获取openid

```
    [[QYLiveEngine sharedInstance] connect:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
        
        if (code == QYShareSuccess) {
        
        }else {
        
            NSLog(@"connect error is %@",extra);
        }
    }];


```
* connect成功之后，在connect的成功回调中同步用户信息到金山云Server

```
    [[QYLiveEngine sharedInstance] connect:^(QYErrCode code, NSInteger what, NSString * _Nullable extra) {
        
        if (code == QYShareSuccess) {
        
            QYUserProfile *userProfile = [[QYUserProfile alloc] init];
            userProfile.uid = @"asdfghjkl";
            userProfile.nickName = @"傲娇盟主";
            userProfile.profileIcon = @"http://test-huzilong.kss.ksyun.com/ObjectPrefix/201606071506258791";

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
* 在需要进入直播页面的时候调用enterMainScene方法，一键进入直播列表页

```
- (void)enterLive
{
    UIViewController *liveViewController = [[QYLiveEngine sharedInstance] enterMainScene:nil];

    [self.navigationController pushViewController:liveViewController animated:YES];

}


```

* 若按照以上步骤集成仍然出现问题，请及时联系我们，我们将竭诚为您服务！















[1]: http://183.131.21.162:8001/tt-sdk/zxc.jpg


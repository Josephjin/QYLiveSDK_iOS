//
//  QYTypeDef.h
//  SaaSPrj
//
//  Created by 张俊 on 7/14/16.
//  Copyright © 2016 ksyun. All rights reserved.
//

/**
 *定义数据类型
 */

#import <Foundation/Foundation.h>

@class QYShareInfo;
@class QYUserProfile;

#ifdef __cplusplus
#define QY_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define QY_EXTERN	    extern __attribute__((visibility ("default")))
#endif

NS_ASSUME_NONNULL_BEGIN

// 通知
QY_EXTERN NSString *const QYPushIdentifierNotification;

QY_EXTERN NSString *const QYStreamPushDidChangeNotification;


QY_EXTERN NSString *const QYStreamPullDidChangeNotification;

QY_EXTERN NSString *const QYPlayerUserStatusChangeNotification;

QY_EXTERN NSString *const QYPlayerWillReloadNotification;

/**
 *  enterScene接口中context 所在的NSDictionary中的key
 *  value 所对应的值为QYViewControllerType, 传入对应的页面 会做相应的跳转
 */

QY_EXTERN NSString *const kQYLiveEngineViewController;


#pragma mark ---------------------- sdk相关枚举定义

typedef NS_ENUM(NSUInteger, QYViewControllerType){
    //对应首页
    QYMainViewController     = 1,
    QYReChargeViewController = 2,
};

/*
 *  性别
 */
typedef NS_ENUM(NSUInteger, QYSex){
    //男
    QYSexMan      = 1,
    //女
    QYSexWoman    = 2,
    //保密或者未知
    QYSexSecret   = 3,
};

/*
 *  第三方登录类型，微信、QQ、微博等
 */
typedef NS_ENUM(NSUInteger, QYThirdPartyLoginType) {
    //QQ
    QYThirdPartyQQ = 1,
    //微博
    QYThirdPartyWeibo,
    //微信
    QYThirdPartyWeChat,
};


#pragma mark -- 分享相关
/**
 *  分享类型，微信、QQ、微博等
 */
typedef NS_ENUM(NSUInteger, QYSharePlatformType) {
    //QQ
    QYShareTypeQQ =1,
    //微博
    QYShareTypeWeibo,
    //微信
    QYShareTypeWeChat,
    //微信朋友圈
    QYShareTypeWeChatFriend,
    //QQ空间
    QYShareTypeQQZone

};

typedef NS_ENUM(NSUInteger, QYShareType) {

    QYShareTypeLiveEvent =1,
    QYShareTypeInviteFriendEvent,
    
};


typedef NS_ENUM(NSUInteger, QYShareMoment){
    QYShareDefault,
    QYShareAtLiveBegin,
    QYShareAtLiveOnair,
    QYShareAtLiveEnd,
};

#pragma mark -- 主播推流状态

typedef NS_ENUM(NSUInteger, QYPushStreamConnectionStatus){
    
    QYConnStatusIdle = 0,/// 初始化时状态为空闲
    QYConnStatusConnecting,  /// 连接中
    QYConnStatusConnected,  /// 已连接
    QYConnStatusDisconnecting, /// 断开连接中
    QYConnStatusError,/// 推流出错

};

#pragma mark -- 观众拉流状态

typedef NS_ENUM(NSUInteger, QYPullStreamConnectionStatus){
    
    QYPlayerStatusPrepared = 0,  //播放器完成对视频文件的初始化时发送此通知
    QYPlayerStatusDidChange,     //播放状态发生改变时发送此通知
    QYplayerStatusDidFinish,     //正常播放结束或者因为错误播放失败时发送此通知
    QYplayerStatusLoadDataDidChange, //数据加载状态发生改变时发送此通知
    QYplayerStatusMovieNaturalSizeAvailable, //第一次检测出视频的宽高或者播放过程中宽高发生改变时发送此通知
    
};

#pragma mark- 播放页用户状态
typedef NS_ENUM(NSUInteger, QYPlayerUserStatus){
    
    QYPlayerUserQuiteRoomeSuccess = 1,
    QYPlayerUserQuiteRoomeError = 2,
    QYPlayerUserDisConnectSuccess = 3,
    QYPlayerUserdisConnectError = 4,
    QYPlayerUserJoinRoomSuccess = 5,
    QYPlayerUserJoinRoomError = 6,
    
};

#pragma mark -- IM连接状态 聊天室 建立连接的过程状态

typedef NS_ENUM(NSUInteger, QYIMConnectionStatus){
    QYIMConnStatusConnecting   = 0,
    QYIMConnStatusDisconnect   = 1,
    QYIMConnStatusConnected    = 2,
    QYIMConnStatusInvalidToken = 100,
    
};

#pragma makr -- 状态码定义

typedef NS_ENUM(NSUInteger, QYErrCode){
    QYErrBadDns              = -1003,
    QYErrNetworkNotAvailable = -1009,
    QYErrOk                  =  0,
    QYErrInvalidCall         =  1,
    QYErrInvalidToken        =  2,
    QYErrUnknown             =  100,
    
};

/*!
    第三方登录
 */
typedef NS_ENUM(NSUInteger, QYThirdPartyLoginStatus){
    //成功
    QYThirdPartyLoginSuccess    = 1,
    //失败
    QYThirdPartyLoginFail       = 2,
    //取消
    QYThirdPartyLoginCancel     = 3,
    
    QYThirdPartyLoginFailedQQNotInstalled,
    
    QYThirdPartyLoginFailedWeChatNotInstalled,
    
    QYThirdPartyLoginFailedWeiboNotInstalled,
};

typedef NS_ENUM(NSUInteger, QYShareState){
    //成功
    QYShareSuccess              = 1,
    //失败
    QYShareFail                 = 2,
    //取消
    QYShareCancel               = 3,
    
    QYShareFailedQQNotInstalled,
    
    QYShareFailedWeChatNotInstalled,
    
    QYShareFailedWeiboNotInstalled,
};

//typedef void (^)(QYStatusCode status);
#pragma mark ---------------------- sdk相关block定义

typedef void (^QYStatusBlock)(QYErrCode code, NSInteger what, NSString *_Nullable extra);

typedef void (^QYShareStatusBlock)(QYShareState state,  NSError * _Nullable error);

typedef void (^QYShouldLoginBlock)();

typedef void (^QYLogOutBlock)();

typedef void (^QYThirdPartyLoginResultBlock)(QYThirdPartyLoginStatus status, QYUserProfile *_Nullable profile);

typedef void (^QYThirdPartyLoginBlock)(QYThirdPartyLoginType type, QYThirdPartyLoginResultBlock _Nullable result);
/**
 *  分享回调定义
 *
 *  @param type   分享到的平台
 *  @param moment 直播分享的时刻，开播前、开播中、开播后
 */
typedef void (^QYShareBlock)(QYShareInfo *_Nonnull shareInfo, QYShareStatusBlock _Nullable result);




#pragma mark ---------------------- sdk相关协议定义

@protocol QYStatusChangeDelegate <NSObject>

/**
 *   聊天室 建立连接的状态
 *
 *  @param type
 *  @param moment
 */
- (void)onConnectionStatusChanged:(QYIMConnectionStatus)status;

/**
 *  推流转态
 *
 *  @param type
 *  @param moment
 */
- (void)onPushStreamStatusChanged:(QYPushStreamConnectionStatus)status;

/**
 *  拉流状态
 *
 *  @param type
 *  @param moment
 */
- (void)onPullStreamStatusChanged:(QYPullStreamConnectionStatus)status;

- (void)playerUserStatusChanged:(QYPlayerUserStatus)status;

- (void)connectTokenStatusChanged:(QYErrCode)status;

@end

NS_ASSUME_NONNULL_END



//
//  QYShareInfo.h
//  QYLiveSDK
//
//  Created by 张俊 on 7/16/16.
//  Copyright © 2016 qyvideo. All rights reserved.
//

/**
 *  分享功能
 */

#import <Foundation/Foundation.h>
#import "QYTypeDef.h"

@interface QYShareInfo : NSObject

//分享平台
@property(nonatomic, assign) QYSharePlatformType        platform;

//主播昵称
@property(nonatomic, copy) NSString                     *nickName;

//主播头像
@property(nonatomic, copy) NSString                     *anchorUrl;

//分享url
@property(nonatomic, copy) NSString                     *shareUrl;

//分享的时机
@property(nonatomic, assign) QYShareMoment              moment;

//分享类型
@property(nonatomic, assign) QYShareType                type;

@end

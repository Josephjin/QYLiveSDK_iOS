//
//  QYUserProfile.h
//  QYLiveSDK
//
//  Created by 张俊 on 7/15/16.
//  Copyright © 2016 qyvideo. All rights reserved.
//

/**
 *  用户基本信息
 */

#import <Foundation/Foundation.h>
#import "QYTypeDef.h"

@interface QYUserProfile : NSObject

//可选
@property(nonatomic, copy) NSString    *uid;

//头像
@property(nonatomic, copy) NSString    *profileIcon;

//昵称
@property(nonatomic, copy) NSString    *nickName;

//性别
@property(nonatomic, assign) QYSex     sex;

@end

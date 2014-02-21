//
//  DesignResolution.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/20/14.
//
//

#include "Types.h"

#ifndef LotteryDefense_DesignResolution_h
#define LotteryDefense_DesignResolution_h

//Resolution definitions
#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_960X640    1
#define DESIGN_RESOLUTION_1024X768   2
#define DESIGN_RESOLUTION_2048X1536  3
#define DESIGN_RESOLUTION_4096X3072  4

#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480x320

static Resource iphoneResource   =  { cocos2d::CCSizeMake(480, 320),   "iphone"   };
static Resource iphonehdResource =  { cocos2d::CCSizeMake(960, 640),   "iphonehd" };
static Resource ipadResource     =  { cocos2d::CCSizeMake(1024, 768),  "ipad"     };
static Resource ipadhdResource   =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd"   };
static Resource hdResource       =  { cocos2d::CCSizeMake(4096, 3072), "hd"       };


#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960X640)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(960, 640);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(2048, 1536);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_4096X3072)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(4096, 3072);
#else
#error unknown target design resolution!
#endif

#endif

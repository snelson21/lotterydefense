//
//  Types.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/20/14.
//
//

#ifndef LotteryDefense_Types_h
#define LotteryDefense_Types_h

#include "ccTypes.h"

USING_NS_CC;

typedef struct tagResource
{
    CCSize size;
    char directory[100];
} Resource;

enum UnitAlliance { Friendly, Enemy, Neutral };

#endif

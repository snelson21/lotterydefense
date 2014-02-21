//
//  Unit.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/21/14.
//
//

#include "Unit.h"
#include "cocos2d.h"

USING_NS_CC;


#pragma mark -
#pragma mark Constructor/Destructor

Unit::Unit()
{
    
}

Unit::~Unit()
{
    
}

#pragma mark -
#pragma mark Autorelease Creators

Unit *Unit::createWithSpriteFrame(CCSpriteFrame *spriteFrame)
{
    Unit *unit = new Unit();
    if(spriteFrame && unit && unit->initWithSpriteFrame(spriteFrame))
    {
        unit->autorelease();
        return unit;
    }
    
    CC_SAFE_DELETE(unit);
    return NULL;
}

Unit *Unit::createWithSpriteFrameName(const char *spriteFrameName)
{
    CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName %s", spriteFrameName);
    CCAssert(spriteFrame != NULL, msg);
#endif
    
    Unit *unit = Unit::createWithSpriteFrame(spriteFrame);
    return unit;
}

#pragma mark -
#pragma mark Initialization

bool Unit::initWithSpriteFrame(CCSpriteFrame *spriteFrame)
{
    //TODO custom initilization will go here eventually
    
    //return the super
    return CCSprite::initWithSpriteFrame(spriteFrame);
}
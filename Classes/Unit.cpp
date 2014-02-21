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

#pragma mark -
#pragma mark Getters / Setters

void Unit::setTargetEnemy(Unit *targetEnemy)
{
    CC_SAFE_RELEASE(_targetEnemy);
    _targetEnemy = targetEnemy;
    CC_SAFE_RETAIN(_targetEnemy);
}

void Unit::setMovingAnimation(CCAnimation *movingAnimation)
{
    CC_SAFE_RELEASE(_movingAnimation);
    _movingAnimation = movingAnimation;
    CC_SAFE_RETAIN(_movingAnimation);
}

void Unit::setAttackAnimation(CCAnimation *attackAnimation)
{
    CC_SAFE_RELEASE(_attackAnimation);
    _attackAnimation = attackAnimation;
    CC_SAFE_RETAIN(_attackAnimation);
}

void Unit::setStationaryAnimation(CCAnimation *stationaryAnimation)
{
    CC_SAFE_RELEASE(_stationaryAnimation);
    _stationaryAnimation = stationaryAnimation;
    CC_SAFE_RETAIN(_stationaryAnimation);
}

void Unit::setDeathAnimation(CCAnimation *deathAnimation)
{
    CC_SAFE_RELEASE(_deathAnimation);
    _deathAnimation = deathAnimation;
    CC_SAFE_RETAIN(_deathAnimation);
}
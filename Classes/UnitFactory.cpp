//
//  UnitFactory.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/21/14.
//
//

#include "UnitFactory.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "Unit.h"

USING_NS_CC;
using namespace std;

UnitFactory &UnitFactory::sharedInstance()
{
    static UnitFactory instance;
    return instance;
}

UnitFactory::UnitFactory()
{
    init();
}

bool UnitFactory::init()
{
    loadSpriteCache();
    
    loadAnimations();
    
    _units = CCDictionary::createWithContentsOfFileThreadSafe(UNITS_FILE);
    
    return (_units);
}

void UnitFactory::loadSpriteCache()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(UNITS_FRAMES);
    setSpriteBatchNode(CCSpriteBatchNode::create(UNITS_IMAGE));
}

void UnitFactory::loadAnimations()
{
    CCAnimationCache *cache = CCAnimationCache::sharedAnimationCache();
    cache->addAnimationsWithFile(ANIMATIONS_FILE);
}

CCArray *UnitFactory::getUnitTypes()
{
    return _units->allKeys();
}

CCSpriteBatchNode *UnitFactory::getSpriteBatchNode()
{
    return _spriteBatchNode;
}

void UnitFactory::setSpriteBatchNode(CCSpriteBatchNode *spriteBatchNode)
{
    CC_SAFE_RELEASE(_spriteBatchNode);
    _spriteBatchNode = spriteBatchNode;
    CC_SAFE_RETAIN(_spriteBatchNode);
}

Unit *UnitFactory::createUnit(const char *name)
{
    CCDictionary *unitSettings = (CCDictionary *)_units->objectForKey(name);
    if(unitSettings == NULL)
    {
        return NULL;
    }
    
    const char *stationaryFrameName = unitSettings->valueForKey("stationaryFrameName")->getCString();
    float rateOfFire = unitSettings->valueForKey("rateOfFire")->floatValue();
    long attackDamage = unitSettings->valueForKey("attackDamage")->intValue();
    float attackRadius = unitSettings->valueForKey("attackRadius")->floatValue();
    float speed = unitSettings->valueForKey("speed")->floatValue();
    const char *movingAnimationName = unitSettings->valueForKey("movingAnimation")->getCString();
    const char *attackAnimationName = unitSettings->valueForKey("attackAnimation")->getCString();
    
    float anchorVertical = unitSettings->valueForKey("anchorVertical")->floatValue();
    float anchorHorizontal = unitSettings->valueForKey("anchorHorizontal")->floatValue();
    
    
    Unit *unit = Unit::createWithSpriteFrameName(stationaryFrameName);
    unit->setRateOfFire(rateOfFire);
    unit->setAttackDamage(attackDamage);
    unit->setAttackRadius(attackRadius);
    unit->setSpeed(speed);
    
    if(movingAnimationName != NULL)
    {
        CCAnimation *movingAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(movingAnimationName);
        unit->setMovingAnimation(movingAnimation);
    }
    if(attackAnimationName != NULL)
    {
        CCAnimation *attackAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(attackAnimationName);
        unit->setAttackAnimation(attackAnimation);
    }
    
    //unit->setContentSize(unit->getTextureRect().size);
    unit->setAnchorPoint(ccp(anchorHorizontal, anchorVertical));
    //unit->setAnchorPoint(ccp(0.5f, 0.5f));
    _spriteBatchNode->addChild(unit);
    
    return unit;
    
}
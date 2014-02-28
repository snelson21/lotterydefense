//
//  Unit.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/21/14.
//
//

#include "Unit.h"
#include "cocos2d.h"
#include "MovePathIndicator.h"
#include "GameScene.h"
#include "Map.h"
#include "GameTile.h"

USING_NS_CC;


#pragma mark -
#pragma mark Constructor/Destructor

Unit::Unit()
: _stationaryFrame(NULL)
, _movingAnimation(NULL)
, _stationaryAnimation(NULL)
, _attackAnimation(NULL)
, _deathAnimation(NULL)
, _targetEnemy(NULL)
, _movePathIndicator(NULL)
{
    
}

Unit::~Unit()
{
    CC_SAFE_RELEASE(_movingAnimation);
    CC_SAFE_RELEASE(_stationaryAnimation);
    CC_SAFE_RELEASE(_attackAnimation);
    CC_SAFE_RELEASE(_deathAnimation);
    CC_SAFE_RELEASE(_targetEnemy);
    CC_SAFE_RELEASE(_movePathIndicator);
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
    //TODO custom initilization will go here
    _stationaryFrame = spriteFrame;
    
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

void Unit::setStationaryFrame(CCSpriteFrame * stationaryFrame)
{
    CC_SAFE_RELEASE(_stationaryFrame);
    _stationaryFrame = stationaryFrame;
    CC_SAFE_RETAIN(_stationaryFrame);
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


CCRect Unit::getRect()
{
    CCSize size = getContentSize();
    CCPoint anchor = getAnchorPointInPoints();
    return CCRectMake(-anchor.x, -anchor.y, size.width, size.height);
}

void Unit::setMovePathIndicator(MovePathIndicator *movePathIndicator)
{
    CC_SAFE_RELEASE(_movePathIndicator);
    _movePathIndicator = movePathIndicator;
    CC_SAFE_RETAIN(_movePathIndicator);
    getParent()->getParent()->addChild(_movePathIndicator);
}

#pragma mark -
#pragma mark Movement


void Unit::moveToLocation(const CCPoint &newLocation)
{
    CCPoint currentLocation = getPosition();
    float distance = ccpDistance(currentLocation, newLocation);
    float travelTime = distance / _speed;
    CCFiniteTimeAction* actionMove = CCMoveTo::create(travelTime, newLocation);
    CCFiniteTimeAction* actionMoveFinished = CCCallFuncN::create(this, callfuncN_selector(Unit::moveFinished));
    CCRepeat *repeatAnimation = CCRepeat::create(CCAnimate::create(_movingAnimation), -1);
    repeatAnimation->setTag(MOVEMENT_ANIMATION_TAG);
    runAction(repeatAnimation);
    runAction(CCSequence::create(actionMove, actionMoveFinished, NULL));
}

void Unit::moveFinished()
{
    stopActionByTag(MOVEMENT_ANIMATION_TAG);
    setDisplayFrame(_stationaryFrame);
}

#pragma mark -
#pragma mark Touches

bool Unit::containsTouchLocation(CCTouch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void Unit::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void Unit::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool Unit::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if(containsTouchLocation(touch))
    {
        CCLog("Touched Unit at %f,%f", getPosition().x, getPosition().y);
        if(_movePathIndicator == NULL)
        {
            //create the move path indicator
            moveFinished();
            setMovePathIndicator(MovePathIndicator::createWithUnit(this));
        }
        return true;
    }
    return false;
}

void Unit::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    getMovePathIndicator()->setEndPoint(touch->getLocation());
}

void Unit::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    Map *map = ((GameScene *)(getParent()->getParent()))->getMap();
    GameTile *tile = map->getTileForTouch(touch);
    if(tile != NULL)
    {
        CCPoint tilePosition = tile->getPosition();
        _movePathIndicator->setEndPoint(tilePosition);
    }
}

CCObject* Unit::copyWithZone(CCZone *pZone)
{
    this->retain();
    return this;
}

void Unit::touchDelegateRetain()
{
    this->retain();
}

void Unit::touchDelegateRelease()
{
    this->release();
}
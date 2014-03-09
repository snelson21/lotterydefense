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
#include "Pathfinder.h"
#include "AppMacros.h"
#include "Path.h"
#include "PathNode.h"

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
, _gameTile(NULL)
{
    
}

Unit::~Unit()
{
    CC_SAFE_RELEASE(_stationaryFrame);
    CC_SAFE_RELEASE(_movingAnimation);
    CC_SAFE_RELEASE(_stationaryAnimation);
    CC_SAFE_RELEASE(_attackAnimation);
    CC_SAFE_RELEASE(_deathAnimation);
    CC_SAFE_RELEASE(_targetEnemy);
    CC_SAFE_RELEASE(_movePathIndicator);
    CC_SAFE_RELEASE(_gameTile);
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

void Unit::setZIndex(int zIndex)
{
    if(_zIndex != zIndex)
    {
        _zIndex = zIndex;
        getParent()->reorderChild(this, _zIndex);
    }
}

void Unit::setGameTile(GameTile *gameTile)
{
    if(_gameTile != NULL)
    {
        _gameTile->setUnit(NULL);
    }
    
    CC_SAFE_RELEASE(_gameTile);
    _gameTile = gameTile;
    CC_SAFE_RETAIN(_gameTile);
    
    if(gameTile != NULL)
    {
        gameTile->setUnit(this);
        setZIndex(gameTile->getZIndex());
    }
}


CCRect Unit::getRect()
{
    CCSize size = getContentSize();
    CCPoint anchor = getAnchorPointInPoints();
    return CCRectMake(-anchor.x, -anchor.y, size.width, size.height);
}

void Unit::setMovePathIndicator(MovePathIndicator *movePathIndicator)
{
    if(_movePathIndicator != NULL)
    {
        getParent()->getParent()->removeChild(_movePathIndicator);
    }
    CC_SAFE_RELEASE(_movePathIndicator);
    _movePathIndicator = movePathIndicator;
    CC_SAFE_RETAIN(_movePathIndicator);
    if(_movePathIndicator != NULL)
    {
        getParent()->getParent()->addChild(_movePathIndicator);
    }
}

#pragma mark -
#pragma mark Movement


void Unit::moveToLocation(const CCPoint &newLocation)
{
    float travelTime = calcTravelTime(getPosition(), newLocation);
    CCFiniteTimeAction* actionMove = CCMoveTo::create(travelTime, newLocation);
    CCFiniteTimeAction* actionMoveFinished = CCCallFuncN::create(this, callfuncN_selector(Unit::moveFinished));
    CCRepeat *repeatAnimation = createRepeatAnimation(_movingAnimation, MOVEMENT_ANIMATION_TAG);
    runAction(repeatAnimation);
    runAction(CCSequence::create(actionMove, actionMoveFinished, NULL));
}

void Unit::moveAlongPath(Path *path)
{
    if(path == NULL)
    {
        return;
    }
    
    CCPoint startPosition = getPosition();
    CCArray *moveActions = CCArray::create();
    
    PathNode *node = path->head();
    while(node)
    {
        GameTile *tile = node->getGameTile();
        moveActions->addObject(createMoveAction(startPosition, tile->getPosition()));
        startPosition = tile->getPosition();
        node = node->next();
    }
    
    CCFiniteTimeAction* actionMoveFinished = CCCallFuncN::create(this, callfuncN_selector(Unit::moveFinished));
    moveActions->addObject(actionMoveFinished);
    
    CCRepeat *repeatAnimation = createRepeatAnimation(_movingAnimation, MOVEMENT_ANIMATION_TAG);
    runAction(repeatAnimation);
    runAction(CCSequence::create(moveActions));
    this->schedule(schedule_selector(Unit::movementUpdate), MOVEMENT_UPDATE_TIMESTEP);
}


CCRepeat *Unit::createRepeatAnimation(CCAnimation *animation, int tag)
{
    CCRepeat *repeatAnimation = CCRepeat::create(CCAnimate::create(animation), -1);
    repeatAnimation->setTag(tag);
    return repeatAnimation;
}

CCFiniteTimeAction *Unit::createMoveAction(const CCPoint &startPosition, const CCPoint &endPosition)
{
    float travelTime = calcTravelTime(startPosition, endPosition);
    CCLog("Move time %f", travelTime);
    return CCMoveTo::create(travelTime, endPosition);
}

float Unit::calcTravelTime(const CCPoint &startLocation, const CCPoint &endLocation)
{
    float distance = ccpDistance(startLocation, endLocation);
    return distance / _speed;
}

void Unit::moveFinished()
{
    this->unschedule(schedule_selector(Unit::movementUpdate));
    setMovePathIndicator(NULL);
    stopActionByTag(MOVEMENT_ANIMATION_TAG);
    setDisplayFrame(_stationaryFrame);
}


void Unit::warpToTile(GameTile *tile)
{
    setPosition(tile->getPosition());
    setGameTile(tile);
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
        
        GameTile *currentTile = map->getTileForLocation(getPosition());
        
        Pathfinder *pathfinder = Pathfinder::createWithMap(map);
        CC_SAFE_RETAIN(pathfinder);
        Path *path = pathfinder->findPath(currentTile, tile);
        CC_SAFE_RELEASE(pathfinder);
        //drawPath(path);
        
        moveAlongPath(path);
    }
}

void Unit::drawPath(CCArray *path)
{
    if(path == NULL)
    {
        return;
    }
    CCDrawNode *drawNode = CCDrawNode::create();
    CCObject *object;
    CCPoint startLocation = getPosition();
    CCARRAY_FOREACH(path, object)
    {
        GameTile *gameTile = (GameTile *)object;
        CCPoint endLocation = gameTile->getPosition();
        drawNode->drawSegment(startLocation, endLocation, 2, ccc4f(1.0f, 1.0f, 0.0f, 1.0f));
        startLocation = endLocation;
    }
    ((GameScene *)(getParent()->getParent()))->addChild(drawNode);
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

void Unit::movementUpdate(float tileElapsed)
{
    Map *map = ((GameScene *)(getParent()->getParent()))->getMap();
    GameTile *tile = map->getTileForLocation(getPosition());
    
    if(tile->getUnit() != NULL && tile->getUnit() != this)
    {
        stopAllActions();
        moveFinished();
        return;
    }
    
    if(tile != _gameTile)
    {
        CCLog("Updating game tile");
        setGameTile(tile);
    }
    
    if(_movePathIndicator != NULL)
    {
        _movePathIndicator->setStartPoint(getPosition());
    }
}
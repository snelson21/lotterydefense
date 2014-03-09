//
//  Unit.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/21/14.
//
//

#ifndef __LotteryDefense__Unit__
#define __LotteryDefense__Unit__

#include "cocos2d.h"
#include "Types.h"

#define MOVEMENT_ANIMATION_TAG      1
#define STATIONARY_ANIMATION_TAG    2
#define ATTACK_ANIMATION_TAG        3
#define DEATH_ANIMATION_TAG         4

USING_NS_CC;

class MovePathIndicator;
class GameTile;
class Path;

class Unit : public CCSprite, public CCTargetedTouchDelegate
{
    
#pragma mark -
#pragma mark Constructor/Destructor
    
public:
    
    /**
     @brief  Unit constructor
     */
    Unit();
    
    /**
     @brief  Unit destructor
     */
    virtual ~Unit();

#pragma mark -
#pragma mark Autorelease Creators
    
public:
    
    /**
     @brief  Creates and initializes an autoreleased Unit with a sprite frame
     @param  CCSpriteFrame that defines the image and location of the sprite in the image
     @return an autoreleased Unit
     */
    static Unit *createWithSpriteFrame(CCSpriteFrame *spriteFrame);
    
    /**
     @brief  Creates and initializes an autoreleased Unit with a string to retreive the sprite frame from
             CCSpriteFrameCache
     @param  string representing the CCSpriteFrame to use from CCSpriteFrameCache
     @return an autoreleased Unit
     */
    static Unit *createWithSpriteFrameName(const char *spriteFrameName);
   
#pragma mark -
#pragma mark Initialization
    
public:
    
    /**
     @brief  Initializes the Unit with a CCSpriteFrame
     @param  CCSpriteframe that defines the image and location of the sprite in the image
     @return true if the Unit was initialized properly
             false if the Unit failed to initialize
     */
    bool initWithSpriteFrame(CCSpriteFrame *spriteFrame);
    
#pragma mark -
#pragma mark Getters / Setters

public:
    
    inline long getInitialHitPoints() { return _initialHitPoints; }
    inline void setInitialHitPoints(long initialHitPoints) { _initialHitPoints = initialHitPoints; }
    
    inline long getCurrentHitPoints() { return _currentHitPoints; }
    inline void setCurrentHitPoints(long currentHitPoints) { _currentHitPoints = currentHitPoints; }
    
    inline UnitAlliance getAlliance() { return _alliance; }
    inline void setAlliance(UnitAlliance alliance) { _alliance = alliance; }
    
    inline float getAttackRadius() { return _attackRadius; }
    inline void setAttackRadius(float attackRadius) { _attackRadius = attackRadius; }
    
    inline long getAttackDamage() { return _attackDamage; }
    inline void setAttackDamage(long attackDamage) { _attackDamage = attackDamage; }
    
    inline Unit *getTargetEnemy() { return _targetEnemy; }
    void setTargetEnemy(Unit *targetEnemy);
    
    inline float getRateOfFire() { return _rateOfFire; }
    inline void setRateOfFire(float rateOfFire) { _rateOfFire = rateOfFire; }
    
    inline float getSpeed() { return _speed; }
    inline void setSpeed(float speed) { _speed = speed; }
    
    inline CCSpriteFrame *stationaryFrame() { return _stationaryFrame; }
    void setStationaryFrame(CCSpriteFrame * stationaryFrame);
    
    inline CCAnimation *getMovingAnimation() { return _movingAnimation; }
    void setMovingAnimation(CCAnimation *movingAnimation);
    
    inline CCAnimation *getStationaryAnimation() { return _stationaryAnimation; }
    void setStationaryAnimation(CCAnimation *stationaryAnimation);
    
    inline CCAnimation *getAttackAnimation() { return _attackAnimation; }
    void setAttackAnimation(CCAnimation *attackAnimation);
    
    inline CCAnimation *getDeathAnimation() { return _deathAnimation; }
    void setDeathAnimation(CCAnimation *deathAnimation);
    
    CCRect getRect();
    
    inline MovePathIndicator *getMovePathIndicator() { return _movePathIndicator; }
    void setMovePathIndicator(MovePathIndicator *movePathIndicator);
    
    inline GameTile *getGameTile(){ return _gameTile; }
    void setGameTile(GameTile *gameTile);
    
    inline int getZIndex(){ return _zIndex; }
    void setZIndex(int zIndex);
    
#pragma mark -
#pragma mark Movement
    
public:
    
    /**
     @brief  Move the unit to the location specified with movement animation
     @param  the location to move to
     */
    void moveToLocation(const CCPoint &newLocation);
    
    /**
     @brief  Move the unit along an array of tiles
     @param  the array of GameTile objects
     */
    void moveAlongPath(Path *path);
    
    /**
     @brief  Warp the unit to a specific GameTile (no time and no animation)
     @param  GameTile to warp to
     */
    void warpToTile(GameTile *tile);

protected:
    
    /**
     @brief  Callback that will stop the movement animation.  Should be called when movement stops.
     */
    void moveFinished();
    
    /**
     @brief  Create a chainable move action from the start location to the end location
     @param  start position
     @param  end position
     @return moveto action
     */
    CCFiniteTimeAction *createMoveAction(const CCPoint &startPosition, const CCPoint &endPosition);
    
    
    /**
     @brief  Update callback that should be called when the unit is moving
     @param  the amount of time that has elapsed since the last movement
     */
    virtual void movementUpdate(float timeElapsed);
    
#pragma mark -
#pragma mark Touches

public:
    
    /**
     @brief  Check if the location of the given touch event is within the bounding box of the unit
     @param  Touch event with location to check
     @return true if the touch location is within the bounding box of this unit
             false if the touch location is not within the bounding box of this unit
     */
    bool containsTouchLocation(CCTouch* touch);
    
    /**
     @brief  Called when the unit enters the scene
     */
    virtual void onEnter();
    
    /**
     @brief  Called when the unit exits the scene
     */
    virtual void onExit();
    
    /**
     @brief  Called whenever a touch begins on the screen.  This function should translate the touch
             coordinates to node space and confirm if the touch is inside its bounding box then return 
             true or false based on the result.
     @param  The touch object.  Contains location information.
     @param  The event object.  Not Currently Used.
     @return true if this object is claiming the touch
             false if this object does not claim the touch
     */
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    virtual CCObject* copyWithZone(CCZone *pZone);
    
    virtual void touchDelegateRetain();
    
    virtual void touchDelegateRelease();
    
#pragma mark -
#pragma mark Drawing Helpers
    
    
protected:
    
    /**
     @brief  Draws a path segment by segment
     */
    void drawPath(CCArray *path);
    
#pragma mark -
#pragma mark Calculations

protected:
    /**
     @brief  Calculates the travel time for this unit based on its speed to a given location
             from a given location
     @param  start location
     @param  end location
     @return travel time between start and end location
     */
    float calcTravelTime(const CCPoint &startLocation, const CCPoint &endLocation);
    
#pragma mark -
#pragma mark Attributes
    
protected:
    /**
     @brief  The initial hit points this Unit has at creation, used for life percentage calculation
     */
    long _initialHitPoints;
    
    /**
     @brief  The current hit points this Unit has.  When hit with damage this will decrease.
     */
    long _currentHitPoints;
    
    /**
     @brief  Unit alliance
     */
    UnitAlliance _alliance;
    
    /**
     @brief  The radius of a Unit's attack
     */
    float _attackRadius;
    
    /**
     @brief  Unit's attack damage will reduce the attacked unit's hit points by this amount on each hit
     */
    long _attackDamage;
    
    /**
     @brief  Enemy unit that is the current focus of attack.
     */
    Unit *_targetEnemy;
    
    /**
     @brief  Total attacks possible per second
     */
    float _rateOfFire;
    
    /**
     @brief  Speed of movement
     */
    float _speed;
    
    /**
     @brief  Game Tile the unit is currently on
     */
    GameTile *_gameTile;
    
    /**
     @brief  Current z-index of this unit
     */
    int _zIndex;
    

#pragma mark -
#pragma mark Animations

protected:
    /**
     @brief  Stationary sprite frame
     */
    CCSpriteFrame *_stationaryFrame;
    
    /**
     @brief  Animation to play while this unit is moving
     */
    CCAnimation *_movingAnimation;
    
    /**
     @brief  Animation to play while this unit is stationary
     */
    CCAnimation *_stationaryAnimation;
    
    /**
     @brief  Animation to play while this unit is attacking
     */
    CCAnimation *_attackAnimation;
    
    /**
     @brief  Animation to play while this unit is dying
     */
    CCAnimation *_deathAnimation;
    
    /**
     @brief  Create a repeat animation 
     @param  animation to repeat
     @param  tag to stop the animation
     @return a repeat of the animation that repeats forever
     */
    CCRepeat *createRepeatAnimation(CCAnimation *animation, int tag);
    
#pragma mark -
#pragma mark Indicators
    
protected:
    
    /**
     @brief Move Path Indicator
            Should only exist when the unit has been clicked on and the click is being
            dragged to another portion of the screen.
     */
    MovePathIndicator *_movePathIndicator;
};


#endif /* defined(__LotteryDefense__Unit__) */

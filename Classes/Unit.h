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

USING_NS_CC;

class Unit : public CCSprite
{
    
public:
#pragma mark -
#pragma mark Constructor/Destructor
    
    /**
     @brief Unit constructor
     */
    Unit();
    
    /**
     @brief Unit destructor
     */
    ~Unit();

#pragma mark -
#pragma mark Autorelease Creators
    
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
    
    /**
     @brief  Initializes the Unit with a CCSpriteFrame
     @param  CCSpriteframe that defines the image and location of the sprite in the image
     @return true if the Unit was initialized properly
             false if the Unit failed to initialize
     */
    bool initWithSpriteFrame(CCSpriteFrame *spriteFrame);
    
#pragma mark -
#pragma mark Getters / Setters
    
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
    
    inline CCAnimation *getMovingAnimation() { return _movingAnimation; }
    void setMovingAnimation(CCAnimation *movingAnimation);
    
    inline CCAnimation *getStationaryAnimation() { return _stationaryAnimation; }
    void setStationaryAnimation(CCAnimation *stationaryAnimation);
    
    inline CCAnimation *getAttackAnimation() { return _attackAnimation; }
    void setAttackAnimation(CCAnimation *attackAnimation);
    
    inline CCAnimation *getDeathAnimation() { return _deathAnimation; }
    void setDeathAnimation(CCAnimation *deathAnimation);
    
protected:
    
#pragma mark -
#pragma mark Attributes
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

#pragma mark -
#pragma mark Animations
    
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
};


#endif /* defined(__LotteryDefense__Unit__) */

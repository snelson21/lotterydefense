//
//  GameTile.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/24/14.
//
//

#ifndef __LotteryDefense__GameTile__
#define __LotteryDefense__GameTile__

#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

class GameTile
{
public:
    GameTile();
    ~GameTile();
    
    inline Unit *getUnit() { return _unit; }
    void setUnit(Unit *unit);
    
    inline CCPoint getPosition(){ return ccp(_x, _y); }
    void setPosition(const CCPoint &position);
    
    inline CCRect getFrame(){ return _frame; }
    void setFrame(const CCRect &frame);
    
    GameTile *up;
    GameTile *down;
    GameTile *left;
    GameTile *right;
    GameTile *upLeft;
    GameTile *upRight;
    GameTile *downLeft;
    GameTile *downRight;
    
protected:
    float _x;
    float _y;
    
    CCRect _frame;
    Unit *_unit;
};

#endif /* defined(__LotteryDefense__GameTile__) */

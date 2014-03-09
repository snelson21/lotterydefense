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
#include <vector>

USING_NS_CC;

using namespace std;

class GameTile : public CCObject
{
public:
    GameTile();
    ~GameTile();
    
    static GameTile *createWithPosition(const CCPoint &position);
    bool initWithPosition(const CCPoint &position);
    
    inline Unit *getUnit() { return _unit; }
    void setUnit(Unit *unit);
    
    inline CCPoint getPosition(){ return ccp(_x, _y); }
    void setPosition(const CCPoint &position);
    
    inline CCRect getFrame(){ return _frame; }
    void setFrame(const CCRect &frame);
    
    inline int getZIndex(){ return _zIndex; }
    inline void setZIndex(int zIndex){ _zIndex = zIndex; }
    
    GameTile *up;
    GameTile *down;
    GameTile *left;
    GameTile *right;
    GameTile *upLeft;
    GameTile *upRight;
    GameTile *downLeft;
    GameTile *downRight;
    
    vector<GameTile *> getNeighbors();
    
protected:
    float _x;
    float _y;
    int _zIndex;
    
    CCRect _frame;
    Unit *_unit;
};

#endif /* defined(__LotteryDefense__GameTile__) */

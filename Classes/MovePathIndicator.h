//
//  MovePathIndicator.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/26/14.
//
//

#ifndef __LotteryDefense__MovePathIndicator__
#define __LotteryDefense__MovePathIndicator__

#include "cocos2d.h"

USING_NS_CC;

class Unit;

class MovePathIndicator : public CCNode
{
    
public:
    MovePathIndicator();
    virtual ~MovePathIndicator();
    
    static MovePathIndicator *createWithUnit(Unit *unit);
    bool initWithUnit(Unit *unit);
    
    inline Unit *getUnit() { return _unit; }
    void setUnit(Unit *unit);
    
    inline CCPoint getStartPoint(){ return _startPoint; }
    inline void setStartPoint(const CCPoint &startPoint)
    {
        _startPoint = ccp(startPoint.x, startPoint.y);
    }
    
    inline CCPoint getEndPoint(){ return _endPoint; }
    void setEndPoint(const CCPoint &endPoint);
    
    
    virtual void draw(void);
    
protected:
    void precalculate();
    
    Unit *_unit;
    float _width;
    CCPoint _endPoint;
    CCPoint _startPoint;
    CCPoint _vertices[4];
};

#endif /* defined(__LotteryDefense__MovePathIndicator__) */

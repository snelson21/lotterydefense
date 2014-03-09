//
//  MovePathIndicator.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/26/14.
//
//

#include "MovePathIndicator.h"
#include "cocos2d.h"
#include "Unit.h"
#include "AppMacros.h"

USING_NS_CC;

MovePathIndicator::MovePathIndicator()
: _unit(NULL)
{
    _width = MOVE_PATH_WIDTH;
}
MovePathIndicator::~MovePathIndicator()
{
    CC_SAFE_RELEASE(_unit);
}

MovePathIndicator *MovePathIndicator::createWithUnit(Unit *unit)
{
    MovePathIndicator *movePathIndicator = new MovePathIndicator();
    if (movePathIndicator && movePathIndicator->initWithUnit(unit))
    {
        movePathIndicator->autorelease();
        return movePathIndicator;
    }
    CC_SAFE_DELETE(movePathIndicator);
    return NULL;
}

bool MovePathIndicator::initWithUnit(Unit *unit)
{
    setUnit(unit);
    return true;
}

void MovePathIndicator::setUnit(Unit *unit)
{
    CC_SAFE_RELEASE(_unit);
    _unit = unit;
    CC_SAFE_RETAIN(_unit);
    
    setStartPoint(_unit->getPosition());
    setEndPoint(_unit->getPosition());
}

void MovePathIndicator::setStartPoint(const CCPoint &startPoint)
{
    _startPoint = ccp(startPoint.x, startPoint.y);
    precalculate();
    
}

void MovePathIndicator::setEndPoint(const CCPoint &endPoint)
{
    _endPoint = ccp(endPoint.x, endPoint.y);
    precalculate();
}

void MovePathIndicator::precalculate()
{
    double halfThickness = _width / 2.0;
    
    double dx = _endPoint.x - _startPoint.x;
    double dy = _endPoint.y - _startPoint.y;
    
    if(dy == 0)
    {
        _vertices[0] = ccp(_startPoint.x, _startPoint.y - halfThickness);
        _vertices[1] = ccp(_startPoint.x, _startPoint.y + halfThickness);
        _vertices[2] = ccp(_endPoint.x, _endPoint.y - halfThickness);
        _vertices[3] = ccp(_endPoint.x, _endPoint.y + halfThickness);
        return;
    }
    
    double lambda = ( M_PI / 2.0 ) - atan( dx / dy );
    
    double xOffset = sin(lambda) * ( halfThickness );
    double yOffset = cos(lambda) * ( halfThickness );
    
    _vertices[0] = ccp(_startPoint.x + xOffset, _startPoint.y - yOffset);
    _vertices[1] = ccp(_endPoint.x + xOffset, _endPoint.y - yOffset);
    _vertices[2] = ccp(_endPoint.x - xOffset, _endPoint.y + yOffset);
    _vertices[3] = ccp(_startPoint.x - xOffset, _startPoint.y + yOffset);
}

void MovePathIndicator::draw(void)
{
    ccDrawSolidPoly(_vertices, 4, MOVE_PATH_COLOR);
}
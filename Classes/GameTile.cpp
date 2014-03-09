//
//  GameTile.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/24/14.
//
//

#include "GameTile.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include <vector>

USING_NS_CC;

using namespace std;

GameTile::GameTile()
: _unit(NULL)
, up(NULL)
, down(NULL)
, left(NULL)
, right(NULL)
, upLeft(NULL)
, upRight(NULL)
, downLeft(NULL)
, downRight(NULL)
{
    
}
GameTile::~GameTile()
{
    CC_SAFE_RELEASE(_unit);
}

GameTile *GameTile::createWithPosition(const CCPoint &position)
{
    GameTile *gameTile = new GameTile();
    if(gameTile && gameTile->initWithPosition(position))
    {
        gameTile->autorelease();
        return gameTile;
    }
    
    CC_SAFE_DELETE(gameTile);
    return NULL;
}
bool GameTile::initWithPosition(const CCPoint &position)
{
    setPosition(position);
    return true;
}

void GameTile::setPosition(const CCPoint &position)
{
    _x = position.x;
    _y = position.y;
    
    _frame = CCRectMake(_x - (TILE_HEIGHT / 2.0f), _y - (TILE_HEIGHT / 2.0f), TILE_HEIGHT, TILE_HEIGHT);
}

void GameTile::setFrame(const CCRect &frame)
{
    _frame = CCRectMake(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
    
    _x = frame.origin.x + (frame.size.width / 2.0f);
    _y = frame.origin.y + (frame.size.height / 2.0f);
}

void GameTile::setUnit(Unit *unit)
{
    CC_SAFE_RELEASE(_unit);
    _unit = unit;
    CC_SAFE_RETAIN(_unit);
}

vector<GameTile *>GameTile::getNeighbors()
{
    vector<GameTile *> neighbors;
    
    if(up) neighbors.push_back(up);
    if(down) neighbors.push_back(down);
    if(left) neighbors.push_back(left);
    if(right) neighbors.push_back(right);
    if(upLeft) neighbors.push_back(upLeft);
    if(upRight) neighbors.push_back(upRight);
    if(downLeft) neighbors.push_back(downLeft);
    if(downRight) neighbors.push_back(downRight);
    return neighbors;
}
//
//  PathFindTile.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 3/1/14.
//
//

#include "PathFindTile.h"
#include "cocos2d.h"
#include "GameTile.h"

USING_NS_CC;

PathFindTile::PathFindTile()
: _parent(NULL)
, _gameTile(NULL)
{
    
}

PathFindTile::~PathFindTile()
{
    CC_SAFE_RELEASE(_parent);
    CC_SAFE_RELEASE(_gameTile);
}

PathFindTile *PathFindTile::createWithGameTile(GameTile *gameTile)
{
    PathFindTile *pathFindTile = new PathFindTile();
    if(pathFindTile && pathFindTile->initWithGameTile(gameTile))
    {
        pathFindTile->autorelease();
        return pathFindTile;
    }
    
    CC_SAFE_DELETE(pathFindTile);
    return NULL;
}

bool PathFindTile::initWithGameTile(GameTile *gameTile)
{
    setGameTile(gameTile);
    return true;
}

void PathFindTile::setGameTile(GameTile *gameTile)
{
    CC_SAFE_RELEASE(_gameTile);
    _gameTile = gameTile;
    CC_SAFE_RETAIN(_gameTile);
}

void PathFindTile::setParent(PathFindTile *pathFindTile)
{
    CC_SAFE_RELEASE(_parent);
    _parent = pathFindTile;
    CC_SAFE_RETAIN(_parent);
}
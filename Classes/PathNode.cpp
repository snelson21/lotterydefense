//
//  PathNode.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 3/8/14.
//
//

#include "PathNode.h"
#include "cocos2d.h"
#include "PathFindTile.h"
#include "GameTile.h"

USING_NS_CC;

PathNode::PathNode()
: _next(NULL)
, _previous(NULL)
, _gameTile(NULL)
{
    
}

PathNode::~PathNode()
{
    CC_SAFE_RELEASE(_gameTile);
}

bool PathNode::initWithPathFindTile(PathFindTile *pathFindTile)
{
    CCAssert(pathFindTile != NULL, "Tried to initialize a PathNode with a NULL PathFindTile");
    CCAssert(pathFindTile->getGameTile() != NULL, "PathFindTile did not have a GameTile");
    
    setGameTile(pathFindTile->getGameTile());
    
    return true;
}

void PathNode::setGameTile(GameTile *gameTile)
{
    CC_SAFE_RELEASE(_gameTile);
    _gameTile = gameTile;
    CC_SAFE_RETAIN(_gameTile);
}

PathNode *PathNode::createWithPathFindTile(PathFindTile *pathFindTile)
{
    PathNode *pathNode = new PathNode();
    if(pathNode && pathNode->initWithPathFindTile(pathFindTile))
    {
        pathNode->autorelease();
        return pathNode;
    }
    CC_SAFE_DELETE(pathNode);
    return NULL;
}
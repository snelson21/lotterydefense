//
//  Pathfinder.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 3/1/14.
//
//

#include "Pathfinder.h"
#include "Map.h"
#include "cocos2d.h"
#include "GameTile.h"
#include "PathFindTile.h"
#include "PathFindTileMinHeap.h"
#include "Path.h"

USING_NS_CC;

Pathfinder::Pathfinder()
: _map(NULL)
, _endTile(NULL)
, _openList(NULL)
, _closedList(NULL)
{
   
}

Pathfinder::~Pathfinder()
{
    CC_SAFE_RELEASE(_openList);
    CC_SAFE_RELEASE(_closedList);
    CC_SAFE_RELEASE(_map);
    CC_SAFE_RELEASE(_endTile);
}

Pathfinder *Pathfinder::createWithMap(Map *map)
{
    Pathfinder *pathfinder = new Pathfinder();
    if(pathfinder && pathfinder->initWithMap(map))
    {
        pathfinder->autorelease();
        return pathfinder;
    }
    
    CC_SAFE_DELETE(pathfinder);
    return NULL;
}

bool Pathfinder::initWithMap(Map *map)
{
    CCAssert(map != NULL, "Cannot initialize a Pathfinder without a Map");
    
    setMap(map);
    
    _openList = PathFindTileMinHeap::create();
    CC_SAFE_RETAIN(_openList);
    
    _closedList = CCArray::create();
    CC_SAFE_RETAIN(_closedList);
    
    return true;
}

void Pathfinder::setMap(Map *map)
{
    CC_SAFE_RELEASE(_map);
    _map = map;
    CC_SAFE_RETAIN(_map);
}

void Pathfinder::setEndTile(GameTile *endTile)
{
    CC_SAFE_RELEASE(_endTile);
    _endTile = endTile;
    CC_SAFE_RETAIN(_endTile);
}

Path* Pathfinder::findPath(GameTile *startTile, GameTile *endTile)
{
    setEndTile(endTile);
    PathFindTile *tile = PathFindTile::createWithGameTile(startTile);
    
    addToOpenList(tile);
    
    
    PathFindTile *endPathFindTile = processNextTile();
    if(endPathFindTile)
    {
        CCLog("FOUND PATH");
        
        Path *path = Path::createFromLastChild(endPathFindTile);
        return path;
    }
    
    return NULL;
}

PathFindTile *Pathfinder::processNextTile()
{
    if(_openList->size() == 0)
    {
        CCLog("NO PATH!");
        return NULL;
    }
    
    PathFindTile *pathFindTile = _openList->pop();
    GameTile *gameTile = pathFindTile->getGameTile();
    
    _closedList->addObject(gameTile);
    
    if(gameTile == _endTile)
    {
        return pathFindTile;
    }
    
    vector<GameTile *> neighbors = gameTile->getNeighbors();
    for(int i = 0; i < neighbors.size(); i++)
    {
        
        PathFindTile *neighborPathFindTile;
        
        GameTile *neighbor = neighbors[i];
        if(_closedList->containsObject(neighbor))
        {
            continue;
        }
        if(neighbor->getUnit())
        {
            continue;
        }
        int neighborIndex = _openList->indexOfGameTile(neighbor);
        if(neighborIndex == -1)
        {
            neighborPathFindTile = PathFindTile::createWithGameTile(neighbor);
            neighborPathFindTile->setParent(pathFindTile);
            addToOpenList(neighborPathFindTile);
            continue;
        }
        
        neighborPathFindTile = _openList->pathFindTileForIndex(neighborIndex);
        float distanceFromGameTile = ccpDistance(gameTile->getPosition(), neighbor->getPosition());
        float newFromStartScore = distanceFromGameTile + pathFindTile->getFromStartScore();
        if(newFromStartScore < neighborPathFindTile->getFromStartScore())
        {
            neighborPathFindTile->setFromStartScore(newFromStartScore);
            neighborPathFindTile->setParent(pathFindTile);
            _openList->heapifyUp(neighborIndex);
        }
    }
    
    return processNextTile();
}

void Pathfinder::addToOpenList(PathFindTile *tile)
{
    if(tile->getParent() == NULL)
    {
        tile->setFromStartScore(0);
    }
    else
    {
        PathFindTile *parent = tile->getParent();
        float distanceFromParent = ccpDistance(tile->getGameTile()->getPosition(), parent->getGameTile()->getPosition());
        tile->setFromStartScore(parent->getFromStartScore() + distanceFromParent);
    }
    tile->setToEndScore(ccpDistance(tile->getGameTile()->getPosition(), _endTile->getPosition()));
    _openList->insert(tile);
}




//
//  Pathfinder.h
//  LotteryDefense
//
//  Created by Steele Nelson on 3/1/14.
//
//

#ifndef __LotteryDefense__Pathfinder__
#define __LotteryDefense__Pathfinder__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class Map;
class Path;
class GameTile;
class PathFindTile;
class PathFindTileMinHeap;

class Pathfinder : public CCObject
{
    
public:
    Pathfinder();
    ~Pathfinder();
    
    static Pathfinder *createWithMap(Map *map);
    
    bool initWithMap(Map *map);
    
    inline Map *getMap(){ return _map; }
    void setMap(Map *map);
    
    GameTile *adjustEndTile(GameTile *startTile, GameTile *endTile, CCArray *noPathList);
    
    Path *findPath(GameTile *startTile, GameTile *endTile);
    
    inline GameTile *getEndTile(){ return _endTile; }
    void setEndTile(GameTile *endTile);
    
    void addToOpenList(PathFindTile *tile);
    
    PathFindTile *processNextTile();
    
protected:
    Map *_map;
    GameTile *_endTile;
    PathFindTileMinHeap *_openList;
    CCArray *_closedList;
};

#endif /* defined(__LotteryDefense__Pathfinder__) */

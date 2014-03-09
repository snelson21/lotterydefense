//
//  PathNode.h
//  LotteryDefense
//
//  Created by Steele Nelson on 3/8/14.
//
//

#ifndef __LotteryDefense__PathNode__
#define __LotteryDefense__PathNode__

#include "cocos2d.h"

USING_NS_CC;

class PathFindTile;
class GameTile;

class PathNode : public CCObject
{
    
public:
    
    PathNode();
    ~PathNode();
    
    bool initWithPathFindTile(PathFindTile *pathFindTile);
    
    static PathNode *createWithPathFindTile(PathFindTile *pathFindTile);
    
    inline PathNode *next() { return _next; }
    inline void setNext(PathNode *next) { _next = next; }
    
    inline PathNode *previous() { return _previous; }
    inline void setPrevious(PathNode *previous) { _previous = previous; }
    
    inline GameTile *getGameTile() { return _gameTile; }
    void setGameTile(GameTile *gameTile);
    
protected:
    
    PathNode *_next;
    PathNode *_previous;
    GameTile *_gameTile;
    
};

#endif /* defined(__LotteryDefense__PathNode__) */

//
//  PathFindTile.h
//  LotteryDefense
//
//  Created by Steele Nelson on 3/1/14.
//
//

#ifndef __LotteryDefense__PathFindTile__
#define __LotteryDefense__PathFindTile__

#include "cocos2d.h"

USING_NS_CC;

class GameTile;

class PathFindTile : public CCObject
{
public:
    PathFindTile();
    virtual ~PathFindTile();
    
    static PathFindTile *createWithGameTile(GameTile *gameTile);
    
    bool initWithGameTile(GameTile *gameTile);
    
    inline float getFromStartScore(){ return _fromStartScore; }
    inline void setFromStartScore(float fromStartScore){ _fromStartScore = fromStartScore; }
    
    inline float getToEndScore(){ return _toEndScore; }
    inline void setToEndScore(float toEndScore) { _toEndScore = toEndScore; }
    
    inline float getFinalScore() { return _fromStartScore + _toEndScore; }
    
    inline PathFindTile *getParent() { return _parent; }
    void setParent(PathFindTile *parent);
    
    inline GameTile *getGameTile() { return _gameTile; }
    void setGameTile(GameTile *gameTile);
    
protected:
    PathFindTile *_parent;
    GameTile *_gameTile;
    float _fromStartScore;
    float _toEndScore;
};

#endif /* defined(__LotteryDefense__PathFindTile__) */

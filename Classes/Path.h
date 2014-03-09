//
//  Path.h
//  LotteryDefense
//
//  Created by Steele Nelson on 3/8/14.
//
//

#ifndef __LotteryDefense__Path__
#define __LotteryDefense__Path__

#include "cocos2d.h"

USING_NS_CC;

class PathFindTile;
class PathNode;

class Path : public CCObject
{
    
public:
    
    /**
     @brief  Path constructor
     */
    Path();
    
    /**
     @brief  Path destructor
     */
    virtual ~Path();
    
    /**
     @brief  Path initializer
     */
    bool initFromLastChild(PathFindTile *pathFindTile);
    
    /**
     @brief  Path autorelease object creator
     */
    static Path *createFromLastChild(PathFindTile *pathFindTile);
    
    /**
     @brief  Gets the Game Tile at the head of the linked list
     @return the PathFindTile at the head
     */
    inline PathNode *head(){ return _head; }
    
    /**
     @brief  Gets the tail of the linked list
     @return the PathFindTile at the tail
     */
    inline PathNode *tail(){ return _tail; }
    
    /**
     @brief  Push a PathNode on to the front of the list
     @param  PathNode to push
     */
    void pushToHead(PathNode *pathNode);
    
    /**
     @brief  Push a PathNode to the end of the list
     @param  PathNode to push
     */
    void pushToTail(PathNode *pathNode);
    
    /**
     @brief  Pop a PathNode from the front of the list
     @return PathNode popped
     */
    PathNode *popFromHead();
    
    /**
     @brief  Pop a PathNode from the end of the list
     @return PathNode popped
     */
    PathNode *popFromTail();
    
protected:
    
    /**
     @brief  the head of the linked list
     */
    PathNode *_head;
    
    /**
     @brief  the tail of the linked list
     */
    PathNode *_tail;
};

#endif /* defined(__LotteryDefense__Path__) */

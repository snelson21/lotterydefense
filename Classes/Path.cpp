//
//  Path.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 3/8/14.
//
//

#include "Path.h"
#include "cocos2d.h"
#include "PathFindTile.h"
#include "PathNode.h"

USING_NS_CC;

Path::Path()
: _head(NULL)
, _tail(NULL)
{
    
}
Path::~Path()
{
    while(popFromHead());
}

bool Path::initFromLastChild(PathFindTile *pathFindTile)
{
    CCAssert(pathFindTile != NULL, "Tried to initialize Path with Null last child.");
    
    pushToHead(PathNode::createWithPathFindTile(pathFindTile));
    
    PathFindTile *parent = pathFindTile->getParent();
    while(parent)
    {
        pushToHead(PathNode::createWithPathFindTile(parent));
        parent = parent->getParent();
    }
    return true;
}

Path *Path::createFromLastChild(PathFindTile *pathFindTile)
{
    Path *path = new Path();
    if(path && path->initFromLastChild(pathFindTile))
    {
        path->autorelease();
        return path;
    }
    
    CC_SAFE_DELETE(path);
    return NULL;
}

void Path::pushToHead(PathNode *pathNode)
{
    CCAssert(pathNode != NULL, "Tried to push a null pathnode to the head of the path");
    
    CC_SAFE_RETAIN(pathNode);
    if(_head == NULL)
    {
        _head = pathNode;
        _tail = pathNode;
        return;
    }
    
    PathNode *lastHead = _head;
    _head = pathNode;
    
    _head->setNext(lastHead);
    _head->setPrevious(NULL);
    lastHead->setPrevious(_head);
}

void Path::pushToTail(PathNode *pathNode)
{
    CCAssert(pathNode != NULL, "Tried to push a null path node to the tail of the path");
    
    CC_SAFE_RETAIN(pathNode);
    if(_tail == NULL)
    {
        _tail = pathNode;
        _head = pathNode;
        return;
    }
    
    PathNode *lastTail = _tail;
    _tail = pathNode;
    
    _tail->setPrevious(lastTail);
    _tail->setNext(NULL);
    lastTail->setNext(_tail);
}

PathNode *Path::popFromHead()
{
    if(_head == NULL)
    {
        return NULL;
    }
    
    PathNode *node = _head;
    
    PathNode *next = node->next();
    _head = next;
    
    if(_head)
    {
        _head->setPrevious(NULL);
    }
    
    CC_SAFE_RELEASE(node);
    
    return node;
}

PathNode *Path::popFromTail()
{
    if(_tail == NULL)
    {
        return NULL;
    }
    
    PathNode *node = _tail;
    
    PathNode *previous = node->previous();
    _tail = previous;
    
    if(_tail)
    {
        _tail->setNext(NULL);
    }
    
    CC_SAFE_RELEASE(node);
    
    return node;
    
}
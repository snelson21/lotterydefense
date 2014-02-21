#include "AppDelegate.h"
#include "GameScene.h"
#include "DesignResolution.h"
#include "AppMacros.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    initDesignResolution(pEGLView, pDirector);
    
    vector<string> searchPath = initContentScaleFactor(pEGLView, pDirector);
    
    // set searching path
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(FIXED_TIMESTEP);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::initDesignResolution(CCEGLView *pEGLView, CCDirector *pDirector)
{
    CCSize frameSize = pEGLView->getFrameSize();
    
    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
#endif
    
}

vector<string> AppDelegate::initContentScaleFactor(CCEGLView *pEGLView, CCDirector *pDirector)
{
    
    CCSize frameSize = pEGLView->getFrameSize();
    vector<string> searchPath;
    if (frameSize.height > ipadhdResource.size.height)
    {
        searchPath.push_back(hdResource.directory);
        
        pDirector->setContentScaleFactor(MIN(hdResource.size.height/designResolutionSize.height, hdResource.size.width/designResolutionSize.width));
    }
    else if (frameSize.height > ipadResource.size.height)
	{
        searchPath.push_back(ipadhdResource.directory);
        
        pDirector->setContentScaleFactor(MIN(ipadhdResource.size.height/designResolutionSize.height, ipadhdResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > iphonehdResource.size.height)
    {
        searchPath.push_back(ipadResource.directory);
        
        pDirector->setContentScaleFactor(MIN(ipadResource.size.height/designResolutionSize.height, ipadResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of
    else if (frameSize.height > iphonehdResource.size.height)
    {
        searchPath.push_back(iphonehdResource.directory);
        
        pDirector->setContentScaleFactor(MIN(iphonehdResource.size.height/designResolutionSize.height, iphonehdResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
        searchPath.push_back(iphoneResource.directory);
        
        pDirector->setContentScaleFactor(MIN(iphoneResource.size.height/designResolutionSize.height, iphoneResource.size.width/designResolutionSize.width));
    }
    
    return searchPath;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

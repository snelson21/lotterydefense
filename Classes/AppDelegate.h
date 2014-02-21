#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private CCApplication
{
    
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function to be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function to be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    
    /**
    @brief  The function called to initialize Design Resolution based on device type
    @param  pointer to the OpenGL View
    @param  pointer to the Director
    */
    void initDesignResolution(CCEGLView *pEGLView, CCDirector *pDirector);
    
    /**
    @brief  The function called to initialize the Content Scale Factor and return the appropriate search
            path based on the device resolution
    @param  pointer to the OpenGL View
    @param  pointer to the Director
    @return vector<string> the search paths for image files based on the device resolution
    */
    vector<string> initContentScaleFactor(CCEGLView *pEGLView, CCDirector *pDirector);
};

#endif // _APP_DELEGATE_H_


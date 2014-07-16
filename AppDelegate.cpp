#include "AppDelegate.h"
#include "cocos2d.h"
#include "RootScene.h"
#include "CommonDef.h"
#include "CCAPI.h"
#include "UIManager.h"
#include "RootLayer.h"
#include "NotificationManager.h"
#include "ResManager.h"
#include "UserData.h"
#include "BuffManager.h"


USING_NS_CC;

AppDelegate::AppDelegate(){

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCAPI::shareCCAPI()->init();
    
    UserData::shareUserData();
    
    ResManager::shareResManager()->init();
    BuffManager::share()->init();
    UIManager::shareInstance()->RegisterAllUILayer();
    
    Director *pDirector = Director::getInstance();
    
    Size appSize = CCAPI::shareCCAPI()->getAppSize();
    pDirector->getOpenGLView()->setDesignResolutionSize(appSize.width, appSize.height, ResolutionPolicy::SHOW_ALL);
    pDirector->setAnimationInterval(1.0 / 60);
    RootLayer* pRootLayer = RootLayer::shareRootLayer();
    RootScene *pRootcene = RootScene::create();
//    if(DEBUG_VERSION)
//    {
//        pRootcene->showMemoryLabel();
//        pDirector->setDisplayStats(true);
//    }
    Size homeSceneSize = pRootcene->getContentSize();
    pRootLayer->setAnchorPoint(Point(0.5,0.5));
    pRootLayer->setPosition(Point(homeSceneSize.width*0.5,homeSceneSize.height*0.5));
    pRootcene->addChild(pRootLayer);
    pDirector->runWithScene(pRootcene);
    
    Director::getInstance()->getScheduler()->scheduleUpdateForTarget(NotificationManager::shareInstance(), -1024, false);
    Director::getInstance()->getScheduler()->scheduleUpdateForTarget(UserData::shareUserData(), -1023, false);
    
    NotificationManager::shareInstance()->pushCMD(eGAME_CMD_ID_ShowHome); //eGAME_CMD_ID_ShowSelRole



    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

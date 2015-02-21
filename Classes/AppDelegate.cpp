#include "AppDelegate.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "NendInterstitialModule.h"
#include "NativeLauncher.h"
#include "AppCCloudPlugin.h"
#include "ADGConnectionForAndroid.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    //キキのキャラクターフラグ使用をオンに
    auto userDef = UserDefault::getInstance();
    userDef->setBoolForKey("characterFlag0", true);
    //キキをデフォルトの使用キャラクターに
    userDef->setIntegerForKey("selectCharacter", 0);
    
    
//nendインタースティシャル
    //本番
    char interstitialApiKey[] = "4d356c2beae29f2750413b21abda06698da45e8c";
    char interstitialSpotID[] = "311432";
    //テスト
//    char interstitialApiKey[] = "308c2499c75c4a192f03c02b2fcebd16dcb45cc9";
//    char interstitialSpotID[] = "213208";
    
    // appC cloud 開始
    // pDirector->setDisplayStats(true)の直後で一度だけ呼び出してください
    AppCCloudPlugin::setMK_iOS("e75ecf740e0f495496c853529830b08737f9d237").start();
    
    
    NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
    
    

    
//GameCenterへのログイン
    //NativeLauncher::loginGameCenter();

    
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
//  横画面ゲームは1136,640,ResolutionPolicy::SHOW_ALLは固定で良いと思われる。
//    glview -> setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
    glview -> setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);
    director->setContentScaleFactor(1.0f);


    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //デバッグのため GameSceneに飛ばしてます。
    //auto scene = GameScene::createScene();
    auto scene = TitleScene::createScene();

    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    ADGConnectionForAndroid::showADG();

    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

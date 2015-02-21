//
//  TutorialScene.cpp
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/20.
//
//

#include "TutorialScene.h"
#include "TitleScene.h"
#include <string.h>

cocos2d::Label *tutorial_text;

//画面サイズの取得および設定
#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;
using namespace CocosDenshion;


//画面生成
Scene *TutorialScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = TutorialScene::create();
    scene -> addChild(layer);
    
    return scene;
    
}

//初期画面作成
bool TutorialScene::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    //背景作成
    auto tutorialBg = Sprite::create("tutorialBg.png");
    tutorialBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this -> addChild(tutorialBg);
    
    //キキ作成
    auto tutorial_kiki = Sprite::create("kiki_up.png");
    tutorial_kiki -> setPosition(Vec2(selfFrame.width/3,selfFrame.height/3));
    tutorial_kiki -> setName("tutorial_kiki");
    tutorial_kiki -> setVisible(false);
    this -> addChild(tutorial_kiki);
    
    //指作成
    auto tutorial_hand = Sprite::create("tutorial_hand.png");
    tutorial_hand -> setPosition(Vec2(selfFrame.width*2/3,selfFrame.height/2));
    tutorial_hand -> setName("tutorial_hand");
    tutorial_hand -> setVisible(false);
    this -> addChild(tutorial_hand);
    
    //リング作成
    auto tutorial_tapHold = Sprite::create("tutorial_tapHold.png");
    tutorial_tapHold -> setPosition(Vec2(selfFrame.width*0.64,selfFrame.height*0.56));
    tutorial_tapHold -> setName("tutorial_tapHold");
    tutorial_tapHold -> setVisible(false);
    this -> addChild(tutorial_tapHold);
    
    //タップ時の効果リング作成
    auto tutorial_tapHoldEffect = Sprite::create("tutorial_tapHold.png");
    tutorial_tapHoldEffect -> setPosition(Vec2(tutorial_tapHold->getPosition().x,tutorial_tapHold->getPosition().y));
    tutorial_tapHoldEffect -> setName("tutorial_tapHoldEffect");
    tutorial_tapHoldEffect -> setVisible(false);
    this -> addChild(tutorial_tapHoldEffect);
    
    
    //説明文作成
    //説明文の変更
    LanguageType language = Application::getInstance()->getCurrentLanguage();
    if (language == LanguageType::JAPANESE) {
        tutorial_text = Label::createWithSystemFont("〜操作方法の説明〜\n※説明は自動で進行します。", "HiraKakuPro-W3", 25);
    }else{
        tutorial_text = Label::createWithSystemFont("〜We will show you how to play〜", "HiraKakuPro-W3", 25);
    }

    tutorial_text -> setTextColor(Color4B::BLACK);
    tutorial_text -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/4));
    tutorial_text -> setName("tutorial_text");
    this -> addChild(tutorial_text);
    
    //戻るボタン作成
    setBackBt();
    
    //最初のフェーズの準備
    setPhase();
    
    //ボタン効果音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button70.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);

    
    
    
    
    
    
    
    
        
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(TutorialScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(TutorialScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(TutorialScene::onTouchEnded,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    
    
    //MARK::nendの設定
    //ネンドの呼び出し(ヘッダー)
    /*char apiKey[] = "5aa579f521da85a055c5076641efc68202d5e8e2";
     char spotID[] = "262876";
     NendModule::createNADViewBottom(apiKey, spotID);
     
     //ネンドの呼び出し(飛び出す)
     char interstitialApiKey[] = "6b027f392e0cf11d378908fc4027f1755d6422ad";
     char interstitialSpotID[] = "266067";
     NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
     */
    
    
    
    return true;
    
    
}


#pragma mark-
#pragma mark touchBegan

bool TutorialScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
    return true;
    
}

#pragma mark-
#pragma mark touchMoved

void TutorialScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}


#pragma mark-
#pragma mark touchEnded

void TutorialScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}

void TutorialScene::setBackBt(){
    
    //戻るボタンの作成
    auto backBt = Sprite::create("backBt.png");
    auto backBtTaped = Sprite::create("backBt.png");
    backBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(backBt, backBtTaped, [](Ref *ref){
        
        //ボタン効果音再生
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, TitleScene::createScene(), 1));
    
    });
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを配置
    startMenu->setPosition(Vec2(selfFrame.width/2,100 + backBt->getContentSize().height/2));
    this->addChild(startMenu);

}

//フェーズ進行の準備
void TutorialScene::setPhase(){
    
    //キキ、指、最初の説明文の表示
    this -> getChildByName("tutorial_kiki") -> setVisible(true);
    this -> getChildByName("tutorial_hand") -> setVisible(true);
    this -> scheduleOnce(schedule_selector(TutorialScene::setPhase1), 5);
    
}

//フェーズ１(上昇の説明)
void TutorialScene::setPhase1(float time){
    
    //タップ時のリングとエフェクトを表示
    this -> getChildByName("tutorial_tapHold")->setVisible(true);
    this -> getChildByName("tutorial_tapHoldEffect")->setVisible(true);
    
    
    //キキの上昇
    this -> getChildByName("tutorial_kiki")->runAction(MoveTo::create(4, Vec2(this->getChildByName("tutorial_kiki")->getPosition().x,selfFrame.height*2/3)));
    
    
    //エフェクトリングに効果をつける
    auto scale = ScaleTo::create(1, 1.2);
    auto fadeTo = FadeTo::create(1, 0);
    auto scaleFade = Spawn::create(scale,fadeTo, NULL);
    
    auto reScale = ScaleTo::create(0, 1.0);
    auto reFadeTo = FadeTo::create(0, 250);
    auto reScaleFade = Spawn::create(reScale,reFadeTo, NULL);
    
    auto seq = Sequence::create(scaleFade,reScaleFade, NULL);
    
    auto repeat = RepeatForever::create(seq);
    
    this -> getChildByName("tutorial_tapHoldEffect")->runAction(repeat);
    
    
    //説明文の変更
    LanguageType language = Application::getInstance()->getCurrentLanguage();
    if (language == LanguageType::JAPANESE) {
        tutorial_text -> setString("画面をタップし続けると上昇します。");
    }else{
        tutorial_text -> setString("While you are touching a screen,\nshe goes up.");
    }
    
    //5秒後にフェーズ２に移行
    this->scheduleOnce(schedule_selector(TutorialScene::setPhase2), 5);

}

//フェーズ２(下降の説明)
void TutorialScene::setPhase2(float time){
    
    //タップ時のリングとエフェクトを非表示に
    this -> getChildByName("tutorial_tapHold")->setVisible(false);
    this -> getChildByName("tutorial_tapHoldEffect")->setVisible(false);

    
    //キキの下降
    this -> getChildByName("tutorial_kiki")->runAction(MoveTo::create(4, Vec2(this->getChildByName("tutorial_kiki")->getPosition().x,selfFrame.height*1/3)));
    
    
    //説明文の変更(多言語化)
    LanguageType language = Application::getInstance()->getCurrentLanguage();
    if(language == LanguageType::JAPANESE){
        tutorial_text -> setString("指を離すと下降します。");
    }else{
        tutorial_text -> setString("While you are not touching a screen,\nshe goes down.");
    }
    
    
    //フェーズ１に移行
    this -> scheduleOnce(schedule_selector(TutorialScene::setPhase1), 5);
    
    /***** ここからはフェーズ１→フェーズ２→フェーズ１･･･、の繰り返しになります。******/
    
}
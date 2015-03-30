#include "TitleScene.h"
#include "StorySelect.h"
#include "TutorialScene.h"
#include "GameScene.h"
#include <string.h>
#include "NativeLauncher.h"
#include "SelectCharacterScene.h"
#include "AppCCloudPlugin.h"
#include "ADGConnectionForAndroid.h"
#include "NendInterstitialModule.h"
#include <random>
//#include "NendModule.h"
//#include "NendInterstitialModule.h"
//#include "AppCCloudPlugin.h"



//画面サイズの取得および設定
#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;
using namespace CocosDenshion;

//保存先の生成
//UserDefault *userDef = UserDefault::getInstance();

//画面生成
Scene *TitleScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene -> addChild(layer);
    std::string tag = "cocos";
    std::string msg = "test";
    NativeLauncher::debugLog(tag.c_str(), msg.c_str());

    return scene;
    
}

//初期画面作成
bool TitleScene::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    
    auto titleBg = Sprite::create("titleBg.png");
    titleBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this -> addChild(titleBg);
    

    /*
    auto titleSignboard = Sprite::create("titleObject.png");
    titleSignboard -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*3/4));
    this -> addChild(titleSignboard);
    */
    setStartBt();
    setTutorialBt();
    setRankingBt();
    setCharacterBt();
    setTwitterBt();
    setOtherBt();
    
    //ボタン効果音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button70.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.4f);

   

    
    
    //BGMが鳴っているかチェック
    if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){

    
    }else{
        //鳴っていないときの処理
        //BGMの設定
        SimpleAudioEngine::getInstance()->preloadBackgroundMusic("title.mp3");
        //BGM音量設定
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
        //BGM再生
        SimpleAudioEngine::getInstance()->playBackgroundMusic("title.mp3",true);

    }
    
    
    //広告(appBank SSP) y座標をselfframe.height/2にしているが、理由は不明
    //テスト
    ADGConnectionForAndroid::initADG((char*)"10724" , (char*)"SP" , (char*)"CENTER" , (char*)"TOP");
    //本番
    //ADGConnectionForAndroid::initADG((char*)"20338 ", (char*)"SP", 0, selfFrame.height/2 + 50, NULL);
    //終
    

    
    //didsimulate
//    this->scheduleUpdate();
    
    //MARK::ゲームセンターログイン
    NativeLauncher::loginGameCenter();


    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(TitleScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded,this);
    
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

//MARK::AppCCloudの設定と削除
/*
void TitleScene::setAppCCloud(){
    
    appCCloudBt = Sprite::create("other.png");
    appCCloudBt -> setPosition(Vec2((selfFrame.width)-(appCCloudBt->getContentSize().width*2/3),(selfFrame.height)-(appCCloudBt->getContentSize().height*2/3)));
    this -> addChild(appCCloudBt);
    
    appFlag = true;

}

void TitleScene::removeAppCCloud(){
    
    appCCloudBt -> removeFromParent();
    
    appFlag = false;

}
*/

#pragma mark-
#pragma mark touchBegan

bool TitleScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);

    
    return true;
    
}

#pragma mark-
#pragma mark touchMoved

void TitleScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}


#pragma mark-
#pragma mark touchEnded

void TitleScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}

//MARK::ストーリーボタン
void TitleScene::setStartBt(){

    
    //ストーリーボタン作成
    auto startBt = Sprite::create("storyBt.png");
    
    auto startBtTaped = Sprite::create("storyBt.png");
    startBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(startBt, startBtTaped, [](Ref *ref){
        //ボタン効果音再生
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        Director::getInstance()->replaceScene(TransitionPageTurn::create(1, StorySelect::createScene(), 0));
        
    });
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを画面中央に配置
    startMenu->setPosition(Vec2(selfFrame.width/2+selfFrame.width/40, selfFrame.height*0.48));
    startMenu->setName("start");
    this->addChild(startMenu);
    
}

//MARK::チュートリアルボタン
void TitleScene::setTutorialBt(){
    
    //チュートリアル作成
    auto tutorialBt = Sprite::create("tutorialBt.png");
    
    auto tutorialBtTaped = Sprite::create("tutorialBt.png");
    tutorialBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(tutorialBt, tutorialBtTaped, [](Ref *ref){
        
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        //遊び方を呼び出すメソッド
        Director::getInstance()->replaceScene(TransitionPageTurn::create(1, TutorialScene::createScene(), 0));
        
        
    });
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto tutorialMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを画面中央に配置
    tutorialMenu->setPosition(Vec2(selfFrame.width*3/4+selfFrame.width/40, selfFrame.height*0.36));
    
    tutorialMenu->setName("tutorial");
    this->addChild(tutorialMenu);
    
}

//MARK::ランキングボタン
void TitleScene::setRankingBt(){
    
    
    // ランキングボタン作成
    auto rankingBt = Sprite::create("rankingBt.png");
    
    auto rankingBtTaped = Sprite::create("rankingBt.png");
    rankingBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(rankingBt, rankingBtTaped, [](Ref *ref){
        
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        //ランキング表示
        NativeLauncher::openRanking();
        
        
    });
    
    //メニューの作成
    auto rankingMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    rankingMenu->setPosition(Vec2(selfFrame.width/4+selfFrame.width/40, selfFrame.height*0.36));
    rankingMenu->setName("ranking");
    this->addChild(rankingMenu);
    
}

//MARK::その他のゲームボタン
void TitleScene::setOtherBt(){
    
    //その他のゲームボタン作成
    auto otherBt = Sprite::create("otherBt.png");
    
    auto otherBtTaped = Sprite::create("otherBt.png");
    otherBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(otherBt, otherBtTaped, [](Ref *ref){
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        //appCCloudのメソッド
        AppCCloudPlugin::Ad::openAdListView();
        
    });
    
    //メニューの作成
    auto otherMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    otherMenu->setPosition(Vec2(selfFrame.width/3+selfFrame.width/40, selfFrame.height*0.196));
    otherMenu->setName("other");
    this->addChild(otherMenu);
    
}

//MARK::キャラクター購入ボタン
void TitleScene::setCharacterBt(){
    
    
    //キャラクター購入ボタン作成
    auto characterBt = Sprite::create("characterBt.png");
    
    auto characterBtTaped = Sprite::create("characterBt.png");
    characterBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(characterBt, characterBtTaped, [&](Ref *ref){
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        Director::getInstance()->replaceScene(TransitionPageTurn::create(1, SelectCharacterScene::createScene(), 0));
    });
    
    
    //メニューの作成
    auto characterMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    characterMenu->setPosition(Vec2(selfFrame.width/2+selfFrame.width/40, selfFrame.height*0.32));
    characterMenu->setName("character");
    this->addChild(characterMenu);
    
}

//MARK::ツイッターボタン
void TitleScene::setTwitterBt(){
    
    
    //ツイッターボタン作成
    auto twitterBt = Sprite::create("twitterBt.png");
    
    auto twitterBtTaped = Sprite::create("twitterBt.png");
    twitterBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(twitterBt, twitterBtTaped, [](Ref *ref){
        
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        //呟き回数をカウント
        auto userDef = UserDefault::getInstance();
        userDef->setIntegerForKey("twitterCount",(userDef->getIntegerForKey("twitterCount") + 1));

        //ポイントの読込
        userDef = UserDefault::getInstance();
        auto totalPoint = userDef -> getIntegerForKey("playPoint");
        
        //言語の取得
        LanguageType lang = Application::getInstance()->getCurrentLanguage();
        
        std::string text;
        
        //日本語の場合は日本語の説明文を、それ以外は英語
        if(lang == LanguageType::JAPANESE){

        //テキスト作成
        text = StringUtils::format("現在のポイント：%d点\n【iPhoneアプリ】魔女ムズ\n#魔女ムズ",totalPoint);
        }else{
            text = StringUtils::format("TotalPoints：%dpt\n【iPhone apps】Witch's delivery\n#Witch's delivery",totalPoint);
            
        }
        
        NativeLauncher::openTweetDialog(text.c_str());

        
    });
    
    //メニューの作成
    auto twitterMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    twitterMenu->setPosition(Vec2(selfFrame.width*2/3+selfFrame.width/40, selfFrame.height*0.196));
    twitterMenu->setName("twitter");
    this->addChild(twitterMenu);
    
}



//トランジション終了時に呼ばれる
//initでアラートを呼ぶとなんか気持ちわるかったため
void TitleScene::onEnterTransitionDidFinish(){
    
    
    NendInterstitialModule::showNADInterstitialView();
    
    //デバッグ
    
    if (UserDefault::getInstance()->getBoolForKey("characterFlag1")==false) {
    
        int rnd = arc4random_uniform(2);
        
        if (rnd == 0) {
            
            this->setReviewBox();
            
        }
        
        return;
    }
    
    return;
}


//MARK::レビューボックス
void TitleScene::setReviewBox(){
    

//アラートの型枠を適当に生成
    
//OKの処理
    
    auto reviewBox = Sprite::create("alert.png");
    
    reviewBox->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    reviewBox->setName("reviewBox");
    
    //ボタンの作成
    //OKボタン作成
    auto okBt = Label::createWithSystemFont("OK!", "MagicSchoolOne",80);
    okBt -> setColor(Color3B::BLACK);
    
    auto okBtTaped = Label::createWithSystemFont("OK!", "MagicSchoolOne",80);
    okBtTaped -> setColor(Color3B::BLACK);
    okBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto okBtnItem = MenuItemSprite::create(okBt, okBtTaped, [&](Ref *ref){
        

        //ここでフラグを管理して特典の負荷を行う
        
        //レビューダイアログを消去
        this->removeChildByName("reviewBox");
        
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        
        //他のボタンを操作可能にする(冗長的)
        Menu* menu = (Menu*)this->getChildByName("start");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("tutorial");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("ranking");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("character");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("twitter");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("other");
        menu->setEnabled(true);

        
        
        //レビュー画面へ
        NativeLauncher::openReview();
        
        //小さいキキのフラグをオンにする
        UserDefault::getInstance()->setBoolForKey("characterFlag1", true);
        
    });
    
    //メニューの作成
    auto okMenu = Menu::create(okBtnItem, NULL);
    
    okMenu->setPosition(Vec2(reviewBox->getContentSize().width/5*1,reviewBox->getContentSize().height/6));
    
    reviewBox->addChild(okMenu);
    

//NGの処理
    //ボタンの作成
    //No作成
    auto ngBt = Label::createWithSystemFont("NO...", "MagicSchoolOne",80);
    ngBt -> setColor(Color3B::BLACK);
    
    auto ngBtTaped = Label::createWithSystemFont("NO...", "MagicSchoolOne",80);
    ngBtTaped -> setColor(Color3B::BLACK);
    ngBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto ngBtnItem = MenuItemSprite::create(ngBt, ngBtTaped, [&](Ref *ref){
        
        //ボタン効果音
        SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        
        //レビューダイアログを消去
        this->removeChildByName("reviewBox");
        
        //他のボタンを操作可能にする(冗長的)
        Menu* menu = (Menu*)this->getChildByName("start");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("tutorial");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("ranking");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("character");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("twitter");
        menu->setEnabled(true);
        menu = (Menu*)this->getChildByName("other");
        menu->setEnabled(true);

        
        
        
    });
    
    //メニューの作成
    auto ngMenu = Menu::create(ngBtnItem, NULL);
    
    ngMenu->setPosition(Vec2(reviewBox->getContentSize().width/5*4,reviewBox->getContentSize().height/6));
    
    reviewBox->addChild(ngMenu);
    
    this->addChild(reviewBox);
    
    //他のボタンを操作不可能にする(冗長的)
    Menu* menu = (Menu*)this->getChildByName("start");
    menu->setEnabled(false);
    menu = (Menu*)this->getChildByName("tutorial");
    menu->setEnabled(false);
    menu = (Menu*)this->getChildByName("ranking");
    menu->setEnabled(false);
    menu = (Menu*)this->getChildByName("character");
    menu->setEnabled(false);
    menu = (Menu*)this->getChildByName("twitter");
    menu->setEnabled(false);
    menu = (Menu*)this->getChildByName("other");
    menu->setEnabled(false);

//アラート本文

    //英語と日本語で分岐
    //見出しテキスト
    //説明文の変更(多言語化)
    LanguageType language = Application::getInstance()->getCurrentLanguage();
    
    std::string headlineText;
    
    if(language == LanguageType::JAPANESE){
         headlineText = "プレゼントのお知らせ";
    }else{
         headlineText = "News of the present";
    }
    
    //見出しラベル
    auto alertHeadLabel = Label::createWithSystemFont(headlineText, "Tanuki-Permanent-Marker", 40);
    alertHeadLabel -> enableOutline(Color4B::BLACK,2);
    alertHeadLabel -> setPosition(Vec2(reviewBox->getContentSize().width/2,reviewBox->getContentSize().height*7/8));
    alertHeadLabel -> setColor(Color3B::BLACK);
    reviewBox->addChild(alertHeadLabel);
    
    //中身テキスト
    std::string contentText;
    
    if(language == LanguageType::JAPANESE){
        contentText = "遊んでくれてありがとう。\nレビューを書いてくれた方に、\nキャラクター『ひよっこ魔女』\nをプレゼント！\n(☆５だととても嬉しいです...)";
    }else{
        contentText = "Thank you for playing.\nYou can get a new character\n      \"Younker witch\"      \nby reviewing this apps.\nWill you go to\n       the review page?";
    }
    
    //中身ラベル
    auto alertContentLabel = Label::createWithSystemFont(contentText, "Tanuki-Permanent-Marker", 30);
    
    alertContentLabel -> setPosition(Vec2(reviewBox->getContentSize().width/2,reviewBox->getContentSize().height/2+50));
    alertContentLabel -> setColor(Color3B::BLACK);
    reviewBox -> addChild(alertContentLabel);
    
}




#pragma mark-
#pragma mark:フレーム管理

void TitleScene::update( float frame )
{
    
}

int TitleScene::arc4random_uniform(int max){

//	std::mt19937 rand2(static_cast<unsigned int>(time(nullptr)));
//	std::uniform_int_distribution<int> dist(0, (max - 1));
//	return dist(rand2);
	return NativeLauncher::getRandom(max);
}

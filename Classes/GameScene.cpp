//
//  GameScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "GameScene.h"
#include "LoadScene.h"
#include "NendInterstitialModule.h"
#include "NativeLauncher.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()


Scene* GameScene::createScene()
{

    
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene -> addChild(layer);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // return the scene
    return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//ボタン効果音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button70.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button82.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button83.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);

    
//BGMプリロード
    switch (UserDefault::getInstance()->getIntegerForKey("selectStory")) {
        case 0:CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("stage1.mp3");break;
        case 1:CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("stage2.mp3");break;
        case 2:CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("stage3.mp3");break;
        case 3:CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("stage4.mp3");break;
        case 4:CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("stage5.mp3");break;
        default:break;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//背景処理
    //staticBackGroundの追加
    this -> addChild(BackGround::getInstance()->getStaticBackGround(),0);
    
    //backGroundの追加
    this -> addChild(BackGround::getInstance()->getBackGround1(),1);
    this -> addChild(BackGround::getInstance()->getBackGround2(),1);
    this -> addChild(BackGround::getInstance()->getBackGround3(),1);
//背景処理終
    
//キャラクター処理
    
    auto userDef = UserDefault::getInstance();

    selectCharacter = userDef->getIntegerForKey("selectCharacter");

    //分岐
    this->addChild(CharacterSwitch::getInstance()->getCharacter());
//キャラクター処理終
    
    auto startText = Label::createWithSystemFont("tap to start", "Arial", 50);
    startText -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    startText -> setVisible(true);
    startText -> setName("startText");
    
    startText -> runAction(RepeatForever::create(Blink::create(1, 1)));
    
    this -> addChild(startText);
    

//イベント系処理
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    
    /********************* 上下に壁を用意 ************************/
    //上の壁
    auto upperWall = Sprite::create();
    upperWall -> setTextureRect(Rect(0, 0, selfFrame.width, 2));
    upperWall -> setPosition(Vec2(selfFrame.width/2,selfFrame.height+upperWall->getContentSize().height/2));
    auto upperBody = PhysicsBody::createBox(Size(upperWall->getContentSize()));

    //重力による影響の可否
    upperBody -> setDynamic(false);
    upperBody -> setEnable(true);
    
    //ビットマスクはてきとう
    upperBody -> setCategoryBitmask(0x02);
    upperBody -> setCollisionBitmask(0);
    upperBody -> setContactTestBitmask(0x01);
    
    upperWall -> setPhysicsBody(upperBody);
    
    this -> addChild(upperWall);
    
    //下の壁
    auto lowerWall = Sprite::create();
    lowerWall -> setTextureRect(Rect(0, 0, selfFrame.width, 2));
    lowerWall -> setPosition(Vec2(selfFrame.width/2,-(lowerWall->getContentSize().height/2)));
    
    auto lowerBody = PhysicsBody::createBox(Size(upperWall->getContentSize()));
    
    //重力による影響の可否
    lowerBody -> setDynamic(false);
    lowerBody -> setEnable(true);
    
    //ビットマスクはてきとう
    lowerBody -> setCategoryBitmask(0x02);
    lowerBody -> setCollisionBitmask(0);
    lowerBody -> setContactTestBitmask(0x01);
    
    lowerWall -> setPhysicsBody(lowerBody);
    
    this -> addChild(lowerWall);
    /********************* 上下に壁を用意 終 ************************/

    
    /*************　  衝突イベント設定   ****************/
    
     auto contactListener = EventListenerPhysicsContact::create();
     contactListener -> onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);
     
     _eventDispatcher -> addEventListenerWithSceneGraphPriority(contactListener,this);
    
    /*************　  衝突イベント設定  終 ****************/

    
    this->scheduleUpdate();
    
//イベント系処理終
    
//プレイ回数を加算(解析用)
    auto str = StringUtils::format("playCountFor%d", userDef->getIntegerForKey("selectStory"));
    auto playCount = userDef->getIntegerForKey(str.c_str());
    playCount++;
    userDef->setIntegerForKey(str.c_str(), playCount);
    
    return true;
    
}



#pragma mark-
#pragma mark タッチ判定
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    if (CharacterSwitch::getInstance()->getGamePlayFlag() == false && CharacterSwitch::getInstance()->getGameOverFlag() == false) {
        
        CharacterSwitch::getInstance()->startCharacter();
        
        BackGround::getInstance()->startBackGround();
        
        this -> getChildByName("startText")->setVisible(false);
        this -> getChildByName("startText")->removeFromParent();
        
//MARK::BGM
        switch (UserDefault::getInstance()->getIntegerForKey("selectStory")) {
            case 0:CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("stage1.mp3",true);break;
            case 1:CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("stage2.mp3",true);break;
            case 2:CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("stage3.mp3",true);break;
            case 3:CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("stage4.mp3",true);break;
            case 4:CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("stage5.mp3",true);break;
            default:break;
        }
        
        
        
        
#pragma mark デバッグ用
        struct timeval time;
        gettimeofday(&time, NULL);
        startTime = time.tv_sec * 1000ull + time.tv_usec / 1000ull;
        
    }
    
    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
//キキ処理
    //キキのタップフラグをtrue
    CharacterSwitch::getInstance()->setTappedFlagOfCharacter(true);
//キキ処理終
    
    
    return true;
    
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    
    
    
    
    
    
    
    return;
    
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    

//キキ処理
    //キキのタップフラグをfalse
    CharacterSwitch::getInstance()->setTappedFlagOfCharacter(false);
//キキ処理終

    
    return;
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    
}


 #pragma mark-
 #pragma mark 衝突判定
 bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact){
     
     
     
     if (CharacterSwitch::getInstance()->getGamePlayFlag() == true && CharacterSwitch::getInstance()->getGameOverFlag() == false) {

     //ゲームオーバーの処理へ
     makeGameOver();
         
     }
     
 
 return true;
 
 }
 
#pragma mark-
#pragma mark フレーム管理

void GameScene::update( float frame )
{
    
//キキ処理
    //キキちゃんの1フレーム毎の処理
    CharacterSwitch::getInstance()->characterUpdate();
//キキ処理終

//背景処理
    //背景の1フレーム毎の処理(Layerが帰ってきたらaddchildする)
    BackGround::getInstance()->backGroundUpdate();
//背景処理終
    
//クリアか判定
    //30で全障害物設置完了
    //全障害物を通り抜けたらゲームクリア
    if(BackGround::getInstance()->getReplaceCount() > 30){
        //ゲームクリア
        this->makeGameClear();
    }
    
}

#pragma mark-
#pragma mark ゲームオーバーの処理
void GameScene::makeGameOver(){
    
    //nend表示
    NendInterstitialModule::showNADInterstitialView();
    
    
    //スケジュールの停止
    this->unscheduleUpdate();
    
    //BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //ゲームオーバー効果音
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button83.mp3");
    
    //キキちゃんのgameOver処理
    CharacterSwitch::getInstance()->makeGameOver();
    
    
    //背景の処理
    BackGround::getInstance()->stopBackGround();
    BackGround::getInstance()->makeGameOver();
    

    //gameOver画面の生成
    auto gameOverBg = Sprite::create("pause_gameBg.png");
    gameOverBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverBg -> setGlobalZOrder(0);
    gameOverBg -> setOpacity(255);
    this -> addChild(gameOverBg,2);

    
    //gameOverのlabel用スプライト
    auto gameOverOfLabel = Sprite::create();
    gameOverOfLabel -> setTextureRect(Rect( 0,0,selfFrame.width,selfFrame.height));
    gameOverOfLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverOfLabel -> setOpacity(0);
    gameOverOfLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    this -> addChild(gameOverOfLabel,3);
    
    //gameOver画面のparticle
    auto gameOverParticle = ParticleSystemQuad::create("particle_gameOver.plist");
    gameOverParticle -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    gameOverParticle -> setGlobalZOrder(0/*zOrderOfPause*/);
    gameOverBg -> addChild(gameOverParticle);
    
    
    //リトライボタン作成
    auto retryBt = Sprite::create("retryBt.png");
    retryBt -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto retryBtTaped = Sprite::create("retryBt.png");
    retryBtTaped -> setOpacity(150);
    retryBtTaped -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto retryBtnItem = MenuItemSprite::create(retryBt, retryBtTaped,[](Ref *ref){
        
        //ボタン効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
    
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("GameScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    retryBtnItem -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto retryMenu = Menu::create(retryBtnItem, NULL);
    
    retryMenu->setPosition(Vec2(selfFrame.width*3/4, selfFrame.height/3));
    retryMenu->setGlobalZOrder(zOrderOfPauseLabel);
    retryMenu->setColor(Color3B::BLACK);

    this ->addChild(retryMenu);
    
    
    //ホームボタン作成
    auto homeBt = Sprite::create("homeBt.png");
    homeBt -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto homeBtTaped = Sprite::create("homeBt.png");
    homeBtTaped -> setOpacity(150);
    homeBtTaped -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto homeBtnItem = MenuItemSprite::create(homeBt, homeBtTaped,[](Ref *ref){
        
        //ボタン効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("TitleScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    homeBtnItem -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto homeMenu = Menu::create(homeBtnItem, NULL);
    
    homeMenu->setPosition(Vec2(selfFrame.width/4, selfFrame.height/3));
    homeMenu->setGlobalZOrder(zOrderOfPauseLabel);
    homeMenu->setColor(Color3B::BLACK);
    this -> addChild(homeMenu);
    
    
    //「Game Over」ラベル作成
    auto gameOverLabel = Label::createWithSystemFont("Game Over", "MagicSchoolOne", 150);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    gameOverLabel -> setColor(Color3B::BLACK);
    gameOverOfLabel -> addChild(gameOverLabel);
    
    gameOverOfLabel -> setGlobalZOrder(300);
        
}

#pragma mark-
#pragma mark ゲームクリアの処理

void GameScene::makeGameClear(){
    
    //nend表示
    NendInterstitialModule::showNADInterstitialView();
    
    //スケジュールの停止
    this->unscheduleUpdate();
    
    //BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //クリア時効果音
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button82.mp3");
    
    //キキちゃんのgameOver処理
    CharacterSwitch::getInstance()->makeGameClear();
    
    
    //背景の処理
    BackGround::getInstance()->stopBackGround();
    BackGround::getInstance()->makeGameOver();
    
//ゲームクリア特有の処理
    //選択したステージとクリアステージを比べ、イコールの場合は次のステージを解放
    //ただし変数が4の場合は全ステージクリア済のため、何もしない
    auto userDef = UserDefault::getInstance();
    auto clearStory = userDef->getIntegerForKey("clearStory");
    auto selectStory = userDef->getIntegerForKey("selectStory");
    if (clearStory == selectStory && clearStory != 4) {
        clearStory++;
        //クリアステージの記憶変数に挿入
        userDef->setIntegerForKey("clearStory", clearStory);
    }
    
    //クリア回数に登録
    auto str = StringUtils::format("clearCountFor%d",selectStory);
    auto clearCount = userDef->getIntegerForKey(str.c_str());
    clearCount++;
    userDef->setIntegerForKey(str.c_str(), clearCount);
    
    
//クリアポイントの計算だ
    
    //ステージクリアの計算だ
    int stagePoint ;
    switch (selectStory) {
        case 0:stagePoint = 10;break;
        case 1:stagePoint = 20;break;
        case 2:stagePoint = 40;break;
        case 3:stagePoint = 60;break;
        case 4:stagePoint = 80;break;
        default:break;
    }
    
    //キャラクターに応じて計算だ
    int characterPoint;
    switch (userDef->getIntegerForKey("selectCharacter")) {
        case 0:characterPoint = 0;break;
        case 1:characterPoint = -10;break;
        case 2:characterPoint = 10;break;
        case 3:characterPoint = stagePoint * 3;break;
        case 4:characterPoint = stagePoint * 5;break;
        case 5:characterPoint = stagePoint * 10;break;
        default:break;
    }
    
    //ポイントに加算
    int playPoint = userDef->getIntegerForKey("playPoint");
    playPoint = playPoint + stagePoint + characterPoint;
    userDef->setIntegerForKey("playPoint",playPoint);
    
    
    //ゲームセンターにスコアを贈ろう
    NativeLauncher::postHighScore("WitchRacePointRanking", playPoint);
    
    
//終
    
    
    //gameClear画面の生成
    auto gameOverBg = Sprite::create("pause_gameClear.png");
    gameOverBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverBg -> setGlobalZOrder(0);
    gameOverBg -> setOpacity(255);
    this -> addChild(gameOverBg,2);
    
    
    //gameClearのlabel用スプライト
    auto gameOverOfLabel = Sprite::create();
    gameOverOfLabel -> setTextureRect(Rect( 0,0,selfFrame.width,selfFrame.height));
    gameOverOfLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverOfLabel -> setOpacity(0);
    gameOverOfLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    this -> addChild(gameOverOfLabel,3);
   
    //gameClear画面のparticle
    auto gameOverParticle = ParticleSystemQuad::create("particle_gameClear.plist");
    gameOverParticle -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    gameOverParticle -> setGlobalZOrder(0/*zOrderOfPause*/);
    gameOverOfLabel -> addChild(gameOverParticle,1);
    
//全ステージクリアの場合、今のところボタン生成の処理をスキップします
    if(selectStory != 4){
        //ネクストボタン作成
        auto nextBt = Sprite::create("nextBt.png");
        nextBt ->setGlobalZOrder(zOrderOfPauseLabel);
        
        auto nextBtTaped = Sprite::create("nextBt.png");
        nextBtTaped -> setOpacity(150);
        nextBtTaped ->setGlobalZOrder(zOrderOfPauseLabel);
        
        auto nextBtnItem = MenuItemSprite::create(nextBt, nextBtTaped,[](Ref *ref){
            
            //セレクトステージに1足し込み(次のステージへ)
            auto userDef = UserDefault::getInstance();
            auto selectStory = userDef->getIntegerForKey("selectStory");
            selectStory++;
            userDef->setIntegerForKey("selectStory", selectStory);
            
            //ボタン効果音再生
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
            
            Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("GameScene"));
            
            Director::getInstance()->replaceScene(nextScene);
            
        });
        nextBtnItem ->setGlobalZOrder(zOrderOfPauseLabel);
        
        auto nextMenu = Menu::create(nextBtnItem, NULL);
        
        nextMenu->setPosition(Vec2(selfFrame.width*3/4, selfFrame.height/3));
        nextMenu ->setGlobalZOrder(zOrderOfPauseLabel);
        nextMenu->setColor(Color3B(255, 255, 177));
        
        gameOverOfLabel->addChild(nextMenu,2);
        
    }
    
    
    //ホームボタン作成
    auto homeBt = Sprite::create("homeBt.png");
    
    auto homeBtTaped = Sprite::create("homeBt.png");
    homeBtTaped -> setOpacity(150);
    
    auto homeBtnItem = MenuItemSprite::create(homeBt, homeBtTaped,[](Ref *ref){
        
        //ボタン効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("TitleScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    auto homeMenu = Menu::create(homeBtnItem, NULL);
    
    homeMenu->setPosition(Vec2(selfFrame.width/4, selfFrame.height/3));
    homeMenu->setColor(Color3B(255, 255, 177));
    gameOverOfLabel->addChild(homeMenu,2);
    
    //リトライボタン作成
    auto retryBt = Sprite::create("retryBt.png");
    
    auto retryBtTaped = Sprite::create("retryBt.png");
    retryBtTaped -> setOpacity(150);
    
    auto retryBtnItem = MenuItemSprite::create(retryBt, retryBtTaped,[](Ref *ref){
        
        //ボタン効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
        
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("GameScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    auto retryMenu = Menu::create(retryBtnItem, NULL);
    
    retryMenu->setPosition(Vec2(selfFrame.width/2, selfFrame.height/4));
    retryMenu->setColor(Color3B(255, 255, 177));
    gameOverOfLabel->addChild(retryMenu,2);
    
    
    //「Game Clear」ラベル作成
    auto gameOverLabel = Label::createWithSystemFont("Game Clear", "MagicSchoolOne", 150);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    gameOverLabel -> setColor(Color3B(255, 255, 177));
    gameOverLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(gameOverLabel,3);

    

    //ステージポイントラベル
    std::string stageStr = StringUtils::format("%s","STAGE POINTS");
    auto stagePointLabel = Label::createWithSystemFont(stageStr.c_str(), "MagicSchoolOne", 35);
    stagePointLabel -> setPosition(Vec2(selfFrame.width/6,selfFrame.height/20*11));
    stagePointLabel -> setColor(Color3B(255, 255, 177));
    stagePointLabel -> setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    stagePointLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(stagePointLabel,5);
    
    //ステージポイント数値
    auto stageNumStr = StringUtils::format("%5d",stagePoint);
    auto stageNumLabel = Label::createWithSystemFont(stageNumStr.c_str(), "MagicSchoolOne", 35);
    stageNumLabel -> setPosition(Vec2(selfFrame.width - selfFrame.width /6,stagePointLabel->getPositionY()));
    stageNumLabel -> setColor(Color3B(255, 255, 177));
    stageNumLabel ->setAnchorPoint(Vec2(Vec2::ANCHOR_MIDDLE_RIGHT));
    stageNumLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(stageNumLabel,5);
    


    //キャラクターポイントラベル
    std::string characterStr = StringUtils::format("%s","CHARACTER POINTS");
    auto characterPointLabel = Label::createWithSystemFont(characterStr.c_str(), "MagicSchoolOne", 35);
    characterPointLabel -> setPosition(Vec2(stagePointLabel->getPositionX(),stagePointLabel->getPositionY() - characterPointLabel->getContentSize().height));
    characterPointLabel -> setColor(Color3B(255, 255, 177));
    characterPointLabel -> setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    characterPointLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(characterPointLabel,5);
    
    //キャラクターポイント数値
    auto characterNumStr = StringUtils::format("%5d",characterPoint);
    auto characterNumLabel = Label::createWithSystemFont(characterNumStr.c_str(), "MagicSchoolOne", 35);
    characterNumLabel -> setPosition(Vec2(stageNumLabel->getPositionX(),characterPointLabel->getPositionY()));
    characterNumLabel -> setColor(Color3B(255, 255, 177));
    characterNumLabel ->setAnchorPoint(Vec2(Vec2::ANCHOR_MIDDLE_RIGHT));

    characterNumLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(characterNumLabel,5);


    //ゲットポイントラベル
    std::string getStr = StringUtils::format("%s","GET POINTS");
    auto getPointLabel = Label::createWithSystemFont(getStr.c_str(), "MagicSchoolOne", 35);
    getPointLabel -> setPosition(Vec2(stagePointLabel->getPositionX(),characterPointLabel->getPositionY() - getPointLabel->getContentSize().height));
    getPointLabel -> setColor(Color3B(255, 255, 177));
    getPointLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    getPointLabel -> setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    gameOverOfLabel -> addChild(getPointLabel,5);
    
    //ゲットポイント数値
    auto getNumStr = StringUtils::format("%5d",stagePoint + characterPoint);
    auto getNumLabel = Label::createWithSystemFont(getNumStr.c_str(), "MagicSchoolOne", 35);
    getNumLabel -> setPosition(Vec2(stageNumLabel->getPositionX(),getPointLabel->getPositionY()));
    getNumLabel -> setColor(Color3B(255, 255, 177));
    getNumLabel ->setAnchorPoint(Vec2(Vec2::ANCHOR_MIDDLE_RIGHT));
    getNumLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(getNumLabel,5);


    //現在の総合ポイントラベル
    std::string totalStr = StringUtils::format("%s","TOTAL POINTS");
    auto totalPointLabel = Label::createWithSystemFont(totalStr.c_str(), "MagicSchoolOne", 35);
    totalPointLabel -> setPosition(Vec2(stagePointLabel->getPositionX(),getPointLabel->getPositionY() - getPointLabel->getContentSize().height));
    totalPointLabel -> setColor(Color3B(255, 255, 177));
    totalPointLabel -> setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    totalPointLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(totalPointLabel,5);
    
    //総合ポイント数値
    auto totalNumStr = StringUtils::format("%5d",userDef->getIntegerForKey("playPoint"));
    auto totalNumLabel = Label::createWithSystemFont(totalNumStr.c_str(), "MagicSchoolOne", 35);
    totalNumLabel -> setPosition(Vec2(stageNumLabel->getPositionX(),totalPointLabel->getPositionY()));
    totalNumLabel -> setColor(Color3B(255, 255, 177));
    totalNumLabel ->setAnchorPoint(Vec2(Vec2::ANCHOR_MIDDLE_RIGHT));
    totalNumLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(totalNumLabel,5);
    
    
}

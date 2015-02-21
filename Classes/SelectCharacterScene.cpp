//
//  SelectCharacterScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#include "SelectCharacterScene.h"
#include "TitleScene.h"
#include "NativeLauncher.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()


Scene* SelectCharacterScene::createScene()
{
    
    
    auto scene = Scene::createWithPhysics();
    auto layer = SelectCharacterScene::create();
    scene -> addChild(layer);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // return the scene
    return scene;
    
}

bool SelectCharacterScene::init()

{
    
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//言語設定
    //言語の取得
    LanguageType lang = Application::getInstance()->getCurrentLanguage();
    
    //日本語の場合は日本語の説明文を、それ以外は英語
    if(lang == LanguageType::JAPANESE){
        //キキ
        kikiExText = "飛ぶのが得意なおてんば少女\n夢に向かって修行中";
        //おまけキキ
        petitKikiExText = "飛ぶのが苦手なあなたに、まずは練習用\n\n～キャラクターボーナス～\n障害物にあたりにくくなる";
        //ハリーポッター
        haryyPotterExText = "僕は生き残る！\n\n～キャラクターボーナス～\nストーリクリアポイントに10ポイント加算";
        //ポニョ
        ponyoExText = "元気いっぱい！空もかけちゃお♪\n\n～キャラクターボーナス～\nストーリクリアポイント✕3ポイント加算";
        //空飛ぶ車
        fordAngliaExText = "オジサンからかりた車\n\n～キャラクターボーナス～\nストーリークリアポイント✕5ポイント加算";
        //ポルコ・ロッソ
        porcoRossoExText = "自由気ままに生きる、それが男！\n\n～キャラクターボーナス～\nストーリークリアポイント✕10ポイント加算";
    }else{
        //キキ
        kikiExText = "A tomboy witch,training herself for her dream.";
        //おまけキキ
        petitKikiExText = "A witch for practice\n～Character bonus～\nIt becomes easy to avoid obstacles";
        //ハリーポッター
        haryyPotterExText = "I'll come back alive！\n～Character bonus～\nYou get 10pt when you get at stages end";
        //ポニョ
        ponyoExText = "She is quite energetic and flies high up in the sky\n～Character bonus～\nYou get three times as many points as \npoints you get at stage end";
        //空飛ぶ車
        fordAngliaExText = "A car my friend's father lent\n～Character bonus～\nYou get five times as many points as \npoints when you get at stage end";
        //ポルコ・ロッソ
        porcoRossoExText = "He is called a man among men！\n～Character bonus～\nYou get ten times as many points as \npoints when you get at stage end";
    }
//言語設定終

    
    //ボタン効果音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button70.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);

    
//型枠の作成
    auto bg = Sprite::create("character_bg.png");
    
    bg->setName("bg");
    bg->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this->addChild(bg);
    
//タイトル・獲得ポイント表示
    //タイトル作成
    //auto titleLabel = Label::createWithSystemFont("select character", "MagicSchoolOne", 120);
    auto titleLabel = Label::createWithSystemFont("select character", "MagicSchoolOne", 120);
    titleLabel -> setColor(Color3B::BLACK);
    titleLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*10/11));
    this -> addChild(titleLabel,10);
    
    
    //userDefから獲得ポイント呼び出し準備
    auto userDef = UserDefault::getInstance();

    //userDef->setIntegerForKey("playPoint", 30000);
    
    std::string totalStr = StringUtils::format("point : %d",userDef -> getIntegerForKey("playPoint"));
    
    //ポイントラベル作成
    auto pointLabel = Label::createWithSystemFont(totalStr, "MagicSchoolOne", 60);
    pointLabel -> setColor(Color3B::BLACK);
    pointLabel -> setName("pointLabel");
    pointLabel -> setPosition(Vec2(selfFrame.width/2,titleLabel->getPosition().y-pointLabel->getContentSize().height*9/10));
    this -> addChild(pointLabel,10);
    
//説明文の枠作成
    
    //対象の説明テキスト用意
    charaExLabel = Label::createWithSystemFont("", "HiraKakuPro-W3", 25);
    charaExLabel -> setAlignment(TextHAlignment::CENTER);
    charaExLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/3.2));
    charaExLabel -> setColor(Color3B::BLACK);
    this -> addChild(charaExLabel);
    
//ボタンの作成(for文で回す？？)

    //ユーザーデフォルトを呼び出してキャラクターフラグを確認
    /*
     userDef->setBoolForKey("characterFlag1", true);
     userDef->setBoolForKey("characterFlag2", true);
     userDef->setBoolForKey("characterFlag3", true);
     userDef->setBoolForKey("characterFlag4", true);
     userDef->setBoolForKey("characterFlag5", true);
    */


    for(int idx = 0; idx < 6;idx++){
        

        
        auto characterFlag = userDef->getBoolForKey(StringUtils::format("characterFlag%d",idx).c_str());


        //スプライトの呼び出し
        Sprite *character;

//スプライトの呼び出し
        if(characterFlag == true){
            //キャラクターの画像に
            switch (idx) {
                case 0:character = Sprite::create("character_kiki.png");break;
                case 1:character = Sprite::create("character_petitKiki.png");break;
                case 2:character = Sprite::create("character_harryPotter.png");break;
                case 3:character = Sprite::create("character_ponyo.png");break;
                case 4:character = Sprite::create("character_fordAnglia.png");break;
                case 5:character = Sprite::create("character_porcoRosso.png");break;
                default:break;
            }
            
            //タップ後のボタンの透明度を変更する
            character->setOpacity(128);
            
        }else{
            //はてなの画像を呼び出し
            switch (idx) {
                case 0:character = Sprite::create("character_kiki.png");break;
                case 1:character = Sprite::create("character_petitKiki_locked.png");break;
                case 2:character = Sprite::create("character_harryPotter_locked.png");break;
                case 3:character = Sprite::create("character_ponyo_locked.png");break;
                case 4:character = Sprite::create("character_fordAnglia_locked.png");break;
                case 5:character = Sprite::create("character_porcoRosso_locked.png");break;
                default:break;
            }
            
            int charaPoint;
            
            switch (idx) {
                case 0:break;
                case 1:charaPoint = 0;break;
                case 2:charaPoint = 200;break;
                case 3:charaPoint = 500;break;
                case 4:charaPoint = 3000;break;
                case 5:charaPoint = 10000;break;
                default:break;
            }
            
            if (userDef -> getIntegerForKey("playPoint") >= charaPoint) {
                character ->setOpacity(255);
            
            }else{
                
                character->setOpacity(128);
                
            }
        }
        
        //後で一括して透明度変更する際に配列つかうことにしました
        characters->pushBack(character);
        
//タップ後のスプライトの呼び出し
        
        Sprite *tappedCharacter;
        
        //スプライトの呼び出し
        if(characterFlag == true){
            //キャラクターの画像に
            switch (idx) {
                case 0:tappedCharacter = Sprite::create("character_kiki.png");break;
                case 1:tappedCharacter = Sprite::create("character_petitKiki.png"); break;
                case 2:tappedCharacter = Sprite::create("character_harryPotter.png"); break;
                case 3:tappedCharacter = Sprite::create("character_ponyo.png"); break;
                case 4:tappedCharacter = Sprite::create("character_fordAnglia.png"); break;
                case 5:tappedCharacter = Sprite::create("character_porcoRosso.png"); break;
                default:break;
            }

            //タップ後のボタンの透明度を変更する
            tappedCharacter->setOpacity(255);

        }else{
            //はてなの画像を呼び出し
            switch (idx) {
                case 0:tappedCharacter = Sprite::create("character_kiki.png");break;
                case 1:tappedCharacter = Sprite::create("character_petitKiki_locked.png");break;
                case 2:tappedCharacter = Sprite::create("character_harryPotter_locked.png");break;
                case 3:tappedCharacter = Sprite::create("character_ponyo_locked.png");break;
                case 4:tappedCharacter = Sprite::create("character_fordAnglia_locked.png");break;
                case 5:tappedCharacter = Sprite::create("character_porcoRosso_locked.png");break;
                default:break;
            }
            //タップ後のボタンの透明度を変更する
            tappedCharacter->setOpacity(128);
        }

        
//メニューボタンを作成していく
        MenuItemSprite *pBtnItem;
        
        //キャラクターが解放されている時の動作
        if(characterFlag == true){
        //メニューアイテムの作成
            pBtnItem = MenuItemSprite::create(character, tappedCharacter, [&](Ref *ref){
            
                /**
                 *  pSenderをMenuItemにキャスト
                 *  なお、中身はpBtnItem
                 */
                MenuItem* button = (MenuItem*)ref;

                
                characters->at(userDef->getIntegerForKey("selectCharacter"))->setOpacity(128);
                
                //ボタン効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
                
                //フラグの設定
                userDef->setIntegerForKey("selectCharacter",button->getTag());
                CCLOG("%d",button->getTag());
                
                //透明度を一括変更
                /*for(auto character : *characters){
                    
                    character->setOpacity(128);
                    
                }*/
                
                //対象のボタンの透明度を変更
                characters->at(button->getTag())->setOpacity(255);
                
                //対象の説明テキストをセット
                switch (userDef -> getIntegerForKey("selectCharacter")) {
                    case 0:charaExLabel->setString(kikiExText);break;
                    case 1:charaExLabel->setString(petitKikiExText);break;
                    case 2:charaExLabel->setString(haryyPotterExText);break;
                    case 3:charaExLabel->setString(ponyoExText);break;
                    case 4:charaExLabel->setString(fordAngliaExText);break;
                    case 5:charaExLabel->setString(porcoRossoExText);break;
                    default:break;
                }
            
            });
        
        }else{
            
            pBtnItem = MenuItemSprite::create(character, tappedCharacter,[&](Ref *ref){
                
                MenuItem* button = (MenuItem*)ref;
                
                CCLOG("%d",button->getTag());
                
                switch (button->getTag()) {
                    case 0:break;
                    
                    case 1:
                        //レビューに飛ばす
                        userDef->setBoolForKey("characterFlag1", true);
                        userDef -> setIntegerForKey("selectCharacter",button->getTag());
                        this->removeAllChildrenWithCleanup(true);
                        characters->clear();
                        init();
                        
                        NativeLauncher::openReview();
                        
                        //ボタン効果音再生
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");




                        
                        break;
                        
                    case 2:
                        if (userDef->getIntegerForKey("playPoint")>=200) {
                        
                            //フラグをオンにする
                            userDef->setBoolForKey("characterFlag2", true);
                        
                        
                        userDef -> setIntegerForKey("playPoint", userDef->getIntegerForKey("playPoint")-200);
                        userDef -> setIntegerForKey("selectCharacter",button->getTag());
                            
                            //ボタン効果音再生
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");

                        
                        this->removeAllChildrenWithCleanup(true);
                            
                            characters->clear();
                        
                        init();
                            
                        }
                        break;
                    case 3:
                        if (userDef->getIntegerForKey("playPoint")>=500) {
                            
                            //フラグをオンにする
                            userDef->setBoolForKey("characterFlag3", true);
                            
                            
                            userDef -> setIntegerForKey("playPoint", userDef->getIntegerForKey("playPoint")-500);
                            userDef -> setIntegerForKey("selectCharacter",button->getTag());
                            
                            //ボタン効果音再生
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
                            
                            
                            this->removeAllChildrenWithCleanup(true);
                            
                            characters->clear();
                            
                            init();
                            
                        }
                        break;
                    case 4:
                        if (userDef->getIntegerForKey("playPoint")>=3000) {
                            
                            //フラグをオンにする
                            userDef->setBoolForKey("characterFlag4", true);
                            
                            
                            userDef -> setIntegerForKey("playPoint", userDef->getIntegerForKey("playPoint")-3000);
                            userDef -> setIntegerForKey("selectCharacter",button->getTag());
                            
                            //ボタン効果音再生
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
                            
                            
                            this->removeAllChildrenWithCleanup(true);
                            
                            characters->clear();
                            
                            init();
                            
                        }
                        break;
                    case 5:
                        if (userDef->getIntegerForKey("playPoint")>=10000) {
                            
                            //フラグをオンにする
                            userDef->setBoolForKey("characterFlag5", true);
                            
                            
                            userDef -> setIntegerForKey("playPoint", userDef->getIntegerForKey("playPoint")-10000);
                            userDef -> setIntegerForKey("selectCharacter",button->getTag());
                            
                            //ボタン効果音再生
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
                            
                            
                            this->removeAllChildrenWithCleanup(true);
                            characters->clear();
                            
                            init();
                            
                        }
                        break;
                        
                    default:
                        break;
                }
                
                
                
            });
            
        }
        
        pBtnItem->setTag(idx);
        
        //メニューの作成　pMenuの中にpBtnItemを入れる
        auto Menu = Menu::create(pBtnItem, NULL);

        //ポジションを設定
        switch (idx) {
            case 0:Menu->setPosition(Vec2(selfFrame.width/10*2,selfFrame.height*7/10));break;
            case 1:Menu->setPosition(Vec2(selfFrame.width/10*5,selfFrame.height*7/10));break;
            case 2:Menu->setPosition(Vec2(selfFrame.width/10*8,selfFrame.height*7/10));break;
            case 3:Menu->setPosition(Vec2(selfFrame.width/10*2,selfFrame.height*0.52));break;
            case 4:Menu->setPosition(Vec2(selfFrame.width/10*5,selfFrame.height*0.52));break;
            case 5:Menu->setPosition(Vec2(selfFrame.width/10*8,selfFrame.height*0.52));break;

            default:break;
        }
        
        bg->addChild(Menu);
        
        
        //キャラクターの価格および名前
        auto priceAndCharaLabel = Label::createWithSystemFont("", "MagicSchoolOne", 25);
        priceAndCharaLabel -> setColor(Color3B::BLACK);
        
        
        //キャラネームと価格
        if (characterFlag == true) {

            
            std::string name;
            //言語による分岐
            if(lang == LanguageType::JAPANESE){
                switch (idx) {
                    case 0: name = "見習い魔女";break;
                    case 1: name = "ひよっこ魔女";break;
                    case 2: name = "☇魔法使い☇";break;
                    case 3: name = "まっかの女の子";break;
                    case 4: name = "空飛ぶ車";break;
                    case 5: name = "元ｴｰｽ･ﾊﾟｲﾛｯﾄ";break;
                    default:break;
                }
            }
            else{
                switch (idx) {
                    case 0: name = "New witch";priceAndCharaLabel -> setSystemFontSize(40);break;
                    case 1: name = "Younker witch";priceAndCharaLabel -> setSystemFontSize(40);break;
                    case 2: name = "☇Wizard☇";priceAndCharaLabel -> setSystemFontSize(40);break;
                    case 3: name = "Red hair girl";priceAndCharaLabel -> setSystemFontSize(40);break;
                    case 4: name = "Skycar";priceAndCharaLabel -> setSystemFontSize(40);break;
                    case 5: name = "Ex-serviceman";priceAndCharaLabel -> setSystemFontSize(40);break;
                    default:break;
                }
            }

            priceAndCharaLabel -> setString(name);
            if(lang == LanguageType::JAPANESE){
                priceAndCharaLabel -> setSystemFontName("HiraKakuPro-W3");
            }
            
        }else{
            
            switch (idx) {
                case 0:
                    if(lang == LanguageType::JAPANESE){
                        priceAndCharaLabel -> setString("見習い魔女");
                        priceAndCharaLabel -> setSystemFontName("HiraKakuPro-W3");
                    }else{
                        priceAndCharaLabel -> setString("New witch");
                        priceAndCharaLabel -> setSystemFontSize(40);

                    }
                    break;
                case 1:
                    if(lang == LanguageType::JAPANESE){
                        priceAndCharaLabel -> setSystemFontName("HiraKakuPro-W3");
                        priceAndCharaLabel -> setString("レビューでゲット!");
                        priceAndCharaLabel -> setSystemFontSize(20);

                    }else{
                        priceAndCharaLabel -> setString("Get by reviews!");
                        priceAndCharaLabel -> setSystemFontSize(40);

                    }

                    priceAndCharaLabel -> setColor(Color3B::RED);
                    break;
                case 2:
                    priceAndCharaLabel -> setSystemFontName("MagicSchoolOne");
                    priceAndCharaLabel -> setString("200PT");
                    priceAndCharaLabel -> setSystemFontSize(40);
                    break;
                case 3:
                    priceAndCharaLabel -> setSystemFontName("MagicSchoolOne");
                    priceAndCharaLabel -> setString("500PT");
                    priceAndCharaLabel -> setSystemFontSize(40);
                    break;
                case 4:
                    priceAndCharaLabel -> setSystemFontName("MagicSchoolOne");
                    priceAndCharaLabel -> setString("3000Pt");
                    priceAndCharaLabel -> setSystemFontSize(40);
                    break;
                case 5:
                    priceAndCharaLabel -> setSystemFontName("MagicSchoolOne");
                    priceAndCharaLabel -> setString("10000Pt");
                    priceAndCharaLabel -> setSystemFontSize(40);
                    break;
                default:break;
            }
        
        }
        
        //キャラネームおよび価格のポジション
        switch (idx) {
            case 0:priceAndCharaLabel -> setPosition(Vec2(selfFrame.width/10*2,selfFrame.height*0.62));break;
            case 1:priceAndCharaLabel -> setPosition(Vec2(selfFrame.width/10*5,selfFrame.height*0.62));
                break;
            case 2:priceAndCharaLabel -> setPosition(Vec2(selfFrame.width/10*8,selfFrame.height*0.62));
                break;
            case 3:priceAndCharaLabel -> setPosition(Vec2(selfFrame.width/10*2,selfFrame.height*0.435));
                break;
            case 4:priceAndCharaLabel -> setPosition(Vec2(selfFrame.width/10*5,selfFrame.height*0.435));
                break;
            case 5:priceAndCharaLabel -> setPosition(Vec2(selfFrame.width/10*8,selfFrame.height*0.435));
                break;
            default:break;
        }
        
        this -> addChild(priceAndCharaLabel);
        
    }
    //ループ文終了
    

    //選択しているキャラのアイコンを黒に(初期位置設定)
    characters->at(userDef->getIntegerForKey("selectCharacter"))->setOpacity(255);
    
    switch (userDef->getIntegerForKey("selectCharacter")){
        case 0:charaExLabel->setString(kikiExText);break;
        case 1:charaExLabel->setString(petitKikiExText);break;
        case 2:charaExLabel->setString(haryyPotterExText);break;
        case 3:charaExLabel->setString(ponyoExText);break;
        case 4:charaExLabel->setString(fordAngliaExText);break;
        case 5:charaExLabel->setString(porcoRossoExText);break;
        default:break;
            
    }

    
    
    
    this->setBackBt();
    
    

    
    
    
    return true;
    
}


void SelectCharacterScene::setBackBt(){
    
    //戻るボタンの作成
    auto backBt = Sprite::create("backBt.png");
    auto backBtTaped = Sprite::create("backBt.png");
    backBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(backBt, backBtTaped, CC_CALLBACK_1(SelectCharacterScene::backBtCallBack, this));
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを配置
    startMenu->setPosition(Vec2(selfFrame.width/20*15,selfFrame.height/20*3));
    
    this->getChildByName("bg")->addChild(startMenu);
    
}

void SelectCharacterScene::backBtCallBack(cocos2d::Ref *pSender){
    
    //ボタン効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button70.mp3");
    
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, TitleScene::createScene(), 1));
    
}
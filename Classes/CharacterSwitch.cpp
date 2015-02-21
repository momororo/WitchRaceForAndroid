//
//  CharacterSwitch.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#include "CharacterSwitch.h"
#include "Kiki.h"
#include "PetitKiki.h"
#include "HarryPotter.h"
#include "FordAnglia.h"
#include "Ponyo.h"
#include "PorcoRosso.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
CharacterSwitch* CharacterSwitch::characterInstance = NULL;

//シングルトン
CharacterSwitch* CharacterSwitch::getInstance(){
    
    if(!characterInstance){
        
        
        characterInstance = new CharacterSwitch();
    }
    
    
    return characterInstance;
    
}
//デストラクタ
void CharacterSwitch::destroyInstance() {
    
    
    //キャラクターのフラグを設定
    auto userDef = UserDefault::getInstance();
    auto destroyFlag = userDef->getIntegerForKey("selectCharacter");

    
    //分岐
    switch (destroyFlag) {
        case 0:Kiki::getInstance()->destroyInstance();break;
        case 1:PetitKiki::getInstance()->destroyInstance();break;
        case 2:HarryPotter::getInstance()->destroyInstance();break;
        case 3:Ponyo::getInstance()->destroyInstance();break;
        case 4:FordAnglia::getInstance()->destroyInstance();break;
        case 5:PorcoRosso::getInstance()->destroyInstance();break;

        default: break;
    }
    
    
    if (characterInstance != NULL){
        delete characterInstance;
        
        characterInstance = NULL;
    }
    
    
}


//キキちゃんのスプライトをGET
Sprite* CharacterSwitch::getCharacter(){

    
    //分岐
    switch (characterFlag) {
        case 0:return Kiki::getInstance()->getCharacter();break;
        case 1:return PetitKiki::getInstance()->getCharacter();break;
        case 2:return HarryPotter::getInstance()->getCharacter();break;
        case 3:return Ponyo::getInstance()->getCharacter();break;
        case 4:return FordAnglia::getInstance()->getCharacter();break;
        case 5:return PorcoRosso::getInstance()->getCharacter();break;

        default: break;
    }
    
    
    return NULL;
    

}




//キキちゃんのタップ状態の変更
void CharacterSwitch::setTappedFlagOfCharacter(bool flag){
    tappedFlag = flag;
    return;
}

//キキちゃんの動作開始
void CharacterSwitch::startCharacter(){
    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->startCharacter();break;
        case 1:PetitKiki::getInstance()->startCharacter();break;
        case 2:HarryPotter::getInstance()->startCharacter();break;
        case 3:Ponyo::getInstance()->startCharacter();break;
        case 4:FordAnglia::getInstance()->startCharacter();break;
        case 5:PorcoRosso::getInstance()->startCharacter();break;

        default: break;
    }
    
    gamePlayFlag = true;


    
}

//キキちゃんの動作停止
void CharacterSwitch::stopCharacter(){
    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->stopCharacter();break;
        case 1:PetitKiki::getInstance()->stopCharacter();break;
        case 2:HarryPotter::getInstance()->stopCharacter();break;
        case 3:Ponyo::getInstance()->stopCharacter();break;
        case 4:FordAnglia::getInstance()->stopCharacter();break;
        case 5:PorcoRosso::getInstance()->stopCharacter();break;

        default: break;
    }
    
    gamePlayFlag = false;
    
    
}

bool CharacterSwitch::getGamePlayFlag(){
    
    return gamePlayFlag;
    
}

bool CharacterSwitch::getGameOverFlag(){
    
    return gameOverFlag;
}



//キキちゃんの初期設定
CharacterSwitch::CharacterSwitch(){
    

    //キャラクターのフラグを設定
    auto userDef = UserDefault::getInstance();
    characterFlag = userDef->getIntegerForKey("selectCharacter");
    
    
    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance();break;
        case 1:PetitKiki::getInstance();break;
        case 2:HarryPotter::getInstance();break;
        case 3:Ponyo::getInstance();break;
        case 4:FordAnglia::getInstance();break;
        case 5:PorcoRosso::getInstance();break;

        default:break;
    }

}

void CharacterSwitch::makeGameOver(){
    

    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->makeGameOver();break;
        case 1:PetitKiki::getInstance()->makeGameOver();break;
        case 2:HarryPotter::getInstance()->makeGameOver();break;
        case 3:Ponyo::getInstance()->makeGameOver();break;
        case 4:FordAnglia::getInstance()->makeGameOver();break;
        case 5:PorcoRosso::getInstance()->makeGameOver();break;

        default: break;
    }
    
    gamePlayFlag = false;
    gameOverFlag = true;
    


    
}

void CharacterSwitch::makeGameClear(){

    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->makeGameClear();break;
        case 1:PetitKiki::getInstance()->makeGameClear();break;
        case 2:HarryPotter::getInstance()->makeGameClear();break;
        case 3:Ponyo::getInstance()->makeGameClear();break;
        case 4:FordAnglia::getInstance()->makeGameClear();break;
        case 5:PorcoRosso::getInstance()->makeGameClear();break;
        default: break;
    }
    
    gamePlayFlag = false;
    gameOverFlag = true;

}




//キキちゃんの1フレーム毎の処理
void CharacterSwitch::characterUpdate(){
    
    
    
    //ゲームプレイ中ではない場合は何もせず終了
    if(gamePlayFlag != true){
        
        return;
        
    }

    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->characterUpdate(tappedFlag);break;
        case 1:PetitKiki::getInstance()->characterUpdate(tappedFlag);break;
        case 2:HarryPotter::getInstance()->characterUpdate(tappedFlag);break;
        case 3:Ponyo::getInstance()->characterUpdate(tappedFlag);break;
        case 4:FordAnglia::getInstance()->characterUpdate(tappedFlag);break;
        case 5:PorcoRosso::getInstance()->characterUpdate(tappedFlag);break;

        default: break;
    }

}

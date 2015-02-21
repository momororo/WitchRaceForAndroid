//
//  CharacterSwitch.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#ifndef __WitchRace__CharacterSwitch__
#define __WitchRace__CharacterSwitch__

#include "cocos2d.h"

using namespace cocos2d;



class CharacterSwitch : public cocos2d::Sprite
{
private:
    //変数
    //クラス
    static CharacterSwitch *characterInstance;
    
    
    
    //タップされているか判定するフラグ
    bool tappedFlag = false;
    
    //重力値
    int pGravity = 0;
    
    //ゲームプレイフラグ
    bool gamePlayFlag = false;
    
    bool gameOverFlag = false;
    
    //キャラクターフラグ
    int characterFlag;


    
    //メソッド
    //コンストラクタ(初期化)
    CharacterSwitch();
    
    
    
public:
    
    
    //メソッド
    //プレイヤーは一体だけなのでシングルトン
    static CharacterSwitch* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(CharacterSwitch);
    
    //getter
    Sprite* getCharacter();
    
    
    
    //キキちゃんの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void characterUpdate();
    
    //キキちゃんのタップ状態の変更
    void setTappedFlagOfCharacter(bool flag);
    
    //キキちゃんの動作開始
    void startCharacter();
    
    //キキちゃんの動作停止
    void stopCharacter();
    
    bool getGamePlayFlag();
    
    bool getGameOverFlag();
    
    
    //gameOverの処理
    void makeGameOver();
    
    void makeGameClear();
    
    
    
};

#endif /* defined(__WitchRace__CharacterSwitch__) */

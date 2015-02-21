//
//  BackGround.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/04.
//
//

#ifndef __WitchRace__BackGround__
#define __WitchRace__BackGround__
#include "GameScene.h"
#include "cocos2d.h"
#include "Enemy.h"
#include "Zorder.h"

using namespace cocos2d;

class BackGround : public cocos2d::Layer
{
private:

//変数
    //クラス
    static BackGround *backGroundInstance;
    
    //カウント(背景のreplace回数)初期値で調整
    int count = -2;
    
    int testcount;

    //配列
    cocos2d::Vector<Sprite*> *backGrounds = new cocos2d::Vector<Sprite*>;
    
    //staticBackGround
    cocos2d::Sprite* staticBackGround;
    
    //プレイフラグ
    bool gamePlayFlag = false;
    
    bool gameOverFlag = false;
    
    
//メソッド
    //コンストラクタ(初期化)
    BackGround();
    
    
public:
    //メソッド
    //シングルトン
    static BackGround* getInstance();
    //シングルトンデストラクタ
    static void destroyInstance();
        
    //getter1
    cocos2d::Sprite* getBackGround1();
    
    //getter2
    cocos2d::Sprite* getBackGround2();
    //getter3
    cocos2d::Sprite* getBackGround3();

    //staticGackGround
    cocos2d::Sprite* getStaticBackGround();
        
    //backGroundの動作開始
    void startBackGround();
    
    //backGroundの動作停止
    void stopBackGround();
    
    //BackGroundの位置を入れ替え
    void replaceBackGround();
    
    //backGroundの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void backGroundUpdate();
    
    //ゲームオーバーシーンの作成
    void makeGameOver();
    
    //背景のreplace回数を返す
    int getReplaceCount();
    
    //4面のみメソッドで背景にスプライトを追加
    void addBackGroundParts4();
    
    CREATE_FUNC(BackGround);

    
    
};


#endif /* defined(__WitchRace__BackGround__) */

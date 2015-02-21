//
//  Kiki.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#ifndef __WitchRace__Kiki__
#define __WitchRace__Kiki__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class Kiki : public cocos2d::Sprite
{
private:
//変数
    //クラス
    static Kiki *kikiInstance;
    
    
    //キキちゃん
    Sprite *kiki;
    //キキ影
    Sprite *kikiShadow;
    
    Sprite *broom;
        
    //重力値
    int pGravity = 0;
    
    
    ParticleSystemQuad* endParticle;
    ParticleSystemQuad* kikiParticle;

    
    
//メソッド
    //コンストラクタ(初期化)
    Kiki();
    
    
    
public:
//メソッド
    //プレイヤーは一体だけなのでシングルトン
    static Kiki* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(Kiki);
    
    //getter
    Sprite* getCharacter();
    

    
    //キキちゃんの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void characterUpdate(bool tappedFlag);
    
    
    //キキちゃんの動作開始
    void startCharacter();
    
    //キキちゃんの動作停止
    void stopCharacter();
    
    //gameOverの処理
    void makeGameOver();
    
    //gameClearの処理
    void makeGameClear();


};

#endif /* defined(__WitchRace__Kiki__) */

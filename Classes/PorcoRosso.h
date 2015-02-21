//
//  PorcoRosso.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#ifndef __WitchRace__PorcoRosso__
#define __WitchRace__PorcoRosso__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class PorcoRosso : public cocos2d::Sprite
{
private:
//変数
    //クラス
    static PorcoRosso *porcoRossoInstance;
    
    
    //キキちゃん
    Sprite *porcoRosso;
    //キキ影
    Sprite *porcoRossoShadow;
    
    Sprite *broom;
        
    //重力値
    int pGravity = 0;
    float pRotate = 0;
    
    
    ParticleSystemQuad* endParticle;
    ParticleSystemQuad* porcoRossoParticle;

    
    
//メソッド
    //コンストラクタ(初期化)
    PorcoRosso();
    
    
    
public:
//メソッド
    //プレイヤーは一体だけなのでシングルトン
    static PorcoRosso* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(PorcoRosso);
    
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

#endif /* defined(__WitchRace__PorcoRosso__) */

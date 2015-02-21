//
//  Ponyo.h
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/31.
//
//

#ifndef __WitchRace__Ponyo__
#define __WitchRace__Ponyo__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class Ponyo : public cocos2d::Sprite
{
private:
    //変数
    //クラス
    static Ponyo *ponyoInstance;
    
    
    //ポニョ
    Sprite *ponyo;
    //ポニョ影
    Sprite *ponyoShadow;
    
    //重力値
    int pGravity = 0;
    float pRotate = 0;
    
    
    ParticleSystemQuad* endParticle;
    ParticleSystemQuad* ponyoParticle;
    
    
    
    //メソッド
    //コンストラクタ(初期化)
    Ponyo();
    
    
    
public:
    //メソッド
    //プレイヤーは一体だけなのでシングルトン
    static Ponyo* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(Ponyo);
    
    //getter
    Sprite* getCharacter();
    
    
    
    //ポニョの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void characterUpdate(bool tappedFlag);
    
    
    //ポニョの動作開始
    void startCharacter();
    
    //ポニョの動作停止
    void stopCharacter();
    
    //gameOverの処理
    void makeGameOver();
    
    //gameClearの処理
    void makeGameClear();

    
    
    
};


#endif /* defined(__WitchRace__Ponyo__) */

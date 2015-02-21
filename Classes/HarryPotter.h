//
//  HarryPotter.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#ifndef __WitchRace__HarryPotter__
#define __WitchRace__HarryPotter__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class HarryPotter : public cocos2d::Sprite
{
private:
//変数
    //クラス
    static HarryPotter *harryPotterInstance;
    
    
    //キキちゃん
    Sprite *harryPotter;
    //キキ影
    Sprite *harryPotterShadow;
    
    Sprite *broom;
        
    //重力値
    int pGravity = 0;
    float pRotate = 0;
    
    
    ParticleSystemQuad* endParticle;
    ParticleSystemQuad* harryPotterParticle;

    
    
//メソッド
    //コンストラクタ(初期化)
    HarryPotter();
    
    
    
public:
//メソッド
    //プレイヤーは一体だけなのでシングルトン
    static HarryPotter* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(HarryPotter);
    
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

#endif /* defined(__WitchRace__HarryPotter__) */

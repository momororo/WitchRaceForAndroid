//
//  Enemy.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/05.
//
//

#ifndef __WitchRace__Enemy__
#define __WitchRace__Enemy__

#include "cocos2d.h"
#include "Zorder.h"
#include "BackGround.h"

using namespace cocos2d;



class Enemy : public cocos2d::Sprite
{
private:
    
    //クラス
    static Enemy *enemyInstance;

    
    //コンストラクタ
    Enemy();
    

    
public:
    
    
    //シングルトン
    static Enemy* getInstance();
    //デストラクタ
    static void destroyInstance();

    //各面のプリロード
    void preLoad1();
    void preLoad2();
    void preLoad3();
    void preLoad4();
    void preLoad5();
    
    
    //enemyの管理
    void addEnemyManager(Sprite* backGround);
    
    //各面の敵追加メソッド
    void addEnemy1(Sprite* backGround);
    void addEnemy2(Sprite* backGround);
    void addEnemy3(Sprite* backGround);
    void addEnemy4(Sprite* backGround);
    void addEnemy5(Sprite* backGround);
    
    //4面のみ別メソッド
    Sprite* addEnemyParts4(int widthAndHeight);

    //4面のみ高さ管理の変数
    int preHeightPosition;
    
    

    CREATE_FUNC(Enemy);
    
    
};

#endif /* defined(__WitchRace__Enemy__) */

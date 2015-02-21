//
//  Enemy.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/05.
//
//

#include "Enemy.h"

//初期値NULL
Enemy* Enemy::enemyInstance = NULL;

//シングルトン
Enemy* Enemy::getInstance(){
    
    if(enemyInstance == NULL){
        
        enemyInstance = new Enemy();
    }
    
    return  enemyInstance;
}

//デストラクタ
void Enemy::destroyInstance() {
    if (enemyInstance != NULL){
        delete enemyInstance;
        
        enemyInstance = NULL;
    }
}



//コンストラクタ(初期化)
Enemy::Enemy(){
    
    //ステージごとに敵を追加するメソッドを分岐
    auto userDef = UserDefault::getInstance();
    auto point = userDef->getIntegerForKey("selectStory");
    
    //各面の読込(1ずつずれているため注意すること)
    switch (point) {
        case 0:this->preLoad1();break;
        case 1:this->preLoad2();break;
        case 2:this->preLoad3();break;
        case 3:this->preLoad4();break;
        case 4:this->preLoad5();break;
        default:break;
    }
    
}

//backGroundにenemyを追加
void Enemy::addEnemyManager(Sprite* backGround){
    

    //ステージごとに敵を追加するメソッドを分岐
    auto userDef = UserDefault::getInstance();
    auto point = userDef->getIntegerForKey("selectStory");

    //各面の読込(1ずつずれているため注意すること)
    switch (point) {
        case 0:this->addEnemy1(backGround);break;
        case 1:this->addEnemy2(backGround);break;
        case 2:this->addEnemy3(backGround);break;
        case 3:this->addEnemy4(backGround);break;
        case 4:this->addEnemy5(backGround);break;
        default:break;
    }

    
}

#pragma mark-
#pragma mark stage1

//1面の的追加
void Enemy::addEnemy1(Sprite* backGround){
    
//badを生成するラムダ
auto addBad = [](){
    
        //コウモリのスプライトを予め作成
        Sprite *bad = Sprite::createWithSpriteFrameName("bad_1.png");
        bad->setName("enemy");
        bad->setGlobalZOrder(zOrderOfEnemy);
    
        //物理体の設定
        auto badMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
        Point spritePoints[5]{
            
            Vec2(-47,-122),Vec2(-47,110),Vec2(47,122),Vec2(47,-10),Vec2(20,-100)
    
        };
    
        auto badBody = PhysicsBody::createPolygon(spritePoints, 5,badMaterial);
    
        //重力による影響の可否
        badBody->setGravityEnable(false);
        //まじない
        badBody->setDynamic(false);
        badBody->setEnable(true);
        
        //カテゴリビットマスク
        badBody->setCategoryBitmask(0x02);
        badBody->setCollisionBitmask(0);
        badBody->setContactTestBitmask(0x01);
        
        //Bodyの追加
        bad->setPhysicsBody(badBody);
        
        
        //アニメーション用配列を用意
        auto  badFrames = new Vector<SpriteFrame*>();
        
        //画像２枚を配列にセットする
        //画像をすべて(2枚)を取り出せるよう、ループ文を使用
        for (int i = 1; i < 3;i++ ) {
            std::string badName = StringUtils::format("bad_%i.png",i);
            SpriteFrame *spBadFrame = SpriteFrameCache::getInstance()-> getSpriteFrameByName(badName.c_str());
            badFrames -> pushBack(spBadFrame);
            
            
        }
        
        //アニメーションの設定
        Animation *badAnimation = Animation::createWithSpriteFrames(*badFrames,0.1f);
        Animate *badAnimate = Animate::create(badAnimation);
        RepeatForever *repeat = RepeatForever::create(badAnimate);
        bad -> runAction(repeat);
        delete badFrames;

    
        return bad;
    
};
    
    
//木のスプライトを作成するラムダ
auto addtree = [](){

    //木のスプライトを作成
    Sprite *tree = Sprite::createWithSpriteFrameName("enemy_tree.png");
    tree->setName("enemy");
    tree->setGlobalZOrder(zOrderOfEnemy);
    
    //物理体の設定
    auto treeMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point spritePoints[7]{
        
        Vec2(-110,-357),Vec2(-110,230),Vec2(-60,310),Vec2(-20,357),Vec2(20,357),Vec2(110,230),Vec2(110,-357)
    
    };
    
    auto treeBody = PhysicsBody::createPolygon(spritePoints, 7,treeMaterial);
    
    //重力による影響の可否
    treeBody->setGravityEnable(false);
    //まじない
    treeBody->setDynamic(false);
    treeBody->setEnable(true);
    
    //カテゴリビットマスク
    treeBody->setCategoryBitmask(0x02);
    treeBody->setCollisionBitmask(0);
    treeBody->setContactTestBitmask(0x01);
    
    //Bodyの追加
    tree->setPhysicsBody(treeBody);
    
    return tree;
    
};
    
    
//xの値を先に決めとく(後で一括変更するのがラクダから)
    int positionX = backGround->getContentSize().width/10;
    
    
//乱数を発生させて配置を決定していく
    int positionRnd = arc4random_uniform(4);


    //0の場合(木がどーん！)
    if(positionRnd == 0){
        //ポジションで合わせる(アンカーでは合わせられず)
        auto tree = addtree();
        tree->setPosition(Vec2(positionX, tree->getContentSize().height/2));
        
        backGround->addChild(tree);
        
        return;
        
    }
    
    
    
    //1の場合(コウモリが3匹上にどーん！)
    if(positionRnd == 1){
        
        Vector<Sprite*> *bads = new Vector<Sprite*>();
        
        //コウモリを4匹生成(面倒なので配列)
        for (int idx = 0; idx < 3 ;idx++){
            
            bads->pushBack(addBad());
            backGround->addChild(bads->at(idx));
        }
        
        //positionの調整
        for (int idx = 0; idx < 3 ;idx++){
            
            //0の時は上に位置を合わせる
            if(idx == 0){

                bads->at(idx)->setPosition(Vec2(positionX,backGround->getContentSize().height - bads->at(idx)->getContentSize().height/2));



            }else{
                

                bads->at(idx)->setPosition(Vec2(positionX,bads->at(idx-1)->getPositionY() - bads->at(idx)->getContentSize().height));
                
                
            }
            
        }
        
        return;
        
    }
    
    
    
    //2の場合(コウモリ2匹上に、木が下に(2/3くらい出てる感じ))
    if(positionRnd == 2){
        
        Vector<Sprite*> *bads = new Vector<Sprite*>();
        
        //コウモリを2匹生成(面倒なので配列)
        for (int idx = 0; idx < 2 ;idx++){
            
            bads->pushBack(addBad());
            backGround->addChild(bads->at(idx));
        }
        
        //positionの調整
        for (int idx = 0; idx < 2 ;idx++){
            
            //0の時は上に位置を合わせる
            if(idx == 0){
                
                bads->at(idx)->setPosition(Vec2(positionX,backGround->getContentSize().height - bads->at(idx)->getContentSize().height/2));
                
                
                
            }else{
                
                
                bads->at(idx)->setPosition(Vec2(positionX,bads->at(idx-1)->getPositionY() - bads->at(idx)->getContentSize().height));
                
                
            }
            
        }

        
        //木の生成
        auto tree = addtree();
        //ポジション
        tree->setPosition(Vec2(positionX, tree->getContentSize().height/2 - tree->getContentSize().height/3*1));
        
        //追加
        backGround->addChild(tree);
        
        
        return;
        
        
    }
    
    
    
    //3の場合(コウモリ3匹上に、木が下に(1/3くらい出てる感じ))
    if(positionRnd == 3){
        
        //コウモリを3匹生成するのは面倒なので上の配列使いました。
        
        Vector<Sprite*> *bads = new Vector<Sprite*>();
        
        //コウモリを3匹生成(面倒なので配列)
        for (int idx = 0; idx < 3 ;idx++){
            
            bads->pushBack(addBad());
            backGround->addChild(bads->at(idx));
        }
        
        //positionの調整
        for (int idx = 0; idx < 3 ;idx++){
            
            //0の時は上に位置を合わせる
            if(idx == 0){
                
                bads->at(idx)->setPosition(Vec2(positionX,backGround->getContentSize().height - bads->at(idx)->getContentSize().height/2));
                
                
                
            }else{
                
                
                bads->at(idx)->setPosition(Vec2(positionX,bads->at(idx-1)->getPositionY() - bads->at(idx)->getContentSize().height));
                
                
            }
            
        }

        
        //木の生成
        auto tree = addtree();
        //ポジション
        tree->setPosition(Vec2(positionX, tree->getContentSize().height/2 - tree->getContentSize().height/3*2));
        
        //追加
        backGround->addChild(tree);


        
        return;
        
    }

}

#pragma mark-
#pragma mark stage2

void Enemy::addEnemy2(Sprite* backGround){
//enemy_witchを生成するラムダ
    auto addWitch = [](){
        
        //witchのスプライトを予め作成
        Sprite *enemy = Sprite::createWithSpriteFrameName("enemy_witch.png");
        enemy->setName("enemy");
        enemy->setGlobalZOrder(zOrderOfEnemy);
        enemy->setScale(0.5f);

        
        //物理体の設定
        auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        
        Point spritePoints[6]={
            
            Vec2(30,-30),Vec2(0,-25), Vec2(-51,5),Vec2(-5,30),Vec2(50,-5),Vec2(40,-30)
            
        };
        
        auto enemyBody = PhysicsBody::createPolygon(spritePoints, 6,enemyMaterial);
        
        //重力による影響の可否
        enemyBody->setGravityEnable(false);
        //まじない
        enemyBody->setDynamic(false);
        enemyBody->setEnable(true);
        
        //カテゴリビットマスク
        enemyBody->setCategoryBitmask(0x02);
        enemyBody->setCollisionBitmask(0);
        enemyBody->setContactTestBitmask(0x01);
        
        //witchの追加
        enemy->setPhysicsBody(enemyBody);
        
        
        return enemy;
        
    };
    
    
    
//ランダムで配置を行う
    //x軸の移動に利用(X軸を4分割)
    for(int idxX = 0 ; idxX < 4 ; idxX++){
 
        //Y軸の分割数をランダムで生成
        auto rndNumberY = arc4random_uniform(5);
        //0が出たらエラーになるため、1を足し込む
        rndNumberY = rndNumberY + 5;

        //更に分散しているように見せるために乱数を追加
        int rnd = arc4random_uniform(120);

        
        //4体ずつランダムで置いていく
        for(int count = 0; count < 5; count++){
            
            
            //乱数を生成
            int rndPositionY = arc4random_uniform(rndNumberY);
            auto enemy = addWitch();
            
            
            
            //ポジションの設定
            enemy->setPosition(Vec2(backGround->getContentSize().width / 5 * idxX + backGround->getContentSize().width/5/2 , backGround->getContentSize().height / rndNumberY * rndPositionY + backGround->getContentSize().height/rndNumberY / 2 + rnd ));
            
            backGround->addChild(enemy);
            
        }
        
    }

}

#pragma mark-
#pragma mark stage3

void Enemy::addEnemy3(Sprite* backGround){
    
//enemy_chimneyを生成するラムダ
    auto addchimney = [](){
        
        //chimneyのスプライトを予め作成
        Sprite *enemy = Sprite::createWithSpriteFrameName("enemy_chimney.png");
        enemy->setName("enemy");
        enemy->setGlobalZOrder(zOrderOfEnemy);
        enemy->setScale(0.5f);
        
        //物理体の設定
        auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        
        Point spritePoints[5]={
            
            Vec2(-35,-146),Vec2(-30,120), Vec2(15,146), Vec2(35,135),Vec2(35,-146)
            
        };
        
        auto enemyBody = PhysicsBody::createPolygon(spritePoints, 5,enemyMaterial);
        
        //重力による影響の可否
        enemyBody->setGravityEnable(false);
        //まじない
        enemyBody->setDynamic(false);
        enemyBody->setEnable(true);
        
        //カテゴリビットマスク
        enemyBody->setCategoryBitmask(0x02);
        enemyBody->setCollisionBitmask(0);
        enemyBody->setContactTestBitmask(0x01);
        
        //chimneyの追加
        enemy->setPhysicsBody(enemyBody);
        
        
        return enemy;
        
    };
    
    //enemy_cloudを生成するラムダ
    auto addcloud = [](){
        
        //chimneyのスプライトを予め作成
        Sprite *enemy = Sprite::createWithSpriteFrameName("enemy_cloud.png");
        enemy->setName("enemy");
        enemy->setGlobalZOrder(zOrderOfEnemy);
        enemy->setScale(0.1f);
        
        //物理体の設定
        auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        
        auto enemyBody = PhysicsBody::createCircle(enemy->getContentSize().width/2 * enemy->getScale(),enemyMaterial);
        
        
        //重力による影響の可否
        enemyBody->setGravityEnable(false);
        //まじない
        enemyBody->setDynamic(false);
        enemyBody->setEnable(true);
        
        //カテゴリビットマスク
        enemyBody->setCategoryBitmask(0x02);
        enemyBody->setCollisionBitmask(0);
        enemyBody->setContactTestBitmask(0x01);
        
        //重力体の追加
        enemy->setPhysicsBody(enemyBody);
        
        
        return enemy;
        
    };
    
    
    //ランダムで配置を行う
    //x軸の移動に利用(X軸を4分割)
    for(int idxX = 0 ; idxX < 5 ; idxX++){

        //後でこいつの座標を使うため、addchildしない場合でも宣言は行う必要がある。
        //煙突を追加
        auto chimney = addchimney();
        //ポジションを設定
        chimney->setPosition(Vec2(backGround->getContentSize().width / 5 * idxX + backGround->getContentSize().width/5/2, chimney->getContentSize().height/2 * chimney->getScale()));
        
        //1/3の確率で煙突を追加
        if(arc4random_uniform(3) == 0){
            
            //backGroundにスプライトを追加
            backGround->addChild(chimney);

        }
        
        //Y軸の分割数をランダム生成
        auto rndNumberY = arc4random_uniform(5);
        //0が出たらエラーになるため、1を足し込む
        rndNumberY = rndNumberY + 5;
        
        //更に分散しているように見せるために乱数を追加(Y座標をずらします)
        int rnd = arc4random_uniform(20);
        

        //雲の配置
        int limit;
        if(arc4random_uniform(2) == 0){
            limit = 2;
        }else{
            limit = 3;
        }
        for(int count = 0; count < limit; count++){
            
            
            //乱数を生成
            int rndPositionY = arc4random_uniform(rndNumberY);
            auto enemy = addcloud();
            
            
            
            //ポジションの設定(樹海化怖くて触れません)
            enemy->setPosition(Vec2(backGround->getContentSize().width / 5 * idxX + backGround->getContentSize().width/10 , backGround->getContentSize().height / rndNumberY * rndPositionY + backGround->getContentSize().height/rndNumberY / 2 + rnd + chimney->getPositionY() + chimney->getContentSize().height/2 * chimney->getScale() ));
            
            
            /**
             *  スケールを乱数で決定(隣のbackGroundの重なりは検知できないため、
             *  idxが4(画面右端)の時は小さめの球をだして、見かけ上重ならないように調整して
             *  す。
             *  隣のbackGroundも含めて走査したら処理が重くなると思われるため、しません！
             */
            if(idxX == 4){
                enemy->setScale(((float)arc4random_uniform(2) + 1.5)/10);
            }else{
                enemy->setScale(((float)arc4random_uniform(3) + 3.0)/10);
            }
            
            //少し横にずらしてみる(2分の1でマイナス方向へ)
            int rndX = arc4random_uniform(20);
            if(arc4random_uniform(2) == 0){
                
                rndX = rndX * -1;
            }
            
            enemy->setPositionX(enemy->getPositionX() + rndX);
            
            backGround->addChild(enemy);
            
            
            
            //重なりを確認(重なっていた場合は再度配置)
            //一時的なnameをset(重なりとご検知されないように)
            enemy->setName("target");
            auto rect1 = enemy->getBoundingBox();
            
            //スプライトを取得
            Vector<Node*>allSprite = backGround->getChildren();
            
            //走査
            for(int idx = 0 ; idx < allSprite.size() ;idx++){
                
                auto sprite = allSprite.at(idx);
                
                //enemyではないネームをif文に入れる。
                if(sprite->getName() != "enemy"){
                    
                    //targetのスプライトが来た = 配列の最後まで回ったため、
                    //nameをenemyに戻して終了
                    if(sprite->getName() == "target"){
                        sprite->setName("enemy");
                        
                    }
                    
                    continue;
                }
                
                
                
                //座標取得
                auto rect2 = sprite->getBoundingBox();
                
                
                //重なりがある場合
                if(rect1.intersectsRect(rect2)){
                    //backGroundから削除
                    enemy->removeFromParent();
                    //カウントを減らして調整(再配置するため)
                    count--;
                    //デバグ
                    CCLOG("重なり探知で削除");
                    //ループから出る
                    break;
                }
   
                
            }
            
            
        }
        
    }

    
    

}

#pragma mark-
#pragma mark stage4

void Enemy::addEnemy4(Sprite* backGround){
    
//各オブジェクトの生成
    

//高さ1のルート
auto addRoute1 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    //電球を3つ設置
    
    for(int idx = 0; idx < 3; idx++){
        auto light = addEnemyParts4(96);
        //電球の高さ
        float height = backGround->getContentSize().height/22*12;

        if(idx == 0){
            
            light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
        }else{

            light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);

        }

        enemies->pushBack(light);
    }
    
    return enemies;

};

    
//高さ2のルート
auto addRoute2 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    //電球を3つ設置
    
    for(int idx = 0; idx < 3; idx++){
        auto light = addEnemyParts4(95);
        //電球の高さ
        float height = backGround->getContentSize().height/22*13;

        if(idx == 0){
            
            light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
        }else{
            
            light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
            
        }
        
        enemies->pushBack(light);
    }
    
    //車を3台設置
    for(int idx = 0; idx < 3; idx++){
        
        auto car = addEnemyParts4(11);
        //高さ
        float height = backGround->getContentSize().height/22*5;

        if(idx == 0){
            
            car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        }else{
            
            car->setPosition(enemies->at(enemies->size()-1)->getPositionX() + car->getContentSize().width, height);
            
        }
        
        enemies->pushBack(car);
    }

    
    
    return enemies;
    
};
    
//高さ3のルート
auto addRoute3 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    //電球を3つ設置
    
    for(int idx = 0; idx < 3; idx++){
        auto light = addEnemyParts4(94);
        //電球の高さ
        float height = backGround->getContentSize().height/22*14;
        
        if(idx == 0){
            
            light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
        }else{
            
            light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
            
        }
        
        enemies->pushBack(light);
    }
    
    //車を3台設置
    for(int idx = 0; idx < 3; idx++){
        
        auto car = addEnemyParts4(12);
        //高さ
        float height = backGround->getContentSize().height/22*6;
        
        if(idx == 0){
            
            car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        }else{
            
            car->setPosition(enemies->at(enemies->size()-1)->getPositionX() + car->getContentSize().width, height);
            
        }
        
        enemies->pushBack(car);
    }
    
    
    
    return enemies;
    
};
    
//高さ4のルート
auto addRoute4 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    //電球を3つ設置
    
    for(int idx = 0; idx < 3; idx++){
        auto light = addEnemyParts4(93);
        //電球の高さ
        float height = backGround->getContentSize().height/22*15;
        
        if(idx == 0){
            
            light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
        }else{
            
            light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
            
        }
        
        enemies->pushBack(light);
    }
    
    //車を1台設置
    for(int idx = 0; idx < 1; idx++){
        
        auto car = addEnemyParts4(33);
        //高さ
        float height = backGround->getContentSize().height/22*7;
        
        
            car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        
        enemies->pushBack(car);
        
    }
    
    
    
    return enemies;
    
};

//高さ5のルート
auto addRoute5 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    //電球を3つ設置
    
    for(int idx = 0; idx < 3; idx++){
        auto light = addEnemyParts4(92);
        //電球の高さ
        float height = backGround->getContentSize().height/22*16;
        
        if(idx == 0){
            
            light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
        }else{
            
            light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
            
        }
        
        enemies->pushBack(light);
    }
    
    //車を1台設置
    for(int idx = 0; idx < 1; idx++){
        
        auto car = addEnemyParts4(34);
        //高さ
        float height = backGround->getContentSize().height/22*8;
        
        
        car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        
        enemies->pushBack(car);
        
    }
    
    
    
    return enemies;
        
};
    
//高さ6のルート
auto addRoute6 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    //電球を3つ設置
    
    for(int idx = 0; idx < 3; idx++){
        auto light = addEnemyParts4(91);
        //電球の高さ
        float height = backGround->getContentSize().height/22*17;
        
        if(idx == 0){
            
            light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
        }else{
            
            light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
            
        }
        
        enemies->pushBack(light);
    }


    
    bool carSwitch;

    if(arc4random_uniform(2) == 0){

        carSwitch = true;
        
    }
    
    
    
    //車を1台設置
    for(int idx = 0; idx < 2; idx++){
        Sprite* car;
        
        if(carSwitch == true){
            car = addEnemyParts4(25);
            carSwitch = false;
        }else{
            car = addEnemyParts4(15);
            carSwitch = true;
        }
        
        
        //高さ
        float height = backGround->getContentSize().height/22*9;
        
        if(idx == 0){
            car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        }else{
            car->setPosition(Vec2(enemies->at(enemies->size()-1)->getPositionX() + enemies->at(enemies->size()-1)->getContentSize().width/2 + car->getContentSize().width/2 , height));
            
        }
        
        enemies->pushBack(car);
        
    }
    
    
    
    return enemies;
    
};

//高さ7のルート
auto addRoute7 = [&](){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
    
    bool carSwitch;
    
    if(arc4random_uniform(2) == 0){
        
        carSwitch = true;
        
    }
    
    
    
    //車を2台設置
    for(int idx = 0; idx < 2; idx++){
        Sprite* car;
        
        if(carSwitch == true){
            car = addEnemyParts4(26);
            carSwitch = false;
        }else{
            car = addEnemyParts4(16);
            carSwitch = true;
        }
        
        
        //高さ
        float height = backGround->getContentSize().height/22*10;
        
        if(idx == 0){
            car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        }else{
            car->setPosition(Vec2(enemies->at(enemies->size()-1)->getPositionX() + enemies->at(enemies->size()-1)->getContentSize().width/2 + car->getContentSize().width/2 , height));
            
        }
        
        enemies->pushBack(car);
        
    }
    
    
    
    return enemies;
    
};
    
auto addRouteChange = [&](int preHeightPosition, int heightPosition){
    
    Vector<Sprite*> *enemies = new Vector<Sprite*>;
    
//低いところから高いところに行くパターン
if(preHeightPosition < heightPosition){
//地面部分の生成
        //車を3台設置
        for(int idx = 0; idx < 3; idx++){
            
            Sprite* car;

        //Spriteの生成
            if(idx < 2){
                
                //車が不要なのでreturn
                if(preHeightPosition == 1){
                    continue;
                }
                
                int number = 10 + (preHeightPosition - 1);
                car = addEnemyParts4(number);
            }
            
            if(idx == 2){

                int number = 10 + (heightPosition - 1);
                 car = addEnemyParts4(number);

            }
            
        //positionの生成
            if(idx != 2){
                
                //高さ
                float height = backGround->getContentSize().height/22*(3 + preHeightPosition);

                
                if(idx == 0 ){
                    car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
                }else{

                    car->setPosition(Vec2(enemies->at(enemies->size()-1)->getPositionX() + enemies->at(enemies->size()-1)->getContentSize().width/2 + car->getContentSize().width/2 , height));

                }
                
                
            }else{
                
                float height = backGround->getContentSize().height/22*(3 + heightPosition);

                //例外
                if(preHeightPosition == 1){
                    car->setPosition(backGround->getContentSize().width/3*2+car->getContentSize().width/2, height);

                }else{
                
                car->setPosition(Vec2(enemies->at(enemies->size()-1)->getPositionX() + enemies->at(enemies->size()-1)->getContentSize().width/2 + car->getContentSize().width/2 , height));
                }

            }
            
            enemies->pushBack(car);
            
        }
        
//天井部分の生成
        for(int idx = 0; idx < 3; idx++){
            
            //何もせず配列を返す
            if(heightPosition == 7){
                return enemies;
            }
            
            Sprite* light;
            //Spriteの生成
                int number = 90 + (7 - heightPosition);
                light = addEnemyParts4(number);
            
                //電球の高さ
                float height = backGround->getContentSize().height/22*(11 +heightPosition);
                
                if(idx == 0){
                    
                    light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
                }else{
                    
                    light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
                    
                }
            
            enemies->pushBack(light);
            
        }

        



        
    }
    
//高いところから低いところに行くパターン
else
{

//天井部分の生成
        for(int idx = 0; idx < 3; idx++){
            
            Sprite* light;
            
            //Spriteの生成
            if(idx < 2){
                
                if(preHeightPosition == 7){
                    continue;
                }
                
                int number = 90 + (7 - preHeightPosition);
                light = addEnemyParts4(number);
            }
            
            if(idx == 2){
                
                int number = 90 + (7 - heightPosition);
                light = addEnemyParts4(number);
                
            }
            
            //positionの生成
            if(idx != 2){
                
                //高さ
                float height = backGround->getContentSize().height/22*(11 +preHeightPosition);
                
                
                if(idx == 0 ){
                    light->setPosition(backGround->getContentSize().width/3*0+light->getContentSize().width/2, height);
                }else{
                    
                    light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
                    
                }
                
                
            }else{
                
                //高さ
                float height = backGround->getContentSize().height/22*(11 +heightPosition);
                
                //例外
                if(preHeightPosition == 7){
                    light->setPosition(backGround->getContentSize().width/3*2+light->getContentSize().width/2, height);
                }else{
                
                light->setPosition(enemies->at(enemies->size()-1)->getPositionX() + light->getContentSize().width, height);
                }
            }
            
            enemies->pushBack(light);
            
        }
    
//地面部分の生成
    for(int idx = 0; idx < 3; idx++){
        
        //何もせず配列を返す
        if(heightPosition == 1){
            return enemies;
        }
        
        Sprite* car;
        //Spriteの生成
        int number = 10 + (heightPosition - 1);
        car = addEnemyParts4(number);
        
        //車の高さ
        float height = backGround->getContentSize().height/22*(3 + heightPosition);
        
        if(idx == 0 ){
            car->setPosition(backGround->getContentSize().width/3*0+car->getContentSize().width/2, height);
        }else{
            
            car->setPosition(Vec2(enemies->at(enemies->size()-1)->getPositionX() + enemies->at(enemies->size()-1)->getContentSize().width/2 + car->getContentSize().width/2 , height));
            
        }
        

    
        enemies->pushBack(car);
        
    }
    
    
    
    
}
        return enemies;
    
};
    
    Vector<Sprite*> *enemies;
    
    //初回は高さ3で行ってみる
    if(BackGround::getInstance()->getReplaceCount() == -2){
        enemies = addRoute4();
        preHeightPosition = 4;
    }
    
    //初回以外
    if(BackGround::getInstance()->getReplaceCount() != -2){

        
        //乱数を生成
        int heightPosition = arc4random_uniform(7);
        //乱数を調整
        heightPosition++;
        
        
        //面倒なのでぽい
        if(preHeightPosition == heightPosition){
            switch (heightPosition) {
                case 1:enemies = addRoute1();break;
                case 2:enemies = addRoute2();break;
                case 3:enemies = addRoute3();break;
                case 4:enemies = addRoute4();break;
                case 5:enemies = addRoute5();break;
                case 6:enemies = addRoute6();break;
                case 7:enemies = addRoute7();break;
                default:break;
            }
            
        }else{
            
            //誤差がある場合に生成
            enemies = addRouteChange(preHeightPosition,heightPosition);
            
        }
        
        preHeightPosition = heightPosition;


    }
    

    
    //追加
    for(auto enemy : *enemies){
        backGround->addChild(enemy);
    }
    






}

#pragma mark-
#pragma mark stage5

void Enemy::addEnemy5(Sprite* backGround){
    
//FieldTreeを生成するラムダ
auto addFireldTree = [](){
        
    //chimneyのスプライトを予め作成
        Sprite *enemy = Sprite::createWithSpriteFrameName("enemy_fieldTree.png");
        enemy->setName("enemy");
        enemy->setGlobalZOrder(zOrderOfEnemy);
        enemy->setScale(1.3f);
    
        //物理体の設定
        auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        
    
        Point spritePoints[6]={
        
            Vec2(-180,-150),Vec2(-120,100),Vec2(10,310),Vec2(120,100), Vec2(180,-150),Vec2(10,-350)
            
        };
    
        auto enemyBody = PhysicsBody::createPolygon(spritePoints, 6,enemyMaterial);

    
    
        //重力による影響の可否
        enemyBody->setGravityEnable(false);
        //まじない
        enemyBody->setDynamic(false);
        enemyBody->setEnable(true);
        
        //カテゴリビットマスク
        enemyBody->setCategoryBitmask(0x02);
        enemyBody->setCollisionBitmask(0);
        enemyBody->setContactTestBitmask(0x01);
        
        //chimneyの追加
        enemy->setPhysicsBody(enemyBody);
        
        
        return enemy;
        
    };
    
    //birdを生成するラムダ
    auto addBird = [](){
        
        //コウモリのスプライトを予め作成
        Sprite *enemy = Sprite::createWithSpriteFrameName("bird_1.png");
        enemy->setName("enemy");
        enemy->setGlobalZOrder(zOrderOfEnemy);
        enemy->setScale(1.3f);
        
        //物理体の設定
        auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        //auto enemyBody = PhysicsBody::createBox(enemy->getContentSize()*0.9,enemyMaterial);
        
        Point spritePoints[8]={
            
            Vec2(-200,250),Vec2(10,400), Vec2(200,250),Vec2(160,-20) ,Vec2(70,-280), Vec2(10,-330),Vec2(-40,-280),Vec2(-140,0)
            
            //Vec2(-180,-150),Vec2(-120,100),Vec2(10,330),Vec2(120,100), Vec2(180,-150),Vec2(10,-350)
            
        };
        
        auto enemyBody = PhysicsBody::createPolygon(spritePoints, 8,enemyMaterial);

        
        
        //重力による影響の可否
        enemyBody->setGravityEnable(false);
        //まじない
        enemyBody->setDynamic(false);
        enemyBody->setEnable(true);
        
        //カテゴリビットマスク
        enemyBody->setCategoryBitmask(0x02);
        enemyBody->setCollisionBitmask(0);
        enemyBody->setContactTestBitmask(0x01);
        
        //Bodyの追加
        enemy->setPhysicsBody(enemyBody);
        
        
        //アニメーション用配列を用意
        auto  enemyFrames = new Vector<SpriteFrame*>();
        
        //画像２枚を配列にセットする
        //画像をすべて(2枚)を取り出せるよう、ループ文を使用
        for (int i = 1; i < 3;i++ ) {
            std::string enemyName = StringUtils::format("bird_%i.png",i);
            SpriteFrame *spEnemyFrame = SpriteFrameCache::getInstance()-> getSpriteFrameByName(enemyName.c_str());
            enemyFrames -> pushBack(spEnemyFrame);
            
            
        }
        
        //アニメーションの設定
        Animation *enemyAnimation = Animation::createWithSpriteFrames(*enemyFrames,0.1f);
        Animate *enemyAnimate = Animate::create(enemyAnimation);
        RepeatForever *repeat = RepeatForever::create(enemyAnimate);
        enemy -> runAction(repeat);
        delete enemyFrames;
        
        
        return enemy;
        
    };
    
    //調整用の変数
    int limit = 1;
    
    //木を配置
    for(int idx = 0; idx < limit ; idx++){
        
        auto fieldTree = addFireldTree();
        
        fieldTree->setPosition(Vec2(backGround->getContentSize().width/(limit*2) * (idx * 2), 0 + fieldTree -> getContentSize().height/2 * fieldTree->getScale()));
        
        backGround->addChild(fieldTree);
        
    }
    
    //鳥を配置
    for(int idx = 0; idx < limit ; idx++){
        
        auto bird = addBird();

        bird->setPosition(Vec2(backGround->getContentSize().width/(limit*2) * (idx * 2 + 1), backGround->getContentSize().height - bird -> getContentSize().height/2 * bird->getScale()));
        
        backGround->addChild(bird);

    }
    


}

//各面のプリロード
void Enemy::preLoad1(){
    
}
void Enemy::preLoad2(){
    
    
}
void Enemy::preLoad3(){
    
}
void Enemy::preLoad4(){
    
}
void Enemy::preLoad5(){
    
}


//4面の各オブジェクトを生成するメソッド
//引数二桁xy(xは幅、yは高さ)で返すスプライトを分岐(ライトは幅を9にすること)
Sprite* Enemy::addEnemyParts4(int widthAndHeight){
    
    //与えられた引数に応じて呼び出すpngNameを変える
    std::string pngName;
    switch (widthAndHeight) {
        case 11: pngName = "car_1_1.png";break;
        case 12: pngName = "car_1_2.png";break;
        case 13: pngName = "car_1_3.png";break;
        case 14: pngName = "car_1_4.png";break;
        case 15: pngName = "car_1_5.png";break;
        case 16: pngName = "car_1_6.png";break;
        case 25: pngName = "car_2_5.png";break;
        case 26: pngName = "car_2_6.png";break;
        case 33: pngName = "car_3_3.png";break;
        case 34: pngName = "car_3_4.png";break;
        case 91: pngName = "light_1.png";break;
        case 92: pngName = "light_2.png";break;
        case 93: pngName = "light_3.png";break;
        case 94: pngName = "light_4.png";break;
        case 95: pngName = "light_5.png";break;
        case 96: pngName = "light_6.png";break;
        default:break;
    }
            
            Sprite *enemy = Sprite::createWithSpriteFrameName(pngName);
            enemy->setName("enemy");
            enemy->setGlobalZOrder(zOrderOfEnemy);
            enemy->setScale(1.0f);
            
            //物理体の設定
            auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;

/*
    //与えられた引数に応じて物理体のポイントを変える。(後で)

    PhysicsBody enemyBody;

 
    switch (widthAndHeight) {
        case 11: pngName = "car_1_1.png";break;
        case 12: pngName = "car_1_2.png";break;
        case 13: pngName = "car_1_3.png";break;
        case 14: pngName = "car_1_4.png";break;
        case 15: pngName = "car_1_5.png";break;
        case 16: pngName = "car_1_6.png";break;
        case 25: pngName = "car_2_5.png";break;
        case 26: pngName = "car_2_6.png";break;
        case 33: pngName = "car_3_3.png";break;
        case 34: pngName = "car_3_4.png";break;
        case 91: pngName = "light_1.png";break;
        case 92: pngName = "light_2.png";break;
        case 93: pngName = "light_3.png";break;
        case 94: pngName = "light_4.png";break;
        case 95: pngName = "light_5.png";break;
        case 96: pngName = "light_6.png";break;
        default:break;
    }
*/
    
    auto enemyBody = PhysicsBody::create();
 
    if (widthAndHeight == 11) {
        
        Point spritePoints[6]{
        
            Vec2(-106.5,-51.5),Vec2(-106.5,0), Vec2(-20,51.5),Vec2(40,51.5), Vec2(106.5,0),Vec2(106.5,-51.5)
            
        };
        
        enemyBody = PhysicsBody::createPolygon(spritePoints, 6,enemyMaterial);
        
    }else if (widthAndHeight == 33){
    
        Point spritePoints[5]{
            
            Vec2(-319.5,-154.5),Vec2(-319.5,50),Vec2(-180,154.5),Vec2(319.5,154.5),Vec2(319.5,-154.5)
            
        };
        
        enemyBody = PhysicsBody::createPolygon(spritePoints, 5,enemyMaterial);
    
    }else if (widthAndHeight == 34){
    
        Point spritePoints[6]{
            
            Vec2(-320,-197),Vec2(-320,20),Vec2(-280,197),Vec2(290,197), Vec2(320,20), Vec2(320,-197)
            
        };
        
        enemyBody = PhysicsBody::createPolygon(spritePoints, 6,enemyMaterial);
        
    }else{
    
        enemyBody = PhysicsBody::createBox(Size(enemy->getContentSize()),enemyMaterial);
    
    }
    
    
    
    

    
            
            //重力による影響の可否
            enemyBody->setGravityEnable(false);
            //まじない
            enemyBody->setDynamic(false);
            enemyBody->setEnable(true);
            
            //カテゴリビットマスク
            enemyBody->setCategoryBitmask(0x02);
            enemyBody->setCollisionBitmask(0);
            enemyBody->setContactTestBitmask(0x01);
            
            //物理体の追加
            enemy->setPhysicsBody(enemyBody);
            
            
            return enemy;
    
}


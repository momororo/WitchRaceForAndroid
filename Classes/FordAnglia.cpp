//
//  FordAnglia.cpp
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/21.
//
//

#include "FordAnglia.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
FordAnglia* FordAnglia::fordAngliaInstance = NULL;

//シングルトン
FordAnglia* FordAnglia::getInstance(){
    
    if(!fordAngliaInstance){
        fordAngliaInstance = new FordAnglia();
    }
    
    
    return fordAngliaInstance;
    
}
//デストラクタ
void FordAnglia::destroyInstance() {
    if (fordAngliaInstance != NULL){
        delete fordAngliaInstance;
        
        fordAngliaInstance = NULL;
    }
}


//空飛ぶ車のスプライトをGET
Sprite* FordAnglia::getCharacter(){
    return fordAnglia;
}


//空飛ぶ車の動作開始
void FordAnglia::startCharacter(){
    
    fordAnglia->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//空飛ぶ車の動作停止
void FordAnglia::stopCharacter(){
    
    fordAnglia->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//空飛ぶ車の初期設定
FordAnglia::FordAnglia(){
    
    //キャラクタースプライトの生成(UP時)
    fordAnglia = Sprite::create("fordAnglia.png");
    //影
    fordAngliaShadow = Sprite::create("fordAnglia_shadow.png");
    
    //キャラクタースプライトの大きさ
    fordAnglia -> setScale(0.5);
    
    //影を実体に入れちゃう
    fordAnglia->addChild(fordAngliaShadow);
    //影のポジション調整
    fordAngliaShadow->setPosition(fordAnglia->getContentSize().width/2,fordAnglia->getContentSize().height/2);
    //影の透明度を設定
    fordAngliaShadow->setOpacity(180);
    fordAngliaShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //kikiShadow -> setScale(kiki->getScale());
    
    
    //ポジションの設定
    fordAnglia->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    fordAnglia->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    fordAnglia->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    fordAnglia->setTag(1);
    
    //物理体の生成
    auto fordAngliaMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point spritePoints[4]{
        
        Vec2(-45,-20),Vec2(-40,17),Vec2(15,22),Vec2(50,-20)
    
    };
    
    auto fordAngliaBody = PhysicsBody::createPolygon(spritePoints, 4,fordAngliaMaterial);
    
    //重力による影響の可否
    fordAngliaBody->setGravityEnable(false);
    //まじない
    fordAngliaBody->setDynamic(true);
    fordAngliaBody->setEnable(false);
    
    //ビットマスクはてきとう
    fordAngliaBody->setCategoryBitmask(0x01);
    fordAngliaBody->setCollisionBitmask(0);
    fordAngliaBody->setContactTestBitmask(0x02);
    
    fordAnglia->setPhysicsBody(fordAngliaBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    auto broomMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point broomPoint[5]={
        
        Vec2(20,20), Vec2(5,25), Vec2(5,60), Vec2(260,55), Vec2(260,20)
        
    };
    
    auto broomBody = PhysicsBody::createPolygon(broomPoint,5,broomMaterial);
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    fordAnglia -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    fordAngliaParticle = ParticleSystemQuad::create("particle_fordAnglia.plist");
    fordAngliaParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    fordAngliaParticle->setPosition(Vec2(3,fordAnglia->getContentSize().height/3-6));
    fordAngliaParticle->setName("kikiParticle");
    fordAngliaParticle->setGlobalZOrder(zOrderOfKikiShadow);
    fordAngliaParticle->cocos2d::ParticleSystem::setSpeed(500);
    fordAnglia->addChild(fordAngliaParticle);
    
}

void FordAnglia::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(fordAnglia->getPosition());
    //空飛ぶ車から親ノード(scene)取ってaddchild
    fordAnglia->getParent()->addChild(endParticle);
    //空飛ぶ車をremove
    fordAnglia->removeFromParent();
    
}

void FordAnglia::makeGameClear(){
    //パーティクルを飛ばす
    auto action = MoveTo::create(1, Vec2(selfFrame.width * 1.5, fordAnglia->getPositionY()));
    
    auto remove = RemoveSelf::create(true);
    
    //フェードアウト->削除のアニメーション開始
    fordAnglia->runAction(Sequence::create(action, remove, NULL));
}




//空飛ぶ車の1フレーム毎の処理
void FordAnglia::characterUpdate(bool tappedFlag){
    

    CCLOG("回転:%f",pRotate);

    
    
    //タップされている場合は上昇！
    if (tappedFlag == true) {
        
        
        
        //fordAngliaParticle->cocos2d::ParticleSystem::setSpeed(500);
        
        
        
        //透明度を変更
        if(fordAngliaShadow->getOpacity() != 255){
            
            fordAngliaShadow->setOpacity(255);
            
        }
        
        //画像の交換(下降画像の場合のみ)
        if(fordAnglia->getTag() == 0){
            
            fordAnglia->setTexture("fordAnglia.png");
            fordAngliaShadow->setTexture("fordAnglia_shadow.png");
            //タグを上昇状態へ変更
            fordAnglia->setTag(1);
            
        }
        
        if (pGravity>700) {
            
            pGravity = 700;
            
        }else{
            
            //下降時はより強く
            if(pGravity < -200){
                
                pGravity+= 15;
                
            }else{
                
                pGravity+= 11;
                
                
            }
            
            
        }
        
        if (pRotate < -30) {
            
            pRotate = -30;
        
        }else if (pRotate < -4){
            
            pRotate -= 1;
        
        }else if(pRotate > 5){
            
            pRotate -= 1;
        
        }else{
        
            pRotate -= 0.4;
            
        }
        
    
        fordAnglia->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        fordAnglia -> setRotation(pRotate);
        fordAngliaParticle->setRotation(-pRotate);
        
    }else{
        
        
        //タップされていない場合は下降！
        
        //kikiParticle->cocos2d::ParticleSystem::setSpeed(300);
        
        
        
        
        //透明度を変更
        if(fordAngliaShadow->getOpacity() != 180){
            fordAngliaShadow->setOpacity(180);
        }
        
        
        
        //画像の交換(上昇画像の場合のみ)
        if(fordAnglia->getTag() == 1){
            
            fordAnglia->setTexture("fordAnglia.png");
            fordAngliaShadow->setTexture("fordAnglia_shadow.png");
            //タグを下降状態へ変更
            fordAnglia->setTag(0);
        }
        
        
        if (pGravity<-700) {
            
            pGravity = -700;
            
        }else{
            
            //上昇時はより強く
            if(pGravity > 200){
                
                pGravity -= 15;
                
            }else{
                
                pGravity -= 10;
                
            }
            
            
        }
        
        
        if (pRotate > 30) {
            
            pRotate = 30;
        
        }else if(pRotate < -4) {
            
            pRotate += 1;
        
        }else if (pRotate > 5){
            
            pRotate += 1;
        
        }else{
            
            pRotate += 0.35;
            
        }
        
        
        fordAnglia->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        fordAnglia -> setRotation(pRotate);
        fordAngliaParticle->setRotation(-pRotate);
        
    }
    
}

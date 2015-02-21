//
//  HarryPotter.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "HarryPotter.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
HarryPotter* HarryPotter::harryPotterInstance = NULL;

//シングルトン
HarryPotter* HarryPotter::getInstance(){
    
    if(!harryPotterInstance){
        harryPotterInstance = new HarryPotter();
    }
    
    
    return harryPotterInstance;
    
}
//デストラクタ
void HarryPotter::destroyInstance() {
    if (harryPotterInstance != NULL){
        delete harryPotterInstance;
        
        harryPotterInstance = NULL;
    }
}


//ハリーポッターのスプライトをGET
Sprite* HarryPotter::getCharacter(){
    return harryPotter;
}


//ハリーポッターの動作開始
void HarryPotter::startCharacter(){
    
    harryPotter->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//ハリーポッターの動作停止
void HarryPotter::stopCharacter(){
    
    harryPotter->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//ハリーポッターの初期設定
HarryPotter::HarryPotter(){
 
    //キャラクタースプライトの生成(UP時)
    harryPotter = Sprite::create("harryPotter.png");
    //影
    harryPotterShadow = Sprite::create("harryPotter_shadow.png");
    
    //キャラクタースプライトの大きさ
    harryPotter -> setScale(0.5);
    
    //影を実体に入れちゃう
    harryPotter->addChild(harryPotterShadow);
    //影のポジション調整
    harryPotterShadow->setPosition(harryPotter->getContentSize().width/2,harryPotter->getContentSize().height/2);
    //影の透明度を設定
    harryPotterShadow->setOpacity(180);
    harryPotterShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //harryPotterShadow -> setScale(harryPotter->getScale());

    
    //ポジションの設定
    harryPotter->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    harryPotter->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    harryPotter->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    harryPotter->setTag(1);
    
    //物理体の生成
    auto harryPotterMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    //auto harryPotterBody = PhysicsBody::createCircle((harryPotter->getContentSize().width/2),harryPotterMaterial);

    
    
    Point spritePoints[8]={
    
        Vec2(-8,-20),Vec2(-40,-5),Vec2(-20,20), Vec2(-5,22),Vec2(13,13),Vec2(15,-5)
    
    };
    
    auto harryPotterBody = PhysicsBody::createPolygon(spritePoints, 8,harryPotterMaterial);
    
    //重力による影響の可否
    harryPotterBody->setGravityEnable(false);
    //まじない
    harryPotterBody->setDynamic(true);
    harryPotterBody->setEnable(false);

    //ビットマスクはてきとう
    harryPotterBody->setCategoryBitmask(0x01);
    harryPotterBody->setCollisionBitmask(0);
    harryPotterBody->setContactTestBitmask(0x02);
    
    harryPotter->setPhysicsBody(harryPotterBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    auto broomMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point broomPoint[4]={
        
        Vec2(23,5), Vec2(0,15), Vec2(30,25), Vec2(150,32)
    
    };
    
    auto broomBody = PhysicsBody::createPolygon(broomPoint,4,broomMaterial);
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    harryPotter -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    harryPotterParticle = ParticleSystemQuad::create("kikiparticle.plist");
    harryPotterParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    harryPotterParticle->setPosition(Vec2(3,harryPotter->getContentSize().height/3-6));
    harryPotterParticle->setName("kikiParticle");
    harryPotterParticle->setGlobalZOrder(zOrderOfKikiShadow);
    harryPotter->addChild(harryPotterParticle);
    
}

void HarryPotter::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(harryPotter->getPosition());
    //ハリーポッターから親ノード(scene)取ってaddchild
    harryPotter->getParent()->addChild(endParticle);
    //ハリーポッターをremove
    harryPotter->removeFromParent();

}

void HarryPotter::makeGameClear(){
    //パーティクルを飛ばす
    auto action = MoveTo::create(1, Vec2(selfFrame.width * 1.5, harryPotter->getPositionY()));
    
    auto remove = RemoveSelf::create(true);
    
    //フェードアウト->削除のアニメーション開始
    harryPotter->runAction(Sequence::create(action, remove, NULL));
}




//ハリーポッターの1フレーム毎の処理
void HarryPotter::characterUpdate(bool tappedFlag){
    
    CCLOG("重力:%d",pGravity);
    CCLOG("回転:%f",pRotate);
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            
            
            harryPotterParticle->cocos2d::ParticleSystem::setSpeed(500);
            
            
            
            //透明度を変更
            if(harryPotterShadow->getOpacity() != 255){
            
                harryPotterShadow->setOpacity(255);
            
            }

            //画像の交換(下降画像の場合のみ)
            if(harryPotter->getTag() == 0){

                harryPotter->setTexture("harryPotter.png");
                harryPotterShadow->setTexture("harryPotter_shadow.png");
                //タグを上昇状態へ変更
                harryPotter->setTag(1);
            
            }
            
            if (pGravity>700) {
                
                pGravity = 700;
                
            }else{
                
                //下降時はより強く
                if(pGravity < 0){

                    pGravity+= 15;
                    
                }else{

                    pGravity+= 11;
                    
                }
                
            }
            
            if (pRotate < -30) {
                
                pRotate = -30;
                
            }else if(pRotate > 10){
                
                pRotate -= 1;
                
            }else{
                
                pRotate -= 0.4;
                
            }
            
            
            harryPotter->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            harryPotter -> setRotation(pRotate);
            harryPotterParticle->setRotation(-pRotate);

            
        }else{
            
            
            //タップされていない場合は下降！
        
            //harryPotterParticle->cocos2d::ParticleSystem::setSpeed(300);


            
            
            //透明度を変更
            if(harryPotterShadow->getOpacity() != 180){
                harryPotterShadow->setOpacity(180);
            }


            
            //画像の交換(上昇画像の場合のみ)
            if(harryPotter->getTag() == 1){
                
                harryPotter->setTexture("harryPotter.png");
                harryPotterShadow->setTexture("harryPotter_shadow.png");
                //タグを下降状態へ変更
                harryPotter->setTag(0);
            }

            
            if (pGravity<-700) {
                
                pGravity = -700;
                
            }else{
                
                //上昇時はより強く
                if(pGravity > 0){

                    pGravity -= 15;
                    
                }else{

                    pGravity -= 10;
                    
                }
                
                
            }
            
            if (pRotate > 30) {
                
                pRotate = 30;
                
            }if (pRotate < -10) {
                
                pRotate += 1;
                
            }else{
                
                pRotate += 0.35;
                
            }
            
            
            
            
            harryPotter->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            harryPotter -> setRotation(pRotate);
            harryPotterParticle->setRotation(-pRotate);


            
            
        }
        
}

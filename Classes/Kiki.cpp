//
//  Kiki.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "Kiki.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
Kiki* Kiki::kikiInstance = NULL;

//シングルトン
Kiki* Kiki::getInstance(){
    
    if(!kikiInstance){
        kikiInstance = new Kiki();
    }
    
    
    return kikiInstance;
    
}
//デストラクタ
void Kiki::destroyInstance() {
    if (kikiInstance != NULL){
        delete kikiInstance;
        
        kikiInstance = NULL;
    }
}


//キキちゃんのスプライトをGET
Sprite* Kiki::getCharacter(){
    return kiki;
}


//キキちゃんの動作開始
void Kiki::startCharacter(){
    
    kiki->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//キキちゃんの動作停止
void Kiki::stopCharacter(){
    
    kiki->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//キキちゃんの初期設定
Kiki::Kiki(){
 
    //キャラクタースプライトの生成(UP時)
    kiki = Sprite::create("kiki_up.png");
    //影
    kikiShadow = Sprite::create("kiki_up_shadow.png");
    
    //キャラクタースプライトの大きさ
    kiki -> setScale(0.5);
    
    //影を実体に入れちゃう
    kiki->addChild(kikiShadow);
    //影のポジション調整
    kikiShadow->setPosition(kiki->getContentSize().width/2,kiki->getContentSize().height/2);
    //影の透明度を設定
    kikiShadow->setOpacity(180);
    kikiShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //kikiShadow -> setScale(kiki->getScale());

    
    //ポジションの設定
    kiki->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    kiki->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    kiki->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    kiki->setTag(1);
    
    //物理体の生成
    auto kikiMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    //auto kikiBody = PhysicsBody::createCircle((kiki->getContentSize().width/2),kikiMaterial);

    
    
    Point spritePoints[5]={
    
        //Vec2(-10,-22),Vec2(-18,0),Vec2(-10,20),Vec2(15,15),Vec2(10,-20)
        Vec2(-8,-20),Vec2(-16,0),Vec2(-8,18),Vec2(13,13),Vec2(8,-18)
    
    };
    
    auto kikiBody = PhysicsBody::createPolygon(spritePoints, 5,kikiMaterial);
    
    //重力による影響の可否
    kikiBody->setGravityEnable(false);
    //まじない
    kikiBody->setDynamic(true);
    kikiBody->setEnable(false);

    //ビットマスクはてきとう
    kikiBody->setCategoryBitmask(0x01);
    kikiBody->setCollisionBitmask(0);
    kikiBody->setContactTestBitmask(0x02);
    
    kiki->setPhysicsBody(kikiBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    auto broomMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point broomPoint[3]={
        
        //Vec2(0,0), Vec2(0,40), Vec2(180,35)
        Vec2(10,5), Vec2(10,35), Vec2(160,35),
    
    };
    
    auto broomBody = PhysicsBody::createPolygon(broomPoint,3,broomMaterial);
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    kiki -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    kikiParticle = ParticleSystemQuad::create("kikiparticle.plist");
    kikiParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    kikiParticle->setPosition(Vec2(3,kiki->getContentSize().height/3-6));
    kikiParticle->setName("kikiParticle");
    kikiParticle->setGlobalZOrder(zOrderOfKikiShadow);
    kiki->addChild(kikiParticle);
    
}

void Kiki::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(kiki->getPosition());
    //キキから親ノード(scene)取ってaddchild
    kiki->getParent()->addChild(endParticle);
    //キキをremove
    kiki->removeFromParent();

}

void Kiki::makeGameClear(){
    //パーティクルを飛ばす
    auto action = MoveTo::create(1, Vec2(selfFrame.width * 1.5, kiki->getPositionY()));
    
    auto remove = RemoveSelf::create(true);
    
    //フェードアウト->削除のアニメーション開始
    kiki->runAction(Sequence::create(action, remove, NULL));
}




//キキちゃんの1フレーム毎の処理
void Kiki::characterUpdate(bool tappedFlag){
    
    CCLOG("重力:%d",pGravity);

    
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            
            
            kikiParticle->cocos2d::ParticleSystem::setSpeed(500);
            
            
            
            //透明度を変更
            if(kikiShadow->getOpacity() != 255){
            
                kikiShadow->setOpacity(255);
            
            }

            //画像の交換(下降画像の場合のみ)
            if(kiki->getTag() == 0){

                kiki->setTexture("kiki_up.png");
                kikiShadow->setTexture("kiki_up_shadow.png");
                //タグを上昇状態へ変更
                kiki->setTag(1);
            
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
            
            
            kiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
        }else{
            
            
            //タップされていない場合は下降！
        
            //kikiParticle->cocos2d::ParticleSystem::setSpeed(300);


            
            
            //透明度を変更
            if(kikiShadow->getOpacity() != 180){
                kikiShadow->setOpacity(180);
            }


            
            //画像の交換(上昇画像の場合のみ)
            if(kiki->getTag() == 1){
                
                kiki->setTexture("kiki_down.png");
                kikiShadow->setTexture("kiki_down_shadow.png");
                //タグを下降状態へ変更
                kiki->setTag(0);
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
            
            kiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));

            
            
        }
        
}

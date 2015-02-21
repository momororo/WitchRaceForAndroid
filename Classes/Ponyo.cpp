//
//  Ponyo.cpp
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/31.
//
//

#include "Ponyo.h"

#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
Ponyo* Ponyo::ponyoInstance = NULL;

//シングルトン
Ponyo* Ponyo::getInstance(){
    
    if(!ponyoInstance){
        ponyoInstance = new Ponyo();
    }
    
    
    return ponyoInstance;
    
}
//デストラクタ
void Ponyo::destroyInstance() {
    if (ponyoInstance != NULL){
        delete ponyoInstance;
        
        ponyoInstance = NULL;
    }
}


//ポニョのスプライトをGET
Sprite* Ponyo::getCharacter(){
    return ponyo;
}


//ポニョの動作開始
void Ponyo::startCharacter(){
    
    ponyo->getPhysicsBody()->setEnable(true);
    
}

//ポニョの動作停止
void Ponyo::stopCharacter(){
    
    ponyo->getPhysicsBody()->setEnable(false);
    
}


//ポニョの初期設定
Ponyo::Ponyo(){
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ponyo.plist");
    
    //キャラクタースプライトの生成(UP時)
    ponyo = Sprite::createWithSpriteFrameName("ponyo_left.png");
    //影
    ponyoShadow = Sprite::createWithSpriteFrameName("ponyo_shadow_left.png");
    
    CCLOG("width : %f",ponyo->getContentSize().width);
    CCLOG("height : %f",ponyo->getContentSize().height);
    
    //キャラクタースプライトの大きさ
    ponyo -> setScale(0.5);
    
    //影を実体に入れちゃう
    ponyo->addChild(ponyoShadow);
    //影のポジション調整
    ponyoShadow->setPosition(Vec2(ponyo->getContentSize().width/2,ponyo->getContentSize().height/2));
    //影の透明度を設定
    ponyoShadow->setOpacity(180);
    ponyoShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //kikiShadow -> setScale(kiki->getScale());
    
    
    //ポジションの設定
    ponyo->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    ponyo->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    ponyo->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    ponyo->setTag(1);
    
    //物理体の生成
    auto ponyoMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point spritePoints[5]{
        
        Vec2(-15,-15),Vec2(-18,5),Vec2(0,20),Vec2(10,15),Vec2(18,-22)
        
    };
    
    auto ponyoBody = PhysicsBody::createPolygon(spritePoints, 5,ponyoMaterial);
    
    //重力による影響の可否
    ponyoBody->setGravityEnable(false);
    //まじない
    ponyoBody->setDynamic(true);
    ponyoBody->setEnable(true);
    
    //ビットマスクはてきとう
    ponyoBody->setCategoryBitmask(0x01);
    ponyoBody->setCollisionBitmask(0);
    ponyoBody->setContactTestBitmask(0x02);
    
    ponyo->setPhysicsBody(ponyoBody);
    
    
   
    
        /////////////////// ポニョ本体のアニメーション //////////////////
    
        //アニメーション用配列を用意
        auto  ponyoFrames = new Vector<SpriteFrame*>();
        std::string ponyoName;
    
        //画像２枚を配列にセットする
        //画像をすべて(2枚)を取り出せるよう、ループ文を使用
        for (int i = 1; i < 5;i++ ) {
        
            switch (i) {
                case 1: ponyoName = StringUtils::format("ponyo_left.png");break;
                case 2: ponyoName = StringUtils::format("ponyo_center.png");break;
                case 3: ponyoName = StringUtils::format("ponyo_right.png");break;
                case 4: ponyoName = StringUtils::format("ponyo_center.png");break;
                default:break;
            }
        
            SpriteFrame *spPonyoFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ponyoName);

            ponyoFrames -> pushBack(spPonyoFrame);
        
        }
    
        //アニメーションの設定
        Animation *ponyoAnimation = Animation::createWithSpriteFrames(*ponyoFrames,0.1f);
        Animate *ponyoAnimate = Animate::create(ponyoAnimation);
        RepeatForever *repeat = RepeatForever::create(ponyoAnimate);
        ponyo -> runAction(repeat);
        delete ponyoFrames;
    
        ////////////////////////// ポニョ本体のアニメーション　終 ///////////////////////////
    
        ///////////////////////// ポニョ影のアニメーション ////////////////////////////////
        //アニメーション用配列を用意
        auto  ponyoShadowFrames = new Vector<SpriteFrame*>();
        std::string ponyoShadowName;
    
        //画像２枚を配列にセットする
        //画像をすべて(2枚)を取り出せるよう、ループ文を使用
        for (int i = 1; i < 5;i++ ) {
        
            switch (i) {
                case 1: ponyoShadowName = StringUtils::format("ponyo_shadow_left.png");break;
                case 2: ponyoShadowName = StringUtils::format("ponyo_shadow_center.png");break;
                case 3: ponyoShadowName = StringUtils::format("ponyo_shadow_right.png");break;
                case 4: ponyoShadowName = StringUtils::format("ponyo_shadow_center.png");break;
                default:break;
            }
        
            SpriteFrame *spPonyoShadowFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ponyoShadowName);
        
            ponyoShadowFrames -> pushBack(spPonyoShadowFrame);
        
        }
    
        //アニメーションの設定
        Animation *ponyoShadowAnimation = Animation::createWithSpriteFrames(*ponyoShadowFrames,0.1f);
        Animate *ponyoShadowAnimate = Animate::create(ponyoShadowAnimation);
        RepeatForever *repeatShadow = RepeatForever::create(ponyoShadowAnimate);
        ponyoShadow -> runAction(repeatShadow);
        delete ponyoShadowFrames;
    
        ////////////////////////////// ポニョ影のアニメーション　終 ///////////////////////////////////
        
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    ponyoParticle = ParticleSystemQuad::create("particle_ponyo.plist");
    ponyoParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    ponyoParticle->setPosition(Vec2(-300,-800));
    ponyoParticle->setName("kikiParticle");
    ponyoParticle->setGlobalZOrder(zOrderOfKikiShadow);
    ponyoParticle->cocos2d::ParticleSystem::setSpeed(500);
    ponyo->addChild(ponyoParticle);
    
    auto runPonyoParticle = ParticleSystemQuad::create("particle_runPonyo.plist");
    runPonyoParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    runPonyoParticle->setPosition(Vec2(ponyo->getContentSize().width/2,-5));
    runPonyoParticle->setName("runPonyoParticle");
    runPonyoParticle->setGlobalZOrder(zOrderOfKiki);
    ponyo->addChild(runPonyoParticle);
    
    auto fish = Sprite::create("fish.png");
    fish -> setPosition(Vec2(-selfFrame.width/3,-selfFrame.height/8));
    fish -> setOpacity(200);
    fish -> setScale(2);
    ponyo->addChild(fish);
    
}

void Ponyo::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(ponyo->getPosition());
    //ポニョから親ノード(scene)取ってaddchild
    ponyo->getParent()->addChild(endParticle);
    //ポニョをremove
    ponyo->removeFromParent();
    
}

//gameClearの処理
void Ponyo::makeGameClear(){
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(ponyo->getPosition());
    //ポニョから親ノード(scene)取ってaddchild
    ponyo->getParent()->addChild(endParticle);
    //ポニョをremove
    ponyo->removeFromParent();
    
}




//ポニョの1フレーム毎の処理
void Ponyo::characterUpdate(bool tappedFlag){
    
    
    CCLOG("回転:%f",pRotate);
    
    
    
    //タップされている場合は上昇！
    if (tappedFlag == true) {
        
        
        
        //ponyoParticle->cocos2d::ParticleSystem::setSpeed(500);
        
        
        
        //透明度を変更
        if(ponyoShadow->getOpacity() != 255){
            
            ponyoShadow->setOpacity(255);
            
        }
        
        //画像の交換(下降画像の場合のみ)
        if(ponyo->getTag() == 0){
            
            //ponyo->setTexture("ponyo.png");
            //ponyoShadow->setTexture("ponyo_shadow.png");
            //タグを上昇状態へ変更
            ponyo->setTag(1);
            
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
            
        }else if(pRotate > 10){
            
            pRotate -= 1;
            
        }else{
            
            pRotate -= 0.4;
            
        }
        
        
        ponyo->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        ponyoParticle->setRotation(-pRotate);
        ponyo -> setRotation(pRotate);
        ponyo -> getChildByName("runPonyoParticle")->setRotation(-pRotate);
        
    }else{
        
        
        //タップされていない場合は下降！
        
        //kikiParticle->cocos2d::ParticleSystem::setSpeed(300);
        
        
        
        
        //透明度を変更
        if(ponyoShadow->getOpacity() != 180){
            ponyoShadow->setOpacity(180);
        }
        
        
        
        //画像の交換(上昇画像の場合のみ)
        if(ponyo->getTag() == 1){
            
            //ponyo->setTexture("ponyo.png");
            //ponyoShadow->setTexture("ponyo_shadow.png");
            //タグを下降状態へ変更
            ponyo->setTag(0);
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
            
        }if (pRotate < -10) {
            
            pRotate += 1;
            
        }else{
            
            pRotate += 0.35;
            
        }
        
        ponyo->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        ponyo -> setRotation(pRotate);
        ponyoParticle->setRotation(-pRotate);
        ponyo -> getChildByName("runPonyoParticle")->setRotation(-pRotate);
        
    }
    
}
/*
 * NativeLauncher.cpp
 *
 *  Created on: 2015/02/21
 *      Author: yasutomo
 */


#include "NativeLauncher.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define CocosLog "org/cocos2dx/cpp/CocosLog"
#define CocosUtil "org/cocos2dx/cpp/CocosUtil"

//レビューに誘導
void NativeLauncher::openReview(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosUtil, "openReview", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NativeLauncher::openTweetDialog(const char *$tweet){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosUtil, "openTweetDialog", "(Ljava/lang/String;)V")) {
		jstring jTweet = t.env->NewStringUTF($tweet);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jTweet);
		t.env->DeleteLocalRef(jTweet);
		t.env->DeleteLocalRef(t.classID);
	}
}

//TODO 実装
void NativeLauncher::loginGameCenter(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosUtil, "loginGameCenter", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NativeLauncher::openRanking(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosUtil, "openRanking", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NativeLauncher::postHighScore(std::string key ,int score){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosUtil, "postHighScore", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NativeLauncher::debugLog(const char *tag, const char *msg){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosLog, "debug", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring jTag = t.env->NewStringUTF(tag);
		jstring jMsg = t.env->NewStringUTF(msg);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jTag, jMsg);
		t.env->DeleteLocalRef(jTag);
		t.env->DeleteLocalRef(jMsg);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NativeLauncher::debugError(const char *tag, const char *msg){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosLog, "error", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring jTag = t.env->NewStringUTF(tag);
		jstring jMsg = t.env->NewStringUTF(msg);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jTag, jMsg);
		t.env->DeleteLocalRef(jTag);
		t.env->DeleteLocalRef(jMsg);
		t.env->DeleteLocalRef(t.classID);
	}
}

int NativeLauncher::getRandom(int max) {
	cocos2d::JniMethodInfo t;
	int random = 0;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CocosUtil, "getRandom", "(I)I")) {
		random = t.env->CallStaticIntMethod(t.classID, t.methodID, max);
		t.env->DeleteLocalRef(t.classID);
	}
	return random;
}

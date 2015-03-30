//
//  NativeLauncher.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/16.
//
//

#ifndef WitchRace_NativeLauncher_h
#define WitchRace_NativeLauncher_h
#include <string>


class NativeLauncher{
public:
    //レビュー誘導
    static void openReview();
    
    //Game Center
    static void loginGameCenter();
    static void openRanking();
    static void postHighScore(std::string key ,int score);
    
    //twitter
    static void openTweetDialog(const char* $tweet);

    static void debugLog(const char *tag, const char *msg);
    static void debugError(const char *tag, const char *msg);
    static int getRandom(int max);
};

#endif

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface GameCenter : NSObject

// GameCenter
+(void)loginGameCenter;
+(void)openRanking;
+(void)postHighScore:(NSString*)key score:(int)score;

@end
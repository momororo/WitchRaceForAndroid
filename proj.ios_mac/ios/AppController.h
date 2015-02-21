#import <UIKit/UIKit.h>
#import <Parse/Parse.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    PFObject *accessData;
}

@property(nonatomic, readonly) RootViewController* viewController;



@end


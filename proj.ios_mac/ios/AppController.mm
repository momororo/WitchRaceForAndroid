/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "CCEAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    // Override point for customization after application launch.

    
//アクセス解析用
    // [Optional] Power your app with Local Datastore. For more info, go to
    // https://parse.com/docs/ios_guide#localdatastore/iOS
    [Parse enableLocalDatastore];
    
    // Initialize Parse.(データベース毎にidとkeyが違うため注意)
    [Parse setApplicationId:@"maRQM6DFh44sSk541Mb6w3NfnGeT16Xld5P1XSBr"
                  clientKey:@"ReUHby4b1vSQAmaF6kkldFI7uYJqAlDtUJIOG6pL"];
    
    // [Optional] Track statistics around application opens.
    [PFAnalytics trackAppOpenedWithLaunchOptions:launchOptions];

    //固有IDの呼び出し用に生成
    NSUUID *vendorUUID = [UIDevice currentDevice].identifierForVendor;
    
    //初期化
    accessData = nil;
    
    //ユーザー情報を検索
    PFQuery *query = [PFQuery queryWithClassName:@"AccessData"];
    [query whereKey:@"user" equalTo:vendorUUID.UUIDString];
    [query findObjectsInBackgroundWithBlock: ^(NSArray *objects, NSError *error){
      
        //検索が見つからなかった場合でもエラーは吐かないようだ
        if(!error){
        
            
            //検索が0件以外 = 登録済
            if([objects count] != 0){
                
                //データを保存
                accessData = objects[0];
                
                
            }else{

                //データを新規に追加
                accessData = [PFObject objectWithClassName:@"AccessData"];
                accessData[@"user"] = vendorUUID.UUIDString;
                
            }
            
            //cocos2d-xプロジェクトはARCが無効となっているため、メモリ管理に気をつける必要がある
            //cocos2dのクラスはフレームワークによりメモリ管理されているが、iosのクラスを使用する際は、注意しなければならない
            //BADACCESSしたらきっとたいがいメモリ管理が原因や
            [accessData retain];
            
        }
        
    }];
    
//アクセス解析用コード終

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    

    
    //データ取得前にこの処理に入った場合、エラーになるのを防ぐ為にif文つけてます
    if(accessData != nil){
        

        //保存する情報を入れて送信
        
        //各ステージのプレイ回数
        NSUserDefaults *usrDef = [NSUserDefaults standardUserDefaults];
        accessData[@"playCountFor0"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"playCountFor0"]];
        accessData[@"playCountFor1"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"playCountFor1"]];
        accessData[@"playCountFor2"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"playCountFor2"]];
        accessData[@"playCountFor3"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"playCountFor3"]];
        accessData[@"playCountFor4"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"playCountFor4"]];
        
        //各ステージのクリア回数
        accessData[@"clearCountFor0"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"clearCountFor0"]];
        accessData[@"clearCountFor1"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"clearCountFor1"]];
        accessData[@"clearCountFor2"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"clearCountFor2"]];
        accessData[@"clearCountFor3"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"clearCountFor3"]];
        accessData[@"clearCountFor4"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"clearCountFor4"]];

        
        //どこまでクリアしたか
        accessData[@"clearStory"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"clearStory"]];
        
        //プレイポイント
        accessData[@"playPoint"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"playPoint"]];
        
        //twitterのつぶやき数
        accessData[@"twitterCount"] = [NSString stringWithFormat:@"%ld",(long)[usrDef integerForKey:@"twitterCount"]];
        
        //言語設定の取得
        NSArray *languages = [NSLocale preferredLanguages];
        accessData[@"language"] = [languages objectAtIndex:0];
        
        //アクセス情報を送信
        [accessData saveInBackground];
    
    }
    
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    
    
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
    
    
}

- (void)applicationWillTerminate:(UIApplication *)application {

    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
    


}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end

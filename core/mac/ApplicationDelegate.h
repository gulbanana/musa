#import <Cocoa/Cocoa.h>

@interface ApplicationDelegate : NSObject {
    int argumentCount;
    char** arguments;
    BOOL doubleClicked;
}

@property int status;

- (ApplicationDelegate*)initWithArgumentCount:(int)argc values:(char**)argv doubleClicked:(BOOL)finderLaunch;

//- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename;
- (void)applicationDidFinishLaunching:(NSNotification *)note;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender;

- (void)resetWorkingDirectory;
@end
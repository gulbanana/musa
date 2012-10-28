#import <engine/core.h>
#import <sys/param.h> /* for MAXPATHLEN */
#import "ApplicationDelegate.h"

@implementation ApplicationDelegate

- (ApplicationDelegate*)initWithArgumentCount:(int)argc values:(char**)argv doubleClicked:(BOOL)finderLaunch
{
    self = [super init];
    if (self)
    {
        argumentCount = argc;
        arguments = argv;
        doubleClicked = finderLaunch;
    }
    
    return self;
}

//from SDLMain.m
- (void)resetWorkingDirectory
{
    char parentdir[MAXPATHLEN];
    CFURLRef url = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFURLRef url2 = CFURLCreateCopyDeletingLastPathComponent(0, url);
    if (CFURLGetFileSystemRepresentation(url2, 1, (UInt8 *)parentdir, MAXPATHLEN)) {
        chdir(parentdir);
    }
    CFRelease(url);
    CFRelease(url2);
}

//run the entire engine event loop before digressing briefly back through Cocoa
- (void)applicationDidFinishLaunching: (NSNotification *) note
{
    if (doubleClicked)
        [self resetWorkingDirectory];
    
    [self setStatus: _main(argumentCount, arguments)];
    
    [NSApp stop:self];
}

//XXX replace this with a message
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
    platform->quit();
    
    return NSTerminateCancel;
}
@end

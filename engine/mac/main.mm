#import <engine/core.h>
#import "ApplePlatform.h"
#import "ApplicationDelegate.h"

//storage for the platform global
IPlatform* platform;

int main (int argc, char **argv)
{
    /* Create platform abstraction */
    platform = new ApplePlatform();
    bool finderLaunch = (argc >= 2 && strncmp (argv[1], "-psn", 4) == 0);
    ApplicationDelegate* engineDelegate = [[ApplicationDelegate alloc]
                                           initWithArgumentCount:argc values:argv doubleClicked:finderLaunch];

    /* Start the main event loop, with callbacks */
    [NSApp setDelegate:engineDelegate];
    [NSApp run];
    int status = [engineDelegate status];
    
    /* cleanup */
    [engineDelegate release];
    delete platform;    
    return status;
}


#import <engine/core.h>
#import "NSApplication_SetAppleMenu.h"
#import "ApplePlatform.h"
using namespace std;

static void setupApplicationMenu(void)
{
    /* warning: this code is very odd */
    NSMenu *appleMenu;
    NSMenuItem *menuItem;
    NSString *title;
    NSString *appName;
    
    const NSDictionary *dict;
    
    /* Determine the application name */
    dict = (const NSDictionary *)CFBundleGetInfoDictionary(CFBundleGetMainBundle());
    if (dict)
        appName = [dict objectForKey: @"CFBundleName"];
    
    if (![appName length])
        appName = [[NSProcessInfo processInfo] processName];
    
    appleMenu = [[NSMenu alloc] initWithTitle:@""];
    
    /* Add menu items */
    title = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Hide " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
    
    menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
    
    [appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(quit:) keyEquivalent:@"q"];
    
    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [[NSApp mainMenu] addItem:menuItem];
    
    /* Tell the application object that this is now the application menu */
    [NSApp setAppleMenu:appleMenu];
    
    /* Finally give up our references to the objects */
    [appleMenu release];
    [menuItem release];
}

static void setupWindowMenu(void)
{
    NSMenu      *windowMenu;
    NSMenuItem  *windowMenuItem;
    NSMenuItem  *menuItem;
    
    windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
    
    /* "Minimize" item */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [windowMenu addItem:menuItem];
    [menuItem release];
    
    /* Put menu into the menubar */
    windowMenuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [windowMenuItem setSubmenu:windowMenu];
    [[NSApp mainMenu] addItem:windowMenuItem];
    
    /* Tell the application object that this is now the window menu */
    [NSApp setWindowsMenu:windowMenu];
    
    /* Finally give up our references to the objects */
    [windowMenu release];
    [windowMenuItem release];
}

ApplePlatform::ApplePlatform() : SDLPlatformBase()
{
    set_environment_variable("SDL_VIDEO_WINDOW_POS", "center");
    
    pool = [[NSAutoreleasePool alloc] init];    //manage memory
    
    [NSApplication sharedApplication];          //init singleton
    
    [NSApp setMainMenu:[[NSMenu alloc] init]];  //create menubar
    setupApplicationMenu();
    setupWindowMenu();
}

ApplePlatform::~ApplePlatform()
{
    [pool drain];
}

void ApplePlatform::print(string output)
{
    NSLog(@"%s", output.c_str());
}

void ApplePlatform::set_environment_variable(string variable, string value)
{
    NSString* var = [[NSString alloc] initWithCString:variable.c_str() encoding:NSUTF8StringEncoding];
    NSString* val = [[NSString alloc] initWithCString:value.c_str() encoding:NSUTF8StringEncoding];
    
    [[[NSProcessInfo processInfo] environment] setValue:val forKey:var];
    
    [var release];
    [val release];
}

string ApplePlatform::get_environment_variable(string cpp_var)
{
    const char* c_var = cpp_var.c_str();
    NSString* objc_var = [[NSString alloc] initWithCString:c_var encoding:NSUTF8StringEncoding];
    
    auto objc_val = [[[NSProcessInfo processInfo] environment] valueForKey:objc_var];
    const char* c_val = [objc_val cStringUsingEncoding:NSUTF8StringEncoding];
    string cpp_val(c_val);
    
    [objc_var release];
    [objc_val release];
    
    return cpp_val;
}

milliseconds MicrosoftPlatform::get_ticks()
{
    return GetTickCount() - _tick_offset;
}

void MicrosoftPlatform::sleep_ticks(milliseconds ttw)
{
	Sleep(ttw);
}

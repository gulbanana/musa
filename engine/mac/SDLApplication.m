#import "SDLMain.h"
#import "SDLApplication.h"
#import "SDL.h"
#include <unistd.h>

@implementation SDLApplication
/* Invoked from the Quit menu item */
- (void)quit:(id)sender
{
    /* Post a SDL_QUIT event */
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}
@end


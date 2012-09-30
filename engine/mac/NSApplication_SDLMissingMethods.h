/* For some reaon, Apple removed setAppleMenu from the headers in 10.4,
 but the method still is there and works. To avoid warnings, we declare
 it ourselves here. */
@interface NSApplication(SDLMissingMethods)
- (void)setAppleMenu:(NSMenu *)menu;
@end
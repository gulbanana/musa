#import <core/sdl/SDLPlatformBase.h>
#import <Cocoa/Cocoa.h>

class ApplePlatform : public SDLPlatformBase
{
private:
    milliseconds _tick_offset;
    NSAutoreleasePool* pool;
    
    milliseconds _get_ticks_internal();
public:
    ApplePlatform();
    ~ApplePlatform();
    
    std::string get_environment_variable(std::string variable) final;
    void set_environment_variable(std::string variable, std::string value) final;

    void println(std::string output) final;

	milliseconds get_ticks() final;
    
    FILE* fopen(std::string path, std::string mode) final;
};
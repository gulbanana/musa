#import <engine/sdl/SDLPlatformBase.h>
#import <Cocoa/Cocoa.h>

class ApplePlatform : public SDLPlatformBase
{
private:
    NSAutoreleasePool* pool;
    
public:
    ApplePlatform();
    ~ApplePlatform();
    
    std::string get_environment_variable(std::string variable) final;
    void set_environment_variable(std::string variable, std::string value) final;

    void print(std::string output) final;

	milliseconds get_ticks() final;
	void sleep_ticks(milliseconds) final;
};
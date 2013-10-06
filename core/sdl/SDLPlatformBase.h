#pragma once
#include <core/framework/IPlatform.h>

class SDLPlatformBase : public IPlatform
{
protected:
    SDLPlatformBase();
    virtual ~SDLPlatformBase();
    
public:
    virtual milliseconds get_ticks() override;
    virtual void sleep_ticks(milliseconds) override;
    virtual void quit() override;
};
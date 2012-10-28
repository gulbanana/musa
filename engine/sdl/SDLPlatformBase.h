#pragma once

class SDLPlatformBase : public IPlatform
{
protected:
    SDLPlatformBase();
    virtual ~SDLPlatformBase();
    
public:
    virtual std::string get_window_title() override;
    virtual void set_window_title(std::string title) override;
    virtual void quit() override;
};
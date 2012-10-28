#pragma once
#include <core/IPlatform.h>

class MicrosoftPlatform : public SDLPlatformBase
{
public:
    virtual void set_environment_variable(std::string variable, std::string value) final;
    virtual void print(std::string output) final;
}
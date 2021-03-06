#pragma once
#include <string>

typedef unsigned long microseconds;
typedef unsigned int milliseconds;
typedef double seconds;

//provides access to nonportable facilities
class IPlatform
{
public:
    virtual ~IPlatform() {}
    
    virtual std::string get_environment_variable(std::string variable) = 0;
    virtual void set_environment_variable(std::string variable, std::string value) = 0;
    
    virtual void println(std::string output) = 0;
    
    virtual void quit() = 0;    //XXX replace this with a message or clarify its name
    
    virtual milliseconds get_ticks() = 0;
    virtual void sleep_ticks(milliseconds) = 0;
    
    virtual FILE* fopen(std::string path, std::string mode) = 0;
};

//global platform access and entry point
extern "C" int _main(int argc, char** argv);
extern IPlatform* platform;
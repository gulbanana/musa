#include <engine/core.h>
#import <Cocoa/Cocoa.h>
using namespace std;

void debug::print(string output)
{
    NSLog(@"%s", output.c_str());
}
#include "Logger.h"
using namespace std;

unique_ptr<ofstream> Logger::_file = unique_ptr<ofstream>(new ofstream("log.txt"));

void Logger::log(string data)
{
	*_file << data << endl;
}

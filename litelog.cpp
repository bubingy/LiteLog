#include <ctime>
#include <map>
#include <iostream>
#include "litelog.h"

using namespace std;
using namespace litelog;

string
BaseLogger::getCurrentDatetime()
{
	time_t nowtime;
	nowtime = time(NULL);
	char tmp[64];
	strftime(tmp, 
             sizeof(tmp), 
             "%Y-%m-%d %H:%M:%S", 
             localtime(&nowtime));
	return tmp;
}

static const map<Level, const char*> 
LevelStr =
{
	{ Level::Debug,     "DEBUG"   },
	{ Level::Info,      "INFO"    },
	{ Level::Warn,      "WARNING" },
	{ Level::Error,     "ERROR"   },
	{ Level::Fatal,     "FATAL"   },
};

BaseLogger::LogStream BaseLogger::operator()(Level nLevel, string sTitle)
{
	return LogStream(*this, nLevel, sTitle);
}

void 
BaseLogger::endline(Level nLevel, 
                    string sTitle, 
                    string oMessage)
{
    _lock.lock();
    output(getCurrentDatetime(), LevelStr.find(nLevel)->second, sTitle, oMessage);
    _lock.unlock();
}

void 
ConsoleLogger::output(string localtime,
                      string level,
                      string title,
                      string message)
{
    cout << '[' << localtime << ']'
        << " - " << title
        << " - " << level 
        << " - " << message << endl;
    cout.flush();
}

FileLogger::FileLogger(string filename) noexcept
    : BaseLogger()
{
    _file.open(filename,
        fstream::out | fstream::app | fstream::ate);
}

FileLogger::~FileLogger()
{
    _file.flush();
    _file.close();
}

void 
FileLogger::output(string localtime,
                   string level,
                   string title,
                   string message)
{
    _file << '[' << localtime << ']'
        << " - " << title
        << " - " << level
        << " - " << message << endl;
    _file.flush();
}
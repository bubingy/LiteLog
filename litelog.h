#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <mutex>

namespace litelog {
	enum class Level { Debug, Info, Warn, Error, Fatal };

	class BaseLogger
	{
		class LogStream;

    public:
        BaseLogger() = default;

        virtual 
        ~BaseLogger() = default;

        virtual 
        LogStream operator()(Level nLevel, 
                             std::string title = "default");

    private:
        std::string 
        getCurrentDatetime();

        void
        endline(Level level, 
                std::string title, 
                std::string message);

        virtual void 
        output(std::string current_data_time,
               std::string level,
               std::string title,
               std::string message) = 0;

    private:
        std::mutex _lock;
    };

    class BaseLogger::LogStream : public std::ostringstream
    {
        BaseLogger& logger;
        Level       level;
        std::string title;

    public:
        LogStream(BaseLogger& oLogger, 
                  Level nLevel, 
                  std::string sTitle)
            : logger(oLogger), level(nLevel), title(sTitle) {};
        
        LogStream(const LogStream& ls)
            : logger(ls.logger), level(ls.level), title(ls.title) {};
        
        ~LogStream()
        {
            logger.endline(level, title, std::move(str()));
        }
    };

    class ConsoleLogger : public BaseLogger
    {
        using BaseLogger::BaseLogger;

        virtual void 
        output(std::string current_data_time,
               std::string level,
               std::string title,
               std::string message);
    };

    class FileLogger : public BaseLogger
    {
    public:
        FileLogger(std::string filename) noexcept;

        FileLogger(const FileLogger&) = delete;

        FileLogger(FileLogger&&) = delete;
        
        virtual ~FileLogger();

    private:
        virtual void 
        output(std::string current_data_time,
               std::string level,
               std::string title,
               std::string message);

    private:
        std::ofstream _file;
    };
}
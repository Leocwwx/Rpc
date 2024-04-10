#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H
#include <string>
#include <queue>
namespace rocket
{
#define DEBUGLOG(str,...)\
    std::string msg = (new LogEvent(Debug))->toString() + formatString(str,##__VA_ARGS__);\
    Logger::getLoggerInstance()->pushLog(msg);\
    Logger::getLoggerInstance()->log(); \

enum LogLevel{
    Debug = 1,
    Info = 2,
    Error = 3
};

template<typename... Args>
std::string formatString(const char* str,Args&&... args);

std::string LogLevelToString(LogLevel level);

class Logger{
public:
    Logger(){};
    Logger(LogLevel level):m_set_level(level){};
    static Logger* getLoggerInstance();
    void pushLog(const std::string& msg);
    void log();
private:
    static Logger* m_Logger;
    LogLevel m_set_level;
    std::queue<std::string> m_buffer;
};


class LogEvent{
public:
    std::string getFileName()
    {
        return m_file_name;
    }

    LogLevel getLogLevel()
    {
        return m_level;
    }
    std::string toString();
private:
    std::string m_file_name;    //  文件名
    int32_t m_file_line;   // 行号
    int32_t m_pid;  //  进程号
    int32_t m_thread_id; //  线程号

    LogLevel m_level;   //  日志级别
};

}

#endif
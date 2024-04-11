#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H
#include <string>
#include <queue>
namespace rocket
{
// template<typename... Args>
// std::string formatString(const char* str,Args&&... args);

template<typename... Args>
std::string formatString(const char* str,Args&&... args)
{
    int size = snprintf(nullptr,0,str,args...);
    std::string res;
    if(size > 0)
    {
        res.resize(size);
        snprintf(&res[0],size+1,str,args...);
    }
    return res;
}

#define DEBUGLOG(str,...)\
    std::string msg = (new rocket::LogEvent(rocket::Debug))->toString() + rocket::formatString(str,##__VA_ARGS__);\
    rocket::Logger::getLoggerInstance()->pushLog(msg);\
    rocket::Logger::getLoggerInstance()->log(); \

enum LogLevel{
    Debug = 1,
    Info = 2,
    Error = 3
};

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
    LogEvent(LogLevel level):m_level(level){};
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

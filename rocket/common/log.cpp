#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "log.h"
#include "utils.h"

namespace rocket{

// template<typename... Args>
// std::string formatString(const char* str,Args&&... args)
// {
//     int size = snprintf(nullptr,0,str,args...);
//     std::string res;
//     if(size > 0)
//     {
//         res.resize(size);
//         snprintf(res,size+1,str,args...);
//     }
//     return res;
// }

static Logger* g_logger = nullptr;

Logger* Logger::getLoggerInstance()
{
    if(!g_logger)
    {
        g_logger = new Logger();
        return g_logger;
    }
    return g_logger;
}

void Logger::pushLog(const  std::string& msg)
{
    m_buffer.push(msg);
}

void Logger::log()
{
    while(!m_buffer.empty())
    {
        std::string msg = m_buffer.front();
        m_buffer.pop();
        printf("%s",msg.c_str());
    }
}

std::string LogLevelToString(LogLevel level)
{
    std::string str_level;
    switch (level)
    {
    case Debug:
        str_level = "DEBUG";
        break;
    case Info:
        str_level = "INFO";
        break;
    case Error:
        str_level = "ERROR";
        break;
    default:
        str_level = "NOTKNOWTYPE";
        break;
    }
    return str_level;
}

std::string LogEvent::toString()
{
    //拼接时间字符串
    struct timeval now_time;
    gettimeofday(&now_time,nullptr);
    struct tm now_time_t;
    localtime_r(&(now_time.tv_sec),&now_time_t);
    char buf[128];
    strftime(buf,128,"%y-%m-%d %H:%M:%S",&now_time_t);
    std::string str_time(buf);
    int ms = now_time.tv_usec / 1000;
    str_time += "." + std::to_string(ms);

    m_pid = getPid();
    m_thread_id = getThreadId();

    std::stringstream ss;
    ss<<"["<<LogLevelToString(m_level)<<"]\t"
    <<"["<<str_time<<"]\t"
    <<"["<<m_pid<<":"<<m_thread_id<<"]\t"
    <<"["<<__FILE__<<":"<<__LINE__<<"]\t";
    return ss.str();
}

}


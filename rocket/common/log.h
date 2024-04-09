#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H
#include <string>
namespace rocket
{

template<typename... Args>
std::string formatString(const char* str,Args&&... args)
{
    int size = snprintf(nullptr,0,str,args...);
    std::string res;
    if(size > 0)
    {
        res.resize(size);
        snprintf(res,size+1,str,args...);
    }
    return res;
}
enum LogLevel{
    Debug = 1,
    Info = 2,
    Error = 3
};

class LogEvent{
public:
std::string getFileName()
{
    return m_file_name;
}

LogLevel getLogLevel()
{
    return m_log_level;
}
private:
    std::string m_file_name;    //  文件名
    int32_t m_finle_line;   // 行号
    int32_t m_pid;  //  进程号
    int32_t m_thread_id; //  线程号

    LogLevel m_log_level;   //  日志级别

};




}

#endif
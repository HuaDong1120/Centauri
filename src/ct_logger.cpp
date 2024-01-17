#include "ct_logger.h"
#include <stdexcept>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <mutex>
using namespace Centauri::Logger;
Logger* Logger::m_instance = nullptr;
const char* Logger::m_Level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERRO",
    "FATAL"
};
Logger::Logger() :m_len(0), m_max(0), levels(DEBUG)
{

}
Logger::~Logger()
{
    close();
}
void Logger::open(const std::string& filename)
{
    m_fileName = filename;
    m_fout.open(filename, std::ios::app);
    if(m_fout.fail())
    {
        throw std::logic_error("open file filed" + filename);
    }
    m_fout.seekp(0, std::ios::end);
    m_len = m_fout.tellp();
}

void Logger::close()
{
    m_fout.close();
}
Logger* Logger::getInstance()
{
    if(m_instance == nullptr)
    {
        std::mutex mtx;
        mtx.lock();
        m_instance = new Logger();
        
        mtx.unlock();
    }
    return m_instance;
}
void Logger::log(Level level, const char* fileName, int line, const char* format, ...)
{

    if(levels > level)
    {
        return;
    }
    if(m_fout.fail())
    {
        throw std::logic_error("open file failed" + m_fileName);
    }
    switch(level)
    {
    case Centauri::Logger::Logger::DEBUG:
        set_color(CONSOLE_COLOR_WHITE);
        break;
    case Centauri::Logger::Logger::INFO:
        set_color(CONSOLE_COLOR_GREEN);
        break;
    case Centauri::Logger::Logger::WARN:
        set_color(CONSOLE_COLOR_YELLOW);
        break;
    case Centauri::Logger::Logger::ERRO:
        set_color(CONSOLE_COLOR_RED);
        break;
    case Centauri::Logger::Logger::FATAL:
        set_color(CONSOLE_COLOR_RED);
        break;
    case Centauri::Logger::Logger::LEVEL_COUNT:
        break;
    default:
        break;
    }
    
    auto timeTicks = time(nullptr);
    auto ptns = localtime(&timeTicks);
    char timeArray[32];
    memset(timeArray, 0, sizeof(timeArray));
    strftime(timeArray, sizeof(timeArray), "[%Y-%m-%d %H:%M:%S]", ptns);

    const char* fmt = "%s %s %s:%d ";

    int size = snprintf(nullptr, 0, fmt, timeArray, m_Level[level], fileName, line);
    
    if(size > 0)
    {
        char* buffer = new char[size + 1];
        memset(buffer, 0, size + 1);
        
        snprintf(buffer, size + 1, fmt, timeArray, m_Level[level], fileName, line);
        
        std::cout << buffer << std::endl;
        m_fout << buffer;
        m_len += size;
        delete[]buffer;
    }

    va_list arg_ptr;
    va_start(arg_ptr, format);
    size = (vsnprintf(nullptr, 0, format, arg_ptr));
    va_end(arg_ptr);
    if(size > 0)
    {
        char* content = new char[size + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, size + 1, format, arg_ptr);
        va_end(arg_ptr);
        std::cout << content << std::endl;
        m_fout << content;
        m_len += size;
        delete[] content;
    }
    m_fout << "\n";
    m_fout.flush();
    if(m_len >= m_max && m_max > 0)
    {
        rotate();
    }
    set_color(CONSOLE_COLOR_WHITE);

}
void Logger::rotate()
{
    close();

    auto timeTicks = time(nullptr);

    auto ptns = localtime(&timeTicks);
    char timeArray[32];
    memset(timeArray, 0, sizeof(timeArray));

    strftime(timeArray, sizeof(timeArray),".%Y-%m-%d_%H-%M-%S",ptns);

    std::string filename = m_fileName + timeArray;
    if(rename(m_fileName.c_str(), filename.c_str()) != 0)
    {
        return;
    }
    open(m_fileName);

}

/*
 *File: ct_logger.h
 *------------------
 * this file exports functions for logger.
 */
#ifndef _ct_logger_h
#define _ct_logger_h
#include <string>
#include <fstream>
#include <Windows.h>
#define CONSOLE_COLOR_GREEN   2
#define CONSOLE_COLOR_RED    12
#define CONSOLE_COLOR_YELLOW 14
#define CONSOLE_COLOR_WHITE  15
namespace Centauri {
    namespace Logger {
#define debug(format,...)\
    Logger::getInstance()->log(Logger::DEBUG,__FILE__,__LINE__,format,##__VA_ARGS__);
#define info(format,...)\
    Logger::getInstance()->log(Logger::INFO,__FILE__,__LINE__,format,##__VA_ARGS__);
#define warn(format,...)\
    Logger::getInstance()->log(Logger::WARN,__FILE__,__LINE__,format,##__VA_ARGS__);
#define erro(format,...)\
    Logger::getInstance()->log(Logger::ERRO,__FILE__,__LINE__,format,##__VA_ARGS__);
#define fatal(format,...)\
    Logger::getInstance()->log(Logger::FATAL,__FILE__,__LINE__,format,##__VA_ARGS__);
        class Logger {
        public:
            enum  Level {
                DEBUG = 0,
                INFO,
                WARN,
                ERRO,
                FATAL,
                LEVEL_COUNT 
            };
            
            //open and create log file
            void open(const std::string& filename);
            //close file
            void close();
            //create Logger
            static Logger* getInstance();
            //print log
            void log(Level level, const char* fileName, int line, const char* format, ...);
            //set log level
            void setLevel(Level level)
            {
                levels = level;
            }
            //set max
            void setMax(int bytes)
            {
                m_max = bytes;
            }
            void rotate();
            //set color
            static void set_color(unsigned short color_index)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
            }

        private:
            Logger();
            ~Logger();


        private:
            //log file 
            std::string m_fileName;
            //stream
            std::ofstream m_fout;
            //log level
            static const char* m_Level[LEVEL_COUNT];
            //signal
            static Logger* m_instance;
            //level
            Level levels;
            //max length
            int m_max;
            //cur length
            int m_len;

        };
    }
    
}
#endif // !_ct_logger_h


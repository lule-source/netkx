#pragma once

#include <string>
#include "noncopyable.h"

#define LOG_INFO(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##_VA_ARGS__); \
        logger.log(buf); \
    } while (0)

#define LOG_ERROR(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while (0)

#define LOG_FATAL(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } while (0)

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(DEBUG); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while (0)
#else
#define LOG_DEBUG(logmsgFormat, ...)
#endif

enum LogLevel
{
    DEBUG,
    INFO,
    ERROR,
    FATAL
}; // NONE is a valid value for

// logger class
class Logger : noncopyable
{
public:
    // get the only instance of the logger class
    static Logger &instance();
    // set the level of logger
    void setLogLevel(int level);
    // write log
    void log(std::string msg);

private:
    int loglevel_;
}

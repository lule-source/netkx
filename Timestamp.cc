#include "Timestamp.h"
#include <time.h>

Timestamp::Timestamp() : microSecondsSinceEpoch_(0) {}
Timestamp::Timestamp(int64_t microSecondsSinceEpoch) : microSecondsSinceEpoch_(microSecondsSinceEpoch) {}

Timestamp Timestamp::now()
{
    return Timestamp(time(NULL));
}

std::string Timestamp::toString() const
{
    char buf[128] = {0};
    tm *tm_time = localtime(&microSecondsSinceEpoch_); // 创建tm对象，包括时区信息和GMT/UTC/本地时区的选择，并返回值给变量。 该函数应自动处理错误或未定义的
    snprintg(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d",
        tm_time->tm_year + 1900,
        tm_time->tm_mon + 1,
        tm_time->tm_mday,
        tm_time->tm_hour,
        tm_time->tm_min,
        tm_time->tm_sec;//将tm对象转换为字符串并将其写入字符串buf中。 该
    return buf; //返回buf的引用。
}
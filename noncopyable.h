#pragma once

/**
 *   派生类对象无法拷贝合赋值操作
 *
 */

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

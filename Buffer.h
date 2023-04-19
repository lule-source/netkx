#pragma once

#include <vector>

// 网络库底层缓冲器类型定义
class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explict Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + kInitialSize), readerIndex_(kCheapPrepend), writerIndex_(kCheapPrepend)
    {
    }

    size_t readableBytes() const
    {
        return writerIndex_ - readerIndex_;
    }

    size_t writableBytes() const
    {
        return buffer_.size() - writerIndex_;
    }

    size_t prependableBytes() const
    {
        return readerIndex_;
    }

    // return the begin address of the readable data
    const char *peek() const
    {
        return begin() + readerIndex_;
    }

    void retrieve(sizt_t len)
    {
        if (len < readableBytes())
        {
            readerIndex_ += len;
        }
        else
        {
            retrieveAll();
        }
    }

    void retrieveAll()
    {
        readerIndex_ = writerIndex_ = kCheapPrepend;
    }

    // 将onmessage上报的buffer数据， 转成string类型的数据返回
    std::string retrieveAllAsString()
    {
        return retrieveAsString(readableBytes()); //  the length of the data to be read(readable)
    }

    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len); // readed from the buffer that enable data
        retrieve(len);                   // buffer retrieve operation
        return result;
    }

    void ensureWriteableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len);
        }
    }

    // the range of data to data + len that memory data, add to the wriable buffer
    void append(const char *data, size_t len)
    {
        ensureWriteableBytes(len); // make space for len bytes data to write(writeable)
        std::copy(data, data + len, beginWrite());
        writerIndex_ += len;
    }

    const char *beginWrite() const
    {
        return begin() + writerIndex_;
    }

    // read data from fd
    ssize_t readFd(int fd, int *saveErrno);
    // send data through fd
    ssize_t writeFd(int fd, int *saveErrno);

private:
    const char *begin() const
    {
        return &*buffer_.begin();
    }

    void makeSpace(size_t len)
    {
        if (readableBytes() + writableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else
        {
            size_t readable = readableBytes();
            std::copy(
                begin() + readerIndex_,
                begin + writerIndex_,
                begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};
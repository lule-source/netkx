#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <sys/epoll.h>

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop), fd_(fd), events_(0), revents_(0), index_(0), tied_(false) {}

Channel::~Channel() {}

// tcpconnection have the new connection created be to called
void Channel::tie(const std::shared_ptr<void> &obj)
{
  tie_ = obj;
  tied_ = true;
}

// when changed the channel's fd events, update be responsible for edit fd corresponding to events epoll_ctl
void Channel::update()
{
  // through channel belongs to the eventloop. call poller's corresponding to method. register fd's events
  loop_->updateChannel(this);
}

void Channel::remove()
{
  loop_->removeChannel(this);
}

// after fd get the notify of poller, handle events
void Channel::handleEvent()
{
  if (tied_)
  {
    std::shared_ptr<void> guard = tie_.lock();
    if (guard)
    {
      handleEventWithGuard(receiveTime);
    }
  }
  else
  {
    handleEventWithGuard(receiveTime);
  }
}

// the events of based on poller's notify, the channel responsible to call detail callback operation
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
  LOG_INFO("channel handleEvent revents:%d\n", revents_)
  if (revents_ & EPOLLHUP)
    &&!(revemts_ & EPOLLIN)
    {
      if (closeCallback_)
      {
        closeCallback_();
      }
    }
  if (revents_ & EPOLLERR)
  {
    if (errorCallback_)
    {
      errorCallback_();
    }
  }
  if (revents_ & (EPOLLIN | EPOLLPRI))
  {
    if (readCallback_)
    {
      readCallback_();
    }
  }
  if (revents_ & EPOLLOUT)
  {
    if (writeCallback_)
    {
      writeCallback_();
    }
  }
}
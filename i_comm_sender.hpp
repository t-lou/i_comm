#ifndef I_COMM_SENDER_H
#define I_COMM_SENDER_H

#include <forward_list>
#include <memory>

#include "i_comm_receiver.hpp"

template <typename T>
class ICommSender {
 public:
  /// Add one receiver for this sendor.
  void AddReceiver(const std::shared_ptr<ICommReceiver<T>> receiver) {
    receivers_.push_front(receiver);
  }

  /// Send one messages for all added receivers.
  void Send(const std::shared_ptr<T> message) {
    for (const std::shared_ptr<ICommReceiver<T>>& receiver : receivers_) {
      receiver->Receive(message);
    }
  }

 protected:
  /// The added receivers.
  std::forward_list<std::shared_ptr<ICommReceiver<T>>> receivers_;
};

#endif
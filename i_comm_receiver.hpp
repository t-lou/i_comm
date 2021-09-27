#ifndef I_COMM_RECEIVER_H
#define I_COMM_RECEIVER_H

#include <cstdint>
#include <memory>
#include <queue>

template <typename T>
class ICommReceiver {
 public:
  /// Set the maximal number of messages in receiver. When the capacity is
  /// reached, receiver will stop receiveal.
  void SetCapacity(const std::size_t capacity) { capacity_ = capacity; }

  /// Checks whether there is unread message. This should always been checked
  /// before reading.
  bool IsDataAvailable() const { return !data_.empty(); }

  /// Drop old messages to allow receiving one message.
  bool Drop() {
    if (capacity_ > 0u) {
      while (data_.size() + 1u > capacity_) {
        data_.pop();
      }
    }
  }

  /// Read one message.
  std::shared_ptr<T> GetMessage() {
    if (data_.empty()) {
      return nullptr;
    }
    const std::shared_ptr<T> result{data_.front()};
    data_.pop();
    return result;
  }

  /// Callback function (for ICommSender) to get one message.
  void Receive(const std::shared_ptr<T> message) {
    if (capacity_ == 0u || capacity_ > data_.size()) {
      data_.push(message);
    }
  }

 protected:
  /// Maximal number of messages to receive. When the capacity is reached,
  /// receiver will stop receiveal.
  std::size_t capacity_{0u};
  /// Buffer to data.
  std::queue<std::shared_ptr<T>> data_;
};

#endif
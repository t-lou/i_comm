#include <cstdint>
#include <memory>
#include <string>

#include "i_comm_client.h"
#include "i_comm_master.h"
#include "i_comm_receiver.hpp"
#include "i_comm_sender.hpp"

struct Message {
  std::uint32_t second;
  std::uint32_t nanosecond;
  int content;
  Message(const std::uint32_t sec, const std::uint32_t nsec, const int value)
      : second(sec), nanosecond(nsec), content(value) {}
};

class Sender : public ICommClient {
 public:
  virtual bool IsActive() override { return number_ < limit_; }

  virtual void Proceed() override {
    std::shared_ptr<Message> message{std::make_shared<Message>(0, 1, number_)};
    std::cout << "sending " << message->content << std::endl;
    sender_->Send(message);
    ++number_;
  }

  void Register(const std::shared_ptr<ICommReceiver<Message>> receiver) {
    sender_->AddReceiver(receiver);
  }

 private:
  std::shared_ptr<ICommSender<Message>> sender_{new ICommSender<Message>{}};
  int number_{0};
  const int limit_{20};
};

class Receiver : public ICommClient {
 public:
  virtual void Proceed() override {
    while (receiver_->IsDataAvailable()) {
      std::cout << receiver_->GetMessage()->content << std::endl;
    }
  }

  virtual bool IsActive() override { return false; }

  std::shared_ptr<ICommReceiver<Message>> GetReceiver() { return receiver_; }

 private:
  std::shared_ptr<ICommReceiver<Message>> receiver_{new ICommReceiver<Message>};
};

int main(int argn, char** argv) {
  ICommMaster master{600};

  std::shared_ptr<Sender> sender{std::make_shared<Sender>()};
  master.Register(sender);

  std::shared_ptr<Receiver> receiver{std::make_shared<Receiver>()};
  master.Register(receiver);

  // sender->AddReceiver(std::string{"receiver"}, receiver);
  std::cout << "before\n";
  sender->Register(receiver->GetReceiver());
  std::cout << "after\n";

  while (master.IsActive()) {
    master.Proceed();
  }
}
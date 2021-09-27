#include "i_comm_master.h"

#include <algorithm>
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include "i_comm_client.h"

ICommMaster::ICommMaster(int wait_time_ms)
    : wait_time_ms_(wait_time_ms),
      interval_(wait_time_ms_),
      last_timestamp_(std::chrono::system_clock::now()) {}

bool ICommMaster::IsActive() {
  // when there is client and all are active
  return !clients_.empty() &&
         std::any_of(clients_.begin(), clients_.end(),
                     [](const std::shared_ptr<ICommClient>& client) {
                       return client->IsActive();
                     });
}

void ICommMaster::Proceed() {
  // all clients execute
  for (const std::shared_ptr<ICommClient>& client : clients_) {
    client->Proceed();
  }

  // sleep if there is still time
  const std::chrono::time_point<std::chrono::system_clock> now{
      std::chrono::system_clock::now()};
  if (wait_time_ms_ > 0) {
    const std::chrono::duration<double> elapsed = now - last_timestamp_;
    if (interval_ > elapsed) {
      std::this_thread::sleep_for(interval_ - elapsed);
    }
    last_timestamp_ = now;
  }
}

void ICommMaster::Register(std::shared_ptr<ICommClient> client) {
  clients_.emplace_back(std::move(client));
  client.reset();
}
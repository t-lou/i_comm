#ifndef I_COMM_MASTER_H
#define I_COMM_MASTER_H

#include <algorithm>
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include "i_comm_client.h"

class ICommMaster {
 public:
  /// Initialize the master with wait time.
  /// When sleep time is non-positive, sleep is deactivated.
  ICommMaster(int wait_time_ms = 0);

  /// Whether the system is active: all clients are active.
  bool IsActive();

  /// Proceed for all clients and sleep (optionally).
  void Proceed();

  /// Add one client in the system.
  void Register(std::shared_ptr<ICommClient> client);

 private:
  /// Milliseconds for sleep. Saved for faster checking: whether sleep is
  /// needed.
  const int wait_time_ms_;
  /// Duration computed from wait_time_ms_ .
  const std::chrono::duration<int, std::milli> interval_;
  /// Last timestamp of Proceed, used to decide sleep time.
  std::chrono::time_point<std::chrono::system_clock> last_timestamp_;
  /// The clients in this system.
  std::vector<std::shared_ptr<ICommClient>> clients_;
};

#endif
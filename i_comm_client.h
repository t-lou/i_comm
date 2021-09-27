#ifndef I_COMM_CLIENT_H
#define I_COMM_CLIENT_H

#include <cstdint>
#include <iostream>
#include <memory>

class ICommClient {
 public:
  /// The function to fullfil one functionality.
  virtual void Proceed();

  /// Virtual destructor.
  virtual ~ICommClient();

  /// Each clients must report whether they are active. When all clients are not
  /// active, the program ends.
  virtual bool IsActive();
};

#endif
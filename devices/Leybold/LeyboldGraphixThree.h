#ifndef _LEYBOLDGRAPHIXTHREE_H_
#define _LEYBOLDGRAPHIXTHREE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <cmath>

#include "VLeyboldGraphixThree.h"
#include "LeyboldComHandler.h"

class LeyboldGraphixThree : public VLeyboldGraphixThree
{
 public:

  LeyboldGraphixThree( const ioport_t );
  ~LeyboldGraphixThree();

  bool DeviceAvailable() const;

  std::string GetVersion() const;

  double GetPressure(int channel) const;

 protected:

  void SendCommand(std::string& command) const;
  bool ReceiveData(std::string& buffer) const;
  void StripBuffer(char*) const;
  void DeviceInit();

  LeyboldComHandler* comHandler_;
  bool isDeviceAvailable_;

  static constexpr const char Separator = 0x3B;
  static constexpr const char EOT       = 0x04;
  static constexpr const char SI        = 0x0F;
  static constexpr const char SO        = 0x0E;
  static constexpr const char ACK       = 0x06;
  static constexpr const char NACK      = 0x15;
};

#endif // _LEYBOLDGRAPHIXTHREE_H_

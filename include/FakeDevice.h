/* 
 * File:   FakeDevice.h
 * Author: tomko
 *
 * Created on 23 kwiecień 2012, 21:18
 */

#ifndef FAKEDEVICE_H
#define	FAKEDEVICE_H

#include <Device.h>

#include <fstream>

class FakeDevice : public Device
{
public:
  FakeDevice();
  FakeDevice(const FakeDevice& orig);
  virtual ~FakeDevice();

  void sendChar(char to_send) throw(Device::ConnectionError)
  {

  }

  void startConnection()
  {

    inf.open("fake.txt", std::ios::in);
  }

  void stopConnection()
  {
    if (inf.is_open())
    {
      inf.close();
    }
  }
  u_int32_t receiveUInt4() throw (Device::ConnectionError);
private:
  std::ifstream inf;
};

#endif	/* FAKEDEVICE_H */


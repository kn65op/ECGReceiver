/* 
 * File:   FakeDevice.cpp
 * Author: tomko
 * 
 * Created on 23 kwiecień 2012, 21:18
 */

#include "../include/FakeDevice.h"

FakeDevice::FakeDevice() : Device()
{
}

FakeDevice::FakeDevice(const FakeDevice& orig) : Device((Device) (orig))
{
}

FakeDevice::~FakeDevice()
{
}

u_int32_t FakeDevice::receiveUInt4() throw (Device::ConnectionError)
{
//  sleep(0);
  if (!inf.eof())
  {
    u_int32_t tmp;
    inf >> tmp;
    return tmp;
  }
  else
  {
    inf.close();
    inf.open("fake.txt", std::ios::in);
    return 555;
  }
}
/* 
 * File:   ECGReceiver.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 19:41
 */

#include "../include/ECGReceiver.h"

#include "../include/DeviceSelector.h"

ECGReceiver::ECGReceiver()
{
  set_title("ECGReceiver");
  set_size_request(200, 200);
  
  //przycik wyboru device
  select_device.set_label("Wybierz urządzenie");
  select_device.signal_clicked().connect(sigc::mem_fun(*this, &ECGReceiver::on_select_device_clicked));
  select_device.show();
  
  //umieszczenie elementów
  add(select_device);
}

ECGReceiver::~ECGReceiver()
{
}
//TODO: usunąć
#include <iostream>
void ECGReceiver::on_select_device_clicked()
{
  DeviceSelector ds;
  ds.run();
  std::cout << "SDASD\n";
 // device = ds.getDevice();
  //TODO pobranie wyniku
}


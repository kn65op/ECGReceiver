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

  //device_info
  name_text.set_label("Nazwa: ");
  MAC_text.set_label("MAC: ");
  
  //umieszczenie elementów
  add(main_box);
  main_box.pack_end(buttons_box);
  buttons_box.pack_start(select_device);
  main_box.pack_start(device_description_box);
  device_description_box.pack_start(name_box);
  device_description_box.pack_end(MAC_box);
  name_box.pack_start(name_text);
  name_box.pack_end(name);
  MAC_box.pack_start(MAC_text);
  MAC_box.pack_end(MAC);

  //wyświetlanie
  main_box.show_all_children(true);
  main_box.show();

  //zerowanie device
  device = 0;

  setDeviceInfo();
}

ECGReceiver::~ECGReceiver()
{
}

void ECGReceiver::on_select_device_clicked()
{
  DeviceSelector ds;
  if (ds.run() == Gtk::RESPONSE_OK)
  {
    device = ds.getDevice();
  }
  setDeviceInfo();
}

void ECGReceiver::setDeviceInfo()
{
  if (device) // jest jakieś urządzenie
  {
    name.set_label(device->getName());
    MAC.set_label(device->getMAC());
  }
  else
  {
    name.set_label("Brak urządzenia");
    MAC.set_label("Brak urządzenia");
  }
}

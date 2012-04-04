/* 
 * File:   DeviceSelector.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 20:25
 */

#include "../include/DeviceSelector.h"

#include <thread>
#include <functional>

//TODO usunąć
#include <iostream>

DeviceSelector::DeviceSelector()
{
  //przyciski
  ok.set_label("OK");
  cancel.set_label("Anuluj");
  
  //umieszczenie prezycisków
  hbox.pack_start(ok);
  hbox.pack_start(cancel);
  
  //widok listy
  scrolled_window.add(view);
  
  //umieszczenie pionowe
  vbox.pack_end(hbox);
  vbox.pack_start(scrolled_window);
  
  //umieszczenie vboxa w oknie
  Gtk::Box *tmp = get_vbox();
  tmp->add(vbox);
  
  //wyświetlenie
  tmp->show_all_children(true);
  
  //szukanie urządzeń
  //std::thread t(std::mem_fn<void, DeviceSelector>(&DeviceSelector::searchDevices));
  //std::thread t(&DeviceSelector::searchDevices, *this);
  
  //wyświetlanie urządzeń
  this->signal_devices_ready().connect(sigc::mem_fun(*this, &DeviceSelector::on_devices_ready));
}


DeviceSelector::~DeviceSelector()
{
}

void DeviceSelector::searchDevices()
{
  BluezBluetooth bt;
  bt.scanDevices();
  devices_mutex.lock();
  devices = bt.getDevices();
  devices_mutex.unlock();
  devices_ready.emit();
}

void DeviceSelector::on_devices_ready()
{
  std::cout << "Ready";
}

sigc::signal<void> DeviceSelector::signal_devices_ready()
{
  return devices_ready;
}
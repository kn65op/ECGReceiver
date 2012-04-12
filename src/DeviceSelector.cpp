/* 
 * File:   DeviceSelector.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 20:25
 */

#include "../include/DeviceSelector.h"
#include <equalMAC.h>
#include "BluezBluetooth.h"

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
  Gtk::Box *tmp = get_content_area();
  tmp->add(vbox);

  //wyświetlenie
  tmp->show_all_children(true);

  //szukanie urządzeń
  //std::thread t(std::mem_fn<void, DeviceSelector>(&DeviceSelector::searchDevices));
  btthread = new std::thread(&DeviceSelector::searchDevices, this);

  //wyświetlanie urządzeń
  this->signal_devices_ready().connect(sigc::mem_fun(*this, &DeviceSelector::on_devices_ready));

  exited = false;
}

DeviceSelector::~DeviceSelector() // na razie będzie czekanie na zakończenie szukania //TODO zmienić zakończenie threada
{
  wd = new WaitingDialog("Czekaj na zakończenie szukania urządzeń.", false);
  s_close_waiting_dialog.connect(sigc::mem_fun(*wd, &WaitingDialog::on_close_waiting_dialog));
  std::thread t(&DeviceSelector::wait_for_end, this);
  wd->run();
  t.join();
  delete wd;
  delete btthread;
  std::cout << "DELETE\n";
  for (auto d : devices)
  {
    delete d;
  }
}

void DeviceSelector::searchDevices()
{
  BluezBluetooth bt;
  bt.scanDevices();
  std::list<Device> devs;
  devices_mutex.lock();
  std::list<DeviceTreeNode*>::iterator it = devices.begin();
  for (auto d : devices) //czyszczenie nowej i starej listy urządzeń
  {
    if (!bt.deleteByMAC(d->getMAC())) // jeśli nie usunięto (tzn. nie ma już urządzenia) to usuwamy z aktualnej listy.
    {
      it = devices.erase(it);
    }
    else
    {
      ++it;
    }

  }
  devs = bt.getDevices();
  for (auto d: devs) //dodawanie nowych elementów do listy (tych, które zostały na liście)
  {
    devices.push_back(new DeviceTreeNode(d));
  }
  devices_mutex.unlock();
  devices_ready.emit();
  std::cout << "EMMITED\n";
}

void DeviceSelector::on_devices_ready()
{
  std::cout << "READY\n";
}

sigc::signal<void> DeviceSelector::signal_devices_ready()
{
  return devices_ready;
}

void DeviceSelector::wait_for_end()
{
  btthread->join();
  s_close_waiting_dialog.emit();
  std::cout << "EMMITED\n";
}
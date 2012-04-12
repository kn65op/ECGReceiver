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
  ref_tree_model = Gtk::ListStore::create(dtn);
  view.set_model(ref_tree_model);

  //kolumny
  view.append_column("Nazwa", dtn.col_name);
  view.append_column("MAC", dtn.col_MAC);

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
  btthread2 = 0;

  //wyświetlanie urządzeń
  this->signal_devices_ready().connect(sigc::mem_fun(*this, &DeviceSelector::on_devices_ready));

  exiting = exited = false;
}

DeviceSelector::~DeviceSelector() // na razie będzie czekanie na zakończenie szukania //TODO zmienić zakończenie threada
{
  exiting = true;
  wd = new WaitingDialog("Czekaj na zakończenie szukania urządzeń.", false);
  s_close_waiting_dialog.connect(sigc::mem_fun(*wd, &WaitingDialog::on_close_waiting_dialog));
  std::thread t(&DeviceSelector::wait_for_end, this);
  wd->run();
  t.join();
  delete wd;
  if (btthread) delete btthread;
  if (btthread2) delete btthread2;
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
  std::list<Device*>::iterator it = devices.begin();
  Gtk::ListStore::iterator modit = ref_tree_model->children().begin();
  while (it != devices.end()) //czyszczenie nowej i starej listy urządzeń
  {
    if (!bt.deleteByMAC((*it)->getMAC())) // jeśli nie usunięto (tzn. nie ma już urządzenia) to usuwamy z aktualnej listy.
    {
      it = devices.erase(it);
      modit = ref_tree_model->erase(modit);
    }
    else
    {
      ++it;
      ++modit;
    }

  }
  devs = bt.getDevices();
  Gtk::TreeModel::Row row;
  for (auto d : devs) //dodawanie nowych elementów do listy (tych, które zostały na liście)
  {
    devices.push_back(new Device(d));
    row = *(ref_tree_model->append());
    row[dtn.col_name] = devices.back()->getName();
    row[dtn.col_MAC] = devices.back()->getMAC();
  }
  devices_mutex.unlock();
  devices_ready.emit();
  std::cout << "EMMITED\n";
}

void DeviceSelector::on_devices_ready()
{
  if (btthread2)
  {
    btthread2->join();
    delete btthread2;
  }
  btthread2 = new std::thread(&DeviceSelector::restart, this);
}

sigc::signal<void> DeviceSelector::signal_devices_ready()
{
  return devices_ready;
}

void DeviceSelector::wait_for_end()
{
  btthread->join();
  btthread2->join();
  s_close_waiting_dialog.emit();
  std::cout << "EMMITED\n";
}

void DeviceSelector::restart()
{
  if (exiting)
  {
    return;
  }
  if (btthread)
  {
    btthread->join();
    delete btthread;
  }
  btthread = new std::thread(&DeviceSelector::searchDevices, this);
}
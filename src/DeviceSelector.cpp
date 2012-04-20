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
  //domyślny rozmiar okna
  set_default_size(600, 300);
  //przyciski
  ok.set_label("OK");
  ok.set_sensitive(false);
  cancel.set_label("Anuluj");
  start_search.set_label("Szukaj urządzeń");

  //umieszczenie prezycisków
  hbox.pack_start(ok);
  hbox.pack_start(cancel);
  hbox.pack_start(start_search);

  //łączenie przycisków z akcjami
  start_search.signal_clicked().connect(sigc::mem_fun(*this, &DeviceSelector::start_search_clicked));
  ok.signal_clicked().connect(sigc::mem_fun(*this, &DeviceSelector::ok_clicked));
  cancel.signal_clicked().connect(sigc::mem_fun(*this, &DeviceSelector::cancel_clicked));


  //widok listy
  scrolled_window.add(view);
  ref_tree_model = Gtk::ListStore::create(dtn);
  view.set_model(ref_tree_model);
  scrolled_window.set_size_request(400, 300);

  //kolumny
  view.append_column("Nazwa", dtn.col_name);
  view.append_column("MAC", dtn.col_MAC);

  //umieszczenie pionowe
  //vbox.pack_start(scrolled_window, Gtk::PACK_EXPAND_PADDING);
  //vbox.pack_end(hbox, Gtk::PACK_SHRINK);

  //umieszczenie vboxa w oknie
  Gtk::Box *tmp = get_content_area();
  tmp->pack_start(scrolled_window, Gtk::PACK_EXPAND_PADDING);
  tmp->pack_end(hbox, Gtk::PACK_SHRINK);
  //tmp->pack_start(vbox, Gtk::PACK_EXPAND_WIDGET);

  //wyświetlenie
  tmp->show_all_children(true);

  //wyświetlanie urządzeń
  this->signal_devices_ready().connect(sigc::mem_fun(*this, &DeviceSelector::on_devices_ready));

  exiting = exited = false;

  //szukanie urządzeń
  search();
}

DeviceSelector::~DeviceSelector() // na razie będzie czekanie na zakończenie szukania //TODO zmienić zakończenie threada
{
  quit();
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
    if (bt.deleteByMAC((*it)->getMAC())) // jeśli usunięto z nowej listy to (tzn. nie ma już urządzenia) to usuwamy z aktualnej listy.
    {
      ++it;
      ++modit;
    }
    else
    {
      it = devices.erase(it);
      modit = ref_tree_model->erase(modit);
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
  if (bt.size() > 0)
  {
    ok.set_sensitive(true);
  }
  else
  {
    ok.set_sensitive(false);
  }
  devices_mutex.unlock();
  devices_ready.emit();
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

void DeviceSelector::start_search_clicked()
{
  search();
}

void DeviceSelector::ok_clicked()
{
  response(Gtk::ResponseType::RESPONSE_OK);
}

void DeviceSelector::cancel_clicked()
{
  response(Gtk::ResponseType::RESPONSE_CANCEL);
}

void DeviceSelector::search()
{
  //szukanie urządzeń
  //std::thread t(std::mem_fn<void, DeviceSelector>(&DeviceSelector::searchDevices));
  if (BluezBluetooth::isDeviceOn()) //bluetooth jest włączony
  {
    btthread = new std::thread(&DeviceSelector::searchDevices, this);
    btthread2 = 0;
    start_search.set_visible(false);
  }
  else //brak bluetootha włączonego
  {
    Gtk::MessageDialog md("Brak włączonego bluetootha");
    md.run();
    btthread = 0;
    start_search.set_visible(true);
  }
}

void DeviceSelector::quit()
{
  if (btthread) // nie było urządzenia bluetooth
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
      if (d)
      {
        delete d;
      }
    }
  }
}

Device* DeviceSelector::getDevice()
{
  devices_mutex.lock();
  Gtk::ListStore::iterator it = view.get_selection()->get_selected();
  std::string MAC = (*it)[dtn.col_MAC];
  for (auto d : devices)
  {
    if (d->getMAC() == MAC)
    {
      devices_mutex.unlock();
      return new Device(*d);
    }
  }
  devices_mutex.unlock();
}
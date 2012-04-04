/* 
 * File:   DeviceSelector.h
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 20:25
 */

#ifndef DEVICESELECTOR_H
#define	DEVICESELECTOR_H

#include <gtkmm-3.0/gtkmm.h>
#include <list>
#include <mutex>
#include <sigc++-2.0/sigc++/sigc++.h>

#include "Device.h"
#include "BluezBluetooth.h"

class DeviceSelector : public Gtk::Dialog//, public sigc::trackable
{
public:
  DeviceSelector();
  DeviceSelector(const DeviceSelector& orig) = delete;
  virtual ~DeviceSelector();
  
  //sygnał
  sigc::signal<void> signal_devices_ready();
private:
  
  //składowe widoku
  Gtk::TreeView view;
  Gtk::ScrolledWindow scrolled_window;
  Gtk::Button ok;
  Gtk::Button cancel;
  //Gtk::Button refresh;
  Gtk::VBox vbox;
  Gtk::HBox hbox;
  
  //bluetooth
  std::list<Device> devices;
  //BluezBluetooth bluetooth;
  //funkcja szukająca
  void searchDevices();
  //mutex do działania na liście
  std::mutex devices_mutex;
  //sygnał do odświeżania listy
  sigc::signal<void> devices_ready;
  //działania na wywołanie sygnału
  void on_devices_ready();
};

#endif	/* DEVICESELECTOR_H */


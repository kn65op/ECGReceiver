/* 
 * File:   DeviceSelector.h
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 20:25
 */

#ifndef DEVICESELECTOR_H
#define	DEVICESELECTOR_H

#include <gtkmm-3.0/gtkmm.h>

#include "BluezBluetooth.h"

class DeviceSelector : public Gtk::Dialog
{
public:
  DeviceSelector();
  virtual ~DeviceSelector();
private:
  DeviceSelector(const DeviceSelector& orig);
  
  //składowe widoku
  Gtk::TreeView view;
  Gtk::ScrolledWindow scrolled_window;
  Gtk::Button ok;
  Gtk::Button cancel;
  //Gtk::Button refresh;
  Gtk::VBox vbox;
  Gtk::HBox hbox;
  
  //bluetooth
  BluezBluetooth bluetooth;
};

#endif	/* DEVICESELECTOR_H */


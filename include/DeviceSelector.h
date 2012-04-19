/* 
 * File:   DeviceSelector.h
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 20:25
 */

#ifndef DEVICESELECTOR_H
#define	DEVICESELECTOR_H

#include <gtkmm-3.0/gtkmm.h>
#include <thread>
#include <list>
#include <mutex>
#include <sigc++-2.0/sigc++/sigc++.h>

#include <Device.h>
#include "DeviceTreeNode.h"

#include "NeedWaitingDialog.h"
#include "WaitingDialog.h"

class DeviceSelector : public Gtk::Dialog, NeedWaitingDialog// public sigc::trackable
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
  Gtk::Button start_search;
  //Gtk::Button refresh;
  Gtk::VBox vbox;
  Gtk::HBox hbox;
  //do listy
   Glib::RefPtr<Gtk::ListStore> ref_tree_model;
   DeviceTreeNode dtn;

  //bluetooth
  std::list<Device*> devices;
  //BluezBluetooth bluetooth;
  //funkcja szukająca
  void searchDevices();
  //mutex do działania na liście
  std::mutex devices_mutex;
  //sygnał do odświeżania listy
  sigc::signal<void> devices_ready;
  //działania na wywołanie sygnału
  void on_devices_ready();
  //czekanie na koniec
  void wait_for_end();

  //Dialog do czekania
  WaitingDialog *wd;


  std::thread *btthread, *btthread2;
  bool exited;
  
  //funkcja restartująca wątek szukania.
  void restart();
  //czy kończymy
  bool exiting;
  
  //funkcje do obsługi przycisków
  void start_search_clicked();
  void ok_clicked();
  void cancel_clicked();
  
  /**
   * Funkcja startująca wyszukiwanie urządzeń.
   */
  void search();
  /**
   * Funkcja zamykająca.
   */
  void quit();
};

#endif	/* DEVICESELECTOR_H */


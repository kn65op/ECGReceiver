/* 
 * File:   ECGReceiver.h
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 19:41
 */

#ifndef ECGRECEIVER_H
#define	ECGRECEIVER_H

#include <gtkmm-3.0/gtkmm.h>
#include <Device.h>

class ECGReceiver : public Gtk::Window
{
public:
  ECGReceiver();
  ECGReceiver(const ECGReceiver& orig) = delete; //blokowanie kopiowania
  virtual ~ECGReceiver();
private:

  //obsługa sygnałów
  void on_select_device_clicked();

  //elementy składowe
  Gtk::Button select_device;

  //urządzenie zdalne
  Device device; //daj tu wskaźnik
};

#endif	/* ECGRECEIVER_H */


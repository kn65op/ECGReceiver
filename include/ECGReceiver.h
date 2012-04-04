/* 
 * File:   ECGReceiver.h
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 19:41
 */

#ifndef ECGRECEIVER_H
#define	ECGRECEIVER_H

#include <gtkmm-3.0/gtkmm.h>

class ECGReceiver : public Gtk::Window
{
public:
  ECGReceiver();
  virtual ~ECGReceiver();
private:
  //blokowanie kopiowania
  ECGReceiver(const ECGReceiver& orig);
  
  //obsługa sygnałów
  void on_select_device_clicked();
  
  //elementy składowe
  Gtk::Button select_device;
  
};

#endif	/* ECGRECEIVER_H */


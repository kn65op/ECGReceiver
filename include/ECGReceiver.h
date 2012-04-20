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

  //boxy
  Gtk::HBox name_box;
  Gtk::HBox MAC_box;
  Gtk::VBox device_description_box;
  Gtk::VBox main_box;
  Gtk::HBox buttons_box;
  //elementy składowe
  Gtk::Button select_device;
  Gtk::Label name;
  Gtk::Label MAC;
  Gtk::Label name_text;
  Gtk::Label MAC_text;

  //urządzenie zdalne
  Device *device; //daj tu wskaźnik
  /**
   * funkcja ustawiająca nazwy i MAC na ekranie
   */
  void setDeviceInfo();
};

#endif	/* ECGRECEIVER_H */


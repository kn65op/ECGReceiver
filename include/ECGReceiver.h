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
  Gtk::Button start_stop;
  Gtk::Label name;
  Gtk::Label MAC;
  Gtk::Label name_text;
  Gtk::Label MAC_text;
  //menu
  Glib::RefPtr<Gtk::UIManager> ref_uimanager;
  Glib::RefPtr<Gtk::ActionGroup> ref_actiongroup;

  //urządzenie zdalne
  Device *device; //daj tu wskaźnik
  /**
   * funkcja ustawiająca nazwy i MAC na ekranie
   */
  void setDeviceInfo();
  // Funkcja do obsługi zapisu
  void saveDeviceToFile() const;
  // Funkcja do obsługi odczytu
  void openDeviceFromFile();
};

#endif	/* ECGRECEIVER_H */


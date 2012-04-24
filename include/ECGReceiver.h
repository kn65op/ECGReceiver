/* 
 * File:   ECGReceiver.h
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 19:41
 */

#ifndef ECGRECEIVER_H
#define	ECGRECEIVER_H

#include <gtkmm-3.0/gtkmm.h>
#include <thread>
#include <mutex>
#include <atomic>

#include <Device.h>
#include "ECGSignal.h"

class ECGReceiver : public Gtk::Window
{
public:
  ECGReceiver();
  ECGReceiver(const ECGReceiver& orig) = delete; //blokowanie kopiowania
  virtual ~ECGReceiver();
private:
  //czy jest nagrywane
  std::atomic<bool> recording;
  ECGSignal<u_int32_t> *signal;
  int signal_handler;

  //serwer
  struct libwebsocket_context * context;

  //wątki
  std::thread *reader, *writer, *listen_to_server;

  //obsługa sygnałów
  void on_select_device_clicked();
  void on_start_stop_clicked();

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
  void saveDeviceToFile();
  // Funkcja do obsługi odczytu
  void openDeviceFromFile();
  //Funkcja do pobierająca dane korzystająca z ECGSignal
  void getData();
  //funkcja zapisująca dane do bazy na końcu pobierania

  //funkcja odbierająca żądania na websocket 
  void listenToServer();
  //funkcja obsługująca web socket
  /**
   * Funkcja tworząca serwer do obsługi websocket.
   */
  void createServer();
};

#endif	/* ECGRECEIVER_H */


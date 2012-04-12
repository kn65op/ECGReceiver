/* 
 * File:   WaitingDialog.h
 * Author: tomko
 *
 * Created on 12 kwiecień 2012, 21:16
 */

#ifndef WAITINGDIALOG_H
#define	WAITINGDIALOG_H

#include <gtkmm-3.0/gtkmm.h>
#include <sigc++-2.0/sigc++/sigc++.h>
//#include <sigc++-2.0/sigc++/trackable.h>

#include <string>

class WaitingDialog : public Gtk::Dialog, virtual public sigc::trackable
{
public:
  WaitingDialog() = delete;
  WaitingDialog(std::string l, bool c);
  WaitingDialog(const WaitingDialog& orig) = delete;
  virtual ~WaitingDialog();

  //obsługa sygnału
  void on_close_waiting_dialog();
  int run();
private:
  Gtk::Label label;
  Gtk::Button cancel;
  Gtk::VBox box;
  bool cancelable;
};

#endif	/* WAITINGDIALOG_H */


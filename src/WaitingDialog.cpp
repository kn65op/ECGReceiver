/* 
 * File:   WaitingDialog.cpp
 * Author: tomko
 * 
 * Created on 12 kwiecień 2012, 21:16
 */

#include "../include/WaitingDialog.h"

//TODO usunąć
#include <iostream>

WaitingDialog::WaitingDialog(std::string l, bool c) : label(l), cancelable(c)
{
  get_content_area()->pack_start(box);
  box.pack_start(label);
  if (cancelable)
  {
    cancel.set_label("Anuluj");
    box.pack_end(cancel);
  }
  get_content_area()->show_all_children(true);
}

WaitingDialog::~WaitingDialog()
{
}

void WaitingDialog::on_close_waiting_dialog()
{
  std::cout << "QWE\n";
  response(0);
}

int WaitingDialog::run()
{
  std::cout << "RUN\n";
  return Gtk::Dialog::run();
}
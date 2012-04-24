/* 
 * File:   main.cpp
 * Author: tomko
 *
 * Created on 4 kwiecień 2012, 19:22
 */

#include <cstdlib>
#include <gtkmm-3.0/gtkmm.h>

#include <X11/Xlib.h>

#include "include/ECGReceiver.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
  XInitThreads();
  
  Gtk::Main gtk(argc, argv);
  
  ECGReceiver ecgr;
  
  Gtk::Main::run(ecgr);
  return 0;
}


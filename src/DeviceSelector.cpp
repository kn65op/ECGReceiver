/* 
 * File:   DeviceSelector.cpp
 * Author: tomko
 * 
 * Created on 4 kwiecień 2012, 20:25
 */

#include "../include/DeviceSelector.h"

#include <thread>

DeviceSelector::DeviceSelector()
{
  //przyciski
  ok.set_label("OK");
  cancel.set_label("Anuluj");
  
  //umieszczenie prezycisków
  hbox.pack_start(ok);
  hbox.pack_start(cancel);
  
  //widok listy
  scrolled_window.add(view);
  
  //umieszczenie pionowe
  vbox.pack_end(hbox);
  vbox.pack_start(scrolled_window);
  
  //umieszczenie vboxa w oknie
  Gtk::Box *tmp = get_vbox();
  tmp->add(vbox);
  
  //wyświetlenie
  tmp->show_all_children(true);
  
}

DeviceSelector::DeviceSelector(const DeviceSelector& orig)
{
  
}

DeviceSelector::~DeviceSelector()
{
}


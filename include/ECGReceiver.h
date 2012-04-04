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
  ECGReceiver(const ECGReceiver& orig);
};

#endif	/* ECGRECEIVER_H */


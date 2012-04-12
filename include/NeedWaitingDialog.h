/* 
 * File:   NeedWaitingDialog.h
 * Author: tomko
 *
 * Created on 12 kwiecień 2012, 21:27
 */

#ifndef NEEDWAITINGDIALOG_H
#define	NEEDWAITINGDIALOG_H

#include <sigc++-2.0/sigc++/sigc++.h>

class NeedWaitingDialog
{
public:
  virtual ~NeedWaitingDialog();
  
  //sygnał
  typedef sigc::signal0<void> close_waiting_dialog;
  close_waiting_dialog signal_close_waiting_dialog();
protected:
  close_waiting_dialog s_close_waiting_dialog;
};

#endif	/* NEEDWAITINGDIALOG_H */


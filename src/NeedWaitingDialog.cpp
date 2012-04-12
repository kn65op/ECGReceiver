/* 
 * File:   NeedWaitingDialog.cpp
 * Author: tomko
 * 
 * Created on 12 kwiecień 2012, 21:27
 */

#include "../include/NeedWaitingDialog.h"


NeedWaitingDialog::~NeedWaitingDialog()
{
}


NeedWaitingDialog::close_waiting_dialog NeedWaitingDialog::signal_close_waiting_dialog()
{
  return s_close_waiting_dialog;
}
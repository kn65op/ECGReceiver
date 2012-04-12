/* 
 * File:   DeviceTreeNode.h
 * Author: tomko
 *
 * Created on 12 kwiecień 2012, 20:28
 */

#ifndef DEVICETREENODE_H
#define	DEVICETREENODE_H

#include <Device.h>
#include <gtkmm-3.0/gtkmm/treemodelcolumn.h>

class DeviceTreeNode :public Device, public Gtk::TreeModelColumnRecord
{
public:
  DeviceTreeNode();
  DeviceTreeNode(const DeviceTreeNode& orig);
  virtual ~DeviceTreeNode();
private:

};

#endif	/* DEVICETREENODE_H */


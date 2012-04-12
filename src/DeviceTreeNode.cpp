/* 
 * File:   DeviceTreeNode.cpp
 * Author: tomko
 * 
 * Created on 12 kwiecień 2012, 20:28
 */

#include "../include/DeviceTreeNode.h"

DeviceTreeNode::DeviceTreeNode(const DeviceTreeNode& orig) : Device(orig)
{
}

DeviceTreeNode::DeviceTreeNode(const Device& orig) : Device(orig)
{
}

DeviceTreeNode::~DeviceTreeNode()
{
}


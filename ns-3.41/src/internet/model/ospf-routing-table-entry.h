/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Mark Greenwood
 *      Nathan Nunes
 *
 *  File: ospf-routing-table-entry.h
 *
 *  Declares OspfRoutingTableEntry which subclasses Ipv4RoutingTableEntry
 *
 */

#ifndef OSPF_ROUTING_TABLE_ENTRY_H
#define OSPF_ROUTING_TABLE_ENTRY_H

#include "ipv4-interface.h"
#include "ipv4-l3-protocol.h"
#include "ipv4-routing-protocol.h"
#include "ipv4-routing-table-entry.h"
#include "ospf-header.h"

namespace ns3 {

class OspfRoutingTableEntry : public Ipv4RoutingTableEntry {

  public:

    OspfRoutingTableEntry();

    /**
     * \brief Constructor
     * \param network network address
     * \param networkPrefix network prefix
     * \param nextHop next hop address to route the packet
     * \param interface interface index
     */
    OspfRoutingTableEntry(Ipv4Address network,
                         Ipv4Mask networkPrefix,
                         Ipv4Address nextHop,
                         uint32_t interface);

    /**
     * \brief Constructor
     * \param network network address
     * \param networkPrefix network prefix
     * \param interface interface index
     */
    OspfRoutingTableEntry(Ipv4Address network, Ipv4Mask networkPrefix, uint32_t interface);

    virtual ~OspfRoutingTableEntry();



};



}

#endif // OSPF_ROUTING_TABLE_ENTRY_H
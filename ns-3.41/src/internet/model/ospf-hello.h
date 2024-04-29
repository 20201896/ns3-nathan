/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-hello.h
 *
 */

#ifndef OSPF_HELLO_H
#define OSPF_HELLO_H

#include <stdint.h>
#include <string>

#include "ospf-header.h"
#include "ospf-neighbor-table.h"

namespace ns3 {
class OspfNeighborTable;

class OspfHello : public OspfHeader{
public:
    OspfHello();
    ~OspfHello();
    void setNeighbors(OspfNeighborTable::neighborList);
    OspfNeighborTable::neighborList getNeighbors();
    void setRouterId(uint32_t);
    uint32_t getRouterId();
    void setAreaId(int);
    int getAreaId();
private:
    OspfNeighborTable::neighborList m_neighbors;
    uint32_t router_id;
    int area_id;
};

}
#endif
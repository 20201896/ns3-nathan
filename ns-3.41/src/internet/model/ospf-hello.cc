/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-hello.cc
 *
 */

#include <stdint.h>
#include <string>
#include "ospf-hello.h"

namespace ns3 {

OspfHello::OspfHello() {

}

OspfHello::~OspfHello() {

}

void OspfHello::setNeighbors(OspfNeighborTable::neighborList newNeighbors) {
    m_neighbors = newNeighbors;
}
OspfNeighborTable::neighborList OspfHello::getNeighbors() {
    return m_neighbors;
}

void OspfHello::setRouterId(uint32_t r_id) {
    router_id = r_id;
}
uint32_t OspfHello::getRouterId() {
    return router_id;
}
void OspfHello::setAreaId(int a_id) {
    area_id = a_id;
}
int OspfHello::getAreaId() {
    return area_id;
}

}
#include "ospf-neighbor-table.h"


namespace ns3
{

OspfNeighborTable::OspfNeighborTable() {

}

void OspfNeighborTable::addNeighbors(ns3::Ipv4Address ip_add, ns3::Ipv4Mask net_mask, Ptr<ns3::Ipv4Interface> ip_interface, int current_state)
{
    neighborItems new_neigbhbor = {ip_add, net_mask, ip_interface, current_state};
    m_neighbors.push_back({new_neigbhbor});
}
void OspfNeighborTable::set_State(int new_state){

}
void OspfNeighborTable::delete_neighbor(){

}
OspfNeighborTable::neighborList OspfNeighborTable::getCurrentNeighbors() {
    return m_neighbors;
}

}
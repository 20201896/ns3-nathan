/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-neighbor-table.h
 *
 */

#include "ospf-neighbor-table.h"


namespace ns3
{

OspfNeighborTable::OspfNeighborTable() {

}

void OspfNeighborTable::addNeighbors(ns3::Ipv4Address ip_add, ns3::Ipv4Mask net_mask, Ptr<ns3::Ipv4Interface> ip_interface, int current_state, uint32_t r_id)
{
    neighborItems new_neighbor = {ip_add, net_mask, ip_interface, current_state, r_id};
    m_neighbors.push_back({new_neighbor});
}

void OspfNeighborTable::set_State(int new_state, uint32_t r_id){
    for (auto& row : m_neighbors){
        for (auto& neighborItems : row){
            if (neighborItems.router_id == r_id){
                neighborItems.state = new_state;
            }
        }
    }
}

void OspfNeighborTable::delete_neighbor(uint32_t r_id){
    for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it){
        bool found = false;
        for (const auto& neighborItems : *it){
            if (neighborItems.router_id == r_id){
                found = true;
                break;
            }
        }
        if (found){
            m_neighbors.erase(it);
            break;
        }
    }
}

OspfNeighborTable::neighborList OspfNeighborTable::getCurrentNeighbors() {
    return m_neighbors;
}

}
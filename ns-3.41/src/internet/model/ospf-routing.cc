/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-routing.cc
 *
 */

#include "ospf-routing.h"
#include "ospf-l4-protocol.h"
#include "ospf-header.h"

#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/node.h"

#define OSPF_ALL_NODE "224.0.0.5"

namespace ns3
{
OspfRouting::OspfRouting() : m_ipv4(nullptr){
    m_ospf_protocol = CreateObject<OspfL4Protocol>();
}
OspfRouting::~OspfRouting() {
    //NS_LOG_FUNCTION(this);
}
TypeId OspfRouting::GetTypeId() {
    static TypeId tid;
    tid = TypeId("ns3::OspfRouting")
            .SetParent<Ipv4RoutingProtocol>()
            .SetGroupName("Internet")
            .AddConstructor<OspfRouting>();
    return tid;
}

Ptr<Ipv4Route> OspfRouting::RouteOutput(Ptr<Packet> p, const Ipv4Header& header, Ptr<NetDevice> oif, Socket::SocketErrno& sockerr)
{
    return nullptr;
}
bool OspfRouting::RouteInput(Ptr<const Packet> p,
                const Ipv4Header& header,
                Ptr<const NetDevice> idev,
                const UnicastForwardCallback& ucb,
                const MulticastForwardCallback& mcb,
                const LocalDeliverCallback& lcb,
                const ErrorCallback& ecb)
{
    return false;
}
void OspfRouting::NotifyInterfaceUp(uint32_t interface){

}
void OspfRouting::NotifyInterfaceDown(uint32_t interface){

}
void OspfRouting::NotifyRemoveAddress(uint32_t interface, Ipv4InterfaceAddress address){

}
void OspfRouting::NotifyAddAddress(uint32_t interface, Ipv4InterfaceAddress address){

}
void OspfRouting::PrintRoutingTable(Ptr<OutputStreamWrapper> stream, Time::Unit unit) const{

}

void OspfRouting::DoInitialize() {
    //NS_LOG_FUNCTION(this);
    m_down_timer = Time(10);
    m_ospf_protocol->SetIpv4(m_ipv4);
    m_ospf_protocol->SetExclusions(m_interfaceExclusions);
    m_ospf_protocol->startDownState();

    Ipv4RoutingProtocol::DoInitialize();
}

void OspfRouting::SetInterfaceExclusions(std::set<uint32_t> exceptions){
    //NS_LOG_FUNCTION(this);
    m_interfaceExclusions = exceptions;
}

void OspfRouting::DoDispose(){
    Ipv4RoutingProtocol::DoDispose();
}

void OspfRouting::SetIpv4(Ptr<Ipv4> ipv4){
    //NS_LOG_FUNCTION(this << ipv4);

    NS_ASSERT(!m_ipv4 && ipv4);
    uint32_t i = 0;
    m_ipv4 = ipv4;

    for (i = 0; i < m_ipv4->GetNInterfaces(); i++){
        if (m_ipv4->IsUp(i)){
            NotifyInterfaceUp(i);
        }else{
            NotifyInterfaceDown(i);
        }
    }
}

void SendDownUpdate(){

}
void OspfRouting::SetArea(int a_id) {
    m_ospf_protocol->SetOspfAreaType(a_id);
}

}
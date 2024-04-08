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

void OspfRouting::DoInitialize() {
    //NS_LOG_FUNCTION(this);
    m_down_timer = Time(10);

    for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
        Ptr<LoopbackNetDevice> check = DynamicCast<LoopbackNetDevice>(m_ipv4->GetNetDevice(i));
        if (check) {
            continue;
        }

        bool activeInterface = false;
        if (m_interfaceExclusions.find(i) == m_interfaceExclusions.end()) {
            activeInterface = true;
            m_ipv4->SetForwarding(i, true);
        }

        for (uint32_t j = 0; j < m_ipv4->GetNAddresses(i); j++) {
            Ipv4InterfaceAddress address = m_ipv4->GetAddress(i, j);
            if (address.GetScope() != Ipv4InterfaceAddress::HOST && activeInterface) {
                Ptr<Packet> p = Create<Packet>();
                dest_add = Ipv4Address(OSPF_ALL_NODE);
                //TODO find out how rip get empheral ports allocated and figure out how it listens on protocol ports
                //m_ospf_protocol->Send(p, address.GetLocal(), dest_add);
                m_ospf_protocol->Allocate(address.GetLocal());
            }
        }
    }
    m_ospf_protocol->SetState(0);
    m_ospf_protocol->SetIpv4(m_ipv4);
    m_ospf_protocol->handleDownState();

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

}
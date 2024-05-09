/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-routing.h
 *
 */

#ifndef OSPF_ROUTING_H
#define OSPF_ROUTING_H

#include "ipv4-routing-protocol.h"
#include "ospf-l4-protocol.h"

namespace ns3
{
class OspfRouting : public Ipv4RoutingProtocol{
public:
    OspfRouting();
    ~OspfRouting() override;
    static TypeId GetTypeId();
    OspfRouting(const OspfRouting&) = delete;
    OspfRouting& operator=(const OspfRouting&) = delete;
    void SetIpv4(Ptr<Ipv4> ipv4) override;
    void SetInterfaceExclusions(std::set<uint32_t> exceptions);

    Ptr<Ipv4Route> RouteOutput(Ptr<Packet> p,
                               const Ipv4Header& header,
                               Ptr<NetDevice> oif,
                               Socket::SocketErrno& sockerr) override;
    bool RouteInput(Ptr<const Packet> p,
                    const Ipv4Header& header,
                    Ptr<const NetDevice> idev,
                    const UnicastForwardCallback& ucb,
                    const MulticastForwardCallback& mcb,
                    const LocalDeliverCallback& lcb,
                    const ErrorCallback& ecb) override;
    void NotifyInterfaceUp(uint32_t interface) override;
    void NotifyInterfaceDown(uint32_t interface) override;
    void NotifyAddAddress(uint32_t interface, Ipv4InterfaceAddress address) override;
    void NotifyRemoveAddress(uint32_t interface, Ipv4InterfaceAddress address) override;
    void PrintRoutingTable(Ptr<OutputStreamWrapper> stream,
                           Time::Unit unit = Time::S) const override;
    void SetArea(int);
    void SetInterfaceMetric(uint32_t, uint8_t);

protected:
    void DoInitialize() override;
    void DoDispose() override;
private:

    Ptr<OspfL4Protocol> m_ospf_protocol;
    std::set<uint32_t> m_interfaceExclusions;   //interface
    Ptr<Ipv4> m_ipv4;                           //reference for an ipv4 address

    Ipv4Address dest_add;

    std::map<uint32_t, uint8_t> m_interfaceMetrics;
};
}

#endif
/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Mark Greenwood
 *      Nathan Nunes
 *
 *  File: ospf-protocol.cc
 *
 */

#include "ospf-l4-protocol.h"

#include "ipv4-end-point-demux.h"
#include "ipv4-end-point.h"
#include "ipv4-route.h"
#include "ipv4.h"
#include "ipv6-end-point-demux.h"
#include "ipv6-end-point.h"
#include "ipv6-route.h"
#include "ipv6.h"
#include "udp-header.h"

#include "ns3/assert.h"
#include "ns3/boolean.h"
#include "ns3/log.h"
#include "ns3/node.h"
#include "ns3/object-map.h"
#include "ns3/packet.h"

#include "ospf-header.h"

#include <unordered_map>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("OspfL4Protocol");
NS_OBJECT_ENSURE_REGISTERED(OspfL4Protocol);

/* see http://www.iana.org/assignments/protocol-numbers */
const uint8_t OspfL4Protocol::PROTOCOL_NUMBER = 89;


// Constructor
OspfL4Protocol::OspfL4Protocol() : m_endPoints(new Ipv4EndPointDemux()), m_endPoints6(new Ipv6EndPointDemux()){
    NS_LOG_FUNCTION(this);
}

// Destructor
OspfL4Protocol::~OspfL4Protocol(){
    NS_LOG_FUNCTION(this);
}

// GetTypeId
TypeId OspfL4Protocol::GetTypeId() {
    static TypeId tid = TypeId("ns3::OspfL4Protocol")
                            .SetParent<IpL4Protocol>()
                            .SetGroupName("Internet")
                            .AddConstructor<OspfL4Protocol>();
    return tid;
}

// Set the owning Node
void OspfL4Protocol::SetNode(Ptr<Node> node) {
    m_node = node;
}

/******************************************************************************
 *
 * MRG: Implementation of pure virtual and virtual functions inherited from
 * pv4L4Protocol.
 *
 * See documentation in ospf-protocol.h
 *
 ******************************************************************************/

// GetProtocolNumber
int OspfL4Protocol::GetProtocolNumber() const {
    return PROTOCOL_NUMBER;
}

// DoDispose
void OspfL4Protocol::DoDispose() {
    // TODO
    NS_LOG_FUNCTION(this);
    if (m_endPoints != nullptr)
    {
        delete m_endPoints;
        m_endPoints = nullptr;
    }
    if (m_endPoints6 != nullptr)
    {
        delete m_endPoints6;
        m_endPoints6 = nullptr;
    }
    m_node = nullptr;
    m_downTarget.Nullify();
    m_downTarget6.Nullify();
    IpL4Protocol::DoDispose();
}

// NotifyNewAggregate
void OspfL4Protocol::NotifyNewAggregate() {

    NS_LOG_FUNCTION(this);

    Ptr<Node> node = this->GetObject<Node>();
    Ptr<Ipv4> ipv4 = this->GetObject<Ipv4>();
    Ptr<Ipv6> ipv6 = node->GetObject<Ipv6>();

    if (!m_node)
    {
        if (node && (ipv4 || ipv6))
        {
            this->SetNode(node);
            // Ptr<UdpSocketFactoryImpl> udpFactory = CreateObject<UdpSocketFactoryImpl>();
            // udpFactory->SetUdp(this);
            // node->AggregateObject(udpFactory);
        }
    }

    if (ipv4 && m_downTarget.IsNull())
    {
        ipv4->Insert(this);
        this->SetDownTarget(MakeCallback(&Ipv4::Send, ipv4));
    }
    if (ipv6 && m_downTarget6.IsNull())
    {
        ipv6->Insert(this);
        this->SetDownTarget6(MakeCallback(&Ipv6::Send, ipv6));
    }
    IpL4Protocol::NotifyNewAggregate();
}

// Receive IPv4
IpL4Protocol::RxStatus OspfL4Protocol::Receive(Ptr<Packet> packet, const Ipv4Header& header, Ptr<Ipv4Interface> interface) {
    NS_LOG_FUNCTION(this);
    return RxStatus::RX_OK;
}

// Receive IPv6
IpL4Protocol::RxStatus OspfL4Protocol::Receive(Ptr<Packet> p, const Ipv6Header& header, Ptr<Ipv6Interface> interface) {
    NS_LOG_FUNCTION(this);
    return RxStatus::RX_OK;
}

// SetDownTarget
void OspfL4Protocol::SetDownTarget(IpL4Protocol::DownTargetCallback cb) {
    NS_LOG_FUNCTION(this);
    m_downTarget = cb;
}

// SetDownTarget6
void OspfL4Protocol::SetDownTarget6(IpL4Protocol::DownTargetCallback6 cb) {
    NS_LOG_FUNCTION(this);
    m_downTarget6 = cb;
}

// GetDownTarget
IpL4Protocol::DownTargetCallback OspfL4Protocol::GetDownTarget() const {
    NS_LOG_FUNCTION(this);
    return m_downTarget;
}

// GetDownTarget6
IpL4Protocol::DownTargetCallback6 OspfL4Protocol::GetDownTarget6() const {
    NS_LOG_FUNCTION(this);
    return m_downTarget6;
}

/*
void OspfL4Protocol::Send(Ptr<Packet> packet, Ipv4Address saddr, Ipv4Address daddr, uint16_t sport, uint16_t dport)
{
    NS_LOG_FUNCTION(this << packet << saddr << daddr << sport << dport);

    OspfHeader ospfHeader;
    if (Node::ChecksumEnabled())
    {
        ospfHeader.EnableChecksums();
        ospfHeader.InitializeChecksum(saddr, daddr, OspfL4Protocol::PROTOCOL_NUMBER);
    }
    ospfHeader.SetDestinationPort(dport);
    ospfHeader.SetSourcePort(sport);

    packet->AddHeader(ospfHeader);

    m_downTarget(packet, saddr, daddr, OspfL4Protocol::PROTOCOL_NUMBER, nullptr);
}
*/

Ipv4EndPoint* OspfL4Protocol::Allocate(Ipv4Address address)
{
    NS_LOG_FUNCTION(this << address);
    return m_endPoints->Allocate(address);
}

}

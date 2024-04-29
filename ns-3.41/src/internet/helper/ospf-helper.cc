/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-helper.h
 *
 */

#include "ospf-helper.h"
#include "ns3/ospf-routing.h"

#include "ns3/ipv4-list-routing.h"
#include "ns3/node-list.h"
#include "ns3/node.h"
#include "ns3/ospf-l4-protocol.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-global-routing.h"
#include "ns3/global-router-interface.h"

namespace ns3
{
OspfHelper::OspfHelper()
{
    m_factory.SetTypeId("ns3::OspfL4Protocol");
}

OspfHelper::OspfHelper(const OspfHelper& o)
        : m_factory(o.m_factory)
{
    m_interfaceExclusions = o.m_interfaceExclusions;
    m_interfaceMetrics = o.m_interfaceMetrics;
}

OspfHelper::~OspfHelper()
{
    m_interfaceExclusions.clear();
    m_interfaceMetrics.clear();
}
OspfHelper* OspfHelper::Copy() const
{
    return new OspfHelper(*this);
}

Ptr<Ipv4RoutingProtocol> OspfHelper::Create(Ptr<Node> node) const
{
    Ptr<OspfRouting> ospf = m_factory.Create<OspfRouting>();

    auto it = m_interfaceExclusions.find(node);

    if (it != m_interfaceExclusions.end())
    {
        ospf->SetInterfaceExclusions(it->second);
    }

    node->AggregateObject(ospf);
    return ospf;
}

void OspfHelper::Set(std::string name, const AttributeValue& value){
    m_factory.Set(name, value);
}

void OspfHelper::ExcludeInterface(Ptr<Node> node, uint32_t interface)
{
    auto it = m_interfaceExclusions.find(node);

    if (it == m_interfaceExclusions.end()){
    std::set<uint32_t> interfaces;
    interfaces.insert(interface);

    m_interfaceExclusions.insert(std::make_pair(node, interfaces));

    }else{
        it->second.insert(interface);
    }
}

void OspfHelper::AssignAreaNumber(Ptr<Node> node, int a_id){
    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
    Ptr<Ipv4RoutingProtocol> proto = ipv4->GetRoutingProtocol();
    Ptr<OspfRouting> ospfRouting = DynamicCast<OspfRouting>(proto);
    ospfRouting->SetArea(a_id);
}

void OspfHelper::CreateAndAggregateObjectFromTypeId(Ptr<Node> node, const std::string typeId)
{
    TypeId tid = TypeId::LookupByName(typeId);
    if (node->GetObject<Object>(tid))
    {
        return;
    }

    ObjectFactory factory;
    factory.SetTypeId(typeId);
    Ptr<Object> protocol = factory.Create<Object>();
    node->AggregateObject(protocol);
}

void OspfHelper::Install(Ptr<Node> node){
    CreateAndAggregateObjectFromTypeId(node, "ns3::OspfL4Protocol");
}

/*
int64_t OspfHelper::AssignStreams(NodeContainer c, int64_t stream)
{
    int64_t currentStream = stream;
    Ptr<Node> node;
    for (auto i = c.Begin(); i != c.End(); ++i)
    {
        node = (*i);
        Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
        NS_ASSERT_MSG(ipv4, "Ipv4 not installed on node");
        Ptr<Ipv4RoutingProtocol> proto = ipv4->GetRoutingProtocol();
        NS_ASSERT_MSG(proto, "Ipv4 routing not installed on node");
        Ptr<OspfRouting> ospf = DynamicCast<OspfRouting>(proto);
        if (ospf)
        {
            currentStream += ospf->AssignStreams(currentStream);
            continue;
        }
        Ptr<Ipv4ListRouting> list = DynamicCast<Ipv4ListRouting>(proto);
        if (list)
        {
            int16_t priority;
            Ptr<Ipv4RoutingProtocol> listProto;
            Ptr<OspfRouting> listOspf;
            for (uint32_t j = 0; j < list->GetNRoutingProtocols(); j++)
            {
                listProto = list->GetRoutingProtocol(j, priority);
                listOspf = DynamicCast<OspfHelper>(listProto);
                if (listOspf)
                {
                    currentStream += listOspf->AssignStreams(currentStream);
                    break;
                }
            }
        }
    }
    return (currentStream - stream);
}
*/
}
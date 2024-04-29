/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Nathan Nunes
 *
 *  File: ospf-helper.h
 *
 */

#ifndef OSPF_HELPER_H
#define OSPF_HELPER_H

#include "ipv4-routing-helper.h"

#include "ns3/node-container.h"
#include "ns3/node.h"
#include "ns3/object-factory.h"

namespace ns3
{

class OspfHelper : public Ipv4RoutingHelper{
    public:
        OspfHelper();
        ~OspfHelper() override;

        OspfHelper(const OspfHelper& o);

        OspfHelper& operator=(const OspfHelper&) = delete;

        OspfHelper* Copy() const override;

        Ptr<Ipv4RoutingProtocol> Create(Ptr<Node> node) const override;

        void Set (std::string name, const AttributeValue& value);

        //int64_t AssignStreams(NodeContainer c, int64_t stream);

        void ExcludeInterface(Ptr<Node> node, uint32_t interface);

        void AssignAreaNumber(Ptr<Node>, int);

        void Install(Ptr<Node> node);

        //void SetInterfaceMetric(Ptr<Node> node, uint32_t interface, uint8_t metric);

        //void SetGatewayRouter(Ptr<Node> node, Ipv4Address nextHop, uint32_t interface);
            //route to lead out of subnet
    protected:
        void CreateAndAggregateObjectFromTypeId(Ptr<Node> node, const std::string typeId);

    private:
        ObjectFactory m_factory;

        std::map<Ptr<Node>, std::set<uint32_t>> m_interfaceExclusions;
        std::map<Ptr<Node>, std::map<uint32_t, uint8_t>> m_interfaceMetrics;
};

}

#endif
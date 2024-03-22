/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Mark Greenwood
 *      Nathan Nunes
 *
 *  File: ospf-starter.cc ns-3 scratch file
 *
 *  Simple starting topology
 *  ========================
 *  src(host) <--> r1 (OSPF enabled router) <--> r2 (OSPF enabled router) <--> dst (host)
 *
 *  Purpose is just to start building the basic plumbing for implementation of
 *  the OSPF protocol in ns-3/internet
 *
 *
 */

#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/ipv4-static-routing-helper.h"

#include <fstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("RipSimpleRouting");

int main(int argc, char** argv) {

    // We want verbose logging and at some point we'd like to print
    // the evolving routing tables.
    bool verbose = true;
    bool printRoutingTables = true;

    if (verbose)
    {
        LogComponentEnableAll(LogLevel(LOG_PREFIX_TIME | LOG_PREFIX_NODE));
        //LogComponentEnable("RipSimpleRouting", LOG_LEVEL_INFO);
        //LogComponentEnable("Rip", LOG_LEVEL_ALL);
        LogComponentEnable("Ipv4Interface", LOG_LEVEL_ALL);
        LogComponentEnable("Icmpv4L4Protocol", LOG_LEVEL_ALL);
        LogComponentEnable("Ipv4L3Protocol", LOG_LEVEL_ALL);
        LogComponentEnable("ArpCache", LOG_LEVEL_ALL);
        LogComponentEnable("Ping", LOG_LEVEL_ALL);
    }

    // Create our Nodes; src, r1, r2 and dst
    NS_LOG_INFO("Create nodes.");
    Ptr<Node> src = CreateObject<Node>();
    Names::Add("SrcNode", src);
    Ptr<Node> r1 = CreateObject<Node>();
    Names::Add("OspfRouter1", r1);
    Ptr<Node> r2 = CreateObject<Node>();
    Names::Add("OspfRouter1", r2);
    Ptr<Node> dst = CreateObject<Node>();
    Names::Add("DstNode", dst);

    // Wrap the Nodes into NodeContainers
    NodeContainer nc_src_r1(src, r1);
    NodeContainer nc_r1_r2(r1, r2);
    NodeContainer nc_r2_dst(r2, dst);

    NS_LOG_INFO("Create channels.");
    CsmaHelper csma_helper;
    csma_helper.SetChannelAttribute("DataRate", DataRateValue(5000000));
    csma_helper.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
    NetDeviceContainer ndc_src_r1 = csma_helper.Install(nc_src_r1);
    NetDeviceContainer ndc_r1_r2 = csma_helper.Install(nc_r1_r2);
    NetDeviceContainer ndc_r2_dst = csma_helper.Install(nc_r2_dst);

    printf("Hello World");


    if(printRoutingTables) {

    }

    return 0;
}

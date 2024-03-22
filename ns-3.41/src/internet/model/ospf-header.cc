/*
*  Copyright (c) 2024 Liverpool Hope University, UK
*  Authors:
*      Mark Greenwood
*      Nathan Nunes
*
*  File: ospf-header.cc
*
*  Implementation of the header of an OSPF packet
*  REM OSPF packets are IP datagrams with protocol identifier 89
*
*/

#include "ospf-header.h"
#include "ns3/address-utils.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED(OspfHeader);

/******************************************************************************
 *
 * MRG: Overridden functions from Header class
 *
 *****************************************************************************/

TypeId OspfHeader::GetTypeId() {
    static TypeId tid = TypeId("ns3::OspfHeader")
                            .SetParent<Header>()
                            .SetGroupName("Internet")
                            .AddConstructor<OspfHeader>();
    return tid;
}

TypeId OspfHeader::GetInstanceTypeId() const {
    return GetTypeId();
}

void OspfHeader::Print(std::ostream& os) const {
    // TODO
}

uint32_t OspfHeader::GetSerializedSize() const {
    // TODO - replace with a real value
    return 8;
}

void OspfHeader::Serialize(Buffer::Iterator start) const {
    // TODO
}

uint32_t OspfHeader::Deserialize(Buffer::Iterator start) {
    // TODO
    return 0;
}


}
/*
 *  Copyright (c) 2024 Liverpool Hope University, UK
 *  Authors:
 *      Mark Greenwood
 *      Nathan Nunes
 *
 *  File: ospf-header.h
 *
 *  Represents the header of an OSPF packet.
 *
 *  REM OSPF packets are IP datagrams with protocol identifier 89
 *
 *  MRG: This is the easy stuff. Obviously OSPF has a number of header
 *  parameters and we need to model them. My expectation at the moment
 *  is that we will eventually define an OspfPacket which has this header
 *  and we will sub-class that OspfPacket in a collection of other (small) classes
 *  for each of the OSPF message types.
 *
 *  All headers in ns3 are represented by subclassing Header.
 *
 */

#ifndef OSPF_HEADER_H
#define OSPF_HEADER_H

#include "ns3/header.h"
#include "ns3/ipv4-address.h"

#include <stdint.h>
#include <string>

namespace ns3 {

class OspfHeader : public Header {
public:

    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    TypeId GetInstanceTypeId() const override;

    void Print(std::ostream& os) const override;
    uint32_t GetSerializedSize() const override;
    void Serialize(Buffer::Iterator start) const override;
    uint32_t Deserialize(Buffer::Iterator start) override;
    //void EnableChecksums();
    void InitializeChecksum(Ipv4Address source, Ipv4Address destination, uint8_t protocol);
    void SetState(int);
    int GetState() const;
    void SetPacketType(int);
    int GetPacketType() const;

private:
    bool m_calcChecksum;
    Address m_source;           //!< Source IP address
    Address m_destination;      //!< Destination IP address
    uint8_t m_protocol;        //!< Protocol number
    int m_state;
    int m_packet_type;
};

}

#endif // OSPF_HEADER_H
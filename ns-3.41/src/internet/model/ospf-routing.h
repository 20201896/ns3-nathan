#include "ipv4-routing-protocol.h"
#include "ospf-l4-protocol.h"

namespace ns3
{
class OspfRouting : public Ipv4RoutingProtocol{
public:
    OspfRouting();
    ~OspfRouting() override;
    OspfRouting(const OspfRouting&) = delete;
    OspfRouting& operator=(const OspfRouting&) = delete;
    void SetIpv4(Ptr<Ipv4> ipv4) override;
    void SetInterfaceExclusions(std::set<uint32_t> exceptions);

protected:
    void DoInitialize() override;
    void DoDispose() override;
private:
    void SendDownUpdate();

    Ptr<OspfL4Protocol> m_ospf_protocol;
    std::set<uint32_t> m_interfaceExclusions;   //interface
    Ptr<Ipv4> m_ipv4;                           //reference for an ipv4 address

    Ipv4Address dest_add;

    Time m_down_timer;
    Time m_next_down_timer;
};
}
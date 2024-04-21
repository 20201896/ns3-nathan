#include <stdint.h>
#include <string>
#include "ipv4.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ptr.h"
#include <list>
#include <stdint.h>

namespace ns3 {

class OspfNeighborTable{
public:
    struct neighborItems{
        Ipv4Address ipAdd;
        Ipv4Mask netMask;
        Ptr<Ipv4Interface> ipInterface;
        int state;
        uint32_t router_id;
    };

    typedef std::vector<std::vector<neighborItems>> neighborList;
    OspfNeighborTable();

    void addNeighbors(Ipv4Address, Ipv4Mask, Ptr<Ipv4Interface>, int, uint32_t);
    neighborList getCurrentNeighbors();
    void set_State(int, uint32_t);
    void delete_neighbor(uint32_t);

private:
    neighborList m_neighbors;
};

}
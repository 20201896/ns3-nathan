#include <stdint.h>
#include <string>
#include "ipv4.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ptr.h"
#include <list>

namespace ns3 {

class OspfNeighborTable{
public:
    struct neighborItems{
        Ipv4Address ipAdd;
        Ipv4Mask netMask;
        Ptr<Ipv4Interface> ipInterface;
        int state;
    };

    typedef std::vector<std::vector<neighborItems>> neighborList;
    OspfNeighborTable();

    void addNeighbors(Ipv4Address, Ipv4Mask, Ptr<Ipv4Interface>, int);
    neighborList getCurrentNeighbors();
    void set_State(int);
    void delete_neighbor();

private:
    neighborList m_neighbors;
};

}
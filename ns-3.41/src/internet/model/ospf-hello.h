#include <stdint.h>
#include <string>

#include "ospf-header.h"
#include "ospf-neighbor-table.h"

namespace ns3 {

class OspfHello : public OspfHeader{
public:
    OspfHello();
    ~OspfHello();
    void setNeighbors(OspfNeighborTable::neighborList);
    OspfNeighborTable::neighborList getNeighbors();
private:
    OspfNeighborTable::neighborList m_neighbors;

};

}
#include <stdint.h>
#include <string>
#include "ospf-hello.h"

namespace ns3 {

OspfHello::OspfHello() {

}

OspfHello::~OspfHello() {

}

void OspfHello::setNeighbors(OspfNeighborTable::neighborList newNeighbors) {
    m_neighbors = newNeighbors;
}
OspfNeighborTable::neighborList OspfHello::getNeighbors() {
    return m_neighbors;
}

}
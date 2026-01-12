#include "traffic_mirrorer/traffic.h"

Traffic::Traffic()
{
}

Traffic::Traffic(const Traffic &traffic) 
{   
    listeningPort = traffic.getListeningPort(); 
    destinations = traffic.getDestinations(); 
}

Traffic::Traffic(std::string lPort) :
    listeningPort(lPort)
{
}

Traffic::~Traffic()
{
}

void Traffic::addConnection(Connection conn)
{
    destinations.push_back(conn);
}

std::string Traffic::getListeningPort() const
{
    return listeningPort;
}

std::vector<Connection> Traffic::getDestinations() const
{
    return destinations;
}
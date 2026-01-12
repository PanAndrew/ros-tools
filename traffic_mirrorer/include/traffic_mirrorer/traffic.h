#pragma once
#pragma once

#include <string>
#include <vector>

#include "traffic_mirrorer/connection.h"

class Traffic
{
private:
    std::string listeningPort;
    std::vector<Connection> destinations;

public:
    Traffic();
    Traffic(const Traffic &traffic);
    Traffic(std::string lPort);
    ~Traffic();

    void addConnection(Connection conn);
    std::string getListeningPort() const;
    std::vector<Connection> getDestinations() const;
};
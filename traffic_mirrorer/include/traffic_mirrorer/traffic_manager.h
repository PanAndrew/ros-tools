#pragma once

#include <thread>

#include "traffic_mirrorer/traffic.h"
#include "traffic_mirrorer/comm_handler.h"

class TrafficManager
{
private:
    std::vector<std::shared_ptr<CommunicationHandler>> handlers;
    std::vector<std::thread> threads;

public:
    TrafficManager();
    ~TrafficManager();

    void addTraffic(Traffic traffic);
    void startAsync();
    void proceed();
};
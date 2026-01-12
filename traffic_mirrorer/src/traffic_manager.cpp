#include "traffic_mirrorer/traffic_manager.h"

TrafficManager::TrafficManager()
{
}

TrafficManager::~TrafficManager()
{
}

void TrafficManager::addTraffic(Traffic traffic)
{
    handlers.push_back(std::make_shared<CommunicationHandler>(traffic));
}

void TrafficManager::proceed()
{
    for(auto &handler : handlers)
    {
        threads.push_back(std::thread(&CommunicationHandler::proceed, handler));
    }
}
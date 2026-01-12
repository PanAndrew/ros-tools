#pragma once

#include <memory>
#include "boost/asio.hpp"
#include "boost/array.hpp"
#include "boost/bind.hpp"

#include "traffic_mirrorer/traffic.h"

class CommunicationHandler
{
private:    
    Traffic trafficInfo;
    
    boost::asio::io_service io_service;

    boost::asio::ip::udp::socket listeningSocket;
    std::vector<boost::asio::ip::udp::endpoint> endpoints;
    boost::array<uint8_t, 1500> rcvBuffer;

    boost::asio::ip::udp::socket clientSocket;

    void startReceive();
    void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

public:
    CommunicationHandler(Traffic traffic);
    ~CommunicationHandler();

    void proceed();
};
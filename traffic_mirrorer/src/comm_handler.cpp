#include "traffic_mirrorer/comm_handler.h"
#include <iostream>

CommunicationHandler::CommunicationHandler(Traffic traffic) :
    trafficInfo(traffic),
    listeningSocket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(trafficInfo.getListeningPort()))),
    clientSocket(io_service)
{
    boost::asio::ip::udp::resolver resolver(io_service);
    for(auto &conn : trafficInfo.getDestinations())
    {
        boost::asio::ip::udp::resolver::query query(conn.getDestinationAddress(), conn.getDestinationPort());
        endpoints.push_back(*resolver.resolve(query));
    }

    clientSocket.open(boost::asio::ip::udp::v4());
}

CommunicationHandler::~CommunicationHandler()
{
}

void CommunicationHandler::startReceive()
{
    listeningSocket.async_receive(
            boost::asio::buffer(rcvBuffer),
            boost::bind(&CommunicationHandler::handleReceive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void CommunicationHandler::proceed()
{
    startReceive();
    io_service.run();
}

void CommunicationHandler::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    try
    {
        for(auto &endpoint : endpoints)
        {
            clientSocket.send_to(boost::asio::buffer(rcvBuffer, bytes_transferred), endpoint);
        }

        startReceive();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
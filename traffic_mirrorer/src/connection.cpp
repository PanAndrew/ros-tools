#include "traffic_mirrorer/connection.h"

Connection::Connection(std::string dPort, std::string dAddr) :
    destPort(dPort),
    destAddr(dAddr)
{
}

Connection::~Connection()
{
}

std::string Connection::getDestinationPort()
{
    return destPort;
}

std::string Connection::getDestinationAddress()
{
    return destAddr;
}
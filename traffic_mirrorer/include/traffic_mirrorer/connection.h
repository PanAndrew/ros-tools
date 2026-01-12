#pragma once

#include <string>

class Connection
{
private:
    std::string destPort;
    std::string destAddr;
public:
    Connection(std::string dPort, std::string dAddr);
    ~Connection();

    std::string getDestinationPort();
    std::string getDestinationAddress();
};
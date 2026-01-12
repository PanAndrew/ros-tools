#include "ros/ros.h"
#include "traffic_mirrorer/traffic_manager.h"
#include "traffic_mirrorer/traffic.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "traffic_mirrorer_node");
    ros::Time::init();

    Traffic traffic_front("2111");
    traffic_front.addConnection(Connection("8888", "localhost"));
    traffic_front.addConnection(Connection("2111", "192.168.1.100"));

    Traffic traffic_rear("2110");
    traffic_rear.addConnection(Connection("9999", "localhost"));
    traffic_rear.addConnection(Connection("2110", "192.168.1.100"));
    std::cout << "Created traffic description..." << std::endl;

    TrafficManager trafficManager;
    trafficManager.addTraffic(traffic_front);
    trafficManager.addTraffic(traffic_rear);

    trafficManager.proceed();

    std::cout << "Started..." << std::endl;

    double rate_hz = 10;
    ros::Rate rate(rate_hz);

    while (ros::ok())
    {
        rate.sleep();
    }
    
    ros::waitForShutdown();
    return 0;
}

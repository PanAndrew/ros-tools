# traffic_mirrorer

A ROS node that mirrors UDP traffic from a 2D LiDAR safety scanner to multiple
destinations.

## Why

Safety-rated 2D LiDAR scanners (e.g. laser safety scanners used on AGVs/AMRs)
typically stream their scan/telegram data over UDP to exactly one configured
destination — the scanner's own configuration only allows a single IP/port.
In practice you often need that same data in more than one place at once, for
example a safety PLC/controller *and* a PC running visualization or logging.

`traffic_mirrorer` sits between the scanner and its consumers: it listens on
the port the scanner sends to, and re-transmits every UDP datagram it
receives, unmodified, to a configurable list of destination `host:port`
pairs.

## How it works

- `Traffic` describes one mirroring rule: a listening port plus a list of
  `Connection` (destination host + port) targets.
- `CommunicationHandler` owns a Boost.Asio `io_service`, binds a UDP socket
  to the listening port, and asynchronously forwards each received datagram
  to every configured destination endpoint.
- `TrafficManager` owns one `CommunicationHandler` per `Traffic` entry and
  runs each on its own thread, so multiple independent mirrors (e.g. a front
  and a rear scanner) can run concurrently in a single node.

## Requirements

- ROS1 (Kinetic/Melodic/Noetic), catkin
- Boost (`system` component)

## Build

Clone into a catkin workspace and build as usual:

```bash
cd ~/catkin_ws/src
git clone git@github.com:PanAndrew/ros-tools.git
cd ~/catkin_ws
catkin_make   # or catkin build
```

## Run

```bash
roslaunch traffic_mirrorer traffic_mirrorer.launch
```

## Configuration

The example configuration in `main()` mirrors two independent streams:

| Traffic | Listens on | Destinations |
|---|---|---|
| front LiDAR | UDP `2111` | `localhost:8888`, `192.168.1.100:2111` |
| rear LiDAR | UDP `2110` | `localhost:9999`, `192.168.1.100:2110` |

To add or change a mirror, edit `traffic_mirrorer.cpp`:

```cpp
Traffic traffic_front("2111");
traffic_front.addConnection(Connection("8888", "localhost"));
traffic_front.addConnection(Connection("2111", "192.168.1.100"));

trafficManager.addTraffic(traffic_front);
```

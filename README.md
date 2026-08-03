# ros-tools

A collection of standalone ROS packages/utilities.

## Packages

### [traffic_mirrorer](traffic_mirrorer/)

Mirrors UDP traffic from a 2D LiDAR safety scanner to multiple destinations.
Safety scanners typically support only a single configured output
destination; `traffic_mirrorer` listens on that destination's port and
re-transmits every received frame, unmodified, to several destinations at
once (e.g. a safety controller and a visualization/logging PC).

See the [package README](traffic_mirrorer/README.md) for build, usage, and
configuration details.


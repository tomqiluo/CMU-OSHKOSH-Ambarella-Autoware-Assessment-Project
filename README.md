# oshkosh-ambarella-project

## Autoware System Monitoring
### Supported Monitors
- **CPU Monitor**
- **HDD Monitor**
- **Memory Monitor**
- **Network Monitor**
- **NTP Monitor**
- **Process Monitor**
- **GPU Monitor**
- **Voltage Monitor**
### How to Use
```sh
colcon build

source /opt/ros/iron/setup.bash

export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

ros2 launch system_monitor system_monitor.launch.xml
```


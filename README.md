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

cd /home/lychee/6v_yolop_yolov5/ros2/gstreamer/ros2_gst_6v_demo
source /opt/ros2/iron-20231205/setup.bash

ros2 launch system_monitor system_monitor.launch.xml
```


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
```
source ~/autoware/install/setup.bash
source /opt/ros2/humble/setup.bash
chmod +x log_system_monitor.sh
./log_system_monitor.sh
```

## Autoware Topics Monitoring
### Supported Topics
- **/diagnostic/planning_evaluator/metrics**
- **/diagnostics**
- **/diagnostics_agg**
- **/diagnostics_err**
- **/diagnostics_toplevel_state**

### Obtain topics list
`ros2 topic list > topic_list.txt`

### How to Use
```
source ~/autoware/install/setup.bash
source /opt/ros2/humble/setup.bash
chmod +x diagnostics_logger.py
./diagnostics_logger.py
```

                                                                                                                                    
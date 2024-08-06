# oshkosh-ambarella-project

## Autoware System Monitoring
### Supported Monitors
- **CPU Monitor**
- **Memory Monitor**
- **GPU Monitor**

### How to Use
```
chmod +x system_logger.py
python3 log_system_monitor.sh
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
source /opt/ros/humble/setup.bash
chmod +x diagnostics_logger.py
python3 diagnostics_logger.py
```

                                                                                                                                    
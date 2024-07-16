#!/bin/bash

# Directory to store logs
LOG_DIR="/home/lychee/oshkosh-ambarella-project"
mkdir -p "$LOG_DIR"

# Log file with timestamp
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="$LOG_DIR/system_monitor_$TIMESTAMP.log"

# ROS topics
TOPICS=(
    "/cpu_monitor/cpu_temperature"
    "/cpu_monitor/cpu_usage"
    "/cpu_monitor/cpu_load_average"
    "/cpu_monitor/cpu_thermal_throttling"
    "/cpu_monitor/cpu_frequency"
    "/hdd_monitor/hdd_temperature"
    "/hdd_monitor/hdd_poweron_hours"
    "/hdd_monitor/hdd_total_data_written"
    "/hdd_monitor/hdd_recovered_error"
    "/hdd_monitor/hdd_usage"
    "/hdd_monitor/hdd_read_data_rate"
    "/hdd_monitor/hdd_write_data_rate"
    "/hdd_monitor/hdd_read_iops"
    "/hdd_monitor/hdd_write_iops"
    "/hdd_monitor/hdd_connection"
    "/memory_monitor/memory_usage"
    "/net_monitor/network_connection"
    "/net_monitor/network_usage"
    "/net_monitor/network_crc_error"
    "/net_monitor/ip_packet_reassembles_failed"
    "/ntp_monitor/ntp_offset"
    "/process_monitor/tasks_summary"
    "/process_monitor/high_load_proc"
    "/process_monitor/high_mem_proc"
    "/gpu_monitor/gpu_temperature"
    "/gpu_monitor/gpu_usage"
    "/gpu_monitor/gpu_memory_usage"
    "/gpu_monitor/gpu_thermal_throttling"
    "/gpu_monitor/gpu_frequency"
    "/voltage_monitor/cmos_battery_status"
)

# Function to log a ROS topic
log_topic() {
    local topic=$1
    echo "Logging $topic to $LOG_FILE"
    rostopic echo -n 1 "$topic" >> "$LOG_FILE" &
}

# Start logging each topic
for topic in "${TOPICS[@]}"; do
    log_topic "$topic"
done

echo "Logging started. Check logs in $LOG_FILE"

# Wait for all background processes to complete
wait

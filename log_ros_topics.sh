#!/bin/bash

# Ensuring directory exists for logs
mkdir -p ~/ros_logs

# Start logging each topic to a separate file
ros2 topic echo /diagnostic/planning_evaluator/metrics >> ~/ros_logs/planning_evaluator_metrics.log &
ros2 topic echo /diagnostics >> ~/ros_logs/diagnostics.log &
ros2 topic echo /diagnostics_agg >> ~/ros_logs/diagnostics_agg.log &
ros2 topic echo /diagnostics_err >> ~/ros_logs/diagnostics_err.log &
ros2 topic echo /diagnostics_toplevel_state >> ~/ros_logs/diagnostics_toplevel_state.log &

# Wait for any process to exit
wait
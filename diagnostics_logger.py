#!/usr/bin/env python
import rospy
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus
from std_msgs.msg import String  # Assuming a generic message type for planning evaluator metrics

def log_planning_evaluator_metrics(data):
    with open('planning_evaluator_metrics.log', 'a') as file:
        file.write(str(data) + '\n')

def log_diagnostics(data):
    with open('diagnostics.log', 'a') as file:
        file.write(str(data) + '\n')

def log_diagnostics_agg(data):
    with open('diagnostics_agg.log', 'a') as file:
        file.write(str(data) + '\n')

def log_diagnostics_err(data):
    with open('diagnostics_err.log', 'a') as file:
        file.write(str(data) + '\n')

def log_diagnostics_toplevel_state(data):
    with open('diagnostics_toplevel_state.log', 'a') as file:
        file.write(str(data) + '\n')

def listener():
    rospy.init_node('diagnostics_logger', anonymous=True)
    
    rospy.Subscriber("/diagnostic/planning_evaluator/metrics", String, log_planning_evaluator_metrics)
    rospy.Subscriber("/diagnostics", DiagnosticArray, log_diagnostics)
    rospy.Subscriber("/diagnostics_agg", DiagnosticArray, log_diagnostics_agg)
    rospy.Subscriber("/diagnostics_err", DiagnosticArray, log_diagnostics_err)
    rospy.Subscriber("/diagnostics_toplevel_state", DiagnosticStatus, log_diagnostics_toplevel_state)
    
    rospy.spin()

if __name__ == '__main__':
    listener()

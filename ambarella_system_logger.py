import subprocess
import psutil
import time
import csv

def system_metrics():
    """Collect system-wide CPU and memory usage."""
    cpu_usage = psutil.cpu_percent(interval=1)
    memory = psutil.virtual_memory()
    return cpu_usage, memory.percent

def log_metrics():
    filename = "system_performance_log.csv"
    fields = ['Timestamp', 'CPU Usage (%)', 'Memory Usage (%)']
    with open(filename, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(fields)  # Write header
        try:
            while True:
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                cpu_usage, memory_usage = system_metrics()
                
                # Log only CPU and Memory usage
                row = [timestamp, cpu_usage, memory_usage]
                writer.writerow(row)
                
                print("Logged metrics at:", timestamp)
                time.sleep(1)  # Log every second
        except KeyboardInterrupt:
            print("Logging stopped.")

if __name__ == "__main__":
    log_metrics()
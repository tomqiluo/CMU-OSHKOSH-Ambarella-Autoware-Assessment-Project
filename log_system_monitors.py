import subprocess
import psutil
import time
import csv

def execute_command(command):
    """Execute a system command and return its output."""
    try:
        output = subprocess.run(command, text=True, capture_output=True, check=True)
        return output.stdout
    except subprocess.CalledProcessError as e:
        print(f"An error occurred while executing the command: {e}")
        return ""

def parse_nvidia_smi():
    """Parse the output of nvidia-smi to get desired GPU metrics."""
    command = ['nvidia-smi', '--query-gpu=timestamp,name,utilization.gpu,utilization.memory,memory.total,memory.free,memory.used', '--format=csv']
    output = execute_command(command)
    lines = output.strip().split('\n')
    if len(lines) > 1:
        # Skip the header row and return the last (most recent) line's values
        return lines[-1].split(',')
    return []

def system_metrics():
    """Collect system-wide CPU and memory usage."""
    cpu_usage = psutil.cpu_percent(interval=1)
    memory = psutil.virtual_memory()
    return cpu_usage, memory.percent

def log_metrics():
    filename = "system_performance_log.csv"
    fields = ['Timestamp', 'CPU Usage (%)', 'Memory Usage (%)', 'GPU Usage (%)', 'GPU Memory Usage (%)', 'Total GPU Memory (MB)', 'Free GPU Memory (MB)', 'Used GPU Memory (MB)']
    with open(filename, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(fields)  # Write header
        try:
            while True:
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                cpu_usage, memory_usage = system_metrics()
                gpu_metrics = parse_nvidia_smi()
                if gpu_metrics:
                    # Assuming GPU metrics are returned in the order we requested
                    row = [timestamp, cpu_usage, memory_usage] + gpu_metrics[2:]
                    writer.writerow(row)
                    print("Logged metrics at:", timestamp)
                time.sleep(1)  # Log every second
        except KeyboardInterrupt:
            print("Logging stopped.")

if __name__ == "__main__":
    log_metrics()

import pandas as pd
import matplotlib.pyplot as plt
import io

# Sample data as a string, normally you would read this from a file
data = """
Timestamp,CPU Usage (%),Memory Usage (%),GPU Usage (%),GPU Memory Usage (%),Total GPU Memory (MB),Free GPU Memory (MB),Used GPU Memory (MB)
2024-08-06 14:33:09,0.3,12.4,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:13,0.1,11.7,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:15,0.5,11.7,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:17,0.2,11.7,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:19,0.4,11.7,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:21,0.8,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:23,0.4,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:25,0.5,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:27,0.7,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:29,0.3,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:31,0.4,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-06 14:33:33,0.2,11.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
Timestamp,CPU Usage (%),Memory Usage (%),GPU Usage (%),GPU Memory Usage (%),Total GPU Memory (MB),Free GPU Memory (MB),Used GPU Memory (MB)
2024-08-07 13:21:42,0.3,12.6,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:46,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:48,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:50,0.3,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:52,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:54,0.6,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:56,0.6,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:21:58,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:22:00,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:22:02,0.3,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:22:04,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:22:07,0.6,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
2024-08-07 13:22:09,0.4,11.9,0 %,0 %,4096 MiB,3796 MiB,14 MiB
"""

# Read the data into a list of dataframes, one for each run
def read_data(data):
    runs = []
    for chunk in data.strip().split("Timestamp,CPU Usage (%),Memory Usage (%),GPU Usage (%),GPU Memory Usage (%),Total GPU Memory (MB),Free GPU Memory (MB),Used GPU Memory (MB)")[1:]:
        chunk = "Timestamp,CPU Usage (%),Memory Usage (%),GPU Usage (%),GPU Memory Usage (%),Total GPU Memory (MB),Free GPU Memory (MB),Used GPU Memory (MB)" + chunk
        runs.append(pd.read_csv(io.StringIO(chunk), skipinitialspace=True))
    return runs

runs = read_data(data)

# Function to plot the data
def plot_data(runs):
    for i, run in enumerate(runs):
        run['Timestamp'] = pd.to_datetime(run['Timestamp'])
        plt.figure(figsize=(12, 6))
        
        plt.subplot(2, 1, 1)
        plt.plot(run['Timestamp'], run['CPU Usage (%)'], label='CPU Usage (%)')
        plt.plot(run['Timestamp'], run['Memory Usage (%)'], label='Memory Usage (%)')
        plt.xlabel('Timestamp')
        plt.ylabel('Usage (%)')
        plt.title(f'Run {i + 1} - CPU and Memory Usage')
        plt.legend()
        
        plt.subplot(2, 1, 2)
        plt.plot(run['Timestamp'], run['Used GPU Memory (MB)'], label='Used GPU Memory (MB)')
        plt.xlabel('Timestamp')
        plt.ylabel('GPU Memory (MB)')
        plt.title(f'Run {i + 1} - GPU Memory Usage')
        plt.legend()
        
        plt.tight_layout()
        plt.show()

plot_data(runs)
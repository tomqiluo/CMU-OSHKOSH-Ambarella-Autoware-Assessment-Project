import pandas as pd
import matplotlib.pyplot as plt
import io

# Function to read the data from a CSV file
def read_data_from_file(file_path):
    with open(file_path, 'r') as file:
        data = file.read()
        
    runs = []
    for chunk in data.strip().split("Timestamp,CPU Usage (%),Memory Usage (%)")[1:]:
        chunk = "Timestamp,CPU Usage (%),Memory Usage (%)" + chunk
        runs.append(pd.read_csv(io.StringIO(chunk), skipinitialspace=True))
    return runs

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
        
        # plt.tight_layout()
        plt.show()

# Path to the CSV file
file_path = 'ambarella_system_performance_log.csv'

# Read the data from the file
runs = read_data_from_file(file_path)

# Plot the data
plot_data(runs)
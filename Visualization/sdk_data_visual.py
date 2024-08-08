import pandas as pd
import matplotlib.pyplot as plt

# Function to parse the provided data format
def read_and_parse_data(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        
    # Parse the header
    header_line = lines[1].strip()
    headers = header_line.split('\t')
    
    # Extract column headers for individual data points
    columns = headers[:7]
    for i in range(8, len(headers), 4):
        columns += [f"{headers[i]}_{suffix}" for suffix in ["Min (ms)", "Max (ms)", "Avg (ms)", "Sum (%)"]]
    
    # Parse the data rows
    data_rows = []
    for line in lines[2:]:
        if line.strip():
            row = line.strip().split('\t')
            if len(row) > 1:
                data_rows.append(row)
    
    # Create DataFrame
    df = pd.DataFrame(data_rows, columns=columns)
    
    # Convert columns to numeric where applicable
    for col in df.columns:
        df[col] = pd.to_numeric(df[col], errors='coerce')
    
    return df

# Function to plot the data
def plot_data(df):
    # Plot each group of metrics separately
    for metric in ["NVP0", "NVP1", "NVP2", "NVP3", "NVP4", "NVP5", "GVP0", "GVP1"]:
        plt.figure(figsize=(12, 6))
        
        plt.subplot(2, 1, 1)
        plt.plot(df[f"{metric}_Min (ms)"], label=f'{metric} Min (ms)')
        plt.plot(df[f"{metric}_Max (ms)"], label=f'{metric} Max (ms)')
        plt.plot(df[f"{metric}_Avg (ms)"], label=f'{metric} Avg (ms)')
        plt.xlabel('Index')
        plt.ylabel('Time (ms)')
        plt.title(f'{metric} Timing Metrics')
        plt.legend()
        
        plt.subplot(2, 1, 2)
        plt.plot(df[f"{metric}_Sum (%)"], label=f'{metric} Sum (%)')
        plt.xlabel('Index')
        plt.ylabel('Sum (%)')
        plt.title(f'{metric} Sum (%)')
        plt.legend()
        
        plt.tight_layout()
        plt.show()

# Path to the data file
file_path = 'system_performance_log.csv'

# Read and parse the data from the file
df = read_and_parse_data(file_path)

# Plot the data
plot_data(df)
import matplotlib.pyplot as plt
import pandas as pd

# Sample data creation
data_avg_times = {
    "PID": [817279, 817280, 817281, 817282, 817283, 817284],
    "resize_avg": [4.023, 3.355, 3.355, 3.355, 3.335, 4.023],
    "resize_itl_avg": [1.095, 0.856, 0.856, 0.856, 0.856, 1.096],
    "yuv2rgb_avg": [0.094, 0.095, 0.117, 0.094, 0.096, 0.116],
}

data_single_pid = {
    "Process": ["resize", "resize_itl", "yuv2rgb"],
    "Min": [3.995, 1.072, 0.087],
    "Max": [4.068, 1.128, 0.136],
    "Avg": [4.023, 1.095, 0.094],
}

data_sum_percentage = { 
    "PID": [817279, 817280, 817281, 817282, 817283, 817284],
    "NVP0": [3.465, 1.835, 1.979, 5.537, 4.597, 4.78],
    "NVP1": [1.152, 0.929, 0.897, 2.434, 1.795, 1.97],
    "NVP2": [0.369, 0.415, 0.339, 1.217, 1.734, 1.025],
    "NVP3": [0.189, 0.115, 0.155, 0.304, 0.913, 0.657],
    "NVP4": [0.079, 0.059, 0.022, 0.183, 0.487, 0.328],
    "NVP5": [0.01, 0.03, 0.006, 0.03, 0.091, 0.036],
    "GVP0": [2.01, 2.649, 2.696, 2.683, 2.644, 1.98],
    "GVP1": [0.444, 0.529, 0.529, 0.524, 0.535, 0.401],
}

# Convert to DataFrames
df_avg_times = pd.DataFrame(data_avg_times)
df_single_pid = pd.DataFrame(data_single_pid)
df_sum_percentage = pd.DataFrame(data_sum_percentage)

# Create the figure and subplots
fig, axs = plt.subplots(3, 1, figsize=(12, 18))

# Bar plot of average times for each process across PIDs
df_avg_times.set_index("PID").plot(kind="bar", ax=axs[0])
axs[0].set_title("Average Times for Each Process Across PIDs")
axs[0].set_xlabel("PID")
axs[0].set_ylabel("Average Time (ms)")

# Line plot of min, max, and average times for each process for a single PID
df_single_pid.set_index("Process").plot(kind="line", ax=axs[1], marker='o')
axs[1].set_title("Min, Max, and Average Times for Each Process for PID 817279")
axs[1].set_xlabel("Process")
axs[1].set_ylabel("Time (ms)")

# Stacked bar plot for sum percentage for NVP and GVP values
df_sum_percentage.set_index("PID").plot(kind="bar", stacked=True, ax=axs[2])
axs[2].set_title("Sum Percentage for NVP and GVP Values")
axs[2].set_xlabel("PID")
axs[2].set_ylabel("Sum Percentage (%)")

# Adjust layout and show plot
plt.tight_layout()
plt.show()
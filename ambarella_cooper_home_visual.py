import matplotlib.pyplot as plt
import pandas as pd

# All data provided
data = {
    "PID": [817279, 817280, 817281, 817282, 817283, 817284],
    "resize_avg": [4.023, 3.355, 3.355, 3.355, 3.335, 4.023],
    "resize_itl_avg": [1.095, 0.856, 0.856, 0.856, 0.856, 1.096],
    "yuv2rgb_avg": [0.094, 0.095, 0.117, 0.094, 0.096, 0.116],
    "resize_min": [3.995, 3.354, 3.354, 3.354, 0.387, 3.991],
    "resize_max": [4.068, 3.357, 3.357, 3.357, 3.357, 4.077],
    "resize_itl_min": [1.072, 0.852, 0.852, 0.852, 0.852, 1.074],
    "resize_itl_max": [1.128, 0.86, 0.86, 0.859, 0.86, 1.124],
    "yuv2rgb_min": [0.087, 0.087, 0.099, 0.086, 0.086, 0.1],
    "yuv2rgb_max": [0.136, 0.117, 0.148, 0.124, 0.12, 0.138],
    "NVP0_sum": [3.465, 1.835, 1.979, 5.537, 4.597, 4.78],
    "NVP1_sum": [1.152, 0.929, 0.897, 2.434, 1.795, 1.97],
    "NVP2_sum": [0.369, 0.415, 0.339, 1.217, 1.734, 1.025],
    "NVP3_sum": [0.189, 0.115, 0.155, 0.304, 0.913, 0.657],
    "NVP4_sum": [0.079, 0.059, 0.022, 0.183, 0.487, 0.328],
    "NVP5_sum": [0.01, 0.03, 0.006, 0.03, 0.091, 0.036],
    "GVP0_sum": [2.01, 2.649, 2.696, 2.683, 2.644, 1.98],
    "GVP1_sum": [0.444, 0.529, 0.529, 0.524, 0.535, 0.401],
}

df = pd.DataFrame(data)

# 1. Bar plot of average times for each process across PIDs
fig, ax = plt.subplots(figsize=(10, 6))
df.set_index("PID")[["resize_avg", "resize_itl_avg", "yuv2rgb_avg"]].plot(kind="bar", ax=ax)
ax.set_title("Average Times for Each Process Across PIDs")
ax.set_xlabel("PID")
ax.set_ylabel("Average Time (ms)")
plt.xticks(rotation=0)

# 2. Bar plot of Min, Max, and Average Times for Each Process for PID 817279
fig, ax = plt.subplots(figsize=(12, 6))

index = ['resize', 'resize_itl', 'yuv2rgb']
times_data = {
    "Min": df.loc[df['PID'] == 817279, ['resize_min', 'resize_itl_min', 'yuv2rgb_min']].values.flatten(),
    "Max": df.loc[df['PID'] == 817279, ['resize_max', 'resize_itl_max', 'yuv2rgb_max']].values.flatten(),
    "Average": df.loc[df['PID'] == 817279, ['resize_avg', 'resize_itl_avg', 'yuv2rgb_avg']].values.flatten(),
}

df_times = pd.DataFrame(times_data, index=index)

df_times.plot(kind="bar", ax=ax)
ax.set_title("Min, Max, and Average Times for Each Process for PID 817279")
ax.set_xlabel("Process")
ax.set_ylabel("Time (ms)")
plt.xticks(rotation=0)

# 3. Separate bar plot for NVP sum percentages
fig, ax = plt.subplots(figsize=(10, 6))
df.set_index("PID")[["NVP0_sum", "NVP1_sum", "NVP2_sum", "NVP3_sum", "NVP4_sum", "NVP5_sum"]].plot(kind="bar", stacked=True, ax=ax)
ax.set_title("NVP Sum Percentage Across PIDs")
ax.set_xlabel("PID")
ax.set_ylabel("Sum Percentage (%)")
plt.xticks(rotation=0)

# 4. Separate bar plot for GVP sum percentages
fig, ax = plt.subplots(figsize=(10, 6))
df.set_index("PID")[["GVP0_sum", "GVP1_sum"]].plot(kind="bar", stacked=True, ax=ax)
ax.set_title("GVP Sum Percentage Across PIDs")
ax.set_xlabel("PID")
ax.set_ylabel("Sum Percentage (%)")
plt.xticks(rotation=0)

# Show all plots
plt.tight_layout()
plt.show()

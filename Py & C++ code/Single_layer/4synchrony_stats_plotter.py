
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import pandas as pd
import os                                               # Importing the os module to interact with the operating system
import re

# ------------------------------ Helper Function ------------------------------

def stats_summary(data, confidence=0.95):
    data = np.array(data)
    n = len(data)
    mean = np.mean(data)
    std = np.std(data, ddof=1)
    sem = std / np.sqrt(n)

    # Calculate two-tailed confidence interval using t-distribution
    t_score = stats.t.ppf((1 + confidence) / 2.0, df=n-1)
    margin = t_score * sem
    ci = (mean - margin, mean + margin)

    return {
        'mean': mean,
        'std': std,
        'sem': sem,
        'confidence_interval': ci
    }

# ------------------------------ Configuration ------------------------------

last_coupling = 4          # Maximum coupling strength value
directory_output = f'./Python/Synchrony(T_L_M_R)/'

# ------------------------------ Load and Analyze Data ------------------------------

def list_sorted_files(directory):
    #Returns a sorted list of .npz file names (without extension) in the specified directory.
    #Sorting is based on the float number following 'k=' in the file name.
    try:
        # List all file names in the directory
        files = os.listdir(directory)
        files = [f for f in files if os.path.isfile(os.path.join(directory, f))]

        # Remove the .npz extension if present
        files = [f[:-4] if f.endswith('.npz') else f for f in files]

        # Sort files numerically based on the value after 'k='
        files = sorted(files, key=lambda x: float(re.search(r'k=([0-9.]+)', x).group(1)))

        return files

    except FileNotFoundError:
        raise FileNotFoundError(f"The directory {directory} was not found.")
    except Exception as e:
        raise e


# 🧾 Get the sorted list of files
files = list_sorted_files(directory_output)

results = []
for file in files:
    loaded = np.load(directory_output + file + '.npz')
    data_sync = loaded['phases']
    results.append(stats_summary(data_sync))

# Extract mean and standard deviation for plotting
mean_results = [res['mean'] for res in results]
std_results = [res['std'] for res in results]

# ------------------------------ Plotting ------------------------------

k_arr = np.linspace(0.0, last_coupling, len(results))  # Coupling values (K)

plt.figure(figsize=(16, 4))  # Wide figure for better visibility

# Plot mean with standard deviation as error bars
plt.errorbar(k_arr, mean_results, yerr=std_results, fmt='-o',
             ecolor='gray', capsize=5, label='Mean ± Std')

plt.xlabel("K")
plt.ylabel("R")
plt.title(f"Total Synchronization (R vs K)")
plt.xlim(0, last_coupling)
plt.ylim(0, 1.02)
plt.grid(True)
plt.legend()

# Save the figure to file
plt.savefig(f"RK.png", dpi=300)
# plt.show()  # Uncomment to display plot interactively

# -------------------- Save Statistics to TXT Using NumPy --------------------

# Convert stats to 2D array: each row contains [mean, std, sem, ci_low, ci_high]
stat_array = np.array([
    [res['mean'], res['std'], res['sem'], *res['confidence_interval']]
    for res in results
])

# Header for the TXT file
header = "Mean	Std	SEM	CI_Low	CI_High"

# Output path
os.makedirs('./Python/Synchrony(Mean_std_sem_Confidence)/', exist_ok=True)

output_txt_path = f'./Python/Synchrony(Mean_std_sem_Confidence)/R.txt'

# Save to .txt file with tab separation
np.savetxt(output_txt_path, stat_array, delimiter='	', header=header, comments='', fmt='%.6f')

print(f"✅ Stats saved to TXT file at: {output_txt_path}")


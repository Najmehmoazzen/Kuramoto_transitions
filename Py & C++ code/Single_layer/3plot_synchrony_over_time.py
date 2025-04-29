
# 📦 Import required libraries
import os
import re
import matplotlib.pyplot as plt
import numpy as np

# 🔄 Set whether the data is Forward or Backward

directory_output = f'./Python/Synchrony(T_L_M_R)/'

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

# ⏱️ Create time array corresponding to the synchronization data
time_arr = np.linspace(0, 80, 8000)

# 🎨 Set up the figure
plt.figure(figsize=(16, 4))  # Wider plot for better visualization

# 🔁 Loop through each file and plot the synchronization data
num_k = len(files)
for i, file in enumerate(files, start=1):
    data = np.load(os.path.join(directory_output, file + '.npz'))['phases']
    
    # Plot each line with varying grayscale (darker for higher coupling)
    plt.plot(time_arr, data, c=str((num_k - i) / num_k))

# 🧭 Add plot labels and settings
plt.xlabel("Time (t)")
plt.ylabel("Order Parameter (r)")
plt.title(f"Time Evolution of Synchronization (r vs t) ")
plt.xlim(0, 80)
plt.ylim(0, 1)
plt.grid(True)

# 💾 Save the plot to a file
plt.savefig(f"rt.png", dpi=300)

# 📌 Uncomment to show plot in an interactive window
# plt.show()

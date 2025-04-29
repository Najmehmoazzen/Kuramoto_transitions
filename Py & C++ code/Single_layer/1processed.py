
import os                                               # Importing the os module to interact with the operating system
directory_path = './Save/Phases(time)VS(Node)/'         # Path to the directory from which we want to retrieve files
def list_files(directory):                              # Function to get a list of files from the specified directory
    try:
        files = os.listdir(directory)                   # List all files and directories in the given path
        files = [f for f in files if os.path.isfile(os.path.join(directory, f))] # Filter out only files (ignore directories)
        files = [f[:-4] if f.endswith('.txt') else f for f in files] # Remove the '.txt' extension (last 4 characters) from file names
        return files                                    # Return the processed list of file names
    except FileNotFoundError:
        return f"The directory {directory} was not found." # Handle case where the directory does not exist
    except Exception as e:
        return str(e)                                   # Handle any other unexpected exceptions
files = list_files(directory_path)                      # Call the function with the specified directory path
print("Files in the directory:", files)                 # Print the result

import numpy as np  # Import NumPy for numerical operations
import os  # Import os for interacting with the file system
directory_path = './Save/Phases(time)VS(Node)/'# Define input and output directories
directory_output = './Python/Phases/'
os.makedirs('./Python/', exist_ok=True)# Create the output folders if they do not already exist
os.makedirs(directory_output, exist_ok=True)
print('📂 Create folders for saving data.')
for file in files:# Loop through all files in the list (assuming 'files' is defined earlier)
    print(file)  # Print the current file name being processed
    file_path = directory_path + file  # Construct the full file path (without .txt yet)
    try:
        data = np.loadtxt(file_path + '.txt')        # Load the text data from file (adding .txt extension)
        data = data[:, 1:]        # Remove the first column (e.g., time column) and keep the rest
        data[data < 0] += 2 * np.pi        # Shift any negative phase values by adding 2π
        scale_factor = 100        # Scale the data to keep two decimal places, convert to int16
        data_scaled = np.round(data * scale_factor).astype(np.int16)
        #n_to_remove = 10000        # Remove the first 10002 rows (e.g., burn-in or irrelevant data)
        #dataint16_trimmed = data_scaled[n_to_remove:, :]
        np.savez_compressed(directory_output + file + '.npz', phases=data_scaled)        # Save the processed 2D array in compressed format
    except Exception as e:
        print("❌ Error reading the file:", e)        # Print error message if file reading or processing fails
print(data.shape)# Print the final shape of the last processed dataset
    
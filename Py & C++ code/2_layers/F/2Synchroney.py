
import numpy as np
import os                                               # Importing the os module to interact with the operating system
import re

def list_files(directory):                              # Function to get a list of files from the specified directory
    try:
        files = os.listdir(directory)                   # List all files and directories in the given path
        files = [f for f in files if os.path.isfile(os.path.join(directory, f))] # Filter out only files (ignore directories)
        files = [f[:-4] if f.endswith('.npz') else f for f in files] # Remove the '.txt' extension (last 4 characters) from file names
        return files                                    # Return the processed list of file names
    except FileNotFoundError:
        return f"The directory {directory} was not found." # Handle case where the directory does not exist
    except Exception as e:
        return str(e)                                   # Handle any other unexpected exceptions
def phase_coherence(angles_vec):
    '''
    Compute global order parameter R_t - mean length of resultant vector
    '''
    suma = sum([(np.e ** (1j * i)) for i in angles_vec])
    return abs(suma / len(angles_vec))




Layer="L1"
Forward_or_Backward="F"

directory_path= f'./Python/Phases/{Forward_or_Backward}/{Layer}/'


files = list_files(directory_path)                      # Call the function with the specified directory path

# sort based on the number after 'k=' and before 'layer1'
files = sorted(files, key=lambda x: float(re.search(r'k=([0-9.]+)', x).group(1)))
print(files)

os.makedirs('./Python/', exist_ok=True)
os.makedirs('./Python/Synchrony(T_L_M_R)', exist_ok=True)
os.makedirs(f'./Python/Synchrony(T_L_M_R)/{Forward_or_Backward}/', exist_ok=True)
os.makedirs(f'./Python/Synchrony(T_L_M_R)/{Forward_or_Backward}/{Layer}/', exist_ok=True)

print('📂Create a folders for Save data. ')
k=0
scale_factor = 100  
for file in files:
    loaded = np.load(directory_path + file+'.npz')
    data=loaded['phases'].astype(np.float32) / scale_factor
    arr_sync_total=np.zeros(data[:,0].shape)
    for i in range(len(data[:,0])):
        arr_sync_total[i]=phase_coherence(data[i,:])
    np.savez_compressed(f'./Python/Synchrony(T_L_M_R)/{Forward_or_Backward}/{Layer}/'+files[k], phases=arr_sync_total)
    print(f"✅{files[k]} -> Saved.")
    k+=1

print("✅📃 The file (Synchrony) was successfully created.")




Layer="L2"
Forward_or_Backward="F"

directory_path= f'./Python/Phases/{Forward_or_Backward}/{Layer}/'


files = list_files(directory_path)                      # Call the function with the specified directory path

# sort based on the number after 'k=' and before 'layer1'
files = sorted(files, key=lambda x: float(re.search(r'k=([0-9.]+)', x).group(1)))
print(files)

os.makedirs('./Python/', exist_ok=True)
os.makedirs('./Python/Synchrony(T_L_M_R)', exist_ok=True)
os.makedirs(f'./Python/Synchrony(T_L_M_R)/{Forward_or_Backward}/', exist_ok=True)
os.makedirs(f'./Python/Synchrony(T_L_M_R)/{Forward_or_Backward}/{Layer}/', exist_ok=True)

print('📂Create a folders for Save data. ')
k=0
scale_factor = 100  
for file in files:
    loaded = np.load(directory_path + file+'.npz')
    data=loaded['phases'].astype(np.float32) / scale_factor
    arr_sync_total=np.zeros(data[:,0].shape)
    for i in range(len(data[:,0])):
        arr_sync_total[i]=phase_coherence(data[i,:])
    np.savez_compressed(f'./Python/Synchrony(T_L_M_R)/{Forward_or_Backward}/{Layer}/'+files[k], phases=arr_sync_total)
    print(f"✅{files[k]} -> Saved.")
    k+=1

print("✅📃 The file (Synchrony) was successfully created.")

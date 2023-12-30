import numpy as np
import matplotlib.pyplot as plt

def read_file(address_name,name_of_file):
    # Specify the path to your file
    file_path = address_name+name_of_file

    # Initialize empty lists for each column
    column1 = []
    column2 = []
    column3 = []

    # Read the file and populate the column lists
    with open(file_path, 'r') as file:
        for line in file:
            # Split each line into a list of values
            values = line.strip().split('\t')
            
            # Convert values to the appropriate data type (float or int)
            val1, val2, val3 = map(float, values)
            
            # Append values to the corresponding columns
            column1.append(val1)
            column2.append(val2)
            column3.append(val3)

    return column1,column2

def plot(address_name,name_of_file):

    x,y=read_file(address_name,name_of_file)

    plt.plot(x,y)
    plt.scatter(x,y)
    #plt.show()
    plt.xlabel("coupling strength (k)", fontsize=10)
    plt.ylabel("Synchrony (r)", fontsize=10)
    plt.subplots_adjust(top = 0.98, bottom=0.08,left=0.06,right=0.98, hspace=0.2, wspace=0.44)
    plt.gcf().set_size_inches(12, 6.5)# don't change it
    plt.savefig(address_name+name_of_file+'.png',dpi=300)
    #plt.close()
    pass

def open_all_files(directory_path):
    import os
    file_list = os.listdir(directory_path)
    return file_list

def main():
    address_name='./Save/Avg_Sync/layer1/'
    plot(address_name,open_all_files(address_name)[0])
    print("Done :)")
    pass


if __name__=="__main__":
    main()
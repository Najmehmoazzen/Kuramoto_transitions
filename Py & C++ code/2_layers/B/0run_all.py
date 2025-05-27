import subprocess

# List of Python scripts to run in order
scripts = ['1processed.py', '2Synchroney.py', '3plot_synchrony_over_time.py', '4synchrony_stats_plotter.py']

for script in scripts:
    print(f"Running {script}...")
    result = subprocess.run(['python3', script], check=True, capture_output=True, text=True)
    
    print(f"Output of {script}:\n{result.stdout}")
    if result.stderr:
        print(f"Error in {script}:\n{result.stderr}")

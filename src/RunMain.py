import os
import subprocess
import sys

def run_performance_comparison():
    """
    Run the performance comparison executable.
    Interacts with the program through stdin/stdout.
    """
    try:
        inputs = [
            "1",    
            "1000",  
            "2",    
            "1000",  
            "3",    
            "1000",  
            "4",     
            "1000", 
            "5"
        ]


        process = subprocess.Popen(
            "./src/main.exe", 
            stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE, 
            text=True
        )


        for input_val in inputs:
            process.stdin.write(input_val + "\n")
            process.stdin.flush()


        stdout, stderr = process.communicate()
        
        print("Program Output:")
        print(stdout)
        
        if stderr:
            print("Errors:", stderr)

    except Exception as e:
        print(f"Error running performance comparison: {e}")

def check_prerequisites():
    """
    Check if required files and dependencies exist.
    """

    exe_path = "./src/main.exe"
    if not os.path.exists(exe_path):
        print(f"Executable not found: {exe_path}")
        return False


    viz_scripts = [
        "src/visualize_comparison.py",
        "src/heap_visualize_comparison.py"
    ]

    for script in viz_scripts:
        if not os.path.exists(script):
            print(f"Missing visualization script: {script}")
            return False

    return True

def main():
    if not check_prerequisites():
        print("Please ensure all required files are in place.")
        sys.exit(1)

    run_performance_comparison()

if __name__ == "__main__":
    main()
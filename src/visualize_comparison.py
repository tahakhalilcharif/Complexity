import pandas as pd
import matplotlib.pyplot as plt

CSV_FILE = "comparison_results.csv"

def plot_comparison():
    try:
        data = pd.read_csv(CSV_FILE)
    except FileNotFoundError:
        print(f"Error: File {CSV_FILE} not found.")
        return

    operations = data['Operation'].unique()
    
    for operation in operations:
        operation_data = data[data['Operation'] == operation]
        
        pivot_data = operation_data.pivot(index='Size', columns='Structure', values='TimeTaken')

        plt.figure(figsize=(10, 6))
        for structure in pivot_data.columns:
            plt.plot(pivot_data.index, pivot_data[structure], marker='o', label=structure)
        
        plt.title(f"Comparison of {operation} Times", fontsize=16)
        plt.xlabel("Size of Dataset", fontsize=14)
        plt.ylabel("Execution Time (seconds)", fontsize=14)
        plt.legend(title="Data Structure", fontsize=12)
        plt.grid(True)
        plt.tight_layout()

        plot_filename = f"{operation.lower().replace(' ', '_')}_comparison.png"
        plt.savefig(plot_filename)
        plt.show()
        print(f"Graph for {operation} saved as {plot_filename}")

if __name__ == "__main__":
    plot_comparison()

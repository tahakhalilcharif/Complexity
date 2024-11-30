import matplotlib.pyplot as plt
import pandas as pd
import os

# Get the directory of the current script
current_dir = os.path.dirname(os.path.abspath(__file__))

# Load the CSV file into a pandas DataFrame
file_path = 'C:/Users/hp/Desktop/Complexity/results/arbreBinaire/arbre_benchmark.csv'
data = pd.read_csv(file_path)

# Define output paths for the graphs
insertion_graph_path = os.path.join(current_dir, 'insertion_time_vs_size.png')
search_graph_path = os.path.join(current_dir, 'search_time_vs_size.png')
delete_graph_path = os.path.join(current_dir, 'delete_time_vs_size.png')

# Plot and save the first figure: Insertion Time vs Size
plt.figure(figsize=(8, 6))
plt.plot(data["Size"], data["insertion"], label="Insertion Time", marker="o", color="blue")
plt.xscale("log")
plt.yscale("log")
plt.title("Insertion Time vs Size")
plt.xlabel("Size")
plt.ylabel("Time (seconds)")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig(insertion_graph_path)  # Save the first figure
plt.close()

# Plot and save the second figure: Search Time vs Size
plt.figure(figsize=(8, 6))
plt.plot(data["Size"], data["search"], label="Search Time", marker="o", color="green")
plt.xscale("log")
plt.yscale("log")
plt.title("Search Time vs Size")
plt.xlabel("Size")
plt.ylabel("Time (seconds)")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig(search_graph_path)  # Save the second figure
plt.close()

# Plot and save the third figure: Delete Time vs Size
plt.figure(figsize=(8, 6))
plt.plot(data["Size"], data["delete"], label="Delete Time", marker="o", color="red")
plt.xscale("log")
plt.yscale("log")
plt.title("Delete Time vs Size")
plt.xlabel("Size")
plt.ylabel("Time (seconds)")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig(delete_graph_path)  # Save the third figure
plt.close()

print(f"Graphs have been saved in the directory: {current_dir}")
print("Saved files:")
print(f"- {insertion_graph_path}")
print(f"- {search_graph_path}")
print(f"- {delete_graph_path}")

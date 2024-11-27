import matplotlib.pyplot as plt
import pandas as pd

# Load the CSV file into a pandas DataFrame
file_path = '/Users/anischetouane/Desktop/m1/comp/projects/part1/Complexity/results/bTrees/bTree_benchmark.csv'
data = pd.read_csv(file_path)

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
plt.savefig('insertion_time_vs_size.png')  # Save the first figure
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
plt.savefig('search_time_vs_size.png')  # Save the second figure
plt.close()

# Plot and save the third figure: delete Time vs Size
plt.figure(figsize=(8, 6))
plt.plot(data["Size"], data["delete"], label="delete Time", marker="o", color="green")
plt.xscale("log")
plt.yscale("log")
plt.title("delete Time vs Size")
plt.xlabel("Size")
plt.ylabel("Time (seconds)")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig('delete_time_vs_size.png')  # Save the second figure
plt.close()


print("Graphs have been saved as 'insertion_time_vs_size.png' and 'search_time_vs_size.png' and delete_time_vs_size.png")

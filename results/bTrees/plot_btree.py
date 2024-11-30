# import matplotlib.pyplot as plt # type: ignore
# import pandas as pd # type: ignore

# # Load the CSV file into a pandas DataFrame
# file_path = '/Users/anischetouane/Desktop/m1/comp/projects/part1/Complexity/results/bTrees/bTree_benchmark.csv'
# data = pd.read_csv(file_path)

# # Plot and save the first figure: Insertion Time vs Size
# plt.figure(figsize=(8, 6))
# plt.plot(data["Size"], data["insertion"], label="Insertion Time", marker="o", color="blue",linestyle="None")
# plt.xscale("log")
# plt.yscale("log")
# plt.title("Insertion Time vs Size")
# plt.xlabel("Size")
# plt.ylabel("Time (seconds)")
# plt.legend()
# plt.grid(True, which="both", linestyle="--", linewidth=0.5)
# plt.savefig('insertion_time_vs_size.png')  # Save the first figure
# plt.close()

# # Plot and save the second figure: Search Time vs Size
# plt.figure(figsize=(8, 6))
# plt.plot(data["Size"], data["search"], label="Search Time", marker="o", color="green",linestyle="None")
# plt.xscale("log")
# plt.yscale("log")
# plt.title("Search Time vs Size")
# plt.xlabel("Size")
# plt.ylabel("Time (seconds)")
# plt.legend()
# plt.grid(True, which="both", linestyle="--", linewidth=0.5)
# plt.savefig('search_time_vs_size.png')  # Save the second figure
# plt.close()

# # Plot and save the third figure: delete Time vs Size
# plt.figure(figsize=(8, 6))
# plt.plot(data["Size"], data["delete"], label="delete Time", marker="o", color="green",linestyle="None")
# plt.xscale("log")
# plt.yscale("log")
# plt.title("delete Time vs Size")
# plt.xlabel("Size")
# plt.ylabel("Time (seconds)")
# plt.legend()
# plt.grid(True, which="both", linestyle="--", linewidth=0.5)
# plt.savefig('delete_time_vs_size.png')  # Save the second figure
# plt.close()


# print("Graphs have been saved as 'insertion_time_vs_size.png' and 'search_time_vs_size.png' and delete_time_vs_size.png")
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load the results file
data = pd.read_csv("/Users/anischetouane/Desktop/m1/comp/projects/part1/Complexity/results/bTrees/bTree_benchmark.csv")

# Define size ranges (you can adjust these ranges as needed)
bins = [500000, 1000000,3000000, 10000000]
data['Range'] = pd.cut(data['Size'], bins=bins, labels=bins[:-1])

# Calculate the averages for each range
aggregated = data.groupby('Range')[['insertion', 'search', 'delete']].mean().reset_index()

# Plot the averaged data
plt.figure(figsize=(10, 6))
plt.plot(aggregated['Range'], aggregated['insertion'], label="Insertion Time (Averaged)", color='blue', marker='o')
plt.plot(aggregated['Range'], aggregated['search'], label="Search Time (Averaged)", color='green', marker='o')
plt.plot(aggregated['Range'], aggregated['delete'], label="Delete Time (Averaged)", color='red', marker='o')

# Configure the plot
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Size of B-tree (Grouped by Range)")
plt.ylabel("Time (seconds)")
plt.title("Averaged Experimental Time Complexity of B-tree Operations")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.show()
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import csv

# Path to the CSV file containing list operation results
csv_file = "results/lists/list_benchmark.csv" 
n, insertAtPosition_time, search_time, delete_time = [], [], [], []

# Read the data from the CSV file
with open(csv_file, 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        n.append(int(row['n']))
        insertAtPosition_time.append(float(row['insertAtPosition_time']))
        search_time.append(float(row['search_time']))
        delete_time.append(float(row['delete_time']))


# Graph for the insertion time at a specific position
plt.figure(figsize=(10, 6))
plt.plot(n, insertAtPosition_time, marker='o', color='orange', label='Insertion Time (At Position)')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('List Insertion Time (At Position)')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/lists/insertion_time_at_position.png")
plt.show()

# Graph for the deletion time
plt.figure(figsize=(10, 6))
plt.plot(n, delete_time, marker='o', color='r', label='Deletion Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('List Deletion Time')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/lists/deletion_time.png")
plt.show()

# Graph for the search time
plt.figure(figsize=(10, 6))
plt.plot(n, search_time, marker='o', color='g', label='Search Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('List Search Time')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/lists/search_time.png")
plt.show()

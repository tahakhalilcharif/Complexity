import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import csv

# Read data from CSV file
csv_file = "results\heaps\heap_benchmark.csv"
n, insert_time, delete_time, search_time = [], [], [], []

with open(csv_file, 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        n.append(int(row['n']))
        insert_time.append(float(row['insert_time']))
        delete_time.append(float(row['delete_time']))
        search_time.append(float(row['search_time']))

# Plot insertion time
plt.figure(figsize=(10, 6))
plt.plot(n, insert_time, marker='o', label='Insertion Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Insertion Time')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/heaps/insertion_time_updated.png")
plt.show()

# Plot deletion time
plt.figure(figsize=(10, 6))
plt.plot(n, delete_time, marker='o', color='r', label='Deletion Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Deletion Time')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/heaps/deletion_time_updated.png")
plt.show()

# Plot search time
plt.figure(figsize=(10, 6))
plt.plot(n, search_time, marker='o', color='g', label='Search Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Search Time')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/heaps/search_time_updated.png")
plt.show()

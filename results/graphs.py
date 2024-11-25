import matplotlib.pyplot as plt
import matplotlib.ticker as ticker


n = [
    1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
    20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 200000,
    300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000, 2000000,
    3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000,
    20000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000,
    90000000, 100000000, 200000000, 300000000, 400000000
]
insert_time = [
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.001000, 0.000000,
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.001000,
    0.002000, 0.002000, 0.002000, 0.002000, 0.003000, 0.002000, 0.004000,
    0.003000, 0.007000, 0.011000, 0.014000, 0.018000, 0.025000, 0.025000,
    0.030000, 0.035000, 0.036000, 0.072000, 0.107000, 0.151000, 0.177000,
    0.214000, 0.254000, 0.282000, 0.316000, 0.348000, 0.716000, 1.067000,
    1.544000, 1.786000, 2.147000, 2.513000, 2.858000, 3.151000, 3.539000,
    7.335000, 10.378000, 14.222000
]
delete_time = [
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
    0.001000, 0.001000, 0.001000, 0.001000, 0.001000, 0.001000, 0.003000,
    0.005000, 0.006000, 0.008000, 0.011000, 0.012000, 0.016000, 0.017000,
    0.018000, 0.039000, 0.059000, 0.081000, 0.101000, 0.125000, 0.147000,
    0.169000, 0.196000, 0.256000, 0.497000, 0.865000, 1.192000, 1.389000,
    1.807000, 2.009000, 2.371000, 2.736000, 3.098000, 6.599000, 9.808000,
    13.728000, 17.330000, 21.820000, 25.709000, 26.737000, 31.045000,
    34.819000, 69.181000, 106.569000, 140.912000
]
search_time = [
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 0.000000, 0.001000, 0.001000, 0.001000, 0.001000,
    0.001000, 0.001000, 0.002000, 0.003000, 0.004000, 0.006000, 0.006000,
    0.007000, 0.008000, 0.010000, 0.011000, 0.012000, 0.033000, 0.071000,
    0.049000, 0.059000, 0.074000, 0.090000, 0.097000, 0.112000, 0.125000,
    0.243000, 0.374000, 0.480000
]

plt.figure(figsize=(10, 6))
plt.plot(n, insert_time, marker='o', label='Insertion Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Insertion Time')
plt.grid(True, linestyle='--', linewidth=0.5)

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/insertion_time_updated.png")
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(n, delete_time, marker='o', color='r', label='Deletion Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Deletion Time')
plt.grid(True, linestyle='--', linewidth=0.5)

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/deletion_time_updated.png")
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(n, search_time, marker='o', color='g', label='Search Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Search Time')
plt.grid(True, linestyle='--', linewidth=0.5)

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/search_time_updated.png")
plt.show()
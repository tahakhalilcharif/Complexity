import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

data = pd.read_csv("results/heap_construction_times.csv")

sizes = data["Size"]
times_nlogn = data["Time_NlogN"]
times_n = data["Time_N"]

plt.figure(figsize=(10, 6))
plt.plot(sizes, times_nlogn, marker='o', label='O(n log n) Construction', color='b')
plt.plot(sizes, times_n, marker='x', label='O(n) Construction', color='g')

plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Heap Construction Complexity Comparison')
plt.grid(True, linestyle='--', linewidth=0.5)

plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))

plt.legend()

plt.savefig("results/heap_construction_comparison_updated.png")
plt.show()

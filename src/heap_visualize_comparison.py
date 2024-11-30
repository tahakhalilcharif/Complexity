import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('heap_sort_results.csv')

print(data.head())

heap_types = data['Heap Type'].unique()
operations = data['Operation'].unique()

plt.figure(figsize=(12, 8))

for heap_type in heap_types:
    for operation in operations:
        subset = data[(data['Heap Type'] == heap_type) & (data['Operation'] == operation)]
        if not subset.empty:
            plt.plot(subset['Size'], subset['TimeTaken'], label=f"{heap_type} - {operation}")

plt.xlabel('Input Size')
plt.ylabel('Time Taken (seconds)')
plt.title('Heap Sort Performance Analysis')
plt.legend()

plt.grid(True)
plt.show()

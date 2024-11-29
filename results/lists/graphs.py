import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Exemple de données pour les listes
n = [
    1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
    20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000
]
insert_time = [
    0.000000, 0.000001, 0.000003, 0.000012, 0.000024, 0.000035, 0.000050,
    0.000062, 0.000075, 0.000088, 0.000100, 0.000112, 0.000125, 0.000250,
    0.000375, 0.000500, 0.000625, 0.000750, 0.000875, 0.001000, 0.001125, 0.001250
]
delete_time = [
    0.000000, 0.000002, 0.000006, 0.000020, 0.000040, 0.000060, 0.000080,
    0.000100, 0.000120, 0.000140, 0.000160, 0.000180, 0.000200, 0.000400,
    0.000600, 0.000800, 0.001000, 0.001200, 0.001400, 0.001600, 0.001800, 0.002000
]
search_time = [
    0.000000, 0.000001, 0.000005, 0.000015, 0.000030, 0.000045, 0.000060,
    0.000075, 0.000090, 0.000105, 0.000120, 0.000135, 0.000150, 0.000300,
    0.000450, 0.000600, 0.000750, 0.000900, 0.001050, 0.001200, 0.001350, 0.001500
]

# Graphe pour le temps d'insertion
plt.figure(figsize=(10, 6))
plt.plot(n, insert_time, marker='o', label='Insertion Time')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('List Insertion Time')
plt.grid(True, linestyle='--', linewidth=0.5)
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f"{int(x):,}"))
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: f"{y:.6f}"))
plt.legend()
plt.savefig("results/lists/insertion_time.png")
plt.show()

# Graphe pour le temps de suppression
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

# Graphe pour le temps de recherche
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

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import csv

# Chemin du fichier CSV contenant les données des listes
csv_file = "results/lists/list_benchmark.csv"
n, insertAtPosition_time , search_time,delete_time = [], [], [], []

# Lecture des données depuis le fichier CSV
with open(csv_file, 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        n.append(int(row['n']))
        insertAtPosition_time.append(float(row['insertAtPosition_time']))
        delete_time.append(float(row['delete_time']))
        search_time.append(float(row['search_time']))

# Graphe pour le temps d'insertion à une position spécifique
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

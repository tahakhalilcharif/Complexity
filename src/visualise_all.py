import pandas as pd
import matplotlib.pyplot as plt

def plot_comparison(csv_file, title, y_label, output_file, columns_to_plot):
    # Read the CSV file into a pandas DataFrame
    data = pd.read_csv(csv_file)

    # Plot each column
    plt.figure(figsize=(10, 6))
    for column in columns_to_plot:
        plt.plot(data['Iterations'], data[column], label=column)

    # Add labels, title, legend, and grid
    plt.xlabel('Iterations')
    plt.ylabel(y_label)
    plt.title(title)
    plt.legend()
    plt.grid(True)

    # Save the plot as an image file
    plt.savefig(output_file)
    print(f"Plot saved as {output_file}")
    plt.show()

def visualize_all():
    # Visualize insertion comparison
    plot_comparison(
        csv_file="src/Insertion_Comparison.csv",
        title="Insertion Performance Comparison",
        y_label="Time (seconds)",
        output_file="results/structures_comparison/Insertion_Comparison.png",
        columns_to_plot=["BST", "BTree", "DLL", "Heap"]
    )

    plot_comparison(
        csv_file="src/Creation_Comparison.csv",
        title="Creation Performance Comparison",
        y_label="Time (seconds)",
        output_file="results/structures_comparison/Creation_Comparison.png",
        columns_to_plot=["BST", "BTree", "DLL", "Heap"]
    )

    # Visualize search comparison
    plot_comparison(
        csv_file="src/Search_Comparison.csv",
        title="Search Performance Comparison",
        y_label="Time (seconds)",
        output_file="results/structures_comparison/Search_Comparison.png",
        columns_to_plot=["BST", "BTree", "DLL", "Heap"]
    )

    # Visualize deletion comparison
    plot_comparison(
        csv_file="src/Deletion_Comparison.csv",
        title="Deletion Performance Comparison",
        y_label="Time (seconds)",
        output_file="results/structures_comparison/Deletion_Comparison.png",
        columns_to_plot=["BST", "BTree", "DLL", "Heap"]
    )

    # Visualize heap sort comparison
    plot_comparison(
        csv_file="src/HeapSort_Comparison.csv",
        title="Heap Sort Performance Comparison",
        y_label="Time (seconds)",
        output_file="results/structures_comparison/HeapSort_Comparison.png",
        columns_to_plot=["Build_NlogN", "Build_N"]
    )

if __name__ == "__main__":
    visualize_all()

# Performance Comparison of Data Structures

This project performs performance comparisons of various data structures (Binary Search Tree, B-Tree, Doubly Linked List, and Heaps) using various operations such as Insertion, Search, Deletion, and Heap Sort. The performance is measured and visualized using graphs to compare the time taken by each operation for different data structures.

## Table of Contents
- [Project Description](#project-description)
- [Prerequisites](#prerequisites)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [Visualizing Results](#visualizing-results)
- [Contributing](#contributing)
- [License](#license)

## Project Description

This project is designed to:
1. Compare the performance of various data structures (`Binary Search Tree`, `B-Tree`, `Doubly Linked List`, and Heaps).
2. Measure the time taken for different operations like `Insertion`, `Search`, `Deletion`, and `Heap Sort`.
3. Generate visual graphs that compare the performance across the different operations and data structures.

The comparison is done by running a C program (`performance_comparison`) that interacts with the user, simulating different operations and collecting performance data. The results are then visualized using Python scripts.

## Prerequisites

To use this project, you will need the following:
- **C Compiler**: `gcc` (or equivalent) for compiling the C program.
- **Python 3.x**: Required for running the visualization scripts.
- **Python Libraries**: Install the necessary libraries to run the visualization scripts.

### Required Python Libraries:
- `matplotlib`
- `numpy`

You can install them using `pip`:

```bash
pip install matplotlib numpy
```

### Required Files:
Make sure the following files exist in the project directory structure:

**C Source Files:**
- `main.c`
- `../src/liste.c`
- `../src/arbrebinaire.c`
- `../src/btrees.c`
- `../src/maxheap.c`
- `../src/minheap.c`

**Header Files:**
- `../include/liste.h`
- `../include/arbrebinaire.h`
- `../include/btrees.h`
- `../include/maxheap.h`
- `../include/minheap.h`

**Python Visualization Scripts:**
- `visualize_comparison.py`
- `heap_visualize_comparison.py`

## Setup Instructions

### Clone the repository:
If you haven't already cloned the project repository, do so with:

```bash
git clone https://github.com/yourusername/performance-comparison.git
cd performance-comparison
```

### Ensure all dependencies are installed:
- Install C compiler (if not already installed).
- Install Python dependencies as mentioned in the prerequisites section.

### Compile the C Program:
The C program will need to be compiled before it can be executed. Run the following script to compile all required C source files:

```bash
python runMain.py
```

This will create an executable (`performance_comparison`) that can be run to simulate performance comparisons.

## Usage

After compiling the C program, you can run the program to perform the performance comparison of different data structures.

### Run the simulation:
To simulate user interaction and run the performance comparisons for various data structures, execute:

```bash
python runMain.py
```

This will simulate different operations and collect data on performance (time taken).

### View the results:
After running the performance comparison, the program will automatically generate graphs comparing the performance of different data structures and operations. These graphs will be generated using Python visualization scripts, and the results will be shown in your terminal.

If you want to manually view the graphs, you can run the following scripts:

```bash
python visualize_comparison.py
python heap_visualize_comparison.py
```

## Visualizing Results

The performance data collected by the C program is visualized using two Python scripts:

- `visualize_comparison.py`: This script generates graphs comparing the performance of the Binary Search Tree, B-Tree, and Doubly Linked List data structures.
- `heap_visualize_comparison.py`: This script visualizes the performance of the MaxHeap and MinHeap.

The visualizations allow you to see how different operations perform in terms of execution time for varying input sizes.

## Contributing

We welcome contributions to this project! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
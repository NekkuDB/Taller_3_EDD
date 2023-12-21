# NekkuDB/Taller_3_EDD

## Overview
The NekkuDB/Taller_3_EDD repository is a C++ project focused on reading and processing data from CSV files. It includes the implementation of a graph-like structure and performs operations like finding the shortest path based on certain criteria.

## Key Components

### CSVReader Class
- **Files**: [CSVReader.cpp](CSVReader.cpp), [CSVReader.h](CSVReader.h)
- **Functionality**:
  - Reads data from CSV files.
  - `readData()` method returns data as a vector of vector of strings.

### Main Application
- **File**: [main.cpp](main.cpp)
- **Functionality**:
  - Demonstrates the usage of the CSVReader class.
  - Implements nodes (`Nodo`) and edges (`Arista`) to create a graph.
  - Reads data from `servidores.csv` and `conexiones.csv`.
  - Performs graph-based operations.

### Data Files
- **[conexiones.csv](conexiones.csv)**: Contains data about connections between nodes.
- **[servidores.csv](servidores.csv)**: Contains information about various servers.

## CSVReader Class
### Header File
- [CSVReader.h](CSVReader.h): Declares the CSVReader class, constructor, and `readData` method.

### Implementation File
- [CSVReader.cpp](CSVReader.cpp): Implements the `readData` method.

## Main Application
### [main.cpp](main.cpp)
- Implements the main logic of the application.
- Processes data from CSV files to build and analyze a graph.

## Data Files
### [conexiones.csv](conexiones.csv)
- Contains columns like `idCliente`, `idServidor`, `velocidad`, and `distancia`.

### [servidores.csv](servidores.csv)
- Contains server information (`id`,`nombre`, and `tipo`).

## Getting Started

These instructions will guide you through the process of setting up, running, and using the NekkuDB/Taller_3_EDD project.

### Setting Up the Project

1. **Clone the Repository**:
   Clone the repository to your local machine using Git:
git clone https://github.com/NekkuDB/Taller_3_EDD.git


Navigate to the cloned directory:
cd Taller_3_EDD


2. **Prerequisites**:
Ensure you have a C++ compiler (like GCC, Clang, or MSVC) and the standard C++ library installed.

3. **Compile the Code**:
Compile the source files using your compiler. For example, with GCC:
g++ -o main CSVReader.cpp main.cpp


### Running the Project

1. **Execute the Compiled Program**:
Run the compiled executable: ./main


2. **Follow On-Screen Prompts**:
Interact with the program as per the on-screen instructions.

### Using the Project

- The application reads data from `servidores.csv` and `conexiones.csv` to construct a graph and performs various operations.
- Ensure the CSV files are in the correct format and located in the project directory.
- The program may output results to the console or generate files like `ruta.csv`.

### Troubleshooting

If you encounter issues, ensure all prerequisites are installed and CSV files are correctly formatted.

## Additional Notes
- The `main.cpp` file contains the core logic for processing data from the CSV files.


## Contributors
- Diego Ibacache Díaz
- Arturo Araya Bustos

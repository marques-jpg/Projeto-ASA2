# DAG Path Counter & Truck Routing

## Overview
This repository contains the C++ implementation of the second project for the Analysis and Synthesis of Algorithms (ASA) course. 

The project solves a logistics network problem modeled as a Directed Acyclic Graph (DAG). The system's objective is to distribute delivery tasks (pairs of origin and destination vertices) across a fleet of trucks. The assignment of a route $(u, v)$ to a specific truck is mathematically determined by the **total number of distinct paths** between the origin $u$ and the destination $v$, calculated using modular arithmetic.

## Architecture and Algorithms
To guarantee efficient execution and avoid Time Limit Exceeded (TLE) verdicts within the strict Mooshak evaluation system limits, the solution implements the following advanced techniques:

* **Topological Sorting (Kahn's Algorithm)**: Utilizes in-degree counting and a Queue (`std::queue`) to process nodes linearly, strictly respecting edge dependencies. It also acts as an early-exit mechanism to abort execution if the network contains cycles (i.e., it is not a DAG).
* **Graph Dynamic Programming (DP)**: The calculation of the total distinct paths is performed in a bottom-up manner. For each possible starting node, the algorithm propagates the path count to its neighbors by iterating over the previously computed topological order.
* **Modular Arithmetic**: To prevent integer overflow when counting paths in highly dense graphs, the route accumulation keeps a parallel counter modulo the number of trucks (`pathCountMod[neighbor] = (pathCountMod[neighbor] + pathCountMod[node]) % numTrucks`).
* **STL Data Structures**: Extensive use of `std::vector` for adjacency lists and maintaining the DP state arrays to ensure contiguous memory access and minimal overhead.

## Data Format

### Input
The program reads from *standard input* in the following structured format:
1. An integer representing the total number of nodes/locations in the network.
2. An integer representing the total number of trucks in the fleet (`numTrucks`).
3. Two integers representing the lower and upper bounds of the trucks whose results should be printed (`startTruck` and `endTruck`).
4. An integer representing the total number of unidirectional connections (edges).
5. This is followed by `E` lines, each containing a pair of integers `origin destination`, defining the possible paths.

### Output
For each truck within the range required by the input `[startTruck, endTruck]`, the program writes to *standard output*:
* `CX` where `X` corresponds to the truck identifier (starting at 1).
* A list of `origin,destination` pairs assigned to that truck, **sorted in lexicographical order**, separated by spaces.

## Installation and Execution

### Prerequisites
The implementation was developed in C++ (C++11 standard). It is strongly recommended to compile with the `-O3` optimization flag to ensure the best execution time, strictly complying with the automated evaluation system limits.

### Compilation
```bash
g++ -std=c++11 -O3 -Wall projeto25.cpp -o projeto

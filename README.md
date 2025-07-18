# Port & Polish: Software Optimization for RISC-V

This project implements and benchmarks matrix multiplication using both **naive** and **cache-aware (loop tiling/blocking)** approaches. It is designed for RISC-V software optimization but works on any platform for educational and benchmarking purposes.

---

## 🚀 Features

- Naive matrix multiplication using triple nested loops.
- Optimized matrix multiplication using loop tiling/blocking.
- Benchmarking of both approaches using high-resolution timers.
- Outputs performance results in a `benchmark_results.json` file.
- Written in portable C++17.
- Optional support for vector instructions via compiler flags (planned bonus).

---

## 📁 Project Structure

```

Port-Polish-Software-Optimization/
│
├── main.cpp                  # Main source code
├── benchmark\_results.json    # Output benchmark file (generated after run)
├── include/
│   └── nlohmann/json.hpp     # JSON header (optional if using manual formatting)
├── README.md                 # This file

````

---

## 🧪 Benchmarked Methods

### 1. Naive Matrix Multiplication

Triple loop, row-wise access:

```cpp
for (int i = 0; i < N; ++i)
  for (int j = 0; j < N; ++j)
    for (int k = 0; k < N; ++k)
      C[i][j] += A[i][k] * B[k][j];
````

### 2. Loop Tiling / Blocking

Improves cache usage by operating on small blocks:

```cpp
for (int ii = 0; ii < N; ii += B)
  for (int jj = 0; jj < N; jj += B)
    for (int kk = 0; kk < N; kk += B)
      // inner i,j,k loops within block
```

---

## 📦 Dependencies

If using JSON output:

* [`nlohmann/json`](https://github.com/nlohmann/json) (header-only)

Install it with:

```bash
wget https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp -P include/nlohmann
```

Or install system-wide on Debian/Ubuntu:

```bash
sudo apt install nlohmann-json-dev
```

---

## 🛠 Build Instructions

### With JSON output:

```bash
g++ main.cpp -Iinclude -std=c++17 -O2 -o matrix_benchmark
./matrix_benchmark
```

### Without JSON:

You can use the version that writes plain text manually if `json.hpp` is not available.

---

## 📈 Output

After running, you'll get a file like:

```json
{
  "matrix_size": 512,
  "block_size": 64,
  "naive_time_sec": 4.235682,
  "tiled_time_sec": 1.981312
}
```

---

## 💡 Optional Bonus

Add support for vector instructions via `#ifdef USE_VECTOR` blocks and compiler flags. (Pending)

---

## 🧑‍💻 Author

Aditya Yadav — Software Engineer | Backend & Performance Enthusiast
Inspired by the RISC-V optimization challenge

---

```
```

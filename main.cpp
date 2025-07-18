#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <nlohmann/json.hpp>

using namespace std;
using namespace std::chrono;
using json = nlohmann::json;

const int N = 512;
const int BLOCK_SIZE = 64;

vector<vector<int>> generate_matrix(int n) {
    vector<vector<int>> mat(n, vector<int>(n));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = dis(gen);
    return mat;
}

vector<vector<int>> naive_multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

vector<vector<int>> tiled_multiply(const vector<vector<int>>& A, const vector<vector<int>>& B, int blockSize) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int ii = 0; ii < n; ii += blockSize)
        for (int jj = 0; jj < n; jj += blockSize)
            for (int kk = 0; kk < n; kk += blockSize)
                for (int i = ii; i < min(ii + blockSize, n); ++i)
                    for (int j = jj; j < min(jj + blockSize, n); ++j)
                        for (int k = kk; k < min(kk + blockSize, n); ++k)
                            C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main() {
    auto A = generate_matrix(N);
    auto B = generate_matrix(N);

    auto start_naive = high_resolution_clock::now();
    auto C_naive = naive_multiply(A, B);
    auto end_naive = high_resolution_clock::now();

    auto start_tiled = high_resolution_clock::now();
    auto C_tiled = tiled_multiply(A, B, BLOCK_SIZE);
    auto end_tiled = high_resolution_clock::now();

    double naive_time = duration<double>(end_naive - start_naive).count();
    double tiled_time = duration<double>(end_tiled - start_tiled).count();

    json result;
    result["matrix_size"] = N;
    result["block_size"] = BLOCK_SIZE;
    result["naive_time_sec"] = naive_time;
    result["tiled_time_sec"] = tiled_time;

    ofstream file("benchmark_results.json");
    file << result.dump(2);
    file.close();

    return 0;
}

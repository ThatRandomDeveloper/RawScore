#include <iostream>
#include <thread>

// Function to get CPU information
void getCPUInfo() {
    std::system("lscpu");
}

// Function to perform a CPU benchmark
void performCPUBenchmark() {
    // Define the workload here, for example, calculating prime numbers
    // This is a simple workload for demonstration purposes
    const int n = 1000000;
    int primes = 0;
    for (int i = 2; i <= n; ++i) {
        bool isPrime = true;
        for (int j = 2; j*j <= i; ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes++;
        }
    }
    std::cout << "Primes found: " << primes << std::endl;
}


int main() {
    // Get CPU information
    std::cout << "CPU Information:" << std::endl;
    getCPUInfo();
    
    // Perform CPU benchmark
    std::cout << "\nStarting CPU Benchmark..." << std::endl;
    auto start = std::chrono::steady_clock::now();
    
    // You can adjust the number of threads based on your CPU's cores
    const int num_threads = std::thread::hardware_concurrency();
    std::thread threads[num_threads];
    
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(performCPUBenchmark);
    }
    
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    
    std::cout << "CPU Benchmark Finished." << std::endl;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    
    return 0;
}

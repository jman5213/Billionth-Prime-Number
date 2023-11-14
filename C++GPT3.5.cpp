#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    const int target_position = 1000000000;
    std::vector<int> primes;
    int current_number = 2;

    #pragma omp parallel
    {
        #pragma omp single
        {
            while (primes.size() < target_position) {
                #pragma omp task
                {
                    int local_current_number;
                    #pragma omp critical
                    {
                        local_current_number = current_number++;
                    }

                    if (is_prime(local_current_number)) {
                        #pragma omp critical
                        {
                            primes.push_back(local_current_number);
                        }
                    }
                }
            }
        }
    }

    std::cout << "The billionth prime number is: " << primes.back() << std::endl;

    return 0;
}

#include <algorithm>
#include <vector>
#include <thread>
#include <iostream>

void compare_swap(double& a, double& b) {
    if (a > b) {
        std::swap(a, b);
    }
}

void odd_even_merge(std::vector<double>& vec, int lo, int n, int r) {
    int m = r * 2;
    if (m < n) {
        odd_even_merge(vec, lo, n, m);
        odd_even_merge(vec, lo + r, n, m);
        for (int i = lo + r; i + r < lo + n; i += m) {
            if (i + r < vec.size()) {
                compare_swap(vec[i], vec[i + r]);
            }
        }
    }
    else {
        if (lo + r < vec.size()) {
            compare_swap(vec[lo], vec[lo + r]);
        }
    }
}

void odd_even_merge_sort(std::vector<double>& vec, int lo, int n) {
    if (n > 1) {
        int m = n / 2;
        odd_even_merge_sort(vec, lo, m);
        odd_even_merge_sort(vec, lo + m, m);
        odd_even_merge(vec, lo, n, 1);
    }
}

void parallel_odd_even_merge_sort(std::vector<double>& vec) {
    int n = vec.size();
    const int num_threads = 18;
    std::thread threads[num_threads];

    // Деление массива на равные части для сортировки
    int chunk_size = n / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int lo = i * chunk_size;
        int hi = (i == (num_threads - 1)) ? n : (lo + chunk_size); // Последний поток берет оставшиеся элементы
        threads[i] = std::thread(odd_even_merge_sort, std::ref(vec), lo, hi - lo);
    }

    // Ожидание завершения сортировки в потоках
    for (int i = 0; i < num_threads; ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    // Постепенное слияние отсортированных частей
    for (int i = 1; i < num_threads; i *= 2) {
        for (int j = 0; j < num_threads; j += 2 * i) {
            int lo = j * chunk_size;
            int mid = (j + i) * chunk_size;
            int hi = (j + 2 * i) * chunk_size;
            mid = (mid > n) ? n : mid;
            hi = (hi > n) ? n : hi;
            if (mid < hi) {
                odd_even_merge(vec, lo, hi - lo, chunk_size);
            }
        }
    }
}

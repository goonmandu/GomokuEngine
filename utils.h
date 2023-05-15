#include <vector>
#include <iostream>

template <typename T>
bool vector_contains(const std::vector<T> &tvec, const T &target) {
    for (T t : tvec) {
        if (t == target) {
            return true;
        }
    }
    return false;
}

template <typename T>
void println_vector(const std::vector<T> &tvec, std::string sep) {
    for (T t : tvec) {
        std::cout << t << sep;
    }
    std::cout << std::endl;
}

template <typename T>
T max(T t1, T t2) {
    return (t1 > t2) ? t1 : t2;
}

template <typename T>
T min(T t1, T t2) {
    return (t1 > t2) ? t2 : t1;
}
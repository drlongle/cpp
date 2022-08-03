#include <algorithm>
#include <atomic>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T> concept A = std::integral<T>;
template <typename T> concept B = std::integral<T> && std::equality_comparable<T>;
template <typename T> concept C = std::copyable<T> && B<T>;
template <typename T> concept D = sizeof(T) == 4;

template <typename T> concept Incrementable = requires(T x)
{
    x++; ++x;
};

template <typename T> concept E = requires { typename T::value_type; };

template <typename T> class Foo {};
template <typename T> concept F = requires { typename Foo<T>; };

template <typename T> concept G = requires (T x, T y) {
    { x.swap(y) } noexcept;
    { x.size() } -> convertible_to<size_t>;
};

template <typename T>
concept Comparable = requires(const T a, const T b) {
    { a == b } -> convertible_to<bool>;
    { a < b } -> convertible_to<bool>;
};

template <typename T> concept H = requires (T t) {
    requires sizeof(t) == 4;
    ++t; --t; t++; t--;
};

class Bar {};
template <typename T> concept IsDerivedFromFoo = derived_from<T, Bar>;

template <typename T> concept IsConvertibleToBool = convertible_to<T, bool>;

template <typename T>
concept DefaultAndCopyConstructible = default_initializable<T> && copy_constructible<T>;


template <C T> auto f1(T& t)
{
    return t;
}

auto f2(C auto t)
{
    return 2 * t;
}

template <typename T> auto f3(T& t) requires A<T>
{
    return t;
}

template <convertible_to<bool> T> void f4(const T& t)
{
}

template <Incrementable T> void f5(const T& t)
{
}

template <typename T> requires convertible_to<T, bool>
void f6(const T& t);

template <typename T> requires Incrementable<T>
void f7(const T& t);

template <typename T> requires requires(T x) { x++; ++x; }
void f8(const T& t);

int main() {
    return 0;
}

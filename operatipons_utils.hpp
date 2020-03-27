
#ifndef OPERATIONS_UTILS_H
#define OPERATIONS_UTILS_H

#include <numeric>
#include <iterator>
#include <functional>

namespace myUtils {
    template <typename Container>
    using value_type = typename Container::value_type;

    template <typename Container>
    inline value_type<Container> prod(Container input) {
        return std::accumulate(std::begin(input), std::end(input),
            static_cast<value_type<Container>>(1),
            std::multiplies<value_type<Container>>());
    };

    // based on Christian Ammer's answer at https://stackoverflow.com/questions/9227747/in-place-transposition-of-a-matrix
    template<class RandomIterator>
    void TransposeInPlace(RandomIterator first, RandomIterator last, size_t m)
    {
        if (!(first < last)) throw std::invalid_argument("first iterator should be before last");

        const size_t mn1 = (last - first - 1);
        const size_t n = (last - first) / m;
        std::vector<bool> visited(last - first);
        RandomIterator cycle = first;
        size_t d = (last - cycle) * 100 / mn1;
        while (++cycle != last) {
            if ((last - cycle) * 100 / mn1 != d)
            {
                d = (last - cycle) * 100 / mn1;
                std::cout << d << std::endl;
            }

            if (visited[cycle - first])
                continue;
            size_t a = cycle - first;
            do {
                a = a == mn1 ? mn1 : (n * a) % mn1;
                std::swap(*(first + a), *cycle);
                visited[a] = true;
            } while ((first + a) != cycle);
        }
    }
};
#endif // OPERATIONS_UTILS_H
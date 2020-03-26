
#ifndef OPERATIONS_UTILS_H
#define OPERATIONS_UTILS_H

#include <numeric>
#include <iterator>
#include <functional>

template <typename Container>
using value_type = typename Container::value_type;

template <typename Container>
inline value_type<Container> prod(Container input) {
    return std::accumulate(std::begin(input), std::end(input), 
        static_cast< value_type<Container> >(1),
        std::multiplies<value_type<Container>>());
};

#endif // OPERATIONS_UTILS_H
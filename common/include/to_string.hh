#ifndef TO_STRING_HH
#define TO_STRING_HH

#include <string>

namespace aoc2020::common {

template<typename Iterator>
inline auto
to_string(Iterator && begin, Iterator && end) -> std::string
{
    auto const  size = std::distance(begin, end);
    std::string result = '[' + std::to_string(size) + "]{";

    for (auto it = begin; it != end; ++it) {
        result += std::to_string(*it);
        if (std::next(it) != end) {
            result += ", ";
        }
    }

    result += '}';

    return result;
}

template<typename Container>
inline auto
to_string(Container const & c)
{
    return to_string(std::begin(c), std::end(c));
}

} // namespace aoc2020::common

#endif

#ifndef READ_LINES_HH
#define READ_LINES_HH

#include <fstream>
#include <string>
#include <vector>

namespace aoc2020::common {

template<typename Transform>
inline auto
read_lines(std::string const & path, Transform && transform)
    -> std::vector<std::invoke_result_t<Transform, std::string &>>
{
    std::vector<std::invoke_result_t<Transform, std::string &>> result{};

    std::ifstream f{path.c_str()};

    for (std::string buf{}; std::getline(f, buf);) {
        result.push_back(transform(buf));
    }

    return result;
}

} // namespace aoc2020::common

#endif

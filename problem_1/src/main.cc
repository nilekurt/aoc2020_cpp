#include "gsl/span_ext"
#include "read_lines.hh"
#include "result_cache.hh"
#include "to_string.hh"

#include <iostream>

namespace {

template<int T>
using Int2Type = std::integral_constant<int, T>;

// Base case
template<typename Container>
auto
solve(uint32_t          target,
      Container const & values,
      std::integral_constant<int, 2> &&) -> std::vector<uint32_t>
{
    // Make sure binary_search is possible for the given container
    using IteratorCategory = typename std::iterator_traits<decltype(
        std::begin(values))>::iterator_category;
    static_assert(
        std::is_base_of_v<std::forward_iterator_tag, IteratorCategory>);

    for (auto const a : values) {
        if (a >= target) {
            // All following values will be even larger - fail early
            return {};
        }

        auto const b = target - a;

        // Short-circuit in the symmetric case
        if (a == b ||
            std::binary_search(std::begin(values), std::end(values), b)) {
            return {b, a};
        }
    }

    return {};
}

// General case
template<int Height, typename Container>
auto
solve(uint32_t          target,
      Container const & values,
      std::integral_constant<int, Height> &&) -> std::vector<uint32_t>
{
    static_assert(Height > 2);

    // Cache the result for lower heights
    static aoc2020::common::ResultCache<uint32_t, std::vector<uint32_t>> cache;

    std::vector<uint32_t> result{};
    for (auto const a : values) {
        if (a >= target) {
            // All following values will be even larger - fail early
            break;
        }

        // Note:
        // There is no symmetric case since we have at least 2 more
        // components left

        auto const b = target - a;
        result = cache.wrap(
            [&values](auto input) {
                return solve(input, values, Int2Type<Height - 1>{});
            },
            b);

        if (!result.empty()) {
            // Success
            result.push_back(a);
            break;
        }
    }

    return result;
}

} // namespace

auto
main(int argc, char ** argv) -> int
{
    auto args = gsl::make_span(argv, argc);

    if (args.size() < 2) {
        std::cerr << "Usage: " << args[0] << " [problem_input]\n";
        return -1;
    }

    try {
        auto str_to_int = [](std::string const & s) {
            constexpr int integer_base = 10;
            return static_cast<uint32_t>(
                std::strtoll(s.c_str(), nullptr, integer_base));
        };
        auto int_values = aoc2020::common::read_lines(args[1], str_to_int);

        // Values must be sorted for the solver to work
        std::sort(std::begin(int_values), std::end(int_values));

        constexpr auto target_sum = 2020ULL;
        auto const     part1 = solve(target_sum, int_values, Int2Type<2>{});
        auto const     part2 = solve(target_sum, int_values, Int2Type<3>{});

        auto print_solution = [](auto const & soln) {
            if (soln.empty()) {
                std::cout << "No solution!\n";
            } else {
                std::cout << aoc2020::common::to_string(soln) << '\n';

                int const sum =
                    std::accumulate(std::begin(soln), std::end(soln), 0);
                std::cout << "Sum: " << sum << '\n';

                uint64_t const product = std::accumulate(
                    std::begin(soln), std::end(soln), 1ULL, [](auto x, auto y) {
                        return x * y;
                    });
                std::cout << "Product: " << product << '\n';
            }
        };

        print_solution(part1);
        std::cout << '\n';
        print_solution(part2);

        return 0;
    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
}
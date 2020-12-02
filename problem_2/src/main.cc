#include "gsl/span_ext"
#include "read_lines.hh"

#include <iostream>
#include <optional>
#include <regex>

namespace {

struct Entry {
    std::string data;
    int         first;
    int         second;
    char        c;

    Entry(int f, int s, char b, std::string d)
        : data{std::move(d)}, first{f}, second{s}, c{b}
    {
        // Workaround for make_*
    }
};

auto
parse_entry(std::string const & entry) -> std::optional<Entry>
{
    if (entry.empty()) {
        return std::nullopt;
    }

    // (%d-%d %c: %s)
    static std::regex const format{"([0-9]+)-([0-9]+) ([a-zA-Z]): (.+)"};

    std::smatch m;
    if (!std::regex_match(entry, m, format)) {
        return std::nullopt;
    }

    auto submatch_to_int = [](auto const & submatch) {
        constexpr int base = 10;
        return static_cast<int>(
            std::strtol(submatch.str().c_str(), nullptr, base));
    };

    return std::make_optional<Entry>(submatch_to_int(m[1]),
                                     submatch_to_int(m[2]),
                                     m[3].str()[0],
                                     m[4].str());
}

auto
validate_part1(Entry const & e) -> bool
{
    auto const min = e.first;
    auto const max = e.second;

    auto const n_instances = std::count(e.data.begin(), e.data.end(), e.c);

    return (min <= n_instances) && (n_instances <= max);
}

auto
validate_part2(Entry const & e) -> bool
{
    if (e.first <= 0 || e.second <= 0 || e.first > e.second ||
        static_cast<std::size_t>(e.second) > e.data.size()) {
        return false;
    }

    auto const first = e.first - 1;
    auto const second = e.second - 1;

    // Logical XOR
    return (e.data[first] == e.c) != (e.data[second] == e.c);
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
        auto entries = aoc2020::common::read_lines(args[1], parse_entry);

        auto const part1 = std::count_if(
            entries.begin(), entries.end(), [](auto & maybe_entry) {
                return maybe_entry.has_value() && validate_part1(*maybe_entry);
            });
        auto const part2 = std::count_if(
            entries.begin(), entries.end(), [](auto & maybe_entry) {
                return maybe_entry.has_value() && validate_part2(*maybe_entry);
            });

        std::cout << part1 << '\n' << part2 << '\n';

        return 0;
    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
}
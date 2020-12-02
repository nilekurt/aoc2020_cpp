#ifndef RESULT_CACHE_HH
#define RESULT_CACHE_HH

#include "absl/container/flat_hash_map.h"

namespace aoc2020::common {

template<typename Input, typename Output>
class ResultCache {
    absl::flat_hash_map<Input, Output> cache_{};

public:
    template<typename F, typename In>
    auto
    wrap(F && f, In && input)
    {
        auto const end = cache_.end();
        auto       it = cache_.find(input);
        if (it != end) {
            return it->second;
        }

        auto result = f(std::forward<In>(input));
        cache_.emplace(input, result);
        return result;
    }
};

} // namespace aoc2020::common

#endif

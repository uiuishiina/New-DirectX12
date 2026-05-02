#pragma once
#include<cstdint>
#include<functional>

template <typename Tag>
class StrongId {
    int value;
public:
    explicit StrongId(int v) : value(v) {}
    int get() const { return value; }

    auto operator<=>(const StrongId&) const = default;
};

namespace std {
    template <typename Tag>
    struct hash<StrongId<Tag>> {
        size_t operator()(const StrongId<Tag>& id) const noexcept {
            return std::hash<int>()(id.get());
        }
    };
}

struct windowTag {};
using windowID = StrongId<windowTag>;
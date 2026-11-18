#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Errors.hpp"
#include "Inventory.hpp"

constexpr int FocusHistorySize = 200;

template <typename T, int Cap>
class Registry {
    static_assert(Cap > 0, "Cap must be positive");

public:
    void Add(T v) {
        if (items_.size() >= static_cast<std::size_t>(Cap)) throw CapacityError();
        items_.push_back(std::move(v));
    }

    void Erase(std::size_t i) {
        if (i >= items_.size()) {
            throw std::out_of_range("Registry index out of range");
        }
        items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(i));
    }

    std::size_t Size() const { return items_.size(); }
    T& operator[](std::size_t i) { return items_[i]; }
    const T& operator[](std::size_t i) const { return items_[i]; }

    auto begin() const { return items_.begin(); }
    auto end() const { return items_.end(); }

    friend std::ostream& operator<<(std::ostream& os, const Registry& reg) {
        std::vector<const InventoryItem*> sorted;
        sorted.reserve(reg.items_.size());
        for (const auto& item : reg.items_) {
            sorted.push_back(item.get());
        }
        std::sort(sorted.begin(), sorted.end(),
                  [](const InventoryItem* a, const InventoryItem* b) { return *a < *b; });
        for (const InventoryItem* item : sorted) os << *item << "\n";
        return os;
    }

private:
    std::vector<T> items_;
};

template <>
class Registry<std::weak_ptr<InventoryItem>, FocusHistorySize> {
public:
    void RemoveExpired() {
        items_.erase(std::remove_if(items_.begin(), items_.end(),
                     [](const std::weak_ptr<InventoryItem>& wp) { return wp.expired(); }),
                     items_.end());
    }

    void Add(std::weak_ptr<InventoryItem> v) {
        RemoveExpired();
        if (items_.size() >= static_cast<std::size_t>(FocusHistorySize)) {
            items_.erase(items_.begin());
        }
        items_.push_back(std::move(v));
        if (auto sp = items_.back().lock()) {
            lastFocusId_ = sp->InventoryId();
        }
    }

    std::shared_ptr<InventoryItem> operator[](std::size_t i) const {
        if (i >= items_.size()) throw std::out_of_range("Focus index out of range");
        return items_[i].lock();
    }

    std::size_t Size() const { return items_.size(); }
    auto begin() const { return items_.begin(); }
    auto end() const { return items_.end(); }

    friend std::ostream& operator<<(std::ostream& os, const Registry& reg) {
        if (reg.items_.empty()) return os << "no focus set\n";
        if (auto latest = reg.items_.back().lock()) {
            os << *latest << "\n";
        } else {
            os << "removed (" << reg.lastFocusId_ << ")\n";
        }
        return os;
    }

private:
    std::vector<std::weak_ptr<InventoryItem>> items_;
    std::string lastFocusId_;
};

template <typename Container, typename Func>
double CountAmount(const Container& list, Func f) {
    double res = 0.0;
    for (const auto& u : list) {
        res += f(*u);
    }
    return res;
}

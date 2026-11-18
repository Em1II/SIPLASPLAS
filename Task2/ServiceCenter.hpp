#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "Inventory.hpp"
#include "Registry.hpp"
#include "Things.hpp"
#include "Transport.hpp"

class ServiceCenter {
public:
    static void Inspect(const Transport& t);

    template <class T, class... Args>
    void AddTransport(const std::string& id, const std::string& name, Args... args) {
        static_assert(std::is_base_of<Transport, T>::value, "T must be a Transport");
        auto t = std::make_unique<T>(ItemInfo{name, id}, GetSpec(name), args...);
        Inspect(*t);
        CheckUnique(id);
        fleet_.Add(std::move(t));
    }

    template <class T, class... Args>
    void AddThing(const std::string& id, const std::string& name, Args... args) {
        static_assert(std::is_base_of<Thing, T>::value, "T must be a Thing");
        auto t = std::make_unique<T>(ItemInfo{name, id}, args...);
        CheckUnique(id);
        fleet_.Add(std::move(t));
    }

    double TotalEnergy() const;
    double TotalFuel() const;
    std::size_t Count() const;

    void Novice(std::ostream& out) const;
    void List(std::ostream& out) const;
    void Info(const std::string& id, std::ostream& out);

    void Focus(const std::string& id);
    void ShowFocus(std::ostream& out) const;
    void Remove(const std::string& id);

private:
    static constexpr int kCap = 100;

    Registry<std::shared_ptr<InventoryItem>, kCap> fleet_;
    Registry<std::weak_ptr<InventoryItem>, FocusHistorySize> history_;
    std::unordered_map<std::string, std::weak_ptr<const ModelSpec>> specs_;

    std::shared_ptr<const ModelSpec> GetSpec(const std::string& model);
    void CheckUnique(const std::string& id) const;
    std::shared_ptr<InventoryItem> Find(const std::string& id) const;
};

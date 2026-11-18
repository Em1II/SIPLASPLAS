// Things.hpp — «вещи» на балансе (не транспорт).
//
//   InventoryItem
//     └─ Thing
//          ├─ Helmet
//          ├─ Dock      + EnergyConsumer (множественное наследование)
//          └─ FuelTank  + GasConsumer    (множественное наследование)
#pragma once

#include <memory>
#include <string>

#include "Inventory.hpp"

class Thing : public InventoryItem {
public:
    explicit Thing(ItemInfo info) : info_(std::move(info)) {}
    const std::string& InventoryId() const override { return info_.id; }
    const std::string& Name() const override { return info_.name; }
    std::shared_ptr<const std::string> Label() const override { return info_.ptr; }

private:
    ItemInfo info_;
};

class Helmet : public Thing {
public:
    explicit Helmet(ItemInfo info) : Thing(std::move(info)) {}
    std::string Describe() const override;
};

class Dock : public Thing, public EnergyConsumer {
public:
    Dock(ItemInfo info, double energy) : Thing(std::move(info)), energy_(energy) {}
    double DailyEnergy() const override { return energy_; }
    const EnergyConsumer* Energy() const override { return this; }
    std::string Describe() const override;

private:
    double energy_;
};

class FuelTank : public Thing, public GasConsumer {
public:
    FuelTank(ItemInfo info, double fuel) : Thing(std::move(info)), fuel_(fuel) {}
    double DailyFuel() const override { return fuel_; }
    const GasConsumer* Fuel() const override { return this; }
    std::string Describe() const override;

private:
    double fuel_;
};

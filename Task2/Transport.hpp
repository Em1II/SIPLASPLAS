// Transport.hpp — иерархия транспорта.
//
//   InventoryItem
//     └─ Transport
//          ├─ Bike                                (без потребления)
//          ├─ ElectricTransport  + EnergyConsumer (множественное наследование)
//          │     ├─ ElectricScooter
//          │     └─ ElectricBike
//          └─ ICETransport       + GasConsumer    (множественное наследование)
//                └─ Tractor
#pragma once

#include <memory>
#include <string>

#include "Inventory.hpp"

class Transport : public InventoryItem {
public:
    Transport(ItemInfo info, std::shared_ptr<const ModelSpec> model, int novice_score)
        : info_(std::move(info)), model_(std::move(model)), novice_score_(novice_score) {}

    const std::string& Name() const override { return info_.name; }
    const std::string& InventoryId() const override { return info_.id; }
    std::shared_ptr<const std::string> Label() const override { return info_.ptr; }
    int NoviceScore() const override { return novice_score_; }
    const ModelSpec& Spec() const { return *model_; }

private:
    ItemInfo info_;
    std::shared_ptr<const ModelSpec> model_;
    int novice_score_;
};

class Bike : public Transport {
public:
    Bike(ItemInfo info, std::shared_ptr<const ModelSpec> model, int score)
        : Transport(std::move(info), std::move(model), score) {}
    std::string Describe() const override;
};

class ElectricTransport : public Transport, public EnergyConsumer {
public:
    ElectricTransport(ItemInfo info, std::shared_ptr<const ModelSpec> model, int score, double energy)
        : Transport(std::move(info), std::move(model), score), energy_(energy) {}
    double DailyEnergy() const override { return energy_; }
    const EnergyConsumer* Energy() const override { return this; }

private:
    double energy_;
};

class ElectricScooter : public ElectricTransport {
public:
    ElectricScooter(ItemInfo info, std::shared_ptr<const ModelSpec> model, int score, double energy)
        : ElectricTransport(std::move(info), std::move(model), score, energy) {}
    std::string Describe() const override;
};

class ElectricBike : public ElectricTransport {
public:
    ElectricBike(ItemInfo info, std::shared_ptr<const ModelSpec> model, int score, double energy)
        : ElectricTransport(std::move(info), std::move(model), score, energy) {}
    std::string Describe() const override;
};

class ICETransport : public Transport, public GasConsumer {
public:
    ICETransport(ItemInfo info, std::shared_ptr<const ModelSpec> model, int score, double fuel)
        : Transport(std::move(info), std::move(model), score), fuel_(fuel) {}
    double DailyFuel() const override { return fuel_; }
    const GasConsumer* Fuel() const override { return this; }

private:
    double fuel_;
};

class Tractor : public ICETransport {
public:
    Tractor(ItemInfo info, std::shared_ptr<const ModelSpec> model, int score, double fuel)
        : ICETransport(std::move(info), std::move(model), score, fuel) {}
    std::string Describe() const override;
};

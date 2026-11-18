#pragma once

#include <memory>
#include <ostream>
#include <string>

constexpr int kNoviceThreshold = 6;

class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;
    virtual double DailyEnergy() const = 0;
};

class GasConsumer {
public:
    virtual ~GasConsumer() = default;
    virtual double DailyFuel() const = 0;
};

class InventoryItem {
public:
    virtual ~InventoryItem() = default;

    virtual const std::string& InventoryId() const = 0;
    virtual const std::string& Name() const = 0;
    virtual std::string Describe() const = 0;
    virtual std::shared_ptr<const std::string> Label() const = 0;
    virtual const EnergyConsumer* Energy() const { return nullptr; }
    virtual const GasConsumer* Fuel() const { return nullptr; }
    virtual int NoviceScore() const { return 0; }
    bool NoviceFriendly() const { return NoviceScore() >= kNoviceThreshold; }
};

struct ModelSpec {
    std::string Model;
};

struct ItemInfo {
    std::string name;
    std::string id;
    std::shared_ptr<const std::string> ptr;

    ItemInfo(std::string n, std::string i);
};

bool operator<(const InventoryItem& one, const InventoryItem& two);
bool operator==(const InventoryItem& one, const InventoryItem& two);
std::ostream& operator<<(std::ostream& s, const InventoryItem& it);

struct EnergyReport {
    double total = 0.0;
    EnergyReport& operator+=(const EnergyConsumer& c) {
        total += c.DailyEnergy();
        return *this;
    }
};

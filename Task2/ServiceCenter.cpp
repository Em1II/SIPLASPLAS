#include "ServiceCenter.hpp"

#include <algorithm>
#include <cctype>

#include "Errors.hpp"

void ServiceCenter::Inspect(const Transport& t) {
    std::string n = t.Name();
    std::transform(n.begin(), n.end(), n.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    bool broken = n.find("broken") != std::string::npos;
    bool hated_tractor = n.find("hate") != std::string::npos && n.find("tractor") != std::string::npos;
    if (broken || hated_tractor) {
        throw InspectionRejected();
    }
}

std::shared_ptr<const ModelSpec> ServiceCenter::GetSpec(const std::string& model) {
    auto it = specs_.find(model);
    if (it != specs_.end()) {
        if (auto sp = it->second.lock()) { 
            return sp;
        };
    }
    auto sp = std::make_shared<const ModelSpec>(ModelSpec{model});
    specs_[model] = sp;
    return sp;
}

void ServiceCenter::CheckUnique(const std::string& id) const {
    for (const auto& item : fleet_) {
        if (item->InventoryId() == id) {
            throw CommandError("Dublicated Id");
        }
    }
}

std::shared_ptr<InventoryItem> ServiceCenter::Find(const std::string& id) const {
    for (const auto& item : fleet_) {
        if (item->InventoryId() == id) {
            return item;
        }
    }
    throw CommandError("No Such Id");
}

double ServiceCenter::TotalEnergy() const {
    EnergyReport report;
    for (const auto& item : fleet_) {
        if (const EnergyConsumer* e = item->Energy()) {
            report += *e;
        }
    }
    return report.total;
}

double ServiceCenter::TotalFuel() const {
    return CountAmount(fleet_, [](const InventoryItem& i) {
        const GasConsumer* g = i.Fuel();
        return g ? g->DailyFuel() : 0.0;
    });
}

std::size_t ServiceCenter::Count() const { return fleet_.Size(); }

void ServiceCenter::Novice(std::ostream& out) const {
    for (const auto& item : fleet_) {
        if (item->NoviceFriendly()) {
            out << *item << "\n";
        }
    }
}

void ServiceCenter::List(std::ostream& out) const { out << fleet_; }

void ServiceCenter::Info(const std::string& id, std::ostream& out) {
    out << Find(id)->Describe() << "\n";
}

void ServiceCenter::Focus(const std::string& id) {
    history_.Add(Find(id));
}

void ServiceCenter::ShowFocus(std::ostream& out) const { out << history_; }

void ServiceCenter::Remove(const std::string& id) {
    for (std::size_t i = 0; i < fleet_.Size(); ++i) {
        if (fleet_[i]->InventoryId() == id) {
            fleet_.Erase(i);
            return;
        }
    }
    throw CommandError("No Such Id");
}

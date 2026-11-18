#include "Transport.hpp"

std::string Bike::Describe() const {
    return "Bike " + InventoryId() + " (" + Spec().Model + ")";
}

std::string ElectricScooter::Describe() const {
    return "ElectricScooter " + InventoryId() + " (" + Spec().Model + ")";
}

std::string ElectricBike::Describe() const {
    return "ElectricBike " + InventoryId() + " (" + Spec().Model + ")";
}

std::string Tractor::Describe() const {
    return "TRAAAAAAACTOR " + InventoryId() + " (" + Spec().Model + ")";
}

#include "Things.hpp"

std::string Helmet::Describe() const { return "Helmet " + InventoryId(); }
std::string Dock::Describe() const { return "Dock " + InventoryId(); }
std::string FuelTank::Describe() const { return "FuelTank " + InventoryId(); }

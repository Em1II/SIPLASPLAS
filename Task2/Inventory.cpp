#include "Inventory.hpp"

#include <utility>

ItemInfo::ItemInfo(std::string n, std::string i) : name(std::move(n)), id(std::move(i)) {
    ptr = std::make_shared<const std::string>(name + " " + id);
}

bool operator<(const InventoryItem& one, const InventoryItem& two) {
    return one.InventoryId() < two.InventoryId();
}

bool operator==(const InventoryItem& one, const InventoryItem& two) {
    return one.InventoryId() == two.InventoryId();
}

std::ostream& operator<<(std::ostream& s, const InventoryItem& it) {
    return s << it.InventoryId() << " " << it.Name();
}

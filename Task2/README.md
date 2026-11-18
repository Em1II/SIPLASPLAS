# ФизКат — учёт парка (ДЗ №2)

## Сборка и запуск
```
g++ -std=c++17 -Wall -Wextra -o fleet main.cpp Inventory.cpp Transport.cpp Things.cpp ServiceCenter.cpp
fleet < input.txt
```

## Команды
`add scooter|ebike id name energy score`, `add bike id name score`, `add helmet id name`,
`add dock id name energy`, `add tractor id name fuel score`, `add fueltank id name fuel`,
`energy`, `fuel`, `count`, `novice`, `list`, `info id`, `focus id`, `show_focus`, `remove id`, `quit`.

## Схема наследования
```
EnergyConsumer (abstract)      GasConsumer (abstract)      InventoryItem (abstract)
                                                              ├─ Transport
                                                              │    ├─ Bike
                                                              │    ├─ ElectricTransport : Transport, EnergyConsumer   [multiple]
                                                              │    │    ├─ ElectricScooter
                                                              │    │    └─ ElectricBike
                                                              │    └─ ICETransport : Transport, GasConsumer           [multiple]
                                                              │         └─ Tractor
                                                              └─ Thing
                                                                   ├─ Helmet
                                                                   ├─ Dock : Thing, EnergyConsumer                    [multiple]
                                                                   └─ FuelTank : Thing, GasConsumer                   [multiple]
```
Ромбов нет, поэтому `virtual public` не нужен. Потребителей находим без `dynamic_cast`:
виртуальные `InventoryItem::Energy()` / `Fuel()` возвращают `this` у потребителей и `nullptr` у остальных.

## Умные указатели
- `unique_ptr` — `AddTransport` / `AddThing` создают объект через `make_unique`, проводят проверки и только потом передают владение парку.
  Пока проверки не прошли, объект принадлежит одному `unique_ptr` и при исключении удаляется сам.
- `shared_ptr` — (1) парк `Registry<shared_ptr<InventoryItem>, 100>`: `weak_ptr` можно получить только из `shared_ptr`,
  поэтому `unique_ptr` в парке хранить нельзя; (2) `ModelSpec` общий для всех единиц одной модели; (3) метка `ItemInfo::ptr`.
- `weak_ptr` — история фокуса (`focus` / `show_focus`) и кэш моделей `specs_`: оба не продлевают жизнь объектов.
  После `remove` фокус печатается как `removed (id)`.

## Исключения (Errors.hpp)
`FleetError : std::exception` — общий базис.
- `InspectionRejected` — техосмотр отклонил (в имени `broken`, либо `hate` + `tractor`).
- `CommandError` — неизвестная команда/тип, неверное число аргументов, плохое число,
  простота вне 1..10, отрицательная энергия, дубликат id, нет такого id.
- `CapacityError` — парк переполнен (100).

Бросают доменные функции, печатает `error: ...` только `catch` в `main`.
Все проверки идут до изменения парка, а `Registry::Add` бросает до `push_back`, поэтому состояние не портится.

## Шаблоны (Registry.hpp)
- `Registry<T, Cap>` — журнал до `Cap` элементов: `Add`, `Size`, `Erase`, `operator[]`, `operator<<` (печать по порядку id).
  Используется как парк.
- Явная специализация `Registry<weak_ptr<InventoryItem>, FocusHistorySize>` — история фокуса.
- `CountAmount(container, f)` — шаблонная функция суммирования, используется в `TotalFuel`.

## Операторы
`operator<<` (печать `id name`), `operator<` (сортировка в `list`), `operator==` (по id),
`EnergyReport::operator+=` (накопление энергии в `TotalEnergy`).

## Креативная часть
Новый вид транспорта `Tractor` (ДВС, `GasConsumer`), вещь `FuelTank`, команды `add tractor`, `add fueltank`,
`fuel`, `count`, `info`; правило техосмотра: `hate` + `tractor` тоже отклоняется.

## ИИ
- Рисовка схем наследования.
- Консультации.
- Практические советы по реализации (красивые методы по типу erase, freind метод для перегрузки печати, std::isfinite(v)).
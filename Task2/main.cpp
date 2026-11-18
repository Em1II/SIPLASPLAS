// main.cpp — разбор команд и главный цикл.
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Errors.hpp"
#include "ServiceCenter.hpp"

using Args = std::vector<std::string>;

static int ToInt(const std::string& s) {
    try {
        std::size_t pos = 0;
        int v = std::stoi(s, &pos);
        if (pos != s.size()) {
            throw CommandError("");
        }
        return v;
    } catch (...) {
        throw CommandError("Bad Integer: " + s);
    }
}

static double ToDouble(const std::string& s) {
    try {
        std::size_t pos = 0;
        double v = std::stod(s, &pos);
        if (pos != s.size()) {
            throw CommandError("");
        }
        return v;
    } catch (...) {
        throw CommandError("Bad Double: " + s);
    }
}

static int ToScore(const std::string& s) {
    int v = ToInt(s);
    if (v < 1 || v > 10) {
        throw CommandError("Score must be in 1..10");
    }
    return v;
}

static double ToAmount(const std::string& s) {
    double v = ToDouble(s);
    if (!(v >= 0.0) || !std::isfinite(v)) {
        throw CommandError("Amount must be >= 0");
    }
    return v;
}

static void Need(const Args& a, std::size_t target_size) {
    if (a.size() != target_size) {
        throw CommandError("Wrong Amount Of Arguments");
    }
}

// ---------- Команды ----------

static void ExecuteAdd(ServiceCenter& sc, const Args& args) {
    if (args.size() < 2) {
        throw CommandError("add: kind expected");
    }
    const std::string& type = args[1];

    if (type == "scooter") {
        Need(args, 6);
        const double energy = ToAmount(args[4]);
        const int score = ToScore(args[5]);
        sc.AddTransport<ElectricScooter>(args[2], args[3], score, energy);
    } else if (type == "bike") {
        Need(args, 5);
        const int score = ToScore(args[4]);
        sc.AddTransport<Bike>(args[2], args[3], score);
    } else if (type == "ebike") {
        Need(args, 6);
        const double energy = ToAmount(args[4]);
        const int score = ToScore(args[5]);
        sc.AddTransport<ElectricBike>(args[2], args[3], score, energy);
    } else if (type == "tractor") {
        Need(args, 6);
        const double fuel = ToAmount(args[4]);
        const int score = ToScore(args[5]);
        sc.AddTransport<Tractor>(args[2], args[3], score, fuel);
    } else if (type == "helmet") {
        Need(args, 4);
        sc.AddThing<Helmet>(args[2], args[3]);
    } else if (type == "dock") {
        Need(args, 5);
        sc.AddThing<Dock>(args[2], args[3], ToAmount(args[4]));
    } else if (type == "fueltank") {
        Need(args, 5);
        sc.AddThing<FuelTank>(args[2], args[3], ToAmount(args[4]));
    } else {
        throw CommandError("UNKNOWN TECHNOLOGY B!!!: " + type);
    }
}

bool Execute(ServiceCenter& sc, const Args& args) {
    const std::string& cmd = args[0];
    if (cmd == "quit") {
        return false;
    } else if (cmd == "add") {
        ExecuteAdd(sc, args);
    } else if (cmd == "energy") {
        Need(args, 1);
        std::cout << sc.TotalEnergy() << "\n";
    } else if (cmd == "fuel") {
        Need(args, 1);
        std::cout << sc.TotalFuel() << "\n";
    } else if (cmd == "count") {
        Need(args, 1);
        std::cout << sc.Count() << "\n";
    } else if (cmd == "novice") {
        Need(args, 1);
        sc.Novice(std::cout);
    } else if (cmd == "list") {
        Need(args, 1);
        sc.List(std::cout);
    } else if (cmd == "info") {
        Need(args, 2);
        sc.Info(args[1], std::cout);
    } else if (cmd == "focus") {
        Need(args, 2);
        sc.Focus(args[1]);
    } else if (cmd == "show_focus") {
        Need(args, 1);
        sc.ShowFocus(std::cout);
    } else if (cmd == "remove") {
        Need(args, 2);
        sc.Remove(args[1]);
    } else {
        throw CommandError("UNKNOWN COMMAND!!!");
    }
    return true;
}

int main() {
    std::cout << std::fixed << std::setprecision(1);
    ServiceCenter service_center;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        Args args;
        for (std::string t; iss >> t;) args.push_back(t);
        if (args.empty()) {
            continue;
        }
        try {
            if (!Execute(service_center, args)) {
                break;
            };
        } catch (const FleetError& e) {
            std::cout << "error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << "\n";
        }
    }
    return 0;
}

#pragma once

#include <exception>
#include <string>
#include <utility>

class FleetError : public std::exception {
public:
    explicit FleetError(std::string msg) : msg_(std::move(msg)) {}
    const char* what() const noexcept override { return msg_.c_str(); }

private:
    std::string msg_;
};

class InspectionRejected : public FleetError {
public:
    InspectionRejected() : FleetError("inspection rejected") {}
};

class CommandError : public FleetError {
public:
    explicit CommandError(const std::string& msg) : FleetError(msg) {}
};

class CapacityError : public FleetError {
public:
    CapacityError() : FleetError("Too Much!") {}
};

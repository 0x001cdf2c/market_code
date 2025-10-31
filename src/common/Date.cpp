#include "common/Date.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Date::Date() : timestamp(std::time(nullptr)) {}

Date::Date(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    timestamp = std::mktime(&tm);
}

std::string Date::toString() const {
    std::tm* tm = std::localtime(&timestamp);
    std::ostringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

Date Date::now() {
    return Date();
}

bool Date::operator<(const Date& other) const {
    return timestamp < other.timestamp;
}
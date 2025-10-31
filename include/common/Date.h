#ifndef DATE_H
#define DATE_H

#include <string>
#include <chrono>

class Date {
private:
    std::time_t timestamp;
    
public:
    Date();
    Date(const std::string& dateStr);
    std::string toString() const;
    static Date now();
    bool operator<(const Date& other) const;
};

#endif
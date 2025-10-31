#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <vector>
#include <string>

class Admin : public User {
private:
    std::string adminLevel;
    std::vector<std::string> permissions;

public:
    Admin(const std::string& phone, const std::string& pwd, const std::string& level);
    
    void manageUsers();
    void viewSystemReports() const;
    void manageShops();
    void addPermission(const std::string& permission);
    bool hasPermission(const std::string& permission) const;
    
    std::string getAdminLevel() const { return adminLevel; }
};

#endif
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <vector>
#include <string>
#include <memory>

class Merchant;

class Admin : public User {
private:
    std::string adminLevel;
    std::vector<std::string> permissions;
    std::vector<std::shared_ptr<Merchant>> managedShops;

public:
    Admin(const std::string& phone, const std::string& pwd, const std::string& level);
    
    void manageUsers();
    void viewSystemReports() const;
    void manageShops();
    void addPermission(const std::string& permission);
    bool hasPermission(const std::string& permission) const;
    void suspendUser(const std::string& userId);
    void activateUser(const std::string& userId);
    void addManagedShop(std::shared_ptr<Merchant> shop);
    std::vector<std::string> generateSystemReport() const;
    
    std::string getAdminLevel() const { return adminLevel; }
    std::vector<std::string> getPermissions() const { return permissions; }
};

#endif
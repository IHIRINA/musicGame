#include "UserManager.h"

void UserManager::addUser(const std::string& username, const std::string& password) {
    users.emplace_back(username, password);
    currentUser = &users.back();
}

bool UserManager::authenticate(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return true;
        }
    }
    return false;
}
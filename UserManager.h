#pragma once  
#include <vector>  
#include <string>  
#include "User.h"  

class UserManager {  
private:  
 
    User* currentUser;  

public:  
    std::vector<User> users;
    UserManager() : currentUser(nullptr) {}  
    void addUser(const std::string& username, const std::string& password);  
    bool authenticate(const std::string& username, const std::string& password);  
    User* getCurrentUser() { return currentUser; }  
    void setCurrentUser(User* user) {
        currentUser = user;
    }
};
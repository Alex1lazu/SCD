#ifndef AUTH_SERVER_SHARED_H
#define AUTH_SERVER_SHARED_H

#include <unordered_map>
#include <vector>
#include <string>

extern std::unordered_map<std::string, std::unordered_map<std::string, std::string>> clients;
extern std::vector<std::string> resources;

#endif
#ifndef AUTH_SERVER_SHARED_H
#define AUTH_SERVER_SHARED_H

#include <unordered_map>
#include <vector>
#include <string>


struct Client {
	std::unordered_map<std::string, std::string> permissions;
	std::string req_token;
	std::string access_token;
	std::string refresh_token;
	int lifetime = 0;
	bool auto_refresh;

	Client() = default;

	// Client(std::unordered_map<std::string, std::string>& permissions_map, std::string req_token, std::string access_token)
    //     : permissions(permissions_map), req_token(req_token), access_token(access_token) {}
};
typedef struct Client Client;

extern std::unordered_map<std::string, Client> clients;
extern std::vector<std::string> resources;
extern std::vector<std::string> approvals_lines;
extern int token_lifetime;

#endif
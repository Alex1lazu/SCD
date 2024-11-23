#include "auth.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void
auth_1(char *host, char *client_file)
{
	CLIENT *clnt;
	request req;
	response *resp;
#ifndef	DEBUG
	clnt = clnt_create (host, AUTH, A1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	ifstream in(client_file);
	string line;
	while (getline(in, line)) {
		
		stringstream ss(line);
		string id, action, res;
		getline(ss, id, ','), getline(ss, action, ','), getline(ss, res, ',');
		
		strncpy(req.action, action.c_str(), sizeof(req.action));
		strncpy(req.id, id.c_str(), sizeof(req.id));
		strncpy(req.res, res.c_str(), sizeof(req.res));

		resp = afisare_1(&req, clnt);
		if (resp == (response *) NULL) {
			cout << "Failed on line: " << line<<'\n';
		} else {
			string result = resp->msg;
			cout << result <<"\n";
		}
	}


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host, *client_file;

	if (argc < 3) {
		printf ("usage: %s server_host client_file\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	client_file = argv[2];
	auth_1 (host, client_file);
exit (0);
}
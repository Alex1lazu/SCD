#include "auth.h"
#include "auth_server_shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

using namespace std;	


unordered_map<std::string, Client> clients;
vector<string> resources;
vector<string> approvals_lines;
int token_lifetime;
void parse_input(char **argv) {
	// 0 - ids, 1 - resources, 2 - approvals
	ifstream id_file(argv[1]);
	ifstream res_file(argv[2]);
	ifstream aprov_file(argv[3]);
	

	string id, res, aprov;
	int number_of_clients, number_of_resources;
	token_lifetime = stoi(string(argv[4]));

	getline(id_file, id);
	getline(res_file, res);
	istringstream no_clients_stream(id);
	istringstream no_resources_stream(res);
    no_clients_stream >> number_of_clients;
	no_resources_stream >> number_of_resources;

	while (getline(aprov_file, aprov)) {
		approvals_lines.push_back(aprov);
	}

	for (int i = 0; i < number_of_clients; i++) {
		getline(id_file, id);
		clients[id] = Client();
	}

	for (int i = 0; i < number_of_resources; i++) {
		getline(res_file, res);
		resources.push_back(res);
	}
}

static void
auth_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		request afisare_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case afisare:
		_xdr_argument = (xdrproc_t) xdr_request;
		_xdr_result = (xdrproc_t) xdr_response;
		local = (char *(*)(char *, struct svc_req *)) afisare_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

void print_data() {
	cout << "Clients and their permissions:" << endl;
    for (const auto& client : clients) {
        cout << "Client ID: " << client.first << endl;
        for (const auto& perm : client.second.permissions) {
            cout << "  Resource: " << perm.first << ", Permission: " << perm.second << endl;
        }
    }
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (AUTH, A1);

	if (argc < 5) {
		printf ("usage: %s user_ids resources approvals token_lifetime\n", argv[0]);
		exit (1);
	}
	parse_input(argv);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, AUTH, A1, auth_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (AUTH, A1, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, AUTH, A1, auth_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (AUTH, A1, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	
	exit (1);
	/* NOTREACHED */
}
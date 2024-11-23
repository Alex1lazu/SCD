
#!/bin/bash

cc -g -I/usr/include/tirpc   -c -o auth_xdr.o auth_xdr.c
g++ -g -I/usr/include/tirpc   -c -o auth_svc.o auth_svc.cpp
g++ -g -I/usr/include/tirpc   -c -o auth_server.o auth_server.cpp
g++ -g -I/usr/include/tirpc    -o auth_server auth_svc.o auth_server.o auth_xdr.o -lnsl -ltirpc
./auth_server tests/test3/userIDs.db tests/test3/resources.db tests/test3/approvals.db 2
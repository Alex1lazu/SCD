
#!/bin/bash
g++ -g -I/usr/include/tirpc   -c -o auth_server.o auth_server.cpp
g++ -g -I/usr/include/tirpc    -o auth_server  auth_clnt.o auth_server.o auth_xdr.o -lnsl -ltirpc
./auth_server
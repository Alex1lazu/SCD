
#!/bin/bash
g++ -g -I/usr/include/tirpc   -c -o auth_client.o auth_client.cpp
g++ -g -I/usr/include/tirpc    -o auth_client  auth_clnt.o auth_client.o auth_xdr.o -lnsl -ltirpc
./auth_client localhost
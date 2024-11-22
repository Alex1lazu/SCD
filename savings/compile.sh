
#!/bin/bash
make clean
make
mv auth_client.c auth_client.cpp
mv auth_server.c auth_server.cpp
mv auth_svc.c auth_svc.cpp

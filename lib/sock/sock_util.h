#include <sys/socket.h>
#include <arpa/inet.h>

// API for tcp server
int create_tcp_sock();
int bind_by_port(int sock,unsigned short port);
int do_accept(int sock);

int start_tcp_server(unsigned short port,int* server_sock);

//IP ADDRESS MANIPULATION
char* get_sock_addr(int sock);
unsigned short get_sock_port(int sock);


// UTILS
int set_reuse_addr(int sock);

// API for client server


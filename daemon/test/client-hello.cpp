#include <stdio.h> 

#include "cuda_commands.h"
#include "socket_client.h"

#define SOCKET_PATH "/tmp/server-test"
   
int main(int argc, char const *argv[]) { 
    int sock = initialize(SOCKET_PATH);
    
    if (sock == -1) {
        exit(EXIT_FAILURE);
    }

    cuda_daemon::hello_command_t hello_cmd;
    cuda_daemon::init_hello_command(hello_cmd, "Hello from client");

    cuda_daemon::command_base_t res;

    if(!send_on_socket(sock, &hello_cmd, sizeof(hello_cmd))) {
        return EXIT_FAILURE;
    } 

    printf("Hello message sent\n"); 

    if(!receive_on_socket(sock, &res, sizeof(res))) {
        return EXIT_FAILURE;
    }

    if (res.cmd == cuda_daemon::ACK) {
        printf("Server ack received\n");
    } else {
        return EXIT_FAILURE;
    }

    end(sock);
    
    return EXIT_SUCCESS; 
} 

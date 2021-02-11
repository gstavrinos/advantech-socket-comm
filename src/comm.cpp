#include <chrono>
#include <thread>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h> 

#include "advantech_comm/advantech_comm.hpp"

int main(int argc, char* argv[]) {
    typedef unsigned char byte;
    struct sockaddr_in address; 

    const int PORT = 8666;

    int server_fd, new_socket, valread; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    int opt = 1; 
    std::string response = ""; 

    // Advantech (DAQNavi) connection initialisation
    const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
    const wchar_t * deviceDescription = L"DemoDevice,BID#0";
    const int output_port = 1;
    const int input_port = 0;

    advantech_comm::AdvantechComm adv_comm(deviceDescription, profilePath, input_port, output_port);

    byte bufferForReading[64] = {0};//the first element of this array is used for start port
    byte bufferForWriting[64] = {0};//the first element is used for start port
    // ---

    // Socket connection initialisation
    while ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        std::cout << "Could not create socket. Retrying in 5 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 
       
    while (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "Could not attach socket to port " << PORT << ". Retrying in 5 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    while (listen(server_fd, 3) < 0) { 
        std::cout << "Could not start listening. Retrying in 5 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    } 
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
        std::cout << "Could not establish connection. Retrying in 5 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    // ---

    std::cout << "Socket server is ready to serve..." << std::endl;

    // Server
    while (true) {
        valread = read( new_socket , buffer, 1024); 
        printf("Received %s\n", buffer);
        if (strcmp(buffer, "0") == 0) {
            std::cout << "Received 'turn off' command." << std::endl;
            // TODO fill bufferForWriting with the required byte(s)
            adv_comm.write(bufferForWriting);
            adv_comm.errorChecking();
        }
        else if (strcmp(buffer, "1") == 0) {
            std::cout << "Received 'turn on' command." << std::endl;
            // TODO fill bufferForWriting with the required byte(s)
            adv_comm.write(bufferForWriting);
            adv_comm.errorChecking();
        }
        // adv_comm.read(bufferForReading);
        // adv_comm.errorChecking();
        // TODO fill response with the correct value, based on the info in bufferForReading
        response = "1";
        send(new_socket , response.c_str(), strlen(response.c_str()), 0); 
        printf("Replied with %s\n", response.c_str());
    }

    return 0;
}


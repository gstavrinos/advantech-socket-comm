#include <chrono>
#include <thread>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h> 

#include <bdaqctrl.h>

using namespace Automation::BDaq;

int main(int argc, char* argv[]) {
    typedef unsigned char byte;
    struct sockaddr_in address; 

    const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
    const wchar_t * deviceDescription = L"DemoDevice,BID#0";
    const int PORT = 8666;

    int server_fd, new_socket, valread; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    int output_port = 1;
    int input_port = 0;
    int opt = 1; 
    std::string response = ""; 

    // Advantech (DAQNavi) connection initialisation
    ErrorCode ret = Success;

    InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
    InstantDoCtrl * instantDoCtrl = InstantDoCtrl::Create();

    DeviceInformation devInfo(deviceDescription);

    ret = instantDiCtrl->setSelectedDevice(devInfo);
    ret = instantDoCtrl->setSelectedDevice(devInfo);

    ret = instantDiCtrl->LoadProfile(profilePath);
    ret = instantDoCtrl->LoadProfile(profilePath);

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
            ret = instantDoCtrl->Write(output_port, 1, bufferForWriting);
        }
        else if (strcmp(buffer, "1") == 0) {
            std::cout << "Received 'turn on' command." << std::endl;
            // TODO fill bufferForWriting with the required byte(s)
            ret = instantDoCtrl->Write(output_port, 1, bufferForWriting);
        }
        // ret = instantDiCtrl->Read(input_port, 1, bufferForReading);
        // TODO fill response with the correct value, based on the info in bufferForReading
        response = "1";
        send(new_socket , response.c_str(), strlen(response.c_str()), 0); 
        printf("Replied with %s\n", response.c_str());
        // NOTE
        // Alternative way to read/write single bits to advantech device:
        // int8 data = 0;
        // int  bit = 0;
        // ret = instantDiCtrl->ReadBit(startPort, bit, &data);
        // ret = instantDoCtrl->WriteBit(startPort, bit, data);

        // TODO
        // Check error codes from advantech devices
        // if(BioFailed(ret)) {
            // wchar_t enumString[256];
            // AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
            // printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
        // }
    }

    instantDiCtrl->Dispose();
	instantDoCtrl->Dispose();

    return 0;
}

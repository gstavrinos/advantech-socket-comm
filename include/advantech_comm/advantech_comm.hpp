#pragma once

#include <stdio.h> 
#include <bdaqctrl.h>

using namespace Automation::BDaq;

namespace advantech_comm {

class AdvantechComm {

    public:
        typedef unsigned char byte;
        AdvantechComm(){}
        AdvantechComm(const wchar_t*, const wchar_t*, const int, const int);

        ~AdvantechComm();

        bool errorChecking();
        ErrorCode write(byte*);
        ErrorCode read(byte*);
        ErrorCode writeBit(int8);
        ErrorCode readBit(uint8*);

    private:
        ErrorCode ret;
        int input_port, output_port;
        InstantDiCtrl* instantDiCtrl;
        InstantDoCtrl* instantDoCtrl;

};

}


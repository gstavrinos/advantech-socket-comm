#pragma once

#include <stdio.h> 
#include <bdaqctrl.h>

using namespace Automation::BDaq;

namespace advantech_comm {

class AdvantechComm {
        // NOTE
        // Alternative way to read/write single bits to advantech device:
        // int8 data = 0;
        // int  bit = 0;
        // advantech_comm.ret = advantech_comm.instantDiCtrl->ReadBit(startPort, bit, &data);
        // advantech_comm.errorChecking();
        // advantech_comm.ret = advantech_comm.instantDoCtrl->WriteBit(startPort, bit, data);
        // advantech_comm.errorChecking();

    public:
        typedef unsigned char byte;
        AdvantechComm(){}
        AdvantechComm(const wchar_t*, const wchar_t*, const int, const int);

        ~AdvantechComm();

        bool errorChecking();
        ErrorCode write(byte*);
        ErrorCode read(byte*);

    private:
        ErrorCode ret;
        int input_port, output_port;
        InstantDiCtrl* instantDiCtrl;
        InstantDoCtrl* instantDoCtrl;

};

}


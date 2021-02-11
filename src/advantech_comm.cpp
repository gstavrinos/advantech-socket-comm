#include "advantech_comm/advantech_comm.hpp"

namespace advantech_comm {

    AdvantechComm::AdvantechComm(const wchar_t* deviceDescription, const wchar_t* profilePath, const int input_port, const int output_port) {
        ret = Success;

        instantDiCtrl = InstantDiCtrl::Create();
        instantDoCtrl = InstantDoCtrl::Create();
        DeviceInformation devInfo(deviceDescription);

        ret = instantDiCtrl->setSelectedDevice(devInfo);
        errorChecking();
        ret = instantDoCtrl->setSelectedDevice(devInfo);
        errorChecking();

        ret = instantDiCtrl->LoadProfile(profilePath);
        errorChecking();
        ret = instantDoCtrl->LoadProfile(profilePath);
        errorChecking();

        this->input_port = input_port;
        this->output_port = output_port;

    }

    AdvantechComm::~AdvantechComm() {
        instantDiCtrl->Dispose();
        instantDoCtrl->Dispose();
    }

    ErrorCode AdvantechComm::write(byte* buffer) {
        ret = instantDoCtrl->Write(output_port, 1, buffer);
        return ret;
    }
    
    ErrorCode AdvantechComm::read(byte* buffer) {
        ret = instantDiCtrl->Read(input_port, 1, buffer);
        return ret;
    }

    bool AdvantechComm::errorChecking() {
        // Check error codes from advantech devices
        if(BioFailed(ret)) {
            wchar_t enumString[256];
            AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
            printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
        }
        return BioFailed(ret);
    }
}


#ifndef _MAC_MANAGER_H
#define _MAC_MANAGER_H
#include <cstdint>
#include <cstring>

#define IN
#define OUT

#pragma pack(push, 1)
class MacManager final {
    public:
        static constexpr size_t LENGTH = 6; // 컴파일 타임에 값이 결정된다면 constexpr을 사용한다 !

    private:
        uint8_t macAddress[LENGTH];

    public:
        MacManager() {}
        MacManager(IN uint8_t* macAddress);

        operator uint8_t*() { return macAddress; };
        void operator=(IN const uint8_t* macAddress) { memcpy(this->macAddress, macAddress, LENGTH); };
        bool operator==(IN MacManager& macManager) { return !memcmp(this->macAddress, macManager.macAddress, LENGTH); };
        bool operator==(IN const uint8_t* macAddress) { return !memcmp(this->macAddress, macAddress, LENGTH); };
        bool operator!=(IN MacManager& macManager) { return memcmp(this->macAddress, macManager.macAddress, LENGTH); };
        bool operator!=(IN const uint8_t* macAddress) { return memcmp(this->macAddress, macAddress, LENGTH); };

        // functions
        static void printMacAddress(IN const char* prefix, IN uint8_t* macAddress);
        void printMacAddress(IN const char* macAddress);
        void setBroadcast();
};
#pragma pack(pop)
#endif
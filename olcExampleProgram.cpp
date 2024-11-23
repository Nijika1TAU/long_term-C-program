#include <iostream>
#include <cstring>

namespace HAL {
    struct IMU_Info_t {
        int data[10]; 
    };
}

class Account {
public:
    Account(const char* name, void* dataCenter, size_t bufferSize)
        : name(name), bufferSize(bufferSize) {
        std::cout << "Account created: " << name
            << ", bufferSize: " << bufferSize << std::endl;
    }
    void ShowInfo() const {
        std::cout << "Account Name: " << name
            << ", Buffer Size: " << bufferSize << std::endl;
    }

private:
    const char* name;      // 模块名称
    size_t bufferSize;     // 缓冲区大小
};

void* dataCenter = nullptr;

// 模拟外部初始化函数
void _ACT_Storage_Init(Account* account) {
    std::cout << "[Storage] Initialization complete." << std::endl;
}
void _ACT_Power_Init(Account* account) {
    std::cout << "[Power] Initialization complete." << std::endl;
}
void _ACT_IMU_Init(Account* account) {
    std::cout << "[IMU] Initialization complete." << std::endl;
}
void _ACT_StatusBar_Init(Account* account) {
    std::cout << "[StatusBar] Initialization complete." << std::endl;
}
void _ACT_MusicPlayer_Init(Account* account) {
    std::cout << "[MusicPlayer] Initialization complete." << std::endl;
}
void _ACT_SysConfig_Init(Account* account) {
    std::cout << "[SysConfig] Initialization complete." << std::endl;
}


void Accounts_Init() {
    // dymanic allocate Account instance
#define ACT_DEF(NodeName, bufferSize) \
        Account* act##NodeName = new Account(#NodeName, &dataCenter, bufferSize);

#include "_ACT_LIST.inc"

#undef ACT_DEF

// 调用对应的初始化函数
#define ACT_DEF(NodeName, bufferSize) \
    do { \
        extern void _ACT_##NodeName##_Init(Account* account); \
        _ACT_##NodeName##_Init(act##NodeName); \
    } while(0)

#include "_ACT_LIST.inc"

#undef ACT_DEF  //指引 會使前置處理器結束前置處理器定義的範圍。
}

int main() {
    std::cout << "Initializing Accounts..." << std::endl;
    Accounts_Init(); // 调用初始化函数

    std::cout << "All Accounts initialized successfully!" << std::endl;
    return 0;
}


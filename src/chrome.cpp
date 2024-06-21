#include "list"
#include "iostream"

#include "Windows.h"
#include "TlHelp32.h"
#include "Psapi.h"

#include "include/cactypes.hpp"

namespace chromecac {

    ALMADEN_CAC_NODE verifyChromeProcesses() {

        ALMADEN_CAC_NODE list { -1, 0.f, 0.f, "UNKNOWN" };
        ALMADEN_CAC_NODE* current = &list;

        PROCESSENTRY32W pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32W);

        HANDLE pSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (Process32FirstW(pSnapshot, &pe32)) {

            do {

                if (wcscmp(pe32.szExeFile, L"chrome.exe") == 0) {

                    char* tabUrl = new char[32];
                    float cpuConsumption = 0.f;
                    float memoryConsumption = 0.f;

                    MODULEENTRY32W me32;
                    me32.dwSize = sizeof(MODULEENTRY32W);

                    HANDLE mSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);

                    if (Module32FirstW(mSnapshot, &me32)) {

                        do {

                            if (wcscmp(me32.szModule, L"chrome.dll") == 0) {
                                
                                uintptr_t offset = 0xD613DB8;
                                uintptr_t baseAddress = (uintptr_t)(void*)me32.modBaseAddr;

                                void* urlBaseAddr = (void*)(baseAddress + offset);

                                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
                                ReadProcessMemory(hProcess, urlBaseAddr, tabUrl, 32, nullptr);

                                PROCESS_MEMORY_COUNTERS pmc;
                                
                                if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {

                                    memoryConsumption = pmc.WorkingSetSize;
                                }

                            } 

                        } while (Module32NextW(mSnapshot, &me32));
                    }

                    if (current->record.processId != -1) {

                        ALMADEN_CAC_NODE* nodeRef = new ALMADEN_CAC_NODE;

                        current->next = nodeRef;
                        current = current->next;
                    }

                    current->record.processId = pe32.th32ProcessID;
                    current->record.cpuConsumption = cpuConsumption;
                    current->record.memoryConsumption = memoryConsumption;
                    current->record.url = tabUrl;

                }

            } while (Process32NextW(pSnapshot, &pe32));
        }
        
        return list;
    }

//     // std::list<DWORD> attachedProcesses;

//     // bool isAttached(DWORD processId) {

//     //     std::list<DWORD>::iterator it;

//     //     for (it = attachedProcesses.begin(); it != attachedProcesses.end(); ++it) {

//     //         if (*it == processId) {

//     //             return true;
//     //         }
//     //     }

//     //     return false;
//     // }

//     // void attachThreadToProcess(PROCESSENTRY32 pe32) {

//     //     std::cout << "[CHROME] - Attaching " << pe32.th32ProcessID << std::endl;
//     //     attachedProcesses.push_back(pe32.th32ParentProcessID);
//     // }

//     // void watchChromeProcesses() {
        
//     //     PROCESSENTRY32W pe32;
//     //     pe32.dwSize = sizeof(PROCESSENTRY32W);

//     //     HANDLE pSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

//     //     if (Process32FirstW(pSnapshot, &pe32)) {

//     //         do {

//     //             if (wcscmp(pe32.szExeFile, L"chrome.exe") == 0) {

//     //                 std::cout << "chrome.exe" << std::endl;
//     //             }

//     //         } while (Process32NextW(pSnapshot, &pe32));
//     //     }
//     // }

}

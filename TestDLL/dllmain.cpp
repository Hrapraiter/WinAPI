// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MyFunction.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void Select(std::vector<int>& vect, std::function<int(int elem)> func)
{
    for (int& elem : vect)
        elem = func(elem);
}

void Where(std::vector<int>& vect, std::function<bool(int elem)> func)
{
    std::vector<int> new_vect;
    for (const int& elem : vect)
        if (func(elem))
            new_vect.push_back(elem);

    vect = new_vect;
}
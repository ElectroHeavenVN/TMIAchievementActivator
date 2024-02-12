// dllmain.cpp : Defines the entry point for the DLL application.
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include "pch.h"
#include <Windows.h>
#include "include/MinHook.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <format>
#include <iostream>
#include <shellapi.h>
#include <complex>
#include "il2cpp.h"
#include <codecvt>

uintptr_t gameAssemblyHandle = (uintptr_t)GetModuleHandle("GameAssembly.dll");

uintptr_t GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_offset = gameAssemblyHandle + 0x535000;
uintptr_t System_String__CreateString_offset = gameAssemblyHandle + 0x1CE6B30;
uintptr_t GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement_534BF0_offset = gameAssemblyHandle + 0x534BF0;

#pragma region Utils
std::string utf16_to_utf8(const uint16_t* utf16String, size_t length)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    std::u16string utf16Str(utf16String, utf16String + length);
    return convert.to_bytes(utf16Str);
}

std::string GetStdStr(System_String_o* str)
{
    return utf16_to_utf8(&str->fields._firstChar, str->fields._stringLength);
}

wchar_t* ConvertCharToWchar(const char* charString)
{
    size_t length = mbstowcs(NULL, charString, 0);
    if (length == static_cast<size_t>(-1))
        return nullptr;
    wchar_t* wcharString = new wchar_t[length + 1];
    size_t convertedLength = mbstowcs(wcharString, charString, length);
    if (convertedLength == static_cast<size_t>(-1))
    {
        delete[] wcharString;
        return nullptr;
    }
    wcharString[length] = L'\0';
    return wcharString;
}

void logDebug(const char* format...)
{
    printf(format);
    printf("\r\n");
}

void logDebugStd(std::string str)
{
    logDebug(str.c_str());
}

void logDebug(System_String_o* str)
{
    logDebugStd(GetStdStr(str));
}
 
System_String_o* CreateNetString(const wchar_t* str)    //string.CreateString(char* value)
{
    System_String_o* (__stdcall *String__CreateString)(void* instance, const wchar_t* str) = (System_String_o * (*)(void*, const wchar_t*))System_String__CreateString_offset;
    auto* managed_str = static_cast<System_String_o*>(malloc(sizeof(System_String_o)));
    return String__CreateString(managed_str, str);
}
#pragma endregion

#pragma region Hook
void (__stdcall *GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_original)(GameData_Profile_AchievementData_array* allAchievements, const MethodInfo* method);
void __stdcall GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_hook(GameData_Profile_AchievementData_array* allAchievements, const MethodInfo* method)
{
    GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_original(allAchievements, method);
    for (int i = 0; i < allAchievements->max_length; i++)
    {
        logDebugStd("Achievement ID: " + GetStdStr(allAchievements->m_Items[i].fields.Id) + ", activating...\r\n");
        void(__stdcall * GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement_534BF0)(System_String_o * achievementId, const MethodInfo * method) = (void (*)(System_String_o*, const MethodInfo*))GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement_534BF0_offset;
        GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement_534BF0(allAchievements->m_Items[i].fields.Id, 0);
    }
}

void setupHook()
{
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_offset), &GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_hook, (LPVOID*)&GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_535000_original);
    MH_EnableHook(MH_ALL_HOOKS);
}
#pragma endregion

void Main()
{
    MH_Initialize();
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    printf("Module loaded!\r\n");
    setupHook();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            MH_Uninitialize();
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}


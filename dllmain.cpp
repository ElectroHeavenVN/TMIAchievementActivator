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
#include "pch.h"
#include "wrapper.hpp"

uintptr_t gameAssemblyHandle = (uintptr_t)GetModuleHandle("GameAssembly.dll");
void(__stdcall* GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement)(System_String_o* achievementId, const MethodInfo* method) = nullptr;

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
    printf("\n");
}

void logDebugStd(std::string str)
{
    logDebug(str.c_str());
}

void logDebug(System_String_o* str)
{
    logDebugStd(GetStdStr(str));
}
#pragma endregion

#pragma region Hook
void (__stdcall *GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_original)(GameData_Profile_AchievementData_array* allAchievements, const MethodInfo* method);
void __stdcall GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_hook(GameData_Profile_AchievementData_array* allAchievements, const MethodInfo* method)
{
    GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_original(allAchievements, method);
    for (int i = 0; i < allAchievements->max_length; i++)
    {
        logDebugStd("Achievement ID: " + GetStdStr(allAchievements->m_Items[i].fields.Id) + ", activating...\n");
        GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement(allAchievements->m_Items[i].fields.Id, 0);
    }
    logDebug("You can close this console window now.");
    SetConsoleTitleA("TMIAchievementActivator");
    FreeConsole();
}
#pragma endregion

void Main()
{
    FILE* output = nullptr;
    if (!AllocConsole())
        return;
    SetConsoleTitleA("TMIAchievementActivator - Do not close");
    freopen_s(&output, "CONOUT$", "w", stdout);
    MH_Initialize();
    Il2cpp::initialize();
    const auto il2cppImages = std::make_unique<Wrapper>();
    const auto assemblyCSharp = il2cppImages->get_image("Assembly-CSharp.dll");
    const auto dbAchievement = assemblyCSharp->get_class("DataBaseAchievement", "GameData.RunTime.Common.AchievementSystem");
    const auto initialize = dbAchievement->get_method("Initialize", 1);
    if (initialize == nullptr)
    {
        logDebug("[TMIAchievementActivator] Initialize method not found!");
        return;
    }
    const auto finishAchievement = dbAchievement->get_method("FinishAchievement", 1);
    if (finishAchievement == nullptr)
    {
        logDebug("[TMIAchievementActivator] FinishAchievement method not found!");
        return;
    }
    if (MH_OK == MH_CreateHook(initialize->methodPointer, &GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_hook, (LPVOID*)&GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__Initialize_original) && MH_OK == MH_EnableHook(MH_ALL_HOOKS))
        logDebug("[TMIAchievementActivator] Hook successfully!");
    else 
        logDebug("[TMIAchievementActivator] Hook failed!");
    GameData_RunTime_Common_AchievementSystem_DataBaseAchievement__FinishAchievement = (void (*)(System_String_o*, const MethodInfo*))finishAchievement->methodPointer;
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
            FreeConsole();
            FreeLibraryAndExitThread(hModule, 0);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
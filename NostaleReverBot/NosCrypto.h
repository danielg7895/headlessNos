#pragma once
#include <string>
#include <Windows.h>

std::string decrypt(std::string packet);
std::string encrypt(std::string& packet);
char* encrypt(char* packet, int len);
std::string decryptLoginServer(std::string packet);
char* decryptLoginServer(char* packet, int len);

DWORD generateSeed(DWORD num);
std::string generateRandomNum(DWORD* seed);
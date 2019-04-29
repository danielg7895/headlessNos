#pragma once
#include <iostream>
#include <math.h>
#include "md5.h"
#include "sha512.h"
#include <Windows.h>
#include <vector>

DWORD generateSeed(DWORD num);
std::string generateRandomNum(DWORD* seed);
std::string login(std::string user, std::string password);
std::string int2hex_str(uint8_t number);
std::string decrypt(std::string packet);
std::string encrypt(std::string packet);
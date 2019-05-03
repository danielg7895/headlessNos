#pragma once
#include <string>
#include <Windows.h>

// Login encrypt/decrypt methods
std::string login_decrypt(std::string packet);
std::string login_encrypt(std::string& packet);
std::string login_decrypt_server(std::string packet);

// Ingame encrypt/decrypt methods
std::string ingame_decrypt(std::string packet);
std::string ingame_encrypt(std::string packet);

DWORD generateSeed(DWORD num);
std::string generateRandomNum(DWORD* seed);
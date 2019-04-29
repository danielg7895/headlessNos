#include "nostale_sockets.cpp"
#include "main.h"
#include <vector>
#include <sstream>
#include <iostream>

std::string SERVER_IP = "79.110.84.75";
std::string SERVER_PORT = "4005";


void main() {

	DWORD seed;

	for (int i = 0; i < 120; i++) {
		seed = generateSeed(0x989680);
	}

	//generateRandomNum(&seed);
	std::string loginPacket = login("reloco", "wacho");

	NostaleSocket nostaleSocket;
	std::string curr = " ";
	char tes[500];
	for (int i = 0; i < loginPacket.length(); ) {
		if ((loginPacket.length() % 2 == 1) && i == loginPacket.length() - 1) {
			curr = loginPacket[i];
		}
		else {
			curr = loginPacket[i] + loginPacket[i + 1];
		}
		tes[i] = stoi(curr, nullptr, 16);
		i += 2;
	}


	char loginBuffer[500];

	nostaleSocket.NSend(loginBuffer);
	
	std::cout << loginBuffer<< std::endl;


	printf(decrypt(nostaleSocket.recvBuff).c_str());
}


std::string int2hex_str(int num) {
	static char buffer[8];
	sprintf(buffer, "%08X", num);
	return std::string(buffer);
}

std::string byte2hex_str(BYTE num) {
	static char buffer[2];
	sprintf(buffer, "%.2X", num);
	return std::string(buffer);
}

DWORD prevNum = 0;
DWORD generateSeed(DWORD num) {
	DWORD edx = (DWORD)((int)prevNum * (int)0x8088405);
	++edx;
	prevNum = edx;
	edx = edx * num;
	return edx;
}


std::string generateRandomNum(DWORD *seed) {
	BYTE ecx = 0x0A;
	BYTE resto = 0x00;
	std::string strRandomBytes = "";
	//DWORD64 randomBytes = 0x00;
	//BYTE counter = 0;
	int counter = 0;
	
	while (*seed != 0) {
		resto = 0x00;
		resto = *seed % ecx;
		*seed = *seed / ecx;

		// dec esi
		resto += 0x30;
		if (resto > 0x3A) {
			resto += 0x07;
		}

		counter += resto;
		strRandomBytes = (char)resto + strRandomBytes;
		//randomBytes += resto << (counter * 8);
		//++counter;
	}

	std::string test = int2hex_str(counter);
	//printf("%s\n", strRandomBytes.c_str());
	return strRandomBytes; // devuelve en hex
}


std::string login(std::string user, std::string password) {
	MD5 md5;

	std::string nostalePath = "C:\\Program Files (x86)\\Nostale_ES";
	std::string md5NostaleClientX = md5.digestFile((nostalePath + "\\NostaleClient.exe").c_str());
	std::string md5NostaleClient = md5.digestFile((nostalePath + "\\NostaleClientX_bak.exe").c_str());
	std::string md5_hash = md5NostaleClient + md5NostaleClientX + user;


	std::string opcode = "NoS0575";

	DWORD seed = generateSeed(0x989680);
	seed = generateSeed(0x989680) + 0x86111;
	std::string randomNum1 = generateRandomNum(&seed);

	std::string passSHA512 = sha512(password);
	std::string randomNum2 = int2hex_str((int)generateSeed(0x989680));
	std::string gameVersion = "0.9.3.3102";
	std::string bothMD5 = md5.digestString(md5_hash);
	std::string packet = opcode + " " + randomNum1 + " " + user + " " + passSHA512 + " NONE " + randomNum2 + (char)0x0B + gameVersion + " 0 " + bothMD5;

	printf(packet.c_str());
	printf("\n\n");

	std::string encriptedPacket = encrypt(packet) + (char)0xD8;// +(char)0x8F + (char)0xD8;
	printf("%d\n", encriptedPacket.length());

	std::string dx = "";
	char test[2];
	
	printf("\n=================================================\n");
	for (int i = 0; i < encriptedPacket.length(); i++) {
		printf("%.2X", (uint8_t)encriptedPacket[i]);
		sprintf(test, "%d", (uint8_t)encriptedPacket[i]);
		dx += test;

	}

	return dx;
}


std::string decrypt(std::string packet) {

	for (int i = 0; i < packet.length(); i++) {
		packet[i] -= 0x0F;
		if (packet[i] == 0x0A) {
			break;
		}
	}
	return packet;
}

std::string encrypt(std::string packet) {

	std::string finalPacket = "";
	for (int i = 0; i < packet.length(); i++) {
		uint8_t current = packet[i];
		current = current ^ 0xC3;
		current += 0x0F;
		finalPacket += current;
	}
	return finalPacket;
}
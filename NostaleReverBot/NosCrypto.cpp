#include "NosCrypto.h"
#include "Tools.h"

DWORD prevNum = 0;
DWORD generateSeed(DWORD num) {
	DWORD edx = (DWORD)((int)prevNum * (int)0x8088405);
	++edx;
	prevNum = edx;
	edx = edx * num;
	return edx;
}

std::string generateRandomNum(DWORD* seed) {
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
		if (strRandomBytes.length() == 7) break;
		strRandomBytes = (char)resto + strRandomBytes;
		if (strRandomBytes.length() > 7) strRandomBytes = strRandomBytes.substr(0, 8);

		//randomBytes += resto << (counter * 8);
		//++counter;
	}

	return strRandomBytes; // devuelve en hex
}

// ################################## LOGIN ENCRYPT/DECRYPT METHODS ##############################################
std::string login_decrypt(std::string packet) {
	// server to client login packets decryption.
	for (int i = 0; i < packet.length(); ++i) {
		packet[i] -= 0x0F;
		if (packet[i] == 0x0A) {
			break;
		}
		if (packet[i] == 0x20) {
			continue;
		}
	}
	return packet;
}

std::string login_decrypt_server(std::string packet) {
	// method used on server side to decrypt client packets.
	for (int i = 0; i < packet.length(); ++i) {
		packet[i] = (packet[i] - 0x0F) ^ 0xC3;
	}
	return packet;
}

std::string login_encrypt(std::string & packet) {
	// client to server packet encryption
	for (int i = 0; i < packet.length(); ++i) {
		packet[i] = (packet[i] ^ 0xC3) + 0x0F;
	}
	return packet;
}




// ################################## INGAME ENCRYPT/DECRYPT METHODS ##########################################
std::string ingame_decrypt(std::string packet) {
	return "";
}

std::string ingame_encrypt(std::string packet) {
	return "";
}

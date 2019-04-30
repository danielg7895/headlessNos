#include "nostale_sockets.cpp"
#include "main.h"
#include <vector>

std::string SERVER_IP = "79.110.84.75";
std::string SERVER_PORT = "4005";

std::string string_to_hex(const std::string& input);
void main() {

	DWORD seed;
	NostaleSocket nostaleSocket;

	for (int i = 0; i < 120; i++) {
		seed = generateSeed(0x989680);
	}
	/*
	std::string loginPacket = login("daniel.g7895@gmail.com", "262sda26D");
	int len = loginPacket.length();
	encrypt(loginPacket);
	loginPacket = decryptLoginServer(loginPacket);

	printf(loginPacket.c_str());

	//printf("%d\n", len);
	nostaleSocket.test(loginPacket.c_str(), len);
	printf(decrypt(nostaleSocket.recvBuff).c_str());
	*/
	
	std::string resp2 = "].ctbc/sp}xt{vFGHD/A/D?D?B/FH=@@?=GC=FHIC?ADI?I@=E=Td<X}ux}x../FH=@@?=GC=FHIC?AEI?I@=F=Td<X}ux}x../A?E=ADB=@FD=GGIC?BCI?IB=D=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?ABI?I@=C=Td<X}ux}x../FH=@@?=GC=FHIC?AAI?I@=B=Td<X}ux}x../A?E=ADB=@FD=GGIC?BBI?IB=C=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?ACI?I@=D=Td<X}ux}x../A?E=ADB=@FD=GGIC?BAI?IB=B=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?A@I?I@=A=Td<X}ux}x../A?E=ADB=@FD=GGIC?B@I?IB=A=cwtxp7P|t.xrp8/A?E=ADB=@FD=GGIC?B?IBIB=@=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?A?ICI@=@=Td<X}ux}x../<@I<@I<@I@????=@????=C";
	std::string send = "9CBBF9F02050303F20401FF02FF06FFFFFF02FF02FF03FF0A0096FF05FF04040104000096FF06FF06FF0004FF0096FF09FF05FFFFFF090096FF05FF0AFF000404FF0404010405FF04FF05040504FF04FFF2B6B1BCB9B5BEB3030A0905F29C9B9C95AB8F9999F202020006099696FFD702FC09FCFFFCFF010200F202F29491949591040A000291949196038FFF00039691068F0995068F020006010202D8";
	int size = send.length();
	std::string whaaaa = "";
	for (int i = 0; i < size; i += 2) {
		std::string curr2 = send.substr(i, 2);
		whaaaa += (char)stoi(curr2, nullptr, 16);
	}
	whaaaa = decryptLoginServer(whaaaa);


	
	
	//printf(decryptLoginServer(send).c_str());
	
	
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
	std::string packet;
	packet += opcode;
	packet += " " + randomNum1;
	packet += " " + user + " " + passSHA512;
	packet += " NONE " + randomNum2;
	packet += 0x0B;
	packet += gameVersion + " 0 " + bothMD5;
	packet += 0x0A;

	return packet;
}


std::string decrypt(std::string packet) {

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

std::string decryptLoginServer(std::string packet) {
	for (int i = 0; i < packet.length(); ++i) {
		packet[i] = (packet[i] - 0x0F) ^ 0xC3 ;
	}
	return packet;
}

char* decryptLoginServer(char* packet, int len) {
	for (int i = 0; i < len; ++i) {
		packet[i] = (packet[i] - 0x0F) ^ 0xC3;
	}
	return packet;
}

std::string encrypt(std::string& packet) {

	for (int i = 0; i < packet.length(); ++i) {
		packet[i] = (packet[i] ^ 0xC3) + 0x0F;
	}
	return packet;
}

char* encrypt(char* packet, int len) {
	for (int i = 0; i < len; ++i) {
		packet[i] = (packet[i] ^ 0xC3) + 0x0F;
	}
	return packet;
}
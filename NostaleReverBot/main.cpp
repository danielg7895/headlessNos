#include "nostale_sockets.cpp"
#include "main.h"
#include <vector>
#include "Tools.h"
#include "NosCrypto.h"

std::string SERVER_IP = "79.110.84.75";

std::string SERVER_PORT = "4005";

void main() {

	DWORD seed;
	NostaleSocket nostaleSocket;

	for (int i = 0; i < 150; i++) {
		seed = generateSeed(0x989680);
	}
	
	std::string loginPacket = login("user", "pass");
	int len = loginPacket.length();
	login_encrypt(loginPacket);

	nostaleSocket.test(loginPacket.c_str(), len);
	printf(login_decrypt(nostaleSocket.recvBuff).c_str());
	
	
	std::string resp2 = "].ctbc/sp}xt{vFGHD/A/D?D?B/FH=@@?=GC=FHIC?ADI?I@=E=Td<X}ux}x../FH=@@?=GC=FHIC?AEI?I@=F=Td<X}ux}x../A?E=ADB=@FD=GGIC?BCI?IB=D=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?ABI?I@=C=Td<X}ux}x../FH=@@?=GC=FHIC?AAI?I@=B=Td<X}ux}x../A?E=ADB=@FD=GGIC?BBI?IB=C=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?ACI?I@=D=Td<X}ux}x../A?E=ADB=@FD=GGIC?BAI?IB=B=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?A@I?I@=A=Td<X}ux}x../A?E=ADB=@FD=GGIC?B@I?IB=A=cwtxp7P|t.xrp8/A?E=ADB=@FD=GGIC?B?IBIB=@=cwtxp7P|t.xrp8/FH=@@?=GC=FHIC?A?ICI@=@=Td<X}ux}x../<@I<@I<@I@????=@????=C";
	std::string send = "9CBB9F02050303F2FF020404FF0204FFFF0AFF040405FF0500960404FF0304FFFF000096FF06FF00FFFFFF0A00960400FF06FF04FF060096FF090401FF090405FF03FFFF0404FF0AFF060406FFFFFF09F2B3B5B7B1040202F29C9B9C95AB8F9999F2020204FF94950391D702FC09FCFFFCFF010200F202F20503090A90900105048F9096090596019590FF90000302949004000496020004D8";
	std::string original = "9CBB9F02050305F209090605020906F2B3B5B7B1040202F291028F020909FF940596000996090104098F010095030501060A948F0994FF0405049506050204940605029196029196000691098F96049505960A96940494FF018F9509010004040496058F91FF90050A06040503919004950090940695068F0602FF9605030902959102940001960391940002020606020103949006949400F29C9B9C95F20202FF0200969604D702FC09FCFFFCFF010200F202F2050506090191029691059504030203038F05960A0400028F940003968FFF96FFD8";
	int size = send.length();
	std::string whaaaa = "";
	for (int i = 0; i < size; i += 2) {
		std::string curr2 = send.substr(i, 2);
		whaaaa += (char)stoi(curr2, nullptr, 16);
	}

	whaaaa = login_decrypt_server(whaaaa);

	//printf(whaaaa.c_str());

	std::string originalDecrypt = "";
	for (int i = 0; i < size; i += 2) {
		std::string curr2 = original.substr(i, 2);
		originalDecrypt += (char)stoi(curr2, nullptr, 16);
	}
	originalDecrypt = login_decrypt_server(originalDecrypt);

	//printf(originalDecrypt.c_str());

	
	//printf(decryptLoginServer(send).c_str());
}

std::string login(std::string user, std::string password) {
	MD5 md5;

	std::string nostalePath = "C:\\Program Files (x86)\\Nostale_ES";
	std::string md5NostaleClientX = md5.digestFile((nostalePath + "\\NostaleClient.exe").c_str());
	std::string md5NostaleClient = md5.digestFile((nostalePath + "\\NostaleClientX.exe").c_str());
	std::string md5_hash = md5NostaleClient + md5NostaleClientX + user;


	std::string opcode = "NoS0575";

	DWORD seed = generateSeed(0x989680);
	seed = generateSeed(0x989680) + 0x86111;
	std::string randomNum1 = generateRandomNum(&seed);

	std::string passSHA512 = sha512(password);
	std::string randomNum2 = int2hex_str((int)generateSeed(0x989680));
	std::string gameVersion = "0.9.3.3103";
	std::string bothMD5 = md5.digestString(md5_hash);
	std::string packet;
	packet += opcode;
	packet += " " + randomNum1;
	packet += " " + user + " " + passSHA512;
	packet += " NONE " + randomNum2;
	packet += 0x0B;
	packet += gameVersion + " 0 " + bothMD5;
	packet += 0x0A;


	//std::cout << "NoS0577 30663063383665352D663763322D343233382D623436342D396139653733663834643339 geka600 NONE_CII 0063FE7A\v0.9.3.3102 0 5798BB156CBD95D1EB3B270FB626D026\n" << std::endl;

	return packet;
}
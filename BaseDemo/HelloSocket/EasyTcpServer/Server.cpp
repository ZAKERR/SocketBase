#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <Windows.h>
#include <WinSock2.h>
#include <cstdio>
//#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[]) {
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	
	WSACleanup();
}
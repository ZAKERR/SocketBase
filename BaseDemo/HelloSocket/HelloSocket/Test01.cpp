#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WinSock2.h>

//#pragma comment(lib,"ws2_32.lib")

int main(int argc,char *argv[]) {
	WORD ver = MAKEWORD(2, 2);


	WSADATA dat;

	/*_In_ WORD wVersionRequested,
		_Out_ LPWSADATA lpWSAData
		*/
	//��WSA(Windows Sockets Asynchronous��Windows�첽�׽���)����������
	WSAStartup(ver, &dat);


	WSACleanup();
}
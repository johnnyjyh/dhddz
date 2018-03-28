
#ifndef __NET_H__
#define __NET_H__

#ifdef WIN32
#include <WinSock2.h>
#else
// in linux, android, ios
#define SOCKET int

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#endif

#include "cocos2d.h"


#define NET_MAX_CONN 255
#define BUF_MAX 255
USING_NS_CC;
//

struct recvThreadArgu
{
			SOCKET sock;
			char *buf;
			int len;
			int flag;
};

class Net
{
public:
			static SOCKET _server;
			static SOCKET _connet;
			static SOCKET _clients[NET_MAX_CONN];

			static int _isConnected;
			static bool _isRecvComplete;
			static bool _isRecvCompleteNet  [NET_MAX_CONN];
			static int playertag;//���ڱ����ң����ǹ涨serverΪ0��server��_clients[1]Ϊ1����ң�Ϊ0���¼ң�server��_client[2]Ϊ2��1���¼ң�0���ϼ�

			static char *_recvData;
			static char (*_recvDataCon)[BUF_MAX];

			static bool Listen(short port =9999);
			static int isConnected();

			static bool Connect(const char* ip, short port =9999);
			static int Send(int tag,const char* buffer, int len);
			static int AnalyzeRecvBuf(SOCKET &sock, const char *buf, int len);
			static bool isEmptyStr(const char *str);


			// �������ݵĽӿ�
			static int RecvStart();
			static bool isRecvCompleteNet(int tag);
			static bool isRecvComplete();
			static char* RecvData(int& len);		
			static char *RecvData(int &len, int tag);
			

#ifdef WIN32
			static DWORD WINAPI AcceptThreadFunc(void* arg);
			static DWORD WINAPI RecvThreadFunc(void* arg);
			static DWORD WINAPI RecvThreadFuncServer(void *arg);
			static DWORD WINAPI SelectThreadFunc(void *arg);
#else
			static void* AcceptThreadFunc(void*);
			static void* RecvThreadFunc(void*);
			static void* RecvThreadFuncServer(void *);
			static void *SelectThreadFunc(void *arg);
#endif

			static void clear();
};

#endif


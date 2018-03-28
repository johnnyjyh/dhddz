#include "Net.h"
#ifdef WIN32
#else
#define INVALID_SOCKET -1
#define closesocket close
#endif

//////////////////////////////
//扑克num规定:                //
//黑桃   3 - A, 2  0 - 12     //
//红桃   3 - A, 2  13 - 25   //
//梅花   3 - A, 2   26 - 38  //
//方块   3 - A, 2   39 - 51  //
//大鬼小鬼  52, 53            //
//////////////////////////////

SOCKET Net::_server = INVALID_SOCKET;
SOCKET Net::_connet = INVALID_SOCKET;
SOCKET Net::_clients[NET_MAX_CONN];

int Net::playertag=-1;
int Net::_isConnected = 0;
bool Net::_isRecvComplete = false;
char *Net::_recvData=NULL;
char(*Net::_recvDataCon)[BUF_MAX]=NULL;
bool Net::_isRecvCompleteNet[NET_MAX_CONN];

bool Net::Listen(short port)
{
#ifdef WIN32
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			{
						return false;
			}
#endif
			for (int i = 0; i < NET_MAX_CONN; ++i)
			{
						_clients[i] = INVALID_SOCKET;
			}

			SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
			if (sock == INVALID_SOCKET)
			{
						log("%ld", WSAGetLastError());
						CCLOG("create socket error");
						return false;
			}
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
#ifdef WIN32
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
#else
			addr.sin_addr.s_addr = INADDR_ANY;
#endif

#ifdef WIN32

#else
			int optval = 1;
			setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
#endif
			int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
			if (ret != 0)
			{
						CCLOG("bind error");
						closesocket(sock);
						return false;
			}

			if (listen(sock, 10) < 0)
			{
						CCLOG("listen error");
						closesocket(sock);
						return false;
			}
			
			_server = sock;
			_clients[0] = _server;
			_isConnected = 1;


#ifdef WIN32
			HANDLE hThread1 = CreateThread(NULL, 0, AcceptThreadFunc, NULL, 0, NULL);
			CloseHandle(hThread1);
			//HANDLE hThread2 = CreateThread(NULL, 0, AcceptThreadFunc, NULL, 0, NULL);
			//CloseHandle(hThread2);
#else
			pthread_t tid;
			pthread_create(&tid, NULL, AcceptThreadFunc, NULL);
#endif

#ifdef WIN32
			HANDLE selThread = CreateThread(NULL, 0, SelectThreadFunc, NULL, 0, NULL);
			CloseHandle(selThread);
#else
			pthread_t selTid;
			pthread_create(&selTid, NULL, SelectThreadFunc, NULL);
#endif


			return true;
}

#ifdef WIN32
DWORD Net::AcceptThreadFunc(void*)
#else
void* Net::AcceptThreadFunc(void *)
#endif
{
		 
			SOCKET clienttemp;
			bool conn_max = false;
			while (1)
			{
						clienttemp = accept(_server, NULL, NULL);
						conn_max = false;
						if (clienttemp > 0)
						{
									for (int i = 0; i < NET_MAX_CONN; ++i)
									{
												if (_clients[i] == INVALID_SOCKET)
												{
															CCLOG("_isConnected=%d", _isConnected);
															_clients[_isConnected++] = clienttemp;
															conn_max = true;
															break;
												}
									}
						}
						if (!conn_max)
						{
									CCLOG("client connected  is max");
									break;
						}
			}
								
#ifdef WIN32
			return 0;
#else
			return NULL;
#endif
}

int Net::isConnected()
{
			return _isConnected;
}

bool Net::Connect(const char* ip, short port)
{
#ifdef WIN32
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			{
						return false;
			}
#endif
			_connet = socket(AF_INET, SOCK_STREAM, 0);
			if (_connet == INVALID_SOCKET)
			{
						log("socket:%ld", WSAGetLastError());
						return false;
			}

			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
#ifdef WIN32
			addr.sin_addr.S_un.S_addr = inet_addr(ip);
#else
			addr.sin_addr.s_addr = inet_addr(ip);
#endif
			int ret = connect(_connet, (struct sockaddr*)&addr, sizeof(addr));
			if (ret != 0)
			{
						log("connect :%ld", WSAGetLastError());
						closesocket(_connet);
						return false;
			}			
			return true;
}

int Net::RecvStart()
{
			//开启recv线程,接收数据
			_isRecvComplete = false;
#ifdef WIN32
			HANDLE recHandle = CreateThread(NULL, 0, RecvThreadFunc, NULL, 0, NULL);
			CloseHandle(recHandle);
#else
			pthread_t tid;
			ptread_create(&tid, NULL,RecvThreadFunc,NULL);
#endif
			return 0;
			
}

bool Net::isRecvCompleteNet(int tag)
{
			return _isRecvCompleteNet[tag];
}

#ifdef WIN32
DWORD Net::RecvThreadFunc(void *arg)
#else
void* Net::RecvThreadFunc(void *arg)
#endif
{
						int ret;
						static char recvBuf[BUF_MAX];
						memset(recvBuf, 0, BUF_MAX);
						ret = recv(_connet, recvBuf, BUF_MAX, 0);
						if (ret < 0)
						{
									CCLOG("recv error");
									closesocket(_connet);
							

						}
						else if (ret == 0)
						{
									CCLOG("no thing");
									closesocket(_connet);
						
						}
						else if (ret > 0)
						{
									_recvData = recvBuf;
									_isRecvComplete = true;
									//解包
						}
			
				
#ifdef WIN32
			return 0;
#else
			return NULL;
#endif
}

#ifdef WIN32
DWORD Net::RecvThreadFuncServer(void *arg)
#else
void *Net::RecvThreadFuncServer(void *arg)
#endif
{
			
#ifdef WIN32
			return 0;
#else
			return NULL;
#endif
}

#ifdef WIN32
DWORD Net::SelectThreadFunc(void *arg)
#else
void *Net::SelectThreadFunc(void *arg)
#endif
{
			int ret;
			struct timeval vl = {	2,0 };
			fd_set read_set;
			SOCKET sockfd;
			static char recvbuf[NET_MAX_CONN][BUF_MAX];
			_recvDataCon = recvbuf;
			while (true)
			{
						FD_ZERO(&read_set);
						for (int i = 0; i < NET_MAX_CONN; ++i)
						{									
									if (_clients[i] != INVALID_SOCKET)
									{
												FD_SET(_clients[i], &read_set);
									}
						}
						ret = select(_isConnected+1, &read_set, NULL, NULL, &vl);
						if (ret == 0)
						{
									continue;
						}
						else if (ret < 0)
						{
									CCLOG("select error:%ld",WSAGetLastError ());
									break;
						}
						//unsigned long ul = 1;
						for (int i = 0; i < NET_MAX_CONN; ++i)
						{
									
									if ((sockfd = _clients[i]) < 0)
									{
												continue;
									}
								
									if (FD_ISSET(sockfd, &read_set))
									{															
												ret = recv(sockfd, recvbuf[i], BUF_MAX, 0);
												if (ret < 0)
												{
															CCLOG("recv error");
															FD_CLR(sockfd, &read_set);
															closesocket(sockfd);
															_clients[i] = INVALID_SOCKET;													
												}
												else if (ret == 0)
												{
															CCLOG("recv no thing");
															FD_CLR(sockfd, &read_set);
															closesocket(sockfd);
															_clients[i] = INVALID_SOCKET;
												}
												else if (ret > 0)
												{
															//处理接收到的数据
															//解包														
															_recvData = recvbuf[i];															
															_isRecvCompleteNet[i]=true;	
															//log("%d,%s", i,_recvDataCon[i]);
															//AnalyzeRecvBuf(sockfd, recvbuf, ret);
												}

												if (_isConnected == 0)
												{
															break;
												}											
									}
						}
			}



#ifdef WIN32
			return 0;
#else
			return NULL;
#endif
}

bool Net::isRecvComplete()
{
			return _isRecvComplete;
}

char* Net::RecvData(int& len)
{
			len = 0; // len目前没有用
			_isRecvComplete = false; // 报文被取走，接收状态回到初始状态
			return _recvData;
}

char * Net::RecvData(int & len, int tag)
{
			_isRecvCompleteNet[tag] = false;
			return _recvDataCon[tag];
			
}

int Net::Send(int tag,const char* buffer, int len)
{
			//封包
			int ret = -1;
			do
			{
						if (len > BUF_MAX)
						{
									CCLOG("send size to big");
									return ret;
						}
						if (tag == 0)
						{
									ret = send(_connet, buffer, len, 0);
									if (ret < 0)
									{
												CCLOG("0 send error");
												break;
									}
									ret = 0;
						}
						else if (tag == 1)
						{
									ret = send(_clients[1], buffer, len, 0);
									if (ret < 0)
									{
												CCLOG("1 send error");
												break;
									}
									ret = 1;

						}
						else if (tag == 2)
						{
									ret=send(_clients[2], buffer, len, 0);
									if (ret < 0)
									{
												CCLOG("2 send error");
												break;
									}
									ret = 2;
						}
			} while (0);
			log("%s", buffer);
			return ret;
}

int Net::AnalyzeRecvBuf(SOCKET & sock, const char * buf, int len)
{
			int ret = -1;
			do
			{
						int target;
						for (int i = 0; i < NET_MAX_CONN; ++i)
						{
									if (_clients[i] != INVALID_SOCKET && _clients[i] == sock)
									{
												target = i;
												break;
									}
						}
						if (isEmptyStr(_recvDataCon[target]))
						{									
									break;
						}
						if (strcmp(_recvDataCon[target], buf)!=0)
						{
									ret = 1;
									break;
						}
						ret = 0;
			} while (0);
			return ret;
}

bool Net::isEmptyStr(const char * str)
{
			bool ret = false;
			do
			{
						if (str == nullptr)
						{
									ret = true;
						}
						else if (std::strlen(str) == 0)
						{
									ret = true;
						}
			} while (0);
			return ret;
}

void Net::clear()
{
			if (_isConnected != 0)
			{
						for (int i = 0; i < NET_MAX_CONN; ++i)
						{
									if (_clients[i] != INVALID_SOCKET)
									{
												closesocket(_clients[i]);
												_clients[i] = INVALID_SOCKET;
									}
						}
			}

			if (_server != INVALID_SOCKET)
						closesocket(_server);
}

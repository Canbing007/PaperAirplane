#ifndef SUPERSOCKSRINTERACTIVE_H
#define SUPERSOCKSRINTERACTIVE_H

#include "SocketExtension.h"

#ifndef PAPERAIRPLANE_CONFIG_WRITE_CHANNEL
#define PAPERAIRPLANE_CONFIG_WRITE_CHANNEL "PaperAirplane.Configuration_WriteMmfMap"
#endif
#ifndef PAPERAIRPLANE_CONFIG_READ_CHANNEL
#define PAPERAIRPLANE_CONFIG_READ_CHANNEL "PaperAirplane.Configuration_ReadMmfMap"
#endif

typedef struct SupersocksRConfiguration
{
	BYTE EnableProxyClient; // ���ô���ͻ���
	BYTE ResolveDNSRemote; // Զ�̵�ַ����
	USHORT ProxyHostPort; // ����˿�
	ULONG ProxyHostAddress; // �����ַ
	hash_set<USHORT> FilterPortNumber; // ���˶˿ں�
	hash_set<ULONG> FilterHostAddress; // ���˶˿ں�
	hash_set<string> FilterHostName; // ������������
} SupersocksRConfiguration;

typedef enum SupersocksRInteractiveCommands : UINT8
{
	SupersocksRInteractiveCommands_QueryConfiguration = 1,
	SupersocksRInteractiveCommands_ConnectionHeartbeat = 2,
} SupersocksRInteractiveCommands;

class SupersocksRInteractive 
{
private:
	HANDLE m_hthread;
	SupersocksRConfiguration m_configuration;
	CRITICAL_SECTION m_cs;
	HANDLE m_hReadMap;
	HANDLE m_hReadEvent;
	void* m_pReadMView;
	INT m_msgID;

public:
	SupersocksRInteractive();

	~SupersocksRInteractive();

	bool Enter();

	void Leave();

	SupersocksRConfiguration* Configuration();

private:
	void ResetConfiguration();

	static DWORD WINAPI MMapWorkThread(SupersocksRInteractive* self);

	void HandleQueryConfiguration(char* buf);

	char* mmap(int timeout = INFINITE, int* error = NULL);

	void munmap();
};
#endif
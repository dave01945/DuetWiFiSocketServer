/*
 * Listener.h
 *
 *  Created on: 12 Apr 2017
 *      Author: David
 */

#ifndef SRC_LISTENER_H_
#define SRC_LISTENER_H_

#include <cstdint>
#include <cstddef>
#include "sdkconfig.h"

#if !defined(ESP32) && (defined(CONFIG_IDF_TARGET_ESP32) || defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3) || defined(CONFIG_IDF_TARGET_ESP32C2) || defined(CONFIG_IDF_TARGET_ESP32C3) || defined(CONFIG_IDF_TARGET_ESP32C6) || defined(CONFIG_IDF_TARGET_ESP32H2) || defined(CONFIG_IDF_TARGET_ESP32P4))
#define ESP32 1
#endif

#ifdef ESP32
class Listener
{
public:
	Listener();
	static void Init() { }
	static bool Listen(uint32_t ip, uint16_t port, uint8_t protocol, uint16_t maxConns);
	static void StopListening(uint16_t port);
	static uint16_t GetPortByProtocol(uint8_t protocol);
	static void Poll();
	void PollAccept();

private:
	void Stop();

	static Listener *Allocate();
	static void Unlink(Listener *lst);
	static void Release(Listener *lst);

	Listener *next;
	int sock;
	uint32_t ip;
	uint16_t port;
	uint16_t maxConnections;
	uint8_t protocol;

	static Listener *activeList;
	static Listener *freeList;
};
#else
// If we #include "tcp.h" here we get clashes between two different ip_addr.h files, so don't do that here
class tcp_pcb;
class pbuf;

class Listener
{
public:
	Listener();
	int Accept(tcp_pcb *pcb);

	static void Init() { }
	static bool Listen(uint32_t ip, uint16_t port, uint8_t protocol, uint16_t maxConns);
	static void StopListening(uint16_t port);
	static uint16_t GetPortByProtocol(uint8_t protocol);

private:
	void Stop();

	static Listener *Allocate();
	static void Unlink(Listener *lst);
	static void Release(Listener *lst);

	Listener *next;
	tcp_pcb *listeningPcb;
	uint32_t ip;
	uint16_t port;
	uint16_t maxConnections;
	uint8_t protocol;

	static Listener *activeList;
	static Listener *freeList;
};
#endif
#endif /* SRC_LISTENER_H_ */

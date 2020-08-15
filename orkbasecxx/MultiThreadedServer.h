/*
 * Oreka -- A media capture and retrieval platform
 * 
 * Copyright (C) 2005, orecx LLC
 *
 * http://www.orecx.com
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License.
 * Please refer to http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef __MULTITHREADEDSERVER_H__
#define __MULTITHREADEDSERVER_H__

#include <log4cxx/logger.h>

#include "OrkBase.h"
#include "dll.h"
#include "Utils.h"
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

/** This server accepts permanent telnet like connections.
	commands are accepted in "single line" format.
	one thread per connection
*/
class DLL_IMPORT_EXPORT_ORKBASE CommandLineServer
{
public:
	CommandLineServer(int port);
	bool Initialize();
	void Run();


private:
	apr_pool_t* m_mp;
	int m_port;
	apr_socket_t* m_socket;
    apr_sockaddr_t* m_sockAddr;
	static log4cxx::LoggerPtr s_log;
	static void RoutineSvc(apr_socket_t* sock);
};

/** This server is a lightweight http server that extracts commands from URLs and outputs results in xml format
	one thread per connection
	Example url:
	http://localhost:23000/message=print&text=hello
*/
class DLL_IMPORT_EXPORT_ORKBASE HttpServer
{
public:
	HttpServer(int port);
	bool Initialize();
	void Run();
	void RunHttpServer();

private:
	apr_pool_t* m_mp;
	int m_port;
	apr_socket_t* m_socket;
	apr_socket_t* m_sslSocket;
    apr_sockaddr_t* m_sockAddr;
	static log4cxx::LoggerPtr s_log;
	static void HandleHttpMessage(apr_socket_t* sock, apr_pool_t* pool);

};

#ifdef SUPPORT_TLS_SERVER
class DLL_IMPORT_EXPORT_ORKBASE HttpsServer
{
public:
	HttpsServer(int port);
	bool Initialize();
	void Run();
	void RunHttpsServer();

private:
	apr_pool_t* m_mp;
	apr_socket_t* m_sslSocket;
	int m_sslPort;
	apr_sockaddr_t* m_sslSockAddr;
	static SSL_CTX* m_ctx;
	static log4cxx::LoggerPtr s_log;
	static void HandleSslHttpMessage(apr_socket_t* sock);
};
#endif //#ifndef CENTOS_6

//==========================================================

/** This server is a lightweight http server that prints out the single line
    format of all events from a given port, one thread per connection e.g
	http://localhost:23000/message=streamevents
*/
class DLL_IMPORT_EXPORT_ORKBASE EventStreamingServer
{
public:
	EventStreamingServer(int port);
	~EventStreamingServer() { apr_pool_destroy(m_mp);};
	bool Initialize();
	void Run();


private:
	apr_pool_t* m_mp;
	int m_port;
	apr_socket_t* m_socket;
    apr_sockaddr_t* m_sockAddr;
	static log4cxx::LoggerPtr s_log;
	static void StreamingSvc(apr_socket_t* sock, apr_pool_t* pool);
};



#endif


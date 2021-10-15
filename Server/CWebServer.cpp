/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Server
* File       : CWebServer.cpp
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#include "StdInc.h"
#include "CCore.h"

#include "squirrel.h"
#include "sqstdio.h"

CMutex				webMutex;

void * CWebServer::MongooseEventHandler( mg_event event, mg_connection * connection, const mg_request_info * request_info )
{
	if( event == MG_NEW_REQUEST )
	{
		// Lock the web mutex
		webMutex.Lock ();

		// Get the IP address
		in_addr sa;
		memset( &sa, 0, sizeof(in_addr) );
		sa.s_addr = htonl( request_info->remote_ip );
		char * szIpAddress = inet_ntoa( sa );

		// Call the scripting event
		CSquirrelArguments pArguments;
		pArguments.push( szIpAddress );
		pArguments.push( request_info->remote_port );
		pArguments.push( request_info->uri );
		pArguments.push( request_info->request_method );
		CCore::Instance()->GetEvents()->Call( "onWebRequest", &pArguments );

		// Unlock the web mutex
		webMutex.Unlock ();
	}

	// Not handled
	return NULL;
}

CWebServer::CWebServer( void )
{
	// Reset the mongoose context pointer
	m_pMongooseContext = NULL;

	// Do we not have external webserver configred?
	if( strlen( CVAR_GET_STRING( "httpserver" ) ) == 0 )
	{
		// Allocate the options
		char * options[7];

		for( int i = 0; i < 6; i++ )
			options[i] = new char[256];

		// Set the options
		strcpy( options[0], "listening_ports" );
		String httpPort;
		httpPort.Format( "%d", (CVAR_GET_INTEGER ( "port" ) + 1) );
		strcpy( options[1], httpPort );
		strcpy( options[2], "document_root" );
		strcpy( options[3], SharedUtility::GetAbsolutePath( "webserver" ).Get() );
		strcpy( options[4], "num_threads" );
		strcpy( options[5], "50" );
		options[6] = NULL;

		// Start mongoose
		m_pMongooseContext = mg_start( MongooseEventHandler, (const char **)options );

		// Free the options
		for( int i = 0; i < 6; i++ )
			delete [] options[i];

		// Did mongoose fail to start?
		if( !m_pMongooseContext )
			CLogFile::Printf( "[error] Failed to start webserver on port %d!", (CVAR_GET_INTEGER ( "port" ) + 1) );
	}
}

CWebServer::~CWebServer( void )
{
	// Do we have a valid mongoose context pointer?
	if( m_pMongooseContext )
	{
		// Stop mongoose
		mg_stop( m_pMongooseContext );

		// Reset the mongoose context pointer
		m_pMongooseContext = NULL;
	}
}

void CompileScript_ErrorHandler( HSQUIRRELVM vm, const SQChar * desc, const SQChar * source, SQInteger line, SQInteger column )
{
	CLogFile::Printf( "ERROR: Failed to compile script '%s'. (Line: %d, Column: %d, Error: %s)", source, line, column, desc );
}

bool CompileScript( const char * szFile, const char * szFileOut )
{
	// Open a new squirrel vm
	HSQUIRRELVM vm = sq_open( 1024 );

	// Did the vm fail to open?
	if( !vm )
		return false;

	// Set the script compile error handler
	sq_setcompilererrorhandler( vm, CompileScript_ErrorHandler );

	// Compile the source file
	bool bFailed = SQ_FAILED( sqstd_loadfile( vm, szFile, SQTrue ) );

	// Did the script fail to compile?
	if( bFailed )
	{
		// Close the vm
		sq_close( vm );
		return false;
	}

	// Write the closure containing the compiled script
	bFailed = SQ_FAILED( sqstd_writeclosuretofile( vm, szFileOut ) );

	// Did the script fail to write the compiled script?
	if( bFailed )
	{
		// Close the vm
		sq_close( vm );
		return false;
	}

	sq_close( vm );
	return true;
}

bool CWebServer::FileCopy( String strDirectory, String strFileName, CFileChecksum * pChecksum, bool bIsScript )
{
	// Get the file location
	String strFile;
	strFile.Format( "%s/%s", strDirectory.Get(), strFileName.Get() );

	//
	String strWebServerFilePath = strFile;

	// Do we not have external webserver configured?
	if( strlen( CVAR_GET_STRING( "httpserver" ) ) == 0 )
	{
		// Does the file not exist?
		if( !SharedUtility::Exists( strFile.Get() ) )
			return false;

		// Get the path to copy to
		strWebServerFilePath.Format( "webserver/%s", strFileName.Get() );

		// Does the webserver path not exist?
		if( !SharedUtility::Exists( "webserver" ) )
		{
			// Create the webserver directory
			SharedUtility::CreateDirectory( "webserver" );
		}

		// Is this file a script?
		if( bIsScript )
		{
			// Compile the script
			if( !CompileScript( strFile.Get(), strWebServerFilePath.Get() ) )
				return false;
		}
		else
		{
			// Copy the file to the webserver
			if( !SharedUtility::CopyFile( strFile.Get(), strWebServerFilePath.Get() ) )
				return false;
		}
	}

	if( pChecksum )
		return pChecksum->Calculate( strWebServerFilePath.Get() );

	return true;
}

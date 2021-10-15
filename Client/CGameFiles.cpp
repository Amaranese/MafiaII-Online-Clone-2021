/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Client
* File       : CGameFiles.cpp
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#include "BaseInc.h"

#include "CString.h"
#include "SharedUtility.h"

#include "CCore.h"

#include "CRC.h"
#include "CZlib.h"

#include "CGameFiles.h"

#include "CLogFile.h"

String				CGameFiles::m_strError;
std::list< String >	CGameFiles::m_deleteFiles;

#define	TYPE_MOD		0
#define	TYPE_GAME		1

struct GameFile
{
	unsigned int		uiChecksum;
	const char			* szFile;
	bool				bCompressed;
	const char			* szOutput;
	bool				bDeleteAfterDecompress;
	BYTE				type;
}
gameFiles[] =
{
	{ 0x7C95AB5E,	"edit\\tables\\StreamM2MP.bin",					false,		"",										false,	TYPE_GAME },
	{ 0xE3DC0B73,	"edit\\sdsmpconf.bin",							false,		"",										false,	TYPE_GAME },
	{ 0xC8136525,	"pc\\sds\\missionscript\\freeraid_m2mp.sds",	false,		"",										false,	TYPE_GAME },
	{ 0xAE3CCEE2,	"data\\game\\0.m2o",							true,		"sds\\mp\\gui.sds",						true,	TYPE_MOD },
	{ 0x0B551386,	"data\\game\\1.m2o",							true,		"sds\\mp\\gui-main.sds",				true,	TYPE_MOD },
	{ 0xE1E987D6,	"data\\game\\2.m2o",							true,		"sds\\mp\\tables.sds",					true,	TYPE_MOD },
	{ 0x665303E5,	"data\\game\\3.m2o",							true,		"sds\\skies\\sky_m2mp.sds",				true,	TYPE_MOD }
};

bool CGameFiles::CheckFiles( void )
{
	CCore *pCore = CCore::Instance();

	// Generate the multilpayer path
	String strMultiplayerPath;
	strMultiplayerPath.Format( "%s\\pc\\sds\\mp", pCore->GetGameDirectory().Get() );

	// Does the multiplayer folder not exist?
	if( !SharedUtility::Exists( strMultiplayerPath.Get() ) )
	{
		// Create the multiplayer folder
		SharedUtility::CreateDirectory( strMultiplayerPath.Get() );
	}

	// Loop through all files that need checking
	for( int i = 0; i < ARRAY_LENGTH( gameFiles ); i++ )
	{
		// Set the working directory
		if( gameFiles[i].type == TYPE_GAME )
			SetCurrentDirectory( pCore->GetGameDirectory().Get() );
		else
			SetCurrentDirectory( pCore->GetModDirectory().Get() );

		// Does the file not exist?
		if( !SharedUtility::Exists( gameFiles[i].szFile ) )
		{
			CLogFile::Printf( "Can't find the file '%s\\%s'!", (gameFiles[i].type == TYPE_GAME ? pCore->GetGameDirectory().Get() : pCore->GetModDirectory().Get()), gameFiles[i].szFile );

			// Set the last error
			String error;
			error.Format( "Can't find the file '%s'.", gameFiles[i].szFile );
			SetLastError( error );

			return false;
		}

		// Create the file checksum
		CFileChecksum pFileChecksum;

		// Calculate the current file checksum
		pFileChecksum.Calculate( gameFiles[i].szFile );

		CLogFile::Printf( "File checksum: '%s': 0x%p", gameFiles[i].szFile, pFileChecksum.GetChecksum() );

		// Does the file checksum not match?
		if( pFileChecksum.GetChecksum() != gameFiles[i].uiChecksum )
		{
			// Set the last error
			String error;
			error.Format( "The file '%s' has been modified.", gameFiles[i].szFile );
			SetLastError( error );

			CLogFile::Printf( "File Error: '%s', expected checksum 0x%p, got 0x%p", gameFiles[i].szFile, gameFiles[i].uiChecksum, pFileChecksum.GetChecksum() );

			return false;
		}

		// Does this file need decompressing?
		if( gameFiles[i].bCompressed )
		{
			// Decompress the file
			String path;
			path.Format( "%s\\pc\\%s", pCore->GetGameDirectory().Get(), gameFiles[i].szOutput );
			int iResult = CZlib::Decompress( gameFiles[i].szFile, path );

			// Did the file fail to decompress?
			if( iResult != Z_OK )
			{
				// Set the last error
				String error;
				error.Format( "Failed to decompress the file '%s'. (Error: %d)", gameFiles[i].szFile, iResult );
				SetLastError( error );

				return false;
			}

			// Should we delete this file?
			if( gameFiles[i].bDeleteAfterDecompress )
			{
				// Push the file onto the delete queue
				m_deleteFiles.push_back( gameFiles[i].szOutput );
			}
		}
	}
	return true;
}

void CGameFiles::CleanFiles( void )
{
	// Delete the queued items
	for( std::list< String >::iterator iter = m_deleteFiles.begin(); iter != m_deleteFiles.end(); iter++ )
	{
		// Delete the item
		DeleteFile( (*iter).Get() );
	}

	// Clear the queue
	m_deleteFiles.clear( );

	// Reset the current directory
	SetCurrentDirectory( CCore::Instance()->GetModDirectory().Get() );
}

void CGameFiles::SetLastError( String strError )
{
	m_strError = strError;
}

String CGameFiles::GetLastError( void )
{
	return m_strError;
}

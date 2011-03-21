// Sera executado apenas no Linux
#ifdef __linux__
#include <stdlib.h>
#endif

// Sera executado apenas no Windows
#if defined(mingw32_HOST_OS) || defined(__MINGW32__)
#include <windows.h>
#endif

/*---Limpa a tela---*/
void cls(void)
{
	#ifdef __linux__
	system("clear");
	#endif
	
	#if defined(mingw32_HOST_OS) || defined(__MINGW32__)
    COORD coordScreen = {0, 0}; 
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD dwConSize; 
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	 GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  
    FillConsoleOutputCharacter(hConsole, TEXT(' '),
			       dwConSize, coordScreen, &cCharsWritten);
  
    GetConsoleScreenBufferInfo(hConsole, &csbi);
  
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
                               dwConSize, coordScreen, &cCharsWritten);
    
    SetConsoleCursorPosition(hConsole, coordScreen);
	#endif
	
	/* outra opcao eh usar o CLS do DOS, mas eh mais lento */
	//system("CLS");
}


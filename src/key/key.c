// Sera executado apenas no Windows
#if defined(mingw32_HOST_OS) || defined(__MINGW32__)
#include <conio.h>
#endif

// Sera executado apenas no Linux
#ifdef __linux__
#include <curses.h>
#include "kbhit.h"
#endif

char key='\0';

// Funcao que pega qual tecla esta pressionada
void getkey(void)
{
	char a='a';
	
	#if defined(mingw32_HOST_OS) || defined(__MINGW32__)
	if(_kbhit())
	{
		a=getch();
		if(a=='\0')
		{
			a=getch();
		}
	}
	#endif
	
	#ifdef __linux__
	// Nao funciona ainda
	if(_kbhit())
	{
		a=getch();
		if(a=='^')
		{
			a=getch();
			if(a=='[')
			{
				a=getch();
				if(a=='[')
				{
					a=getch();
					if(a=='C')
					{
						a='M';
					}
					else
						a=27;
				}
			}
		}
	}
	#endif
	
	key = a;
}

// Testa se a tecla pra cima esta pressionada
int up(void)
{
	int k=0;
	if(key=='H')
		k=1;
	return k;
}

// Testa se a tecla pra baixo esta pressionada
int down(void)
{
	int k=0;
	if(key=='P')
		k=1;
	return k;
}

// Testa se a tecla pra esquerda esta pressionada
int left(void)
{
	int k=0;
	if(key=='K')
		k=1;
	return k;
}

// Testa se a tecla pra direita esta pressionada
int right(void)
{
	int k=0;
	if(key=='M')
		k=1;
	return k;
}

// Testa se a tecla ESC esta pressionada
int esc(void)
{
	int k=0;
	if(key==27)
		k=1;
	return k;
}

// Testa se a barra de espaco esta pressionada
int espaco(void)
{
	int k=0;
	if(key==' ')
		k=1;
	return k;
}


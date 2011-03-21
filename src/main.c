#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../include/key.h"			// funcoes do teclado
#include "../include/draw.h"		// funcoes da tela
#include "../include/vars.h"		// variaveis que o usuario configurou


// Funcoes de desenho
extern void zerar();
extern void escrever_tela();
extern void aloc_tela(int, int);
extern void desaloc_tela(int, int);

// Funcao que pega qual tecla esta pressionada
extern void getkey();


// fps do draw
clock_t t0_d=0, t1_d=0;
char fpstxt_d[15];

// fps do game loop
clock_t t0_g=0, t1_g=0;
char fpstxt_g[15];



// Funcao executada no inicio, pra definir as variaveis
void e_init()
{
	// Inicializa os relogios dos FPS
	t0_d = clock();
	t0_g = t0_d;
	
	// Alocar tela
	aloc_tela(tela_x, tela_y);
}



//Funcao executada na saida, para limpar a memoria
void e_fim()
{
	// Desalocar tela
	desaloc_tela(tela_x, tela_y);
}



/*---DRAW---*/
void e_draw()
{
	// Informacoes de debug
	if(debug)
	{
		//----Textos dos FPS----//
		
		// Escreve na string fpstxt_d o texto do fps do draw a ser escrito na tela
		sprintf(fpstxt_d, "fps_d:%.1lf", (double)CLOCKS_PER_SEC/(t1_d-t0_d));
		
		// Escreve na tela a string do fps do draw
		str_draw(fpstxt_d, tela_x-1-strlen(fpstxt_d), tela_y-2);
		
		// Escreve na tela a string do fps do game
		str_draw(fpstxt_g, tela_x-1-strlen(fpstxt_g), tela_y-3);
	}
}



/*---GAME LOOP---*/
void e_game()
{
	// Zera a matriz da tela
	zerar();
	
	// Pega as teclas q tao sendo pressionadas agora
	getkey();
	
	// Informacoes de debug
	if(debug)
	{
		// Traco andando pra direita
		// (pra saber q a tela ta sendo mesmo atualizada)
		static int k=0;
		str_draw("-", k, 0);
		k++;
		if(k>tela_x) k=0;
		
		
		// Escreve na string fpstxt_g o texto do fps do game a ser escrito na tela
		sprintf(fpstxt_g, "fps_g:%.1lf", (double)CLOCKS_PER_SEC/(t1_g-t0_g));
	}
}



/*---MAIN---*/
void e_main( void (*_init)(), void (*_game)(), void (*_draw)(), void(*_fim)())
{
	// Variavel pra ver se eh pra sair do jogo
	short int sair=0;
	
	// Funcoes de inicializar os valores, da engine e do programa
	e_init();
	_init();
	
	do // Loop infinito do jogo
	{
		// game
		t1_g = clock();
		if( (t1_g - t0_g)/(double)CLOCKS_PER_SEC > 1.0/fps_g )
		{
			// Funcoes que redefinem os valores das variaveis
			e_game();
			_game();
			
			// Passa pro outro frame
			t0_g=t1_g;
			
			// Testa pra ver se eh pra sair do jogo
			sair = esc();
		}
		
		// draw
		t1_d = clock();
		if( (t1_d - t0_d)/(double)CLOCKS_PER_SEC > 1.0/fps_d )
		{
			// Funcoes que definem o que deve ser desenhado na tela
			e_draw();
			_draw();
			
			// Passa pro outro frame
			t0_d=t1_d;
			
			// Atualiza a tela
			escrever_tela();
		}
	}while ( !sair );
	
	// Funcoes de desalocar a memoria das variaveis
	e_fim();
	_fim();
}


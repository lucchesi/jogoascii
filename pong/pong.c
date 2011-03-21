#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/key.h"			//funcoes do teclado
#include "../include/draw.h"		//funcoes da tela
#include "../include/vars.h"		//variaveis que você configurou

#define PI 3.141592653589

/*---Barra---*/
Sprite *b_spr;

typedef struct _Barra
{
	float x, y, v;
	int score;
} Barra;

Barra player, cpu;

/*---fim Barra---*/

/*---Bola---*/
char *bola_str = NULL;

struct
{
	float x, y, v, dir;
} bola;

float v_bola;
/*---fim Bola---*/

// flag pra parar o jogo e mostrar algum texto
int mostratxt=1;

int _tela_y;

int numgols = 5;

// Funcoes extras, criadas apenas para esse jogo
void init_jogo()
{
	player.x = 0;
	player.y = ( _tela_y - 5) / 2;
	
	cpu.x = tela_x-1;
	cpu.y = ( _tela_y - 5) / 2;
	
	player.v = 1;
	cpu.v = 0.43;
	
	bola.x = tela_x/3;
	bola.y = _tela_y/2;
	bola.v = 0.9;
	bola.dir = 225;
	
	player.score = 0;
	cpu.score = 0;
}



// Essa funcao eh executada apenas uma vez, no inicio, te dando a chance
// de inicializar os valores das variaveis antes da execucao do codigo
void init()
{
	_tela_y = tela_y - 4;
	
	le_sprite_txt(&b_spr, "./sprites/barra.txt");
	
	init_jogo();
}



// Essa funcao eh executada a cada ciclo do game loop, devendo ser usada
// para calcular valores, movimentar os objetos, etc
void game()
{
	if(!mostratxt)
	{
		// Movimentacao da barra
		if( up() && (player.y > 0) )
			player.y -= player.v;
		if(down() && (player.y + 5 < _tela_y) )
			player.y += player.v;
		
		// Inteligencia Artificial ultra complexa da outra barra
		if( ( (cpu.y + 5.0/2) > bola.y ) && (cpu.y > 0) )
			cpu.y -= cpu.v;
		if( ( (cpu.y + 5.0/2) < bola.y ) && (cpu.y + 5 < _tela_y) )
			cpu.y += cpu.v;
		
		
		/*---Movimentacao da bola---*/
		
		// Atualiza a posicao
		bola.x -= bola.v * cos(bola.dir * PI / 180.0);
		bola.y += bola.v * sin(bola.dir * PI / 180.0);
		
		// Rebater nas paredes
		if( (bola.y < 0)  || (bola.y > _tela_y-1) )
		{
			bola.dir = 360 - bola.dir;
			
			if(bola.y < 0)
				bola.y = 0;
			
			if(bola.y > _tela_y)
				bola.y = _tela_y-1;
		}
		
		// Rebater no player
		if( (bola.y >= player.y) && (bola.y <= player.y + 5) && (bola.x <= 1) && (bola.x >= 0) )
		{
			bola.x = 2;
			bola.dir = 180 - bola.dir;
		}
		
		// Rebater no cpu
		if( (bola.y >= cpu.y) && (bola.y <= cpu.y + 5) && (bola.x <= tela_x ) && (bola.x >= tela_x-1) )
		{
			bola.x = tela_x - 2;
			bola.dir = 180 - bola.dir;
		}
		
		// Mantem o angulo da direcao entre 0 e 360
		while(bola.dir<0) bola.dir += 360;
		while(bola.dir>360) bola.dir -= 360;
		
		
		// Ponto pro player
		if(bola.x > tela_x)
		{
			player.score++;
			
			bola.x = tela_x*2/3;
			bola.y = _tela_y/2;
			bola.dir = 315;
		}
		
		// Ponto pro cpu
		if(bola.x < 0)
		{
			cpu.score++;
			
			bola.x = tela_x/3;
			bola.y = _tela_y/2;
			bola.dir = 225;
		}
		
		
		
		/*---fim Movimentacao da bola---*/
		
		// Termina o jogo
		if( (player.score >= numgols) || (cpu.score >= numgols) )
			mostratxt=1;
	}
	else
	{
		// (re)inicia o jogo
		if( espaco() )
		{
			init_jogo();
			mostratxt=0;
		}
	}
}



// Essa funcao eh executada a cada ciclo de desenho, devendo ser usada para 
// imprimir os objetos na tela
void draw()
{
	// Desenha o player
	sprite_draw(*b_spr, player.x, player.y);
	
	// Desenha o pc
	sprite_draw(*b_spr, cpu.x, cpu.y);
	
	// Desenha a bola
	str_draw("O", bola.x, bola.y);
	
	if(mostratxt)
	{
		str_draw("Aperte espaco para jogar!", 11, tela_y/2+1);
		
		if(player.score >= numgols)
			str_draw("Voce venceu! \\o/", 15, _tela_y/2);
		
		if(cpu.score >= numgols)
			str_draw("Voce perdeu! T.T", 15, _tela_y/2);
	}
	
	// Area dos stats
	h_line_draw('/', tela_y - 4);
	
	char aux[3];
	
	sprintf(aux, "%2d", player.score);
	str_draw(aux, 2, tela_y-2);
	
	sprintf(aux, "%2d", cpu.score);
	str_draw(aux, tela_x-5, tela_y-2);
}



// Essa funcao eh executada apenas uma vez, no final, te dando a chance
// de liberar a memoria das variaveis alocadas no jogo
void fim()
{
	free_sprite(b_spr);
}


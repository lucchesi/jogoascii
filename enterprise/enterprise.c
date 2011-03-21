#include <stdio.h>

#include "../include/key.h" 		// funcoes do teclado
#include "../include/draw.h"		// funcoes da tela
#include "../include/vars.h"		// variaveis que você configurou


/*--Nave--*/

Sprite *enterprise=NULL;
int x=10, y=10, v=1;

/*--underlines--*/

Sprite *stars=NULL;
float stars_x=0;

/*--pontos--*/

Sprite *dots=NULL;
float dots_x=2;


// Essa funcao eh executada apenas uma vez, no inicio, te dando a chance
// de inicializar os valores das variaveis antes da execucao do codigo
void init()
{
	le_sprite_txt(&enterprise, "sprites/enterprise.txt");

	le_sprite_txt(&stars, "./sprites/stars.txt");
	
	le_sprite_txt(&dots, "./sprites/dots.txt");
}



// Essa funcao eh executada a cada ciclo do game loop, devendo ser usada
// para calcular valores, movimentar os objetos, etc
void game()
{
	// Controle da nave
	if( up() && (y>0) )
		y-=v;
	if( down() && (y+3<tela_y) )
		y+=v;
	if( left() && (x>0) )
		x-=v;
	if( right() && (x+11<tela_x) )
		x+=v;
	
	stars_x -= 0.7;
	dots_x -= 0.4;
}



// Essa funcao eh executada a cada ciclo de desenho, devendo ser usada para 
// imprimir os objetos na tela
void draw()
{
	sprite_draw(*dots, dots_x, -1);
	
	sprite_draw(*stars, stars_x, 0);
	
	sprite_draw(*enterprise, x, y);
}



// Essa funcao eh executada apenas uma vez, no final, te dando a chance
// de liberar a memoria das variaveis alocadas no jogo
void fim()
{
	free_sprite(enterprise);
	free_sprite(stars);
	free_sprite(dots);
}


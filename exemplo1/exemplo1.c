#include <stdio.h>

#include "../include/key.h" 		// funcoes do teclado
#include "../include/draw.h"		// funcoes da tela
#include "../include/vars.h"		// variaveis que voce configurou


// Objeto de teste
struct
{
	// posicao do objeto
	float x, y;
	
	// velocidade dele(vou colocar x e y)
	float v;
	
	// animacoes dele(parado, andando, etc)
	struct _Anima *anim;
} obj;



// Sprite de testes
Sprite palito;
Sprite *palito2; //lido do txt

// Matriz de caracteres com o "sprite" em ascii
char spr_palito[3][4]={
	" O ",
	"/|\\",
	"/ \\"
};

// Elementos da lista ligada de linhas
// (declarado como vetor, pra nao me preocupar com alocacao dinamica por enquanto)
Linha lin[3];

// String de teste para leitura de txt
char teste[15];



// Essa funcao eh executada apenas uma vez, no inicio, te dando a chance
// de inicializar os valores das variaveis antes da execucao do codigo
void init()
{
	//----codigo do objeto----//
	
	// Posiciona o objeto no meio da tela, e define a velocidade
	obj.x=5; //tela_x/2;
	obj.y=5; //tela_y/2;
	obj.v=1;
	
	// Apontando os elementos da lista ligada pras strings da matriz
	int i=0;
	for(i=0; i<3; i++) lin[i].str = spr_palito[i];
	
	// Arrumando os ponteiros da lista ligada
	lin[0].prox = &lin[1];
	lin[1].prox = &lin[2];
	lin[2].prox = NULL;
	
	// Apontando o ponteiro do sprite pro inicio da lista
	palito.img = &lin[0];
	
	//----fim do codigo do objeto----//
	
	
	// Le o sprite do txt
	le_sprite_txt(&palito2, "sprites/enterprise_big.txt"); //"sprites/palito.txt");
	
	// Le a string do txt
	//le_string_txt(teste, "sprites/rofl.txt");
}



//Essa funcao eh executada a cada ciclo do game loop, devendo ser usada
//para calcular valores, movimentar os objetos, etc
void game()
{
	//controle
	if(up())
		obj.y-=obj.v;
	if(down())
		obj.y+=obj.v;
	if(left())
		obj.x-=obj.v;
	if(right())
		obj.x+=obj.v;
	
	//limites
	if(obj.x<0)
		obj.x+=tela_x;
	if(obj.x>tela_x)
		obj.x-=tela_x;
	if(obj.y<0)
		obj.y+=tela_y;
	if(obj.y>tela_y)
		obj.y-=tela_y;
}



// Essa funcao eh executada a cada ciclo de desenho, devendo ser usada para 
// imprimir os objetos na tela
void draw()
{
	// Desenha o palito na posicao x e y do objeto
	sprite_draw(palito, obj.x, obj.y);
	
	// Desenha o sprite do txt na posicao x+10 e y
	sprite_draw(*palito2, obj.x+10, obj.y-2);
	
	// Escreve a string do txt
	//str_draw(teste, 10, 10);
	
	
	
	if(debug)
	{
		//----textos com as posicoes x e y do objeto----//
		char str_pos[15];
		
		// Escreve na string str_pos o texto com a posicao x a ser escrita na tela
		sprintf(str_pos, "X:%.2f", obj.x);
		
		// Escreve na tela a string da posicao x
		str_draw(str_pos, 2, tela_y-3);
		
		// Escreve na string str_pos o texto com a posicao y a ser escrita na tela
		sprintf(str_pos, "Y:%.2f", obj.y);
		
		// Escreve na tela a string da posicao y
		str_draw(str_pos, 2, tela_y-2);
	}
}



// Essa funcao eh executada apenas uma vez, no final, te dando a chance
// de liberar a memoria das variaveis alocadas no jogo
void fim()
{
	// Libera o sprite lido do txt
	free_sprite(palito2);
}


#include "../include/vars.h"

// Funcoes do jogo
extern void init(), game(), draw(), fim();

// main da engine
extern void e_main( void (*_init)(), void (*_game)(), void (*_draw)(), void(*_fim)());

// main do jogo
int main(void)
{
	// Define os valores das variaveis
	#include "vars.h"
	
	// Chama a "main" da engine, fornecendo o endereco para as funcoes do jogo
	e_main(&init, &game, &draw, &fim);
	
	return 0;
}


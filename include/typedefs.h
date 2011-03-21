#ifndef TYPEDEFS
#define TYPEDEFS

//--struct com cada linha da imagem--//
typedef struct _Linha
{
	// String da linha da imagem
	char *str;
	
	// Ponteiro pra proxima linha da lista ligada
	struct _Linha *prox;
} Linha;

//--Sprite--//
typedef struct _Sprite
{	
	// "imagem" do sprite(ponteiro pra primeira linha da lista)
	Linha *img;
	
	// Ponteiro pro proximo sprite da lista ligada
	struct _sprite *prox;
} Sprite;

//--Animacao--//
typedef struct _Anima
{
	// Numero do sprite mostrado
	unsigned short int n;
	
	// Ponteiro pro primeiro sprite da lista
	Sprite *spr;
	
	// Ponteiro pra proxima animacao
	struct _Anima *prox;
} Anima;

#endif

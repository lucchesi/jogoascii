#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vars.h"
#include "../include/typedefs.h"


// funcao de limpar a tela do terminal
extern void cls();

// Tela
char **t, *tela;



/*---Zerar matriz da tela---*/
void zerar()
{
	register short int i=0, j=0;
	for(i=0; i<tela_x; i++)
	{
		for(j=0; j<tela_y; j++)
		{
			t[i][j]=fundo;
		}
	}
}



/*---Alocar tela---*/
void aloc_tela(int x, int y)
{
	x++;
	y++;
	
	// Aloca os ponteiros de colunas
	t = ( char** ) malloc( sizeof( char* ) * x );
	
	int i=0;
	for(i=0; i<x; i++)
	{
		// Aloca as colunas
		t[i] = ( char* ) malloc( sizeof( char ) * y );
	}
	
	// Aloca a string que sera impressa na tela
	// (realizar a saida em bloco, em um so printf, eh mais eficiente)
	tela = ( char* ) malloc( sizeof( char) * ( ( x + 2 )*( y + 2 ) + 1 ) );
}



/*---Desalocar tela---*/
void desaloc_tela(int x, int y)
{
	// Libera a string que era impressa na tela
	free(tela);
	
	int i=0;
	for(i=0; i<x; i++)
	{
		// Desaloca as colunas
		free(t[i]);
	}
	
	// Desaloca os ponteiros de colunas
	free(t);
}



/*---Desenhar sprite---*/
void sprite_draw(Sprite spr, int x, int y)
{
	short int i=0, j=0, tx=0, ty=0;
	
	// Ponteiro pra linha usada
	Linha *tmp;
	
	// Aponta o ponteiro pra primeira linha da lista
	tmp=spr.img;
	
	while(tmp!=NULL) // Pra cada linha(y)
	{
		for(j=0; j<strlen(tmp->str); j++) // Pra cada coluna(x)
		{
			// Limites pro x
			tx=x+j;
			while(tx<=0)      tx+=tela_x;
			while(tx>=tela_x) tx-=tela_x;
			
			// Limites pro y
			ty=y+i;
			while(ty<=0)      ty+=tela_y;
			while(ty>=tela_y) ty-=tela_y;
			
			// Copia o char da vez pra matriz da tela, se nao for vazio ou quebra de linha
			if( (tmp->str[j] != ' ') && (tmp->str[j] != '\n') && (tmp->str[j] != '\r') )
			{
				t[tx][ty] = tmp->str[j];
			}
		}
		
		// Vai pra proxima linha
		tmp=tmp->prox;
		
		// Incrementa o contador de linhas
		i++;
	}
}



/*---Desenhar string---*/
void str_draw(char *str, int x, int y)
{
	short int i=0, tx;
	for(i=0; i<strlen(str); i++) // Pra cada char
	{
		// Limites
		tx=x+i;
		while(tx<=0)      tx+=tela_x;
		while(tx>=tela_x) tx-=tela_x;
		
		// Copia o char da vez pra matriz da tela, se nao for vazio ou quebra de linha
		if( (str[i]!=' ') && (str[i]!='\n') && (str[i]!='\r') )
		{
			t[tx][y]=str[i];
		}
	}
}



/*---Desenhar string verticalmente---*/
void str_draw_v(char *str, int x, int y)
{
	short int i=0, ty;
	for(i=0; i<strlen(str); i++) //pra cada char
	{
		// Limites
		ty=y+i;
		while(ty<=0)      ty+=tela_y;
		while(ty>=tela_y) ty-=tela_y;
		
		// Copia o char da vez pra matriz da tela, se nao for vazio ou quebra de linha
		if( (str[i]!=' ') && (str[i]!='\n') && (str[i]!='\r') )
		{
			t[x][ty]=str[i];
		}
	}
}



/*---Desenhar uma linha horizontal de um mesmo char---*/
void h_line_draw(char c, int y)
{
	int i;
	for(i=0; i<tela_x; i++)
		t[i][y] = c;
}



/*---escrever a tela---*/
void escrever_tela()
{
	register short int i=0, j=0;
	char tmp[2]="";
	
	// Limpar tela
	cls();
	
	// Limpa a string unica a ser impressa
	strcpy(tela, "");
	
	// Linha inicial
	if(margem_topo!='\0')
	{
		tmp[0]=margem_topo;
		for(j=0; j<tela_x+2; j++)
			strcat(tela, tmp);
		
		strcat(tela, "\n");
	}
	
	// Pra cada linha (posY)
	for (i=1; i<tela_y+1; i++)
	{
		// Pra cada coluna (posX)
		for(j=0; j<tela_x+2; j++)
		{
			if(j==0) tmp[0]=margem_esq;
			if(j==tela_x+1) tmp[0]=margem_dir;
			
			if( (j>0) && (j<tela_x+1) && (i>0) && (i<tela_y+1) )
			{
				// Pega o char e joga na matriz
				tmp[0]=t[j-1][i-1];
			}
			
			strcat(tela, tmp);
		}
		strcat(tela, "\n");
	}
	
	// Linha final
	if(margem_baixo!='\0')
	{
		tmp[0]=margem_baixo;
		for(j=0; j<tela_x+2; j++)
			strcat(tela, tmp);
	}
	
	// Pular uma linha no final
	strcat(tela, "\n");
	
	
	// Saida pra tela
	printf("%s", tela);
}



/*---Le uma string de um txt---*/
void le_string_txt(char *spr, char *cam_arq)
{
	FILE *arq;
	arq = fopen(cam_arq, "r");
	
	fscanf(arq, "%s", spr);
	
	fclose(arq);
}



/*---Le um sprite de um txt---*/
//(obs: limite de 100 chars por linha, alteravel)
void le_sprite_txt(Sprite **spr, char *cam_arq)
{
	Linha **lin;
	FILE *arq;
	char tmpstr[100];
	int i;
	
	// Abre o arquivo
	arq = fopen(cam_arq, "r");
	
	if(arq!=NULL)
	{
		// Testa se o sprite ta vazio
		if( ( (*spr)!=NULL ) && debug ) // So da chilique se esta em modo debug
		{
			printf("O SPRITE NAO TA VAZIO!!!\n");
			exit(1);
		}
		
		// Aloca o sprite e sua primeira linha
		*spr = (Sprite*) malloc( sizeof(Sprite) );
		(*spr)->img = (Linha*) malloc( sizeof(Linha) );
		
		// Ponteiro pra ela
		lin = &( (*spr)->img );
		
		// Enquanto nao acabou o arquivo
		while( !feof(arq) )
		{
			// Le a linha pra string temporaria
			fgets(tmpstr, 100, arq);
			
			i = strlen(tmpstr);
			
			// Aloca a linha
			*lin = (Linha*) malloc( sizeof(Linha) );
			
			// Aloca a string
			(*lin)->str = (char*) malloc( i*sizeof(char) );
			
			strcpy( (*lin)->str, tmpstr );
			
			if( (*lin)->str[i-1] == '\n') (*lin)->str[i-1] = '\0';
			
			// Vai pra proxima
			lin = &( (*lin)->prox );
			*lin = NULL;
		}
		
		fclose(arq);
	}
	else
	{
		printf("arquivo \"%s\" nao encontrado\n", cam_arq);
		exit(1);
	}
}



/*---Libera a memoria de um sprite---*/
void free_sprite(Sprite *spr)
{
	Linha *tmp1, *tmp2;
	tmp1 = spr->img;
	while(tmp1!=NULL)
	{
		tmp2 = tmp1->prox;
		free(tmp1);
		tmp1 = tmp2;
	}
	
	free(spr);
}


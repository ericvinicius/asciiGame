#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

typedef struct Objeto{
	char name;
	int x;
	int y;
}objeto;

typedef struct Jogador{
	char name;
	int life;
	int posx;
	int posy;
}player;

typedef struct Inimigo{
	char name;
	int dificuldade;
	int x;
	int y;

}ini;

typedef struct Mapa{
	char **valor;
	char parede;
	int x;
	int y;
}mapa;

typedef struct Jogo{
	player pl;
	mapa campo;
	ini bot;
	objeto obj;
	int pontos;
	int fase;
}game;
/* ---------------------------------------------------

 -> MANTENHA SEMPRE ATUALIZADO <-

*/

game limpaMatriz(game jogo);

game verificaFase(game jogo);

game verificaPonto(game jogo);

game andaDireita(game jogo,char espaco);

game andaEsquerda(game jogo,char espaco);

game andaBaixo(game jogo,char espaco);

game andaCima(game jogo,char espaco);

game lerAcao(game jogo, int tecla);

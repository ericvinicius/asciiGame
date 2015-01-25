#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

typedef struct Objeto{
	char name;
	char nome;
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
	mapa campo;
	player pl;
	ini bot;
	objeto obj;
	int pontos;
	int fase;
	char espaco;
}game;
/* ---------------------------------------------------

 -> MANTENHA SEMPRE ATUALIZADO <-

*/

game limpaMatriz(game jogo);

game verificaFase(game jogo);

game verificaPonto(game jogo);

game andaDireita(game jogo);

game andaEsquerda(game jogo);

game andaBaixo(game jogo);

game andaCima(game jogo);

game lerAcao(game jogo, int tecla);

void printSplash();

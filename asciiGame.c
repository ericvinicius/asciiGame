#include "asciiGame.h"
#include "padroes.c"
#include "fase.c"


//Aloca espaco necessario para a matriz e coloca um espaco em cada local
game limpaMatriz(game jogo){
	int x, y;

	//Alocar memoria para uma matriz
	jogo.campo.valor = mallocc(jogo.campo.x * sizeof(char *));
	for(x = 0; x <= jogo.campo.x; x++){
		jogo.campo.valor[x] = mallocc(jogo.campo.y * sizeof(char));
		// TO - DO : E possivel reduzir o outros dois fors, por um unico aqui!!!
	}

	for(x = 0; x < jogo.campo.x; x++){
		for(y = 0; y < jogo.campo.y; y++){
				jogo.campo.valor[x][y] = ' ';
		}
	}
	return jogo;
}

game verificaFase(game jogo){
	if(jogo.fase == 1)
		jogo = insereObjeto(jogo);

	if(jogo.fase == 2)
		jogo = insereObjeto(jogo);


	return jogo;
}

//Verifica se o jogador esta em cima do objeto
game verificaPonto(game jogo){
	if(jogo.pl.posx == jogo.obj.x && jogo.pl.posy == jogo.obj.y){
		jogo.pontos++;

		jogo = verificaFase(jogo);
	}
	return jogo;
}

//O poersonagem anda para direita(verificando se nao e uma parece e se ele marcou um ponto)
game andaDireita(game jogo){
	if(jogo.campo.valor[jogo.pl.posx][jogo.pl.posy+1] != jogo.campo.parede){
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = ' ';
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy+1] = jogo.pl.name;
		jogo.pl.posy++;
		jogo = verificaPonto(jogo);
	}
	return jogo;
}

//O poersonagem anda para esquerda(verificando se nao e uma parece e se ele marcou um ponto)
game andaEsquerda(game jogo){
	if(jogo.campo.valor[jogo.pl.posx][jogo.pl.posy-1] != jogo.campo.parede){
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = ' ';
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy-1] = jogo.pl.name;
		jogo.pl.posy--;
		jogo = verificaPonto(jogo);
	}
	return jogo;
}

//O poersonagem anda para baixo(verificando se nao e uma parece e se ele marcou um ponto)
game andaBaixo(game jogo){
	if(jogo.campo.valor[jogo.pl.posx+1][jogo.pl.posy] != jogo.campo.parede){
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = ' ';
		jogo.campo.valor[jogo.pl.posx+1][jogo.pl.posy] = jogo.pl.name;
		jogo.pl.posx++;
		jogo = verificaPonto(jogo);
	}
	return jogo;
}

//O poersonagem anda para cima(verificando se nao e uma parece e se ele marcou um ponto)
game andaCima(game jogo){
	if(jogo.campo.valor[jogo.pl.posx-1][jogo.pl.posy] != jogo.campo.parede){
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = ' ';
		jogo.campo.valor[jogo.pl.posx-1][jogo.pl.posy] = jogo.pl.name;
		jogo.pl.posx--;
		jogo = verificaPonto(jogo);
	}
	return jogo;
}

//Le acao do usuario chama a funcao que faz ele andar
game lerAcao(game jogo, int tecla){

	//printw("(%d / %d)", jogo.pl.posx, jogo.pl.posy);

	if(tecla == KEY_RIGHT){
		jogo = andaDireita(jogo);

	} else if(tecla == KEY_LEFT){
		jogo = andaEsquerda(jogo);

	} else if(tecla == KEY_DOWN){
		jogo = andaBaixo(jogo);

	} else if(tecla == KEY_UP){
		jogo = andaCima(jogo);
	}

	//TO - DO : nem sempre mostra a batida
	if(jogo.pl.posx == jogo.bot.x && jogo.pl.posy == jogo.bot.y )
		jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = '@';

	return jogo;
}	

int main(){
	mapa campo;
	campo.parede = 'X';
	int ch;
	int cont = 0;
	
	objeto obj;	
	obj.name = '#';

	player one;
	one.posx = 1;
	one.posy = 1;
	one.life = 3;
	one.name = 'o'; 

	ini bot;
	bot.x = 10;
	bot.y = 15;
	bot.name = '*';
	bot.dificuldade = 0;

	game jogo;
	jogo.campo = campo;
	jogo.pl = one;
	jogo.pontos = 0;
	jogo.obj = obj;
	jogo.bot = bot;

	initscr();					/* Start curses mode 		*/
	raw();						/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();					/* Don't echo() while we do getch */
	initCores();
	
	jogo = iniciaFase1(jogo);

	while ((ch = getch()) != 'c') {
		
		jogo = update(jogo, ch);

		if(jogo.pontos == 1 && cont == 0){	
			printw("Ganhou! - Vamos para fase 2!\n");
			cont++;
			refresh();
			jogo = iniciaFase2(jogo);
		}
 
	}

	
	endwin();			/* End curses mode */

	return 0;
}
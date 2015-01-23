//insere um jogador na sua posicao inicial
mapa insereJogadorF1(game jogo){
	jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = jogo.pl.name;

	return jogo.campo;
}

//Desenha o campo com o personagem e as paredes
void desenhaCampoF1(mapa campo){
	int x, y;

	for(x = 0; x < campo.x; x++){
		for(y = 0; y < campo.y; y++){	

			attron(COLOR_PAIR(2));
			if(campo.valor[x][y] == 'X'){
				attron(COLOR_PAIR(4));
				if(x != 0)
					printw("%c ", campo.valor[x][y]);
				else
					printw("%c-", campo.valor[x][y]);
				attroff(COLOR_PAIR(4));
			}else
				printw("%c ", campo.valor[x][y]);
			
			if(x == 0 || y == (campo.y-1) || x == (campo.x-1) || y == 0) //PAREDES
				campo.valor[x][y] = 'X';
		}
		printw("\n");
	}

}

//insere o objeto dentro do mapa em uma posicao aleatoria
game insereObjetoF1(game jogo){
	int x, y;

	do{
		srand (time(NULL));
		x = rand() % (jogo.campo.x-2) + 1;
		y = rand() % (jogo.campo.y-2) + 1;
	} while (jogo.pl.posx == x && jogo.pl.posy == y);
	
	jogo.obj.x = x;
	jogo.obj.y = y;

	jogo.campo.valor[x][y] = jogo.obj.name;
	return jogo;
}

game iniciaFase1(game jogo){
	jogo.campo.x = 20;
	jogo.campo.y = 30;
	jogo.fase = 1;
	jogo.pl.posx = 1;
	jogo.pl.posy = 1;

	clear();

	jogo.campo = limpaMatriz(jogo.campo);
	jogo = insereObjetoF1(jogo);
	desenhaCampoF1(jogo.campo);

	return jogo;
}

game updateF1(game jogo, int ch){
	int botDifuldade = 0;
	
	clear();
	attron(COLOR_PAIR(1));
	printw("\t\t\tPontuacao = %d\n", jogo.pontos);
	attroff(COLOR_PAIR(1));
	desenhaLife(jogo.pl.life);

	jogo.campo = insereJogadorF1(jogo);
	

	if(botDifuldade < 70){
		jogo = moverIni(jogo);
		//botDifuldade = 0;
	}
	jogo = lerAcao(jogo, ch);

	desenhaCampoF1(jogo.campo);

	botDifuldade = rand() % 100;

	if(verificaColisao(jogo)){
		jogo.pl.life--;
		botDifuldade = 100;
		if(jogo.pl.life == -1){
			endwin();
			exit(EXIT_FAILURE);

		}
	}
	
	refresh();

	return jogo;
}
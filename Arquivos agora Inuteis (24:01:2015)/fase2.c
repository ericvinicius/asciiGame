//insere um jogador na sua posicao inicial
mapa insereJogadorF2(game jogo){
	jogo.campo.valor[jogo.pl.posx][jogo.pl.posy] = jogo.pl.name;

	return jogo.campo;
}

//Desenha um campo triangular
void desenhaCampoF2(mapa campo){
	int x, y;

	for(x = 0; x < campo.x; x++){
		for(y = 0; y < campo.y; y++){

			attron(COLOR_PAIR(2));
			printw("%c ", campo.valor[x][y]);
			attron(COLOR_PAIR(2));

			if(y == (campo.y / 2) - x || x == (campo.x-1) || y == (campo.y / 2) + x) //PAREDES
				campo.valor[x][y] = 'X';
		}
		printw("\n");
	}
}

//TO - DO ----------------------------
game insereObjetoF2(game jogo){
	int x, y;

	do{
		srand (time(NULL));
		x = rand() % (jogo.campo.x-2) + 1;
		y = rand() % (jogo.campo.y-2) + 1;
	} while (jogo.pl.posx == x && jogo.pl.posy == y );
	
	jogo.obj.x = x;
	jogo.obj.y = y;

	jogo.obj.name = 'o';

	jogo.campo.valor[x][y] = jogo.obj.name;
	return jogo;
}

game iniciaFase2(game jogo){
	jogo.campo.x = 21;
	jogo.campo.y = 40;
	jogo.fase = 2;
	jogo.pl.posx = 10;
	jogo.pl.posy = 20;

	clear();

	jogo.campo = limpaMatriz(jogo.campo);
	jogo = insereObjetoF2(jogo);
	desenhaCampoF2(jogo.campo);

	return jogo;
}

game updateF2(game jogo, int ch){
	int botDifuldade = 0;
	int vidas = 3;
	clear();

	printw("Pontuacao = %d\n", jogo.pontos);
	desenhaLife(vidas);

	jogo.campo = insereJogadorF2(jogo);
	jogo = lerAcao(jogo, ch);

	if(botDifuldade < 70){
		jogo = moverIni(jogo);
		//botDifuldade = 0;
	}

	desenhaCampoF2(jogo.campo);
	
	botDifuldade = rand() % 100;

	if(verificaColisao(jogo) == 1){
		vidas--;
		botDifuldade = 100;
		if(vidas == 0){
			exit(EXIT_FAILURE);
		}
	}

	refresh();

	return jogo;
}
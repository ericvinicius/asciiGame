void* mallocc(size_t size){
	void *espacoDeMemoria;
	espacoDeMemoria = malloc(size);

	if(espacoDeMemoria == NULL){
		printf("Erro Malloc\n");
		exit(EXIT_FAILURE);
	}

	return espacoDeMemoria;
}

void initCores(){
	start_color(); //Esta função torna possível o uso das cores
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Texto(Branco) | Fundo(Azul)
	init_pair(2,COLOR_WHITE,COLOR_GREEN);  //Texto(Vermelho) | Fundo(Branco)
	init_pair(3,COLOR_RED,COLOR_BLACK);
	init_pair(4,COLOR_RED,COLOR_GREEN);
	bkgd(COLOR_PAIR(1));
}

void desenhaLife(int vidas){
	int vez = vidas;
	attron(COLOR_PAIR(1));
	printw("\t\t\tLIFE: ");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(3));

	while(vez != 0){
		printw("<> ");
		vez--;
	}
	
	attroff(COLOR_PAIR(3));
	printw("\n\n");
}

game moverIni(game jogo){
	int posx,posy,inix,iniy;
	posx = jogo.pl.posx;
	posy = jogo.pl.posy;
	inix = jogo.bot.x;
	iniy = jogo.bot.y;


	int andou = rand() % 100;
	
	if(inix > posx && andou < 30 && jogo.campo.valor[inix-1][iniy] != 'X') {
		jogo.campo.valor[inix][iniy] = ' ';
		jogo.campo.valor[inix-1][iniy] = '-';
		jogo.bot.x--;
		return jogo;
	}
	if(inix < posx && andou < 30 && jogo.campo.valor[inix+1][iniy] != 'X'){
		jogo.campo.valor[inix][iniy] = ' ';
		jogo.campo.valor[inix+1][iniy] = '-';
		jogo.bot.x++;
		return jogo;
	} 
	
	if(iniy > posy && jogo.campo.valor[inix][iniy-1] != 'X'){
		jogo.campo.valor[inix][iniy] = ' ';
		jogo.campo.valor[inix][iniy-1] = '-';
		jogo.bot.y--;
		return jogo;
	}else{
		jogo.campo.valor[inix][iniy] = ' ';
		jogo.campo.valor[inix][iniy+1] = '-';
		jogo.bot.y++;
		return jogo;
	}
	
	return jogo;
}

//ERIC D. <
int verificaColisao(game jogo){
	if(jogo.pl.posx == jogo.bot.x && jogo.pl.posy == jogo.bot.y){
		return 1;
	}
	return 0;
} //ERIC D. >
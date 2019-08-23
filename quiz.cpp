//Programinha para o Quiz
//Verde Amarelo Roxo Azul Laranja Vermelho
//g++ quiz.cpp -lSDL2 -g -o quiz


#include <SDL2/SDL.h>
#include <cstdio>

#define LARG 1024
#define ALTU 600

#define KEY_Q 1 //quit
#define KEY_F 2 //full
#define KEY_T 3 //test
#define KEY_N 4	//quest

#define TELA_QUIZ 1
#define TELA_TURM 2
#define TELA_TEST 3
#define TELA_ERRO 4

bool keyq=false;
bool keyf=false;
bool keyt=false;
bool keyn=false;

const Uint8 *m_keymap = SDL_GetKeyboardState(NULL);

int getkey(){
	SDL_PumpEvents();

	if (m_keymap[SDL_SCANCODE_Q] && !keyq){
		keyq=true;
		return KEY_Q;
	};
	if (m_keymap[SDL_SCANCODE_F] && !keyf){
		keyf=true;
		return KEY_F;
	};
	if (m_keymap[SDL_SCANCODE_T] && !keyt){
		keyt=true;
		return KEY_T;
	};
	if (m_keymap[SDL_SCANCODE_N] && !keyn){
		keyn=true;
		return KEY_N;
	};

	if(!m_keymap[SDL_SCANCODE_Q]) keyq=false;
	if(!m_keymap[SDL_SCANCODE_F]) keyf=false;
	if(!m_keymap[SDL_SCANCODE_T]) keyt=false;
	if(!m_keymap[SDL_SCANCODE_N]) keyn=false;
	
	return 0;
}

int main(){
	int i;
	SDL_Window 		*window = NULL;
	SDL_Renderer 	*renderer = NULL;
	SDL_Texture		*texture = NULL;

	SDL_Surface		*tqui = NULL, *tqui2 = NULL, *terr = NULL, *ttes = NULL;
	SDL_Surface		*ttur[6];
	SDL_Surface		*bot = NULL, *abot = NULL;
	SDL_Surface		*t3 = NULL, *t2 = NULL, *t1 = NULL;

	SDL_Rect rbuf;

	atexit(SDL_Quit);
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return -1;
	}

	char c;
	FILE* arduino;
	arduino = fopen("/dev/ttyACM0","r");
	//arduino = fopen("/dev/null","r");
	if(!arduino){
		arduino = fopen("/dev/ttyACM1","r");
		if(!arduino){
			printf("Arquivo não encontrado\n");
			return -1;
		}
	}

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARG, ALTU, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1366, 768);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);

	SDL_ShowCursor(SDL_DISABLE);
	

	tqui=SDL_LoadBMP("qui.bmp");
	tqui2=SDL_LoadBMP("qui2.bmp");
	ttes=SDL_LoadBMP("tes.bmp");
	terr=SDL_LoadBMP("err.bmp");
	t3=SDL_LoadBMP("t3.bmp");
	t2=SDL_LoadBMP("t2.bmp");
	t1=SDL_LoadBMP("t1.bmp");

	bot=SDL_LoadBMP("bot.bmp");
	abot=SDL_LoadBMP("abot.bmp");
	
	char tur[] = "tur1.bmp";
	for(i=0;i<6;i++){
		ttur[i]=SDL_LoadBMP(tur);
		tur[3]++;
	}

	SDL_Event event;
	bool runing = true;

	bool redraw = true;
	SDL_Surface *buffer = 	SDL_CreateRGBSurface(0, 1366, 768, 32,
		0x00FF0000,
		0x0000FF00,
		0x000000FF,
		0xFF000000);

	SDL_BlitSurface(tqui, NULL, buffer, NULL);

	int key;
	int screen = TELA_QUIZ;
	bool full = false;
	bool allow = false;

	bool timerstart = false;
	unsigned int time;
	unsigned int start;
	int timesec;
	while(runing){
		key = getkey(); //Lê teclado
		c = '0'; //Receta variável c
		c = fgetc(arduino); //Lê Arduino
		
		if (key==KEY_Q) runing=false;
		
		if (key==KEY_F){
			redraw = true;
			if(!full){
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				full = true;
			} else{
				SDL_SetWindowFullscreen(window, 0);
				full = false;
			}
		}


		if(screen == TELA_QUIZ){
			//printf("%c\n",c);
			if(!allow){
				if(c >= 'a' && c <= 'f'){ //Se alguem apertar dá erro
					printf("Erro-10%i.\n",(int)(c-'a')+1);
					screen = TELA_ERRO;
					SDL_BlitSurface(terr, NULL, buffer, NULL);
					redraw = true;
				}
				if(key==KEY_N && !timerstart){ //Se apertar N inicia o tempo
					timerstart = true;
					time = 0;
					timesec = 0;
					start = SDL_GetTicks();
					SDL_BlitSurface(t3, NULL, buffer, NULL);
					redraw = true;
				}
				if(timerstart) time = SDL_GetTicks() - start; //Se iniciou o tempo, atualiza ele
			
				if(time>500 && timesec==0){
					timesec = 1;
					SDL_BlitSurface(t2, NULL, buffer, NULL);
					redraw = true;
				}
				if(time>1000 && timesec==1){
					timesec = 2;
					SDL_BlitSurface(t1, NULL, buffer, NULL);
					redraw = true;
				}
				if(time>1500){
					SDL_BlitSurface(tqui2, NULL, buffer, NULL);
					redraw = true;
					allow = true;
					timerstart = false;
					time = 0;
				}
			} else{
				if(c >= 'a' && c <= 'f'){
					screen = TELA_TURM;
					SDL_BlitSurface(ttur[(int)(c-'a')], NULL, buffer, NULL);
					redraw = true;
				}
			}
		}



		if(screen == TELA_TEST){
			if(key==KEY_T){
				allow = false;
				timerstart = false;
				screen = TELA_QUIZ;
				SDL_BlitSurface(tqui, NULL, buffer, NULL);
				redraw = true;
			}

			if(c >= 'a' && c <= 'f'){
				rbuf.x = 230+160*((int)(c-'a'));
				rbuf.y = 330;
				rbuf.h = 100;
				rbuf.w = 100;
				SDL_BlitSurface(bot,  NULL, buffer, &rbuf);
				redraw = true;
			}
			if(c >= 'A' && c <= 'F'){
				rbuf.x = 230+160*((int)(c-'A'));
				rbuf.y = 330;
				rbuf.h = 100;
				rbuf.w = 100;
				SDL_BlitSurface(abot,  NULL, buffer, &rbuf);
				redraw = true;

			}
		} else if(key==KEY_T){
			screen = TELA_TEST;
			SDL_BlitSurface(ttes, NULL, buffer, NULL);
			redraw = true;
		}




		if(screen == TELA_ERRO){ //
			if(key==KEY_N){
				allow = false;
				timerstart = false;
				screen = TELA_QUIZ;
				SDL_BlitSurface(tqui, NULL, buffer, NULL);
				redraw = true;
			}			
		}

		if(screen == TELA_TURM){ //
			if(key==KEY_N){
				allow = false;
				timerstart = false;
				screen = TELA_QUIZ;
				SDL_BlitSurface(tqui, NULL, buffer, NULL);
				redraw = true;
			}
		}

		

		if (redraw){
			SDL_UpdateTexture(texture, NULL, buffer->pixels, buffer->pitch);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
			redraw = false;
			//printf("Redrawn\n");
		}

		while(SDL_PollEvent(&event)) if(event.type == SDL_QUIT) runing = false;
	}

	return 0;
}

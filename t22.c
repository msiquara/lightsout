/*
 * t22.c
 * 
 * Copyright 29-06-2016 @author: msiquara <msiquara@ufrj.br>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

SDL_Window *window;
SDL_Renderer *render;
SDL_Surface *tempimage;
SDL_Event event;
SDL_Texture *fundo, *fundobmp1, *fundobmp2;
SDL_Rect src, trgt, trgt2, temptrgt;

int main (int argc, char** argv){
	
	srand(time(NULL));
	
	INICIALIZAR();
	
	IMAGEM();
	
	RENDERIZAR();

	EVENTS();

	return 0;
}

//
//FUNCTIONS  
//

void INICIALIZAR(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Lights Out", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL){
		printf("Could not create window: %s\n",SDL_GetError());
		return 1;
	}
	render = SDL_CreateRenderer(window, -1, 0);
}

void IMAGEM(){
	//
	// MATRIZ 3 x 3
	//

	int matriz[3][3];

	for (int i = 0; i<3; i++){
		for (int j = 0; j<3; j++){
			matriz[i][j]=rand() % 2;
		}
	}

	src.w=SCREEN_WIDTH/3;
	src.h=SCREEN_HEIGHT/3;
	src.x=0;
	src.y=0;

	tempimage = SDL_LoadBMP("off.bmp");
	fundobmp1 = SDL_CreateTextureFromSurface(render,tempimage);
	SDL_FreeSurface(tempimage);

	trgt.w=SCREEN_WIDTH/3;
	trgt.h=SCREEN_HEIGHT/3;
	trgt.x=0;
	trgt.y=0;

	tempimage = SDL_LoadBMP("on.bmp");
	fundobmp2 = SDL_CreateTextureFromSurface(render,tempimage);
	SDL_FreeSurface(tempimage);

	trgt2.w=SCREEN_WIDTH/3;
	trgt2.h=SCREEN_HEIGHT/3;

	trgt2.x=0;
	trgt2.y=SCREEN_HEIGHT-(2*SCREEN_HEIGHT/3)+2;
}

void RENDERIZAR(){
	for (int i=0; i<3; ++i){
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderClear(render);
		SDL_RenderCopy(render, fundobmp1, &src, &trgt);
		SDL_RenderCopy(render, fundobmp2, &src, &trgt2);
		SDL_RenderPresent(render);
	}
}
   
void EVENTS(){
	int quit=0;
	while(!quit){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					quit=1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym){
						case SDLK_ESCAPE:
						case SDLK_q:
							quit=1;
							break;		
					}		
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (((event.button.x > 160 && event.button.x < 482) & (event.button.y >= 100 && event.button.y <= 500)) | ((event.button.x > 693 && event.button.x < 1015) && (event.button.y > 100 && event.button.y < 500))){
							temptrgt.x=0;
							temptrgt.x=trgt2.x;
							trgt2.x=trgt.x;
							trgt.x=temptrgt.x;
							for (int i=0; i<3; ++i){
								SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
								SDL_RenderClear(render);
								SDL_RenderCopy(render, fundobmp1, &src, &trgt);
								SDL_RenderCopy(render, fundobmp2, &src, &trgt2);
								SDL_RenderPresent(render);
							}	
						}
					}
			}
		}
	}
	SDL_DestroyTexture(fundobmp1);
	SDL_DestroyTexture(fundobmp2);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


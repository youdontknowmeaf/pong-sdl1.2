#include <stdio.h>
#include <SDL2/SDL.h>
#include "config.h"
#include <ogcsys.h>
#include <wiiuse/wpad.h>

int CheckCollisionRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if (x1 + w1 <= x2 || x1 >= x2 + w2 || y1 + h1 <= y2 || y1 >= y2 + h2) {
        		return 0; }
		/*printf("\033[37;42mCollides.\n\033[0m"); */
			return 1;
	}

void UpdatePaddleL(SDL_Rect *PdlL) {
        PdlL->x = PaddleLX; PdlL->y = PaddleLY;
        PdlL->w = PaddleLW; PdlL->h = PaddleLH;
                                if((int)PaddleLY > WinY-PaddleLH) {
                                        PaddleLY = WinY-PaddleLH;
                                } if((int)PaddleLY < 0) {
                                        PaddleLY = 0;
                                }
        }

void UpdatePaddleR(SDL_Rect *PdlR) {
        PdlR->x = PaddleRX; PdlR->y = PaddleRY;
        PdlR->w = PaddleRW; PdlR->h = PaddleRH;
                                if((int)PaddleRY > WinY-PaddleRH) {
                                        PaddleRY = WinY-PaddleRH;
                                } if((int)PaddleRY < 0) {
                                        PaddleRY = 0;
                                }
        }

void UpdateBall(SDL_Rect *Ball) {
            BallX += BallXS; BallY += BallYS;
            Ball->x = BallX; Ball->y = BallY;
            Ball->w = BallW; Ball->h = BallH;
                if((int)BallY > WinY-BallH) {
                    BallYS *= -1; } if((int)BallY < 0) {
                    BallYS *= -1; }
                if(CheckCollisionRect(BallX, BallY, BallW, BallH, PaddleRX, PaddleRY, PaddleRW, PaddleRH) != 0) {
                        BallXS *= -1; printf("\a"); fflush(stdout);
                } if(CheckCollisionRect(BallX, BallY, BallW, BallH, PaddleLX, PaddleLY, PaddleLW, PaddleLH) != 0) {
                        BallXS *= -1; printf("\a"); fflush(stdout);
                }
                if(BallX <= 0) { BallX = WinX/2; BallY = WinY/2; Score--; }
                if(BallX >= WinX-BallW) { BallY= WinY/2; BallX = WinX/2; Score++; }
           }

void PaddleRAILogic(int yPos) {
                if(PaddleRY < yPos) {
                        PaddleRY += 6;
                } else {
                        PaddleRY -= 7;
                        }
        }

int main(int argc, char *argv[]) {
	SDL_Window *Screen = NULL;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("SDL Failed to initialize.\n");
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		fflush(stderr);
		return 1;
	}
	WPAD_Init();
        
	Screen = SDL_CreateWindow("Pong U", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WinX, WinY, 0);
	SDL_Renderer *Renderer = SDL_CreateRenderer(Screen, -1, 0);
	
	if(!Screen) {
		printf("Window could not be created. SDL_Error @ stage 2\n");
		return 1;
	}

	
	while(Quit != 1) {

		WPAD_ScanPads();
		u32 keyedDown = WPAD_ButtonsDown(0);
		u32 keyedHeld = WPAD_ButtonsHeld(0);

		/*Event handling*/
		while(SDL_PollEvent(&Event)) {
			if(Event.type == SDL_QUIT) {
				exit(0);
			}
		}

		if (keyedDown & WPAD_BUTTON_HOME) Quit = 1;
		if (keyedDown & WPAD_BUTTON_UP) PaddleLY -= 20;
		if (keyedDown & WPAD_BUTTON_DOWN) PaddleLY += 20;
		
		/*Drawing*/
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
		SDL_RenderClear(Renderer);
		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);	
		SDL_RenderFillRect(Renderer, &PaddleL);
		SDL_RenderFillRect(Renderer, &PaddleR);
		SDL_RenderFillRect(Renderer, &Ball);
				/* ^ Window update */	
		SDL_RenderPresent(Renderer);
                SDL_Delay(33);				
				/*Update*/
                
                UpdatePaddleL(&PaddleL);
                UpdatePaddleR(&PaddleR);
                PaddleRAILogic(BallY);
                UpdateBall(&Ball);
		//printf("\r\033[1;37;43mScore: %d\033[0m", Score); fflush(stdout);
	}
				exit(0);	
				SDL_Quit();
				puts("\0");
				return 0;
				}

#include <SDL/SDL.h>
#include "config.h"
#include <pspuser.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>

#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("Controller", 0, 1, 1);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int done = 0;

int exit_callback(int arg1, int arg2, void *common) {
	done = 1;
	return 0;
}

int callback_thread(SceSize args, void *argp) {
	int cbid = sceKernelCreateCallback("Exit callback",
			exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

int setup_callbacks(void) {
	int thid = sceKernelCreateThread("update_thread",
			callback_thread, 0x11, 0xFA0, 0, 0);

	if(thid >= 0) sceKernelStartThread(thid, 0, 0);

	return thid;
}



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
	SceCtrlData Controller;
	setup_callbacks();
	 sceCtrlSetSamplingCycle(0);
    	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	SDL_Surface *Screen = NULL;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("SDL Failed to initialize.\n");
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		fflush(stderr);
		return 1;
	}
	
	Screen = SDL_SetVideoMode(WinX, WinY, COLORMODE, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(!Screen) {
		printf("Window could not be created. SDL_Error @ stage 2\n");
		return 1;
	}

	SDL_WM_SetCaption("SDL Pong", NULL);
	
	while(!Quit && !done) {
		/*Event handling*/
		while(SDL_PollEvent(&Event)) {
			if(Controller.Buttons & PSP_CTRL_LEFT) {
				Quit = 1;
			}
		}
		
		/*Drawing*/

		SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
		SDL_FillRect(Screen, &PaddleL, SDL_MapRGB(Screen->format, 255, 0, 0));
		SDL_FillRect(Screen, &PaddleR, SDL_MapRGB(Screen->format, 255, 0, 0));
		SDL_FillRect(Screen, &Ball, SDL_MapRGB(Screen->format, 255, 0, 0));
				/* ^ Window update */
		SDL_Flip(Screen);
                SDL_Delay(33);				
				/*Update*/
                
                UpdatePaddleL(&PaddleL);
                UpdatePaddleR(&PaddleR);
                PaddleRAILogic(BallY);
                UpdateBall(&Ball);
		
		sceCtrlReadBufferPositive(&Controller, 1);
		if(Controller.Buttons != 0) {
                        if(Controller.Buttons & PSP_CTRL_UP) PaddleLY -= 20;
                        if(Controller.Buttons & PSP_CTRL_DOWN) PaddleLY += 20;
                }
	}
				SDL_Quit();
				sceKernelExitGame();
				return 0;
				}

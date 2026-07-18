#include <stdio.h>
#include <gccore.h>
#include <SDL/SDL.h>
#include "config.h"
#include <wiiuse/wpad.h>
#undef main
#include <ogc/system.h>

// These functions handle the Wii's "Home" button/exit requests
int TerminateRequested() {
    return 0; // Return 1 if you want to force an exit, 0 otherwise
}

void Terminate() {
    exit(0); // Safely exit the program
}

/* ^^^ Hack hack shitass hack made by AI cyz fycj this shit */

static bool isSearching = false;

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

int main(int argc, char **argv) {
	//VIDEO_Init(); //...
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);

/*	
	/ Hack <> /
GXRModeObj *vmode = VIDEO_GetPreferredMode(NULL);
void *xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(vmode));
VIDEO_Configure(vmode);
VIDEO_SetNextFramebuffer(xfb);
VIDEO_SetBlack(FALSE);
VIDEO_Flush();
VIDEO_WaitVSync();
if(vmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
	
	/ Hack </> /
nvm...
*/
	SDL_Surface *Screen = NULL;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("SDL Failed to initialize.\n");
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		fflush(stderr);
		return 1;
	}
	
	Screen = SDL_SetVideoMode(WinX, WinY, COLORMODE, SDL_SWSURFACE);

	if(!Screen) {
		printf("Window could not be created. SDL_Error @ stage 2\n");
		return 1;
	}

	SDL_WM_SetCaption("SDL Pong", NULL);
	
	while(Quit != 1) {
		/*Event handling*/
		while(SDL_PollEvent(&Event)) {
			if(Event.type == SDL_QUIT) {
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
                WPAD_ScanPads();
		u32 pressed = WPAD_ButtonsHeld(0);
                UpdatePaddleL(&PaddleL);
                UpdatePaddleR(&PaddleR);
                PaddleRAILogic(BallY);
                UpdateBall(&Ball);
		
				/*Wiimote*/
		if(pressed & WPAD_BUTTON_HOME) break;
		if(pressed & WPAD_BUTTON_PLUS) {
			if(isSearching) WPAD_StopSearch();
			else WPAD_Search();
		}
		if(pressed & WPAD_BUTTON_UP) PaddleLY -= 20;
		if(pressed & WPAD_BUTTON_DOWN) PaddleLY += 20;
	}
				WPAD_Shutdown();	
				SDL_Quit();
				return 0;
				}

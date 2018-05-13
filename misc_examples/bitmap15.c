#include "../common/bitmap.h"
#include <SDL2/SDL.h>

/* display_BMP:  display given bitmap object at (x,y) position */
void display_BMP(BITMAP_FILE *bmp, int x, int y, SDL_Renderer *renderer)
{
	unsigned char r,g,b;
	int a,c;

	if (bmp) {
		for (c=bmp->header.info.height-1; c > 0; c--) {
			for (a=0; a < bmp->header.info.width; a++) {
				get_pixel_BMP(bmp, a*3, c, &r, &g, &b);
				SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				SDL_RenderDrawPoint(renderer, a+x, c+y);
			}
		}
	}
}

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
	SDL_Event ev;
	SDL_Renderer *renderer;
	SDL_Window *window;
	BITMAP_FILE *bmp;

	bmp = load_BMP("test.bmp");
	if (!bmp)
		return 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
		&window, &renderer) < 0)
		goto error;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	display_BMP(bmp, 0, 0, renderer);
	SDL_RenderPresent(renderer);
	while (1) {
		if (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				break;
			else if (ev.type == SDL_KEYDOWN)
				if (ev.key.keysym.sym == SDLK_ESCAPE)
					break;
		}
	}
	destroy_BMP(bmp);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

error:
	destroy_BMP(bmp);
	SDL_Quit();
	return 1;
}

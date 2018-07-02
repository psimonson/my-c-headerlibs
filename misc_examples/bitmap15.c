#include "../common/bitmap.h"
#include "../common/mybool.h"
#if defined _WIN32 || defined _WIN64
#include "../SDL2-2.0.8/include/SDL.h"
#else
#include "SDL2/SDL.h"
#endif

/* convert_BMP:  convert BMP to SDL texture */
static SDL_Texture* convert_BMP(SDL_Renderer *renderer, BITMAP_FILE *bmp)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = SDL_CreateRGBSurfaceFrom(bmp->data, bmp->header.info.width,
			bmp->header.info.height, bmp->header.info.bpp, 3*bmp->header.info.width,
			0x000000ff, 0x0000ff00, 0x00ff0000, 0x00ffffff);
	if (!surface)
		return NULL;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_FreeSurface(surface);
		return NULL;
	}
	SDL_FreeSurface(surface);
	return texture;
}

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMES_PER_SEC 60

int main(int argc, char *argv[])
{
	SDL_Event ev;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *texture;
	SDL_Rect rect;
	BITMAP_FILE *bmp;
	_Bool bounceX = true;
	_Bool bounceY = true;

	bmp = load_BMP("test.bmp");
	if (check_BMP(bmp))
		return 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
		&window, &renderer) < 0)
		goto error;
	texture = convert_BMP(renderer, bmp);
	if (!texture) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		goto error;
	}
	destroy_BMP(bmp);
	rect.x = 0;
	rect.y = 0;
	rect.w = bmp->header.info.width;
	rect.h = bmp->header.info.height;
	while (1) {
		int start = SDL_GetTicks();
		if (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				break;
			else if (ev.type == SDL_KEYDOWN) {
				if (ev.key.keysym.sym == SDLK_ESCAPE)
					break;
				else if (ev.key.keysym.sym == SDLK_LEFT)
					rect.x -= 4;
				else if (ev.key.keysym.sym == SDLK_RIGHT)
					rect.x += 4;
			}
		}
		if (bounceX)
			rect.x -= 2;
		else
			rect.x += 2;
		if (rect.x >= WINDOW_WIDTH-rect.w) {
			rect.x = WINDOW_WIDTH-rect.w;
			if (rect.x == WINDOW_WIDTH-rect.w)
				bounceX = true;
		} else if (rect.x <= 0) {
			rect.x = 0;
			if (rect.x == 0)
				bounceX = false;
		}
		/* make image bounce around in Y axis */
		if (bounceY)
			rect.y -= 2;
		else
			rect.y += 2;
		if (rect.y >= WINDOW_HEIGHT-rect.h) {
			rect.y = WINDOW_HEIGHT-rect.h;
			if (rect.y == WINDOW_HEIGHT-rect.h)
				bounceY = true;
		} else if (rect.y <= 0) {
			rect.y = 0;
			if (rect.y == 0)
				bounceY = false;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_VERTICAL);
		SDL_RenderPresent(renderer);
		if (1000/FRAMES_PER_SEC > (SDL_GetTicks()-start))
			SDL_Delay(1000/FRAMES_PER_SEC-(SDL_GetTicks()-start));
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

error:
	destroy_BMP(bmp);
	SDL_Quit();
	return 1;
}

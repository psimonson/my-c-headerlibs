#include "../common/bitmap.h"
#if defined _WIN32 || defined _WIN64
#include "../SDL2-2.0.8/include/SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
	SDL_Event ev;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Surface *image;
	SDL_Texture *texture;
	BITMAP_FILE *bmp;

	bmp = load_BMP("test.bmp");
	if (check_BMP(bmp))
		return 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
		&window, &renderer) < 0)
		goto error;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	if (!bmp)
		goto error;
	image = SDL_CreateRGBSurfaceFrom(bmp->data, bmp->header.info.width, bmp->header.info.height, bmp->header.info.bpp, 3*bmp->header.info.width, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00ffffff);
	if (!image)
		goto error;
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture) {
		SDL_FreeSurface(image);
		goto error;
	}
	SDL_FreeSurface(image);
	destroy_BMP(bmp);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

error:
	destroy_BMP(bmp);
	SDL_Quit();
	return 1;
}

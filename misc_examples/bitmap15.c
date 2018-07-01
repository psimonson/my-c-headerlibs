#include "../common/bmp_ext.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
	SDL_Event ev;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *texture;
	SDL_Rect rect;
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
	texture = convert_BMP(renderer, bmp);
	if (!texture) {
		goto error;
	}
	destroy_BMP(bmp);
	rect.x = 0;
	rect.y = 0;
	rect.w = bmp->header.info.width;
	rect.h = bmp->header.info.height;
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_VERTICAL);
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

#ifndef _BMP_EXT_H_
#define _BMP_EXT_H_

#ifndef _BITMAP_H_
#include "bitmap.h"
#endif
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

#endif

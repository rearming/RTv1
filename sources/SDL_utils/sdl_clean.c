#include "rtv1.h"

void		sdl_clean(t_rtv1 *rtv1)
{
	SDL_DestroyRenderer(rtv1->sdl.rend);
	SDL_DestroyWindow(rtv1->sdl.win);
	SDL_Quit();
}

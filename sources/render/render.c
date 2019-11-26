#include "rtv1.h"

void		render(t_rtv1 *rtv1, void (*render_func)(t_rtv1 *))
{
	SDL_LockTexture(rtv1->sdl.texture, 0,
			(void**)&rtv1->img_data, &rtv1->sdl.pitch);
	render_func(rtv1);
	SDL_UnlockTexture(rtv1->sdl.texture);
	SDL_SetRenderTarget(rtv1->sdl.rend, rtv1->sdl.texture);
	SDL_RenderCopy(rtv1->sdl.rend, rtv1->sdl.texture, NULL, NULL);
	SDL_RenderPresent(rtv1->sdl.rend);
}

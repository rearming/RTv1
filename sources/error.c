#include "rtv1_errors.h"
#include "libft.h"

void	raise_error(int err_code)
{
	if (err_code == ERR_SDL_INIT)
		ft_printf("SDL_Init failed.\n");
	else if (err_code == ERR_SDL_WIN)
		ft_printf("SDL_Create_Window failed.\n");
	else if (err_code == ERR_SDL_RENDER)
		ft_printf("SDL_Create_Renderer failed.\n");
	else if (err_code == ERR_SDL_TEXTURE_CREATE)
		ft_printf("SDL_Create_Texture failed.\n");
	else if (err_code == ERR_MALLOC)
		ft_printf("malloc() failed!\n");
	else
		ft_printf("UNKNOWN ERROR!\n");
	exit(err_code);
}

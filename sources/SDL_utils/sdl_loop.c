/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:53:54 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:53:55 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sdl_loop(t_rtv1 *rtv1)
{
	SDL_Event		event;
	Uint32			timeout;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (21)
	{
		timeout = SDL_GetTicks() + 30;
		while (SDL_PollEvent(&event) && (event.type == SDL_KEYUP
			|| !SDL_TICKS_PASSED(SDL_GetTicks(), timeout)))
		{
			process_event(&event, rtv1);
		}
		if (event.type == SDL_QUIT)
			break ;
	}
}

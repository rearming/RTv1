#include "rtv1.h"

void	exit_clean(t_rtv1 *rtv1)
{
	int		err;

	err = 0;
	if (rtv1->cl.queue)
	{
		err += clFlush(rtv1->cl.queue);
		err += clFinish(rtv1->cl.queue);
		err += clReleaseCommandQueue(rtv1->cl.queue);
	}
	if (rtv1->cl.device_id)
		err += clReleaseDevice(rtv1->cl.device_id);
	if (rtv1->cl.kernel)
		err += clReleaseKernel(rtv1->cl.kernel);
	if (rtv1->cl.program)
		err += clReleaseProgram(rtv1->cl.program);
	if (rtv1->cl.context)
		err += clReleaseContext(rtv1->cl.context);
	if (err)
		raise_error(ERR_OPENCL_CLEAN);
	SDL_DestroyRenderer(rtv1->sdl.rend);
	SDL_DestroyWindow(rtv1->sdl.win);
	SDL_Quit();
	exit(0);
}
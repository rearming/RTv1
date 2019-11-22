#include "rtv1.h"
#include <stdarg.h>

char		*concat_source_code(int files_nbr, ...)
{
	t_cl_gnl	gnl;
	va_list		ap;
	char		*str_file;
	size_t		out_file_size;
	int			i;

	i = 0;
	gnl.sum_len = 0;
	gnl.backup = malloc(1);
	gnl.temp_str = NULL;
	va_start(ap, files_nbr);
	while (i < files_nbr)
	{
		str_file = cl_gnl(open(va_arg(ap, char*), O_RDONLY), &out_file_size);
		gnl.sum_len += out_file_size;
		gnl.temp_str = ft_strljoin(gnl.backup, str_file, gnl.sum_len);
		free(str_file);
		free(gnl.backup);
		gnl.backup = gnl.temp_str;
		i++;
	}
	va_end(ap);
	return (gnl.backup);
}

char		*get_cl_file(size_t *out_size)
{
	char		*result_cl_file;
	char 		*cl_file;

	cl_file = concat_source_code(6,
								 "./includes/rtv1_defines.h",
								 "./includes/rtv1_structs.h",
								 "./sources/opencl_source_files/prototypes.cl",
								 "./sources/opencl_source_files/utils.cl",
								 "./sources/opencl_source_files/light_computing.cl",
								 "./sources/opencl_source_files/raytracer.cl");
	ft_sprintf(&result_cl_file, "%s%s", "#define FT_OPENCL___\n\n", cl_file);
	*out_size = ft_strlen(result_cl_file);
	free(cl_file);
	return (result_cl_file);
}

#include "rtv1.h"

char		*cl_gnl(int fd)
{
	t_cl_gnl	gnl;

	gnl.sum_len = 0;
	gnl.backup = malloc(1);
	gnl.temp_str = NULL;
	if (fd < 0 || read(fd, gnl.buf, 0) < 0)
		raise_error(ERR_INV_FILE);
	while ((gnl.read_res = read(fd, gnl.buf, CL_BUFF_SIZE)))
	{
		gnl.sum_len += gnl.read_res;
		gnl.buf[gnl.read_res] = '\0';
		gnl.temp_str = ft_strljoin(gnl.backup, gnl.buf, gnl.sum_len);
		free(gnl.backup);
		gnl.backup = gnl.temp_str;
	}
	return (gnl.backup);
}


#include "../include/cub3D.h"

void *int_memset(void *ptr, int value, size_t num)
{
	int *int_ptr = (int *)ptr;
	size_t i = 0;
	while (i < num)
	{
		int_ptr[i] = value;
		i++;
	}
	return ptr;
}

int rgba_to_int(int r, int g, int b, int a)
{
	return (a << 24) | (r << 16) | (g << 8) | b;
}

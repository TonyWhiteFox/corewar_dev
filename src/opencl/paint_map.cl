__kernel void kercorewar(__global int* picture, __global int* field,
						__global int* changes, const int w_x, const int w_y,
						const int flows)
{
	int gid = get_global_id(0);
	int value = field[gid / 2];
	if (gid % 2 > 0)
		value = value % 16;
	else
		value = value / 16;
	
}
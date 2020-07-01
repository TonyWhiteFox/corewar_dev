__kernel void alfavit(__global int* picture, int start_pos, int back_color,
	int front_color, int w_x, int w_x2, int w_x3, int w_x4, int w_x5, int w_x6,
	int w_x7, int w_x8, int w_x9, int w_x10, int w_x11,
	int x11, int x12, int x13, int x14, int x15, int x16, int x17,
	int x21, int x22, int x23, int x24, int x25, int x26, int x27,
	int x31, int x32, int x33, int x34, int x35, int x36, int x37,
	int x41, int x42, int x43, int x44, int x45, int x46, int x47,
	int x51, int x52, int x53, int x54, int x55, int x56, int x57,
	int x61, int x62, int x63, int x64, int x65, int x66, int x67,
	int x71, int x72, int x73, int x74, int x75, int x76, int x77,
	int x81, int x82, int x83, int x84, int x85, int x86, int x87,
	int x91, int x92, int x93, int x94, int x95, int x96, int x97,
	int x101, int x102, int x103, int x104, int x105, int x106, int x107,
	int x111, int x112, int x113, int x114, int x115, int x116, int x117)
{
	if (x11 == 1)
		picture[start_pos + w_x + 1] = front_color;
	else
		picture[start_pos + w_x + 1] = back_color;
	
	if (x12 == 1)
		picture[start_pos + w_x + 2] = front_color;
	else
		picture[start_pos + w_x + 2] = back_color;
	
	if (x13 == 1)
		picture[start_pos + w_x + 3] = front_color;
	else
		picture[start_pos + w_x + 3] = back_color;
	
	if (x14 == 1)
		picture[start_pos + w_x + 4] = front_color;
	else
		picture[start_pos + w_x + 4] = back_color;
	
	if (x15 == 1)
		picture[start_pos + w_x + 5] = front_color;
	else
		picture[start_pos + w_x + 5] = back_color;
	
	if (x16 == 1)
		picture[start_pos + w_x + 6] = front_color;
	else
		picture[start_pos + w_x + 6] = back_color;
	
	if (x17 == 1)
		picture[start_pos + w_x + 7] = front_color;
	else
		picture[start_pos + w_x + 7] = back_color;
	
	
	if (x21 == 1)
		picture[start_pos + w_x2 + 1] = front_color;
	else
		picture[start_pos + w_x2 + 1] = back_color;
	
	if (x22 == 1)
		picture[start_pos + w_x2 + 2] = front_color;
	else
		picture[start_pos + w_x2 + 2] = back_color;
	
	if (x23 == 1)
		picture[start_pos + w_x2 + 3] = front_color;
	else
		picture[start_pos + w_x2 + 3] = back_color;
	
	if (x24 == 1)
		picture[start_pos + w_x2 + 4] = front_color;
	else
		picture[start_pos + w_x2 + 4] = back_color;
	
	if (x25 == 1)
		picture[start_pos + w_x2 + 5] = front_color;
	else
		picture[start_pos + w_x2 + 5] = back_color;
	
	if (x26 == 1)
		picture[start_pos + w_x2 + 6] = front_color;
	else
		picture[start_pos + w_x2 + 6] = back_color;
	
	if (x27 == 1)
		picture[start_pos + w_x2 + 7] = front_color;
	else
		picture[start_pos + w_x2 + 7] = back_color;
	
	

	if (x31 == 1)
		picture[start_pos + w_x3 + 1] = front_color;
	else
		picture[start_pos + w_x3 + 1] = back_color;
	
	if (x32 == 1)
		picture[start_pos + w_x3 + 2] = front_color;
	else
		picture[start_pos + w_x3 + 2] = back_color;
	
	if (x33 == 1)
		picture[start_pos + w_x3 + 3] = front_color;
	else
		picture[start_pos + w_x3 + 3] = back_color;
	
	if (x34 == 1)
		picture[start_pos + w_x3 + 4] = front_color;
	else
		picture[start_pos + w_x3 + 4] = back_color;
	
	if (x35 == 1)
		picture[start_pos + w_x3 + 5] = front_color;
	else
		picture[start_pos + w_x3 + 5] = back_color;
	
	if (x36 == 1)
		picture[start_pos + w_x3 + 6] = front_color;
	else
		picture[start_pos + w_x3 + 6] = back_color;
	
	if (x37 == 1)
		picture[start_pos + w_x3 + 7] = front_color;
	else
		picture[start_pos + w_x3 + 7] = back_color;
	
	

	if (x41 == 1)
		picture[start_pos + w_x4 + 1] = front_color;
	else
		picture[start_pos + w_x4 + 1] = back_color;
	
	if (x42 == 1)
		picture[start_pos + w_x4 + 2] = front_color;
	else
		picture[start_pos + w_x4 + 2] = back_color;
	
	if (x43 == 1)
		picture[start_pos + w_x4 + 3] = front_color;
	else
		picture[start_pos + w_x4 + 3] = back_color;
	
	if (x44 == 1)
		picture[start_pos + w_x4 + 4] = front_color;
	else
		picture[start_pos + w_x4 + 4] = back_color;
	
	if (x45 == 1)
		picture[start_pos + w_x4 + 5] = front_color;
	else
		picture[start_pos + w_x4 + 5] = back_color;
	
	if (x46 == 1)
		picture[start_pos + w_x4 + 6] = front_color;
	else
		picture[start_pos + w_x4 + 6] = back_color;
	
	if (x47 == 1)
		picture[start_pos + w_x4 + 7] = front_color;
	else
		picture[start_pos + w_x4 + 7] = back_color;
	
	

	if (x51 == 1)
		picture[start_pos + w_x5 + 1] = front_color;
	else
		picture[start_pos + w_x5 + 1] = back_color;
	
	if (x52 == 1)
		picture[start_pos + w_x5 + 2] = front_color;
	else
		picture[start_pos + w_x5 + 2] = back_color;
	
	if (x53 == 1)
		picture[start_pos + w_x5 + 3] = front_color;
	else
		picture[start_pos + w_x5 + 3] = back_color;
	
	if (x54 == 1)
		picture[start_pos + w_x5 + 4] = front_color;
	else
		picture[start_pos + w_x5 + 4] = back_color;
	
	if (x55 == 1)
		picture[start_pos + w_x5 + 5] = front_color;
	else
		picture[start_pos + w_x5 + 5] = back_color;
	
	if (x56 == 1)
		picture[start_pos + w_x5 + 6] = front_color;
	else
		picture[start_pos + w_x5 + 6] = back_color;
	
	if (x57 == 1)
		picture[start_pos + w_x5 + 7] = front_color;
	else
		picture[start_pos + w_x5 + 7] = back_color;
	
	

	if (x61 == 1)
		picture[start_pos + w_x6 + 1] = front_color;
	else
		picture[start_pos + w_x6 + 1] = back_color;
	
	if (x62 == 1)
		picture[start_pos + w_x6 + 2] = front_color;
	else
		picture[start_pos + w_x6 + 2] = back_color;
	
	if (x63 == 1)
		picture[start_pos + w_x6 + 3] = front_color;
	else
		picture[start_pos + w_x6 + 3] = back_color;
	
	if (x64 == 1)
		picture[start_pos + w_x6 + 4] = front_color;
	else
		picture[start_pos + w_x6 + 4] = back_color;
	
	if (x65 == 1)
		picture[start_pos + w_x6 + 5] = front_color;
	else
		picture[start_pos + w_x6 + 5] = back_color;
	
	if (x66 == 1)
		picture[start_pos + w_x6 + 6] = front_color;
	else
		picture[start_pos + w_x6 + 6] = back_color;
	
	if (x67 == 1)
		picture[start_pos + w_x6 + 7] = front_color;
	else
		picture[start_pos + w_x6 + 7] = back_color;
	
	

	if (x71 == 1)
		picture[start_pos + w_x7 + 1] = front_color;
	else
		picture[start_pos + w_x7 + 1] = back_color;
	
	if (x72 == 1)
		picture[start_pos + w_x7 + 2] = front_color;
	else
		picture[start_pos + w_x7 + 2] = back_color;
	
	if (x73 == 1)
		picture[start_pos + w_x7 + 3] = front_color;
	else
		picture[start_pos + w_x7 + 3] = back_color;
	
	if (x74 == 1)
		picture[start_pos + w_x7 + 4] = front_color;
	else
		picture[start_pos + w_x7 + 4] = back_color;
	
	if (x75 == 1)
		picture[start_pos + w_x7 + 5] = front_color;
	else
		picture[start_pos + w_x7 + 5] = back_color;
	
	if (x76 == 1)
		picture[start_pos + w_x7 + 6] = front_color;
	else
		picture[start_pos + w_x7 + 6] = back_color;
	
	if (x77 == 1)
		picture[start_pos + w_x7 + 7] = front_color;
	else
		picture[start_pos + w_x7 + 7] = back_color;
	
	

	if (x81 == 1)
		picture[start_pos + w_x8 + 1] = front_color;
	else
		picture[start_pos + w_x8 + 1] = back_color;
	
	if (x82 == 1)
		picture[start_pos + w_x8 + 2] = front_color;
	else
		picture[start_pos + w_x8 + 2] = back_color;
	
	if (x83 == 1)
		picture[start_pos + w_x8 + 3] = front_color;
	else
		picture[start_pos + w_x8 + 3] = back_color;
	
	if (x84 == 1)
		picture[start_pos + w_x8 + 4] = front_color;
	else
		picture[start_pos + w_x8 + 4] = back_color;
	
	if (x85 == 1)
		picture[start_pos + w_x8 + 5] = front_color;
	else
		picture[start_pos + w_x8 + 5] = back_color;
	
	if (x86 == 1)
		picture[start_pos + w_x8 + 6] = front_color;
	else
		picture[start_pos + w_x8 + 6] = back_color;
	
	if (x87 == 1)
		picture[start_pos + w_x8 + 7] = front_color;
	else
		picture[start_pos + w_x8 + 7] = back_color;
	
	

	if (x91 == 1)
		picture[start_pos + w_x9 + 1] = front_color;
	else
		picture[start_pos + w_x9 + 1] = back_color;
	
	if (x92 == 1)
		picture[start_pos + w_x9 + 2] = front_color;
	else
		picture[start_pos + w_x9 + 2] = back_color;
	
	if (x93 == 1)
		picture[start_pos + w_x9 + 3] = front_color;
	else
		picture[start_pos + w_x9 + 3] = back_color;
	
	if (x94 == 1)
		picture[start_pos + w_x9 + 4] = front_color;
	else
		picture[start_pos + w_x9 + 4] = back_color;
	
	if (x95 == 1)
		picture[start_pos + w_x9 + 5] = front_color;
	else
		picture[start_pos + w_x9 + 5] = back_color;
	
	if (x96 == 1)
		picture[start_pos + w_x9 + 6] = front_color;
	else
		picture[start_pos + w_x9 + 6] = back_color;
	
	if (x97 == 1)
		picture[start_pos + w_x9 + 7] = front_color;
	else
		picture[start_pos + w_x9 + 7] = back_color;
	
	

	if (x101 == 1)
		picture[start_pos + w_x10 + 1] = front_color;
	else
		picture[start_pos + w_x10 + 1] = back_color;
	
	if (x102 == 1)
		picture[start_pos + w_x10 + 2] = front_color;
	else
		picture[start_pos + w_x10 + 2] = back_color;
	
	if (x103 == 1)
		picture[start_pos + w_x10 + 3] = front_color;
	else
		picture[start_pos + w_x10 + 3] = back_color;
	
	if (x104 == 1)
		picture[start_pos + w_x10 + 4] = front_color;
	else
		picture[start_pos + w_x10 + 4] = back_color;
	
	if (x105 == 1)
		picture[start_pos + w_x10 + 5] = front_color;
	else
		picture[start_pos + w_x10 + 5] = back_color;
	
	if (x106 == 1)
		picture[start_pos + w_x10 + 6] = front_color;
	else
		picture[start_pos + w_x10 + 6] = back_color;
	
	if (x107 == 1)
		picture[start_pos + w_x10 + 7] = front_color;
	else
		picture[start_pos + w_x10 + 7] = back_color;
	
	

	if (x111 == 1)
		picture[start_pos + w_x11 + 1] = front_color;
	else
		picture[start_pos + w_x11 + 1] = back_color;
	
	if (x112 == 1)
		picture[start_pos + w_x11 + 2] = front_color;
	else
		picture[start_pos + w_x11 + 2] = back_color;
	
	if (x113 == 1)
		picture[start_pos + w_x11 + 3] = front_color;
	else
		picture[start_pos + w_x11 + 3] = back_color;
	
	if (x114 == 1)
		picture[start_pos + w_x11 + 4] = front_color;
	else
		picture[start_pos + w_x11 + 4] = back_color;
	
	if (x115 == 1)
		picture[start_pos + w_x11 + 5] = front_color;
	else
		picture[start_pos + w_x11 + 5] = back_color;
	
	if (x116 == 1)
		picture[start_pos + w_x11 + 6] = front_color;
	else
		picture[start_pos + w_x11 + 6] = back_color;
	
	if (x117 == 1)
		picture[start_pos + w_x11 + 7] = front_color;
	else
		picture[start_pos + w_x11 + 7] = back_color;
}

__kernel void kercorewar(__global int* picture, __global uchar* field,
						__global int* changes, __global bool* cursor,
						__global int* live,
						const int w_x, const int w_y,
						const int flows, const int total_cycle)
{
	int gid = get_global_id(0);

	int	back_color = 0x000000;
	int	front_color = 0x888888;
	int half_gid = gid / 2;
	int change = changes[half_gid];
	int tithe_change = change / 10;
	if (change > 0)
	{
		switch (change % 10)
		{
			case 0:
				front_color = 0x990000;
				if ((tithe_change + 50 >= total_cycle) && (tithe_change > 1))
					front_color = 0xFF0000;
				break;
			case 1:
				front_color = 0x9900;
				if ((tithe_change + 50 >= total_cycle) && (tithe_change > 1))
					front_color = 0xFF00;
				break;
			case 2:
				front_color = 0x9999;
				if ((tithe_change + 50 >= total_cycle) && (tithe_change > 1))
					front_color = 0xFFFF;
				break;
			case 3:
				front_color = 0x990099;
				if ((tithe_change + 50 >= total_cycle) && (tithe_change > 1))
					front_color = 0xFF00FF;
				break;
		}
	}

	if (cursor[half_gid] == true)
	{
		back_color = front_color;
		front_color = 0x000000;
	}


	if (live[half_gid] > 0)
	{
		tithe_change = live[half_gid] / 10;
		if (tithe_change + 50 >= total_cycle)
		{
			front_color = 0xFFFFFF;
			switch (live[half_gid] % 10)
			{
				case 0:
					back_color = 0xCC0000;
					break;
				case 1:
					back_color = 0xCC00;
					break;
				case 2:
					back_color = 0xCCCC;
					break;
				case 3:
					back_color = 0xCC00CC;
					break;
			}
		}
	}

	int value = field[half_gid];
	if (gid % 2 > 0)
		value = value % 16;
	else
		value = value / 16;
	int	num_x = gid % 128;
	int	num_y = gid / 128;
	int start_x = 30 + num_x * 9 + num_x / 2 * 3;
	int start_y = 30 + num_y * 15;
	int start_pos = start_y * w_x + start_x;
	int w_x2 = w_x * 2;
	int w_x3 = w_x * 3;
	int w_x4 = w_x * 4;
	int w_x5 = w_x * 5;
	int w_x6 = w_x * 6;
	int w_x7 = w_x * 7;
	int w_x8 = w_x * 8;
	int w_x9 = w_x * 9;
	int w_x10 = w_x * 10;
	int w_x11 = w_x * 11;
	int w_x12 = w_x * 12;
	switch (value)
	{
		case 0:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5,	w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 1, 1, 0, 0, 0,
				0, 1, 1, 1, 1, 0, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				0, 1, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 0, 0, 0);
			break;
		case 1:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5,	w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 0, 0, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 1, 0);
			break;
		case 2:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 1, 1, 1, 0, 0,
				0, 1, 1, 1, 1, 1, 0,
				1, 0, 0, 0, 0, 1, 1,
				1, 0, 0, 0, 0, 1, 1,
				0, 1, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 1, 1, 1,
				0, 0, 0, 1, 1, 1, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 1, 1, 1, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 0);
			break;
		case 3:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 0, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 1, 0,
				0, 0, 0, 0, 0, 1, 1,
				0, 1, 0, 0, 0, 1, 1,
				1, 0, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 4:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 1, 1, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 1, 1, 1, 1);
			break;
		case 5:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 0, 1, 1,
				1, 0, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 6:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 0, 1,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 7:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 0, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0);
			break;
		case 8:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				0, 1, 1, 1, 1, 1, 0,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 9:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 1, 1,
				1, 0, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 10:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 	1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 11:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 0);
			break;
		case 12:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 13:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 0);
			break;
		case 14:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 0, 0,
				1, 1, 1, 1, 1, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1);
			break;
		case 15:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 0, 0,
				1, 1, 1, 1, 1, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0);
			break;
		case 16:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 1, 1, 1,
				1, 1, 0, 0, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 17:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 18:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 19:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 1, 1, 1, 1, 0,
				0, 0, 1, 1, 1, 1, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 0, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 1, 0,
				0, 0, 1, 1, 1, 1, 0);
			break;
		case 20:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 0, 1, 1, 1, 1,
				0, 0, 0, 1, 1, 1, 1,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				0, 0, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 0,
				0, 1, 1, 1, 1, 0, 0);
			break;
		case 21:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 1, 1, 1,
				1, 1, 0, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 0, 0,
				1, 1, 1, 1, 0, 1, 0,
				1, 1, 1, 1, 1, 0, 0,
				1, 1, 0, 1, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 22:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1);
			break;
		case 23:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 0, 1, 1, 0,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 24:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 0, 0, 1, 1,
				1, 1, 1, 1, 0, 1, 1,
				1, 1, 0, 1, 1, 1, 1,
				1, 1, 0, 0, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 25:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 26:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				0, 1, 0, 0, 0, 0, 0);
			break;
		case 27:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 0,
				1, 1, 0, 1, 1, 1, 0,
				1, 1, 0, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 1);
			break;
		case 28:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 0, 0, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				0, 1, 0, 0, 0, 1, 1);
			break;
		case 29:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 1, 1, 1, 1, 1,0-,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 0,
				0, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 1, 1, 1,
				0, 0, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 30:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 0,
				1, 1, 1, 1, 1, 1, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0,
				0, 0, 1, 1, 0, 0, 0);
			break;
		case 31:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 1, 1, 1, 0);
			break;
		case 32:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				0, 1, 1, 0, 1, 1, 0,
				0, 1, 1, 0, 1, 1, 0,
				0, 1, 1, 0, 1, 1, 0,
				0, 1, 1, 0, 1, 1, 0,
				0, 0, 1, 0, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 0, 1, 0, 0, 0);
			break;
		case 33:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 0, 1, 0, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 1, 1, 0, 1, 1, 0);
			break;
		case 34:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 0, 1, 1, 1,
				0, 1, 1, 0, 1, 1, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 1, 1, 0, 1, 1, 0,
				1, 1, 1, 0, 1, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1);
			break;
		case 35:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 0, 0, 0, 1, 1,
				1, 1, 1, 0, 1, 1, 1,
				0, 1, 1, 0, 1, 1, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 1, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 0, 1, 1, 1, 0, 0);
			break;
		case 36:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 1, 1, 1,
				0, 0, 0, 1, 1, 1, 0,
				0, 0, 1, 1, 1, 0, 0,
				0, 1, 1, 1, 0, 0, 0,
				1, 1, 1, 0, 0, 0, 0,
				1, 1, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1);
			break;
		case 37:
			alfavit(picture, start_pos, back_color, front_color, w_x,
				w_x2, w_x3, w_x4, w_x5, w_x6, w_x7, w_x8, w_x9, w_x10, w_x11,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
				1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1);
			break;
	}
	picture[start_pos] = back_color;
	picture[start_pos + 1] = back_color;
	picture[start_pos + 2] = back_color;
	picture[start_pos + 3] = back_color;
	picture[start_pos + 4] = back_color;
	picture[start_pos + 5] = back_color;
	picture[start_pos + 6] = back_color;
	picture[start_pos + 7] = back_color;
	picture[start_pos + 8] = back_color;
	picture[start_pos + w_x] = back_color;
	picture[start_pos + w_x + 8] = back_color;
	picture[start_pos + w_x2] = back_color;
	picture[start_pos + w_x2 + 8] = back_color;
	picture[start_pos + w_x3] = back_color;
	picture[start_pos + w_x3 + 8] = back_color;
	picture[start_pos + w_x4] = back_color;
	picture[start_pos + w_x4 + 8] = back_color;
	picture[start_pos + w_x5] = back_color;
	picture[start_pos + w_x5 + 8] = back_color;
	picture[start_pos + w_x6] = back_color;
	picture[start_pos + w_x6 + 8] = back_color;
	picture[start_pos + w_x7] = back_color;
	picture[start_pos + w_x7 + 8] = back_color;
	picture[start_pos + w_x8] = back_color;
	picture[start_pos + w_x8 + 8] = back_color;
	picture[start_pos + w_x9] = back_color;
	picture[start_pos + w_x9 + 8] = back_color;
	picture[start_pos + w_x10] = back_color;
	picture[start_pos + w_x10 + 8] = back_color;
	picture[start_pos + w_x11] = back_color;
	picture[start_pos + w_x11 + 8] = back_color;
	picture[start_pos + w_x12] = back_color;
	picture[start_pos + w_x12 + 1] = back_color;
	picture[start_pos + w_x12 + 2] = back_color;
	picture[start_pos + w_x12 + 3] = back_color;
	picture[start_pos + w_x12 + 4] = back_color;
	picture[start_pos + w_x12 + 5] = back_color;
	picture[start_pos + w_x12 + 6] = back_color;
	picture[start_pos + w_x12 + 7] = back_color;
	picture[start_pos + w_x12 + 8] = back_color;
}
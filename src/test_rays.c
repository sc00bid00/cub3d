/*	mapS defined as 64 (pixel cube size) */
void	draw_rays(t_display *display)
{
	int count;
	// int r; //number of rays
	float atan; // inverse tangens
	float ntan;

	display->rays->a = display->pos->a;
	// display->rays->a = display->pos->a - DR * 30;
	// if (display->rays->a < 0)
	// 	display->rays->a += 2 * M_PI;
	// if (display->rays->a > 0)
	// 	display->rays->a -= 2 * M_PI;
	for (r = 0; r < 25; r++)
	{
		// find horizontal intersections
		float dis_h = 100000; float hx = display->pos->x; float hy = display->pos->y;
		count = 0;
		atan = -1 / tan (display->rays->a);
		// ray facing up
		if (display->rays->a > M_PI)
		// if (display->rays->a > M_PI && display->rays->a < M_PI * 2)
		{
			display->rays->y0 = ((int) (display->pos->y / mapS) * mapS) - 0.0001;
			display->rays->x0 = display->pos->x + ((display->pos->y - display->rays->y0) * atan);
			display->rays->y_off = mapS * -1;
			display->rays->x_off = -(display->rays->y_off) * atan;
		}	
		// ray facing down
		else if (display->rays->a < M_PI)
		// else if (display->rays->a < M_PI && display->rays->a > 0)
		{
			display->rays->y0 = ((int) (display->pos->y / mapS) * mapS) + mapS;
			display->rays->x0 = display->pos->x + ((display->pos->y - display->rays->y0) * atan);
			display->rays->y_off = mapS;
			display->rays->x_off = -(display->rays->y_off) * atan;
		}
		// else if (display->rays->a == M_PI || display->rays->a == 0)
		else if (display->rays->a == 0)
		{
			display->rays->x0 = display->pos->x;
			display->rays->y0 = display->pos->y;
			count = display->maps->max_y;
		}
		while (count < display->maps->max_y)
		{
			display->rays->mx = (int) display->rays->x0 / mapS;
			display->rays->my = (int) display->rays->y0 / mapS;
			if (display->rays->mx < display->maps->max_x && display->rays->my < display->maps->max_y && display->rays->mx >= 0 && display->rays->my >= 0)
			{
				if (map[display->rays->mx][display->rays->my] == '1' || display->rays->mx == 0 || display->rays->my == 0 || display->rays->mx == display->maps->max_x - 1 || display->rays->my == display->maps->max_y - 1)
				{
					printf("hit wall at coordinate[%d][%d]\n", display->rays->mx, display->rays->my);
					hx = display->rays->x0;
					hy = display->rays->y0;
					dis_h = dist(display->pos->x, display->pos->y, hx, hy, display->rays->a);
					count = display->maps->max_y;
				}
				else
				{
					printf("no wall at coordinate[%d][%d]\n", display->rays->mx, display->rays->my);
					display->rays->y0 += display->rays->y_off;
					display->rays->x0 += display->rays->x_off;
				}
				count++;
			}	
		}
		printf("ray angle is %f\n", display->rays->a);
		printf("player angle is %f\n", display->pos->a);
		// if (display->pos->x > 0 && display->pos->x < WIDTH && display->rays->x0 > 0 && display->rays->x0 < WIDTH && display->pos->y > 0 && display->pos->y < HEIGHT && display->rays->y0 > 0 && display->rays->y0 < HEIGHT)
		// 	draw_line_bresenham(display, display->pos->x, display->pos->y, display->rays->x0, display->rays->y0);
		
			// find vertical intersections
		count = 0;
		ntan = -tan(display->rays->a);
		float dis_v = 100000; float vx = display->pos->x; float vy = display->pos->y;
		// ray facing left
		// if (display->rays->a > M_PI)
		if (display->rays->a > M_PI_2 && display->rays->a < (3 * M_PI_2))
		{
			display->rays->x0 = ((int) (display->pos->x / mapS) * mapS) - 0.0001;
			display->rays->y0 = display->pos->y + ((display->pos->x - display->rays->x0) * ntan);
			display->rays->x_off = mapS * -1;
			display->rays->y_off = -(display->rays->x_off) * ntan;
		}	
		// ray facing right
		// else if (display->rays->a < M_PI)
		else if (display->rays->a < M_PI_2 || display->rays->a > (3 * M_PI_2))
		{
			display->rays->x0 = ((int) (display->pos->x / mapS) * mapS) + mapS;
			display->rays->y0 = display->pos->y + ((display->pos->x - display->rays->x0) * ntan);
			display->rays->x_off = mapS;
			display->rays->y_off = -(display->rays->x_off) * ntan;
		}
		// else if (display->rays->a == M_PI || display->rays->a == 0)
		else if (display->rays->a == 0)
		{
			display->rays->x0 = display->pos->x;
			display->rays->y0 = display->pos->y;
			count = display->maps->max_y;
		}
		while (count < display->maps->max_y)
		{
			display->rays->mx = (int) display->rays->x0 / mapS;
			display->rays->my = (int) display->rays->y0 / mapS;
			if (display->rays->mx < display->maps->max_x && display->rays->my < display->maps->max_y && display->rays->mx >= 0 && display->rays->my >= 0)
			{
				if (map[display->rays->mx][display->rays->my] == '1' || display->rays->mx == 0 || display->rays->my == 0 || display->rays->mx == display->maps->max_x - 1 || display->rays->my == display->maps->max_y - 1)
				{
					printf("hit wall at coordinate[%d][%d]\n", display->rays->mx, display->rays->my);
					vx = display->rays->x0;
					vy = display->rays->y0;
					dis_v = dist(display->pos->x, display->pos->y, vx, vy, display->rays->a);
					count = display->maps->max_y;
				}
				else
				{
					printf("no wall at coordinate[%d][%d]\n", display->rays->mx, display->rays->my);
					display->rays->y0 += display->rays->y_off;
					display->rays->x0 += display->rays->x_off;
					// count++;
				}
			}
			count++;
		}
		printf("ray angle is %f\n", display->rays->a);
		printf("player angle is %f\n", display->pos->a);
		if (dis_v < dis_h)
		{
			display->rays->x0 = vx;
			display->rays->y0 = vy;

		}
		if (dis_v > dis_h)
		{
			display->rays->x0 = hx;
			display->rays->y0 = hy;

		}
		if (display->pos->x > 0 && display->pos->x < WIDTH && display->rays->x0 > 0 && display->rays->x0 < WIDTH && display->pos->y > 0 && display->pos->y < HEIGHT && display->rays->y0 > 0 && display->rays->y0 < HEIGHT)
			draw_line_bresenham(display, display->pos->x, display->pos->y, display->rays->x0, display->rays->y0);
		display->rays->a += DR;
		if (display->rays->a < 0)
			display->rays->a += 2 * M_PI;
		if (display->rays->a > 0)
			display->rays->a -= 2 * M_PI;
	}
}

//find horizontal intersections
	if (ray->a > M_PI && ray->a <= M_PI * 2)
	{
		ray->y0 = ((int)(pos->y/mapS)) * mapS - 1;
		ray->y_off = -mapS;
		ray->x0 = pos->x + ((pos->y - ray->y0) * atan);
		ray->x_off = -(ray->y_off) * atan;
	}
	if (ray->a <= M_PI && ray->a >= 0)
	{
		ray->y0 = ((int)(pos->y/mapS)) * mapS + 64;
		ray->y_off = mapS;
		ray->x0 = pos->x + ((pos->y - ray->y0) * atan);
		ray->x_off = -(ray->y_off) * atan;
	}
	while (count < display->maps->max_y)
	{
		ray->y = (int) (ray->y0 / mapS);
		ray->x = (int) (ray->x0 / mapS);
		if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y && ray->x < display->maps->max_x && map[ray->y][ray->x] == '1')
			count = display->maps->max_y;
		else if (ray->y >= 0 && ray->x >= 0 && ray->y < display->maps->max_y && ray->x < display->maps->max_x)
		{
			ray->x0 = ray->x0 + ray->x_off;
			ray->y0 = ray->y0 + ray->y_off;
		}
		count++;
	}
	if (pos->x > 0 && pos->x < WIDTH && ray->x0 > 0 && ray->x0 < WIDTH - 1 && pos->y > 0 && pos->y < HEIGHT && ray->y0 > 0 && ray->y0 < HEIGHT)
			draw_line_bresenham(display, pos->x, pos->y, ray->x0, ray->y0);
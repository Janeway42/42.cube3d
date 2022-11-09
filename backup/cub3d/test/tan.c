#include <math.h>
#include <stdio.h>

typedef struct s_vector{
	double x;
	double y;
}				t_vector;

t_vector calc_ray_vector(double degree, double distance)
{
	t_vector ray;
	double radians;

	radians = (degree / 180.0) * M_PI;
	ray.x = cos(radians) * distance;
	ray.y = sin(radians) * distance;
	return ray;
}

int main(){

	t_vector test = calc_ray_vector(90, 25.0);
	printf("x: %f, y: %f\n",test.x, test.y);
	test = calc_ray_vector(150, 25);
	printf("x: %f, y: %f\n",test.x, test.y);
	test = calc_ray_vector(210, 25);
	printf("x: %f, y: %f\n",test.x, test.y);
	test = calc_ray_vector(330, 25);
	printf("x: %f, y: %f\n",test.x, test.y);
	return (0);
}
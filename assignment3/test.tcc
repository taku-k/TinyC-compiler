int fact(int x)
{
	int z;
	double a;
	z = 1;
	while (x >= 1) {
		z = z * x;
		x = x - 1;
	}
	return z;
}

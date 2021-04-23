#include <stdio.h>
#include <vector.h>

int main(int argc, char** argv)
{
	vector e = vector_new(int, 1);
	int x = 5;
	vector_push_back(int, e, x);
	x = 6;
    vector_push_back(int, e, x);

    size_t i;
    for (i = 0; i < vector_size(int, e); ++i)
        printf("e[%lu] = %d\n", i, vector_at_v(int, e, i));

	return 0;
}

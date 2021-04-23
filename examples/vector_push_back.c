#include <stdio.h>
#include <vector.h>

int main(int argc, char** argv)
{
	vector e = vector_new(int, 1);
	vector_push_back(int, e, 5);
    vector_push_back(int, e, 9);
	vector_push_back(int, e, 2);
	vector_push_back(int, e, 22);
	vector_push_back(int, e, 9);
	vector_push_back(int, e, 29);
	vector_push_back(int, e, 4);
	vector_push_back(int, e, 0);

	printf("size: %lu\ncapacity: %lu\n", vector_size(int, e), vector_capacity(int, e));

    size_t i;
    for (i = 0; i < vector_size(int, e); ++i)
    printf("e[%lu] = %d\n", i, vector_at_v(int, e, i));

	printf("vector front: %d\n", vector_front(int, e));
	printf("vector back: %d\n", vector_back(int, e));

	printf("empty: %s\n", vector_begin(int, e) == vector_end(int, e) ? "true" : "false");

	vector_clear(int, e);
	vector_delete(e);

	return 0;
}

#include <stdio.h>
#include <vector.h>

int main(int argc, char** argv)
{
    vector v = vector_new(int, 0);
    size_t s, i;

    printf("vector empty? %s\n\n", vector_empty(v) ? "yes" : "no");

    printf("Insert the size: ");
    scanf("%lu", &s);

    for (i = 0; i < s; ++i)
        vector_push_back(int, v, i + 1);

    for (i = 0; i < vector_size(int, v); ++i)
        printf("v[%lu] = %d\n", i, vector_at_v(int, v, i));

    vector_delete(v);

	return 0;
}

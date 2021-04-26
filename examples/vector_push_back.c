#include <stdio.h>
#include <vector.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char num[2048];
    char* end_ptr = NULL;

    vector v = vector_new(int, 0);
    size_t s, i;

    printf("vector empty? %s\n\n", vector_empty(v) ? "yes" : "no");

    printf("Insert the size: ");
    fgets(num, 2048, stdin);
    s = strtoull(num, end_ptr, 10);

    for (i = 0; i < s; ++i)
        vector_push_back(int, v, i + 1);

    for (i = 0; i < vector_size(int, v); ++i)
        printf("v[%llu] = %d\n", i, vector_at_v(int, v, i));

    vector_delete(v);

	return 0;
}

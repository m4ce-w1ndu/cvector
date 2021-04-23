#include <stdio.h>
#include <vector.h>

#define SIZE 4

struct vec2 {
    float x, y;
};

int main() {
    vector a = vector_new(int, SIZE);
    vector vec2vec = vector_new(struct vec2, SIZE);

    int i;

    for (i = 0; i < SIZE; ++i) {
        vector_at_v(int, a, i) = i + 1;
    }

    for (i = 0; i < SIZE; ++i) {
        struct vec2 ax = { .x = 0.5f, .y = 1.7f };
        vector_at_v(struct vec2, vec2vec, i) = ax;
    }

    for (i = 0; i < SIZE; ++i) {
        printf("vec2vec[%d] = { %.2f, %.2f }\n", i,
               vector_at_v(struct vec2, vec2vec, i).x,
               vector_at_v(struct vec2, vec2vec, i).y);
    }

    for (i = 0; i < SIZE; ++i) {
        printf("a[%d] = %d\n", i, vector_at_v(int, a, i));
    }

    printf("Vector capacity: %lu\n", vector_capacity(int, a));

    vector_delete(a);
    vector_delete(vec2vec);

    return 0;
}

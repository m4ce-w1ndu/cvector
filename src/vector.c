#include "include/vector.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* flow control functions */
static void failure(const char* message)
{
    fprintf(stderr, "Error: %s. Cause: %s\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

static bool is_null(const void* ptr)
{
    return (NULL == ptr);
}

static size_t alloc(size_t s)
{
    return (size_t) pow(2, ceil(log2((double) s)));
}

/* vector struct */
struct v_type {
    size_t s;
    size_t c;
    void* data;
};

vector gv_alloc(size_t new_cap)
{
    struct v_type* new = (struct v_type*) malloc(sizeof(struct v_type));

    if (is_null(new))
        failure("Base structure allocation failure");
    new->data = malloc(new_cap);

    if (is_null(new->data))
        failure("Data buffer allocation failure");

    new->c = new_cap;
    new->s = 0;

    return new;
}

void gv_free(struct v_type* vector)
{
    free(vector->data);
    free(vector);
}

void* gv_at(struct v_type* vector, size_t pos)
{
    if (!is_null(vector) && !is_null(vector->data))
        return (void*)((char*)vector->data) + pos;
    return NULL;
}

void gv_pb(struct v_type* vector, size_t s, void* e)
{
	if (!is_null(vector) && !is_null(vector->data)) {
		if (vector->s + s >= vector->c) {
			vector->c = alloc(vector->c + s);
			vector->data = realloc(vector->data, vector->c);
		}
		vector->s += s;
        memcpy(vector->data + vector->s - s, e, s);
	}
}

void gv_pop(struct v_type* vector, size_t s)
{
	if (!is_null(vector) && !is_null(vector->data) && vector->s > 0)
	    vector->s -= s;
}

void gv_clr(struct v_type* vector, size_t s)
{
    if (is_null(vector) || vector->s == 0) return;
    memset(vector->data, vector->s / s, s);
    vector->s = 0;
}

size_t gv_size(struct v_type* vector)
{
    if (!is_null(vector) && !is_null(vector->data))
        return vector->s;
    return 0;
}

size_t gv_capacity(struct v_type* vector)
{
    if (!is_null(vector) && !is_null(vector->data))
        return vector->c;
    return 0;
}

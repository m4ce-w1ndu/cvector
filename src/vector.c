#include <vector.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*!
 * \file
 * \brief cvector - c99 vector implementation file. This file contains the
 * real library implementation code, referencing the inteface described in
 * vector.h. This implementation makes use of pointer casting in order to
 * obtain a type agnostic container behaviour, which is then handled by the
 * use of functional macros, which are leveraging all the casting and file
 * preparation.
 */

/*!
 * \brief If a failure is detected, the function is called with a message
 * parameter. failure(const char* message) will print the error message
 * followed by a possible cause extracted by comparing errno. The function
 * is static, which makes it available only to this compilation unit.
 * \param message a const char* string containing the error message.
 */
static void failure(const char* message)
{
    fprintf(stderr, "Error: %s. Cause: %s\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

/*!
 * \brief checks if a pointer of any type is null, returning true if the
 * value corresponds to a NULL pointer or false otherwise. This function
 * uses a property of C pointers, which are implicitly convertible into
 * void*, without requiring explicit casts. If there is a need to compile
 * this library in C++, it must be included into an "extern C" block.
 * \param ptr a pointer of any type.
 */
static bool is_null(const void* ptr)
{
    return (NULL == ptr);
}

static size_type alloc(size_type s)
{
    --s;
    s |= s >> 1;
    s |= s >> 2;
    s |= s >> 4;
    s |= s >> 8;
    s |= s >> 16;
    s |= s >> 32;
    ++s;
    return s;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

struct v_type {
    size_type s;
    size_type c;
    void* data;
};

#endif

vector gv_alloc(size_type new_cap)
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

void vector_delete(struct v_type* vector)
{
    free(vector->data);
    free(vector);
}

void* gv_at(struct v_type* vector, size_type pos)
{
    if (!is_null(vector) && !is_null(vector->data))
        return (void*)((char*)vector->data + pos);
    return NULL;
}

void gv_pb(struct v_type* vector, size_type s, void* e)
{
	if (!is_null(vector) && !is_null(vector->data)) {
		if (vector->s + s >= vector->c) {
			vector->c = alloc(vector->c + s);
			vector->data = realloc(vector->data, vector->c);
            if (is_null(vector->data)) failure("Allocation failure");
		}
		vector->s += s;
        memcpy((void*)((char*)vector->data + vector->s - s), e, s);
	}
}

void gv_pop(struct v_type* vector, size_type s)
{
	if (!is_null(vector) && !is_null(vector->data) && vector->s > 0)
	    vector->s -= s;
}

void gv_erase(struct v_type* vector, size_type esz, size_type pos)
{
    if (is_null(vector)) return;
    if (pos * esz >= vector->s) return;
    /* Real position */
    pos *= esz;
    /* Next position */
    size_type next_pos = pos + esz;
    /* using memmove to shift content */
    memmove(vector->data + pos, vector->data + next_pos, vector->s);
    /* decreasing size */
    vector->s -= esz;
}

void gv_clr(struct v_type* vector, size_type s)
{
    if (is_null(vector) || vector->s == 0) return;
    memset(vector->data, 0, vector->s * s);
    vector->s = 0;
}

void gv_rsv(struct v_type* vector, size_type s)
{
    if (is_null(vector)) return;
    vector->data = realloc(vector->data, s);
    if (is_null(vector->data)) failure("Allocation failure");
    vector->c = s;
}

void gv_rsz(struct v_type* vector, size_type s)
{
    if (is_null(vector)) return;
    if (vector->s >= s) vector->s = s;
    else gv_rsv(vector, s);
}

void vector_shrink_to_fit(struct v_type* vector)
{
    if (is_null(vector)) return;
    vector->c = vector->s;
    vector->data = realloc(vector->data, vector->c);
    if (is_null(vector->data)) failure("Allocation failure");
}

size_type gv_size(struct v_type* vector)
{
    if (!is_null(vector) && !is_null(vector->data))
        return vector->s;
    return 0;
}

size_type gv_capacity(struct v_type* vector)
{
    if (!is_null(vector) && !is_null(vector->data))
        return vector->c;
    return 0;
}

size_type vector_max_size()
{
    return INT64_MAX;
}

bool vector_empty(struct v_type* vector)
{
    return (is_null(vector) || is_null(vector->data)
            || vector->s == 0 || vector->c == 0);
}

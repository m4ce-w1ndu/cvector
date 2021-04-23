#ifndef CVECTOR_VECTOR_H
#define CVECTOR_VECTOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* vector struct forward declaration */
typedef struct v_type* vector;

/* size type */
typedef uint64_t size_type;

vector gv_alloc(size_type new_cap);
void gv_free(struct v_type* vector);
void* gv_at(struct v_type* vector, size_type pos);
size_type gv_size(struct v_type* vector);
size_type gv_capacity(struct v_type* vector);
bool vector_empty(struct v_type* vector);
void gv_pb(struct v_type* vector, size_type s, void* e);
void gv_pop(struct v_type* vector, size_type s);
void gv_clr(struct v_type* vector, size_type s);
void gv_rsv(struct v_type* vector, size_type s);
void gv_rsz(struct v_type* vector, size_type s);
void vector_shrink_to_fit(struct v_type* vector);

#define vector_new(type, size) gv_alloc(sizeof(type) * (size))

#define vector_delete(vector) gv_free(vector)

#define vector_at_v(type, vector, pos) \
    (*(type*)gv_at(vector, sizeof(type) * (pos)))

#define vector_at_p(type, vector, pos) \
    (type*)gv_at(vector, sizeof(type) * (pos))

#define vector_size(type, vector) \
    gv_size(vector) / sizeof(type)

#define vector_capacity(type, vector) \
    gv_capacity(vector) / sizeof(type)

#define vector_push_back(type, vector, e) \
	{ type x = e; gv_pb(vector, sizeof(type), &(x)); }

#define vector_pop_back(type, vector) \
	gv_pop(vector, sizeof(type))

#define vector_front(type, vector) \
    (*(type*)gv_at(vector, 0))

#define vector_back(type, vector) \
    (*(type*)gv_at(vector, sizeof(type) * (vector_size(type, vector) - 1)))

#define vector_begin(type, vector) \
    (type*)gv_at(vector, 0)

#define vector_end(type, vector) \
    (type*)gv_at(vector, sizeof(type) * vector_size(type, vector))

#define vector_data(type, vector) \
    (type*)gv_at(vector, 0)

#define vector_clear(type, vector) \
    gv_clr(vector, sizeof(type))

#define vector_resize(type, vector, size) \
    gv_rsz(vector, sizeof(type) * (size))

#define vector_reserve(type, vector, new_cap) \
    gv_rsv(vector, sizeof(type) * (size))

#endif //CVECTOR_VECTOR_H

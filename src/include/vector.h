#ifndef CVECTOR_VECTOR_H
#define CVECTOR_VECTOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* vector struct forward declaration */
typedef struct v_type* vector;

vector gv_alloc(size_t new_cap);
void gv_free(struct v_type* vector);
void* gv_at(struct v_type* vector, size_t pos);
size_t gv_size(struct v_type* vector);
size_t gv_capacity(struct v_type* vector);
void gv_pb(struct v_type* vector, size_t s, void* e);
void gv_pop(struct v_type* vector, size_t s);
void gv_clr(struct v_type* vector, size_t s);

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


#endif //CVECTOR_VECTOR_H

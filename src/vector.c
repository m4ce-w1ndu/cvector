#include <vector.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*!
\brief at most 256 characters can bee used as an error message buffer 
*/
#define ERR_BUF_LEN 256

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
#define FAILURE(message) \
{ \
	char err_buffer[ERR_BUF_LEN]; \
	strerror_s(err_buffer, ERR_BUF_LEN, errno); \
	fprintf(stderr, "Error: %s. Cause: %s\n", (message), err_buffer); \
	exit(EXIT_FAILURE); \
}

 /*!
  * \brief disables MSVC warnings to quiet down compilation. 
  * This is not advised if you don't know what you are doing.
  */
#ifdef _MSC_VER
#pragma warning (disable: 6011 6308 6387)
#endif

/*!
 * \brief Computes the size of the next vector allocation.
 * \param size current size of the vector
 * \return new size of the vector
 */
inline static size_type alloc(size_type size)
{
	--size;
#if SIZE_MAX == UINT64_MAX || SIZE_MAX == UINT32_MAX
	size |= size >> 1;
	size |= size >> 2;
	size |= size >> 4;
	size |= size >> 8;
	size |= size >> 16;
#endif

#if SIZE_MAX == UINT64_MAX
	size |= size >> 32;
#endif

	++size;
	return size;
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

	if (NULL == new)
		FAILURE("Base structure allocation failure");
	new->data = malloc(new_cap);

	if (NULL == new->data)
		FAILURE("Data buffer allocation failure");

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
	if (NULL != vector && NULL != vector->data)
		return (void*)((char*)vector->data + pos);
	return NULL;
}

void gv_pb(struct v_type* vector, size_type s, void* e)
{
	if (NULL != vector && NULL != vector->data) {
		if (vector->s + s >= vector->c) {
			vector->c = alloc(vector->c + s);
			vector->data = realloc(vector->data, vector->c);
			if (NULL == vector->data) FAILURE("Allocation failure");
		}
		vector->s += s;
		memcpy((void*)((char*)vector->data + vector->s - s), e, s);
	}
}

void gv_pop(struct v_type* vector, size_type s)
{
	if (NULL != vector && NULL != vector->data && vector->s > 0)
		vector->s -= s;
}

void gv_erase(struct v_type* vector, size_type esz, size_type pos)
{
	if (NULL == vector) return;
	if (pos * esz >= vector->s) return;
	/* Real position */
	pos *= esz;
	/* Next position */
	size_type next_pos = pos + esz;
	/* using memmove to shift content */
	memmove(((char*)vector->data + pos), ((char*)vector->data + next_pos), vector->s);
	/* decreasing size */
	vector->s -= esz;
}

void gv_clr(struct v_type* vector, size_type s)
{
	if (NULL == vector || vector->s == 0) return;
	memset(vector->data, 0, vector->s * s);
	vector->s = 0;
}

void gv_rsv(struct v_type* vector, size_type s)
{
	if (NULL == vector) return;
	vector->data = realloc(vector->data, s);
	if (NULL == vector->data) FAILURE("Allocation failure");
	vector->c = s;
}

void gv_rsz(struct v_type* vector, size_type s)
{
	if (NULL == vector) return;
	if (vector->s >= s) vector->s = s;
	else gv_rsv(vector, s);
}

void vector_shrink_to_fit(struct v_type* vector)
{
	if (NULL == vector) return;
	vector->c = vector->s;
	vector->data = realloc(vector->data, vector->c);
	if (NULL == vector->data) FAILURE("Allocation failure");
}

size_type gv_size(struct v_type* vector)
{
	if (NULL != vector && NULL != vector->data)
		return vector->s;
	return 0;
}

size_type gv_capacity(struct v_type* vector)
{
	if (NULL != vector && NULL != vector->data)
		return vector->c;
	return 0;
}

size_type vector_max_size()
{
	return INT64_MAX;
}

bool vector_empty(struct v_type* vector)
{
	return (NULL == vector || NULL == vector->data ||
			vector->s == 0 || vector->c == 0);
}

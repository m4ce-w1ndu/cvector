#ifndef CVECTOR_VECTOR_H
#define CVECTOR_VECTOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*!
 * \file
 * \brief This file provides a comprehensive, easy-to-use interface for
 * a vector-style type agnostic container written in C99. The inteface
 * makes use of functional macros in order to simplify the use of the
 * library itself.
 * \author Simone Rolando
 */

/*!
 * \brief Vector object representation.
 * \a struct v_type*
 */
typedef struct v_type* vector;

/*!
 * \brief vector size type. A 64-bit unsigned integer.
 * \a uint64_t
 */
typedef uint64_t size_type;

/*!
 * \brief Generic vector allocator. Creates a new generic vector
 * object. The new capacity must be specified in bytes.
 * \param new_cap start capacity of vector in bytes.
 * \return new vector object pointer.
 */
vector gv_alloc(size_type new_cap);

/*!
 * \brief Vector deletion function. Deletes the given vector
 * object, freeing its previously used memory.
 * \param vector pointer to a vector object.
 */
void vector_delete(struct v_type* vector);

/*!
 * \brief Generic vector at. Returns a pointer to the object
 * at the given index.
 * \param vector vector object pointer.
 * \param pos vector index.
 * \return a pointer of type \a void* to the object in the vector.
 */
void* gv_at(struct v_type* vector, size_type pos);

/*!
 * \brief Generic vector size. Returns the size in bytes of a
 * given vector object.
 * \param vector vector object pointer.
 * \return 64-bit unsigned integer value containing the size in
 * bytes occupied by the populated elements in the vector.
 */
size_type gv_size(struct v_type* vector);

/*!
 * \brief Generic vector capacity. Returns the size in bytes
 * occupied by the given vector object's data buffer.
 * \param vector vector object pointer.
 * \return 64-bit unsigned integer value containing the size in
 * bytes occupied by the vector's data buffer.
 */
size_type gv_capacity(struct v_type* vector);

/*!
 * \brief Vector max size. Returns the maximum available memory
 * size that a vector object can occupy.
 * \return 64-bit unsigned integer value containing the maximum
 * available size for a vector object.
 */
size_type vector_max_size();

/*!
 * \brief Returns true if the vector is empty, false otherwise.
 * \param vector vector object pointer.
 * \return boolean value indicating the status of the vector.
 */
bool vector_empty(struct v_type* vector);

/*!
 * \brief Adds an element of generic type to the end of the vector.
 * \param vector vector object pointer.
 * \param s new element size.
 * \param e pointer to the new element.
 */
void gv_pb(struct v_type* vector, size_type s, void* e);

/*!
 * \brief Removes an element of generic type from the end of the
 * vector.
 * \param vector vector object pointer.
 * \param s size of the element to remove.
 */
void gv_pop(struct v_type* vector, size_type s);

/*!
 * \brief Clears the vector initializing its data buffer to 0
 * and resetting its size.
 * \param vector vector object pointer.
 * \param s size of the vector in bytes.
 */
void gv_clr(struct v_type* vector, size_type s);

/*!
 * \brief Generic vector reserve. Allocates memory for n bytes.
 * \param vector vector object pointer.
 * \param s number of bytes to allocate.
 */
void gv_rsv(struct v_type* vector, size_type s);

/*!
 * \brief Resizes a generic vector object to the new given size.
 * \param vector vector object pointer.
 * \param s number of bytes to resize the vector.
 */
void gv_rsz(struct v_type* vector, size_type s);

/*!
 * \brief Shrinks the vector capacity to its current number of elements,
 * freeing up unused memory.
 * \param vector vector object pointer.
 */
void vector_shrink_to_fit(struct v_type* vector);

/*!
 * \brief Removes an element of the vector given its position
 * in the underlying byte container.
 * \param vector vector object pointer.
 * \param size size of object to delete.
 * \param pos position in bytes inside vector.
 */
void gv_erase(struct v_type* vector, size_t size, size_t pos);

/*!
 * \def vector_new(type, size)
 * Creates a new vector object of the given type and size.
 */
#define vector_new(type, size) gv_alloc(sizeof(type) * (size))

/*!
 * \brief Returns the value at the given position of a non-empty
 * vector object.
 * \def vector_at_v(type, vector, pos)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \param pos vector element index.
 * \return the corresponding value at index \a pos.
 */
#define vector_at_v(type, vector, pos) \
    (*(type*)gv_at(vector, sizeof(type) * (pos)))

/*!
 * \brief Returns a pointer to the given position of a non-empty
 * vector object.
 * \def vector_at_p(type, vector, pos)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \param pos vector element index.
 * \return a pointer to the value at index \a pos.
 */
#define vector_at_p(type, vector, pos) \
    (type*)gv_at(vector, sizeof(type) * (pos))

/*!
 * \brief Returns the size of the given vector object.
 * \def vector_size(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return size of the vector (number of populated elements).
 */
#define vector_size(type, vector) \
    gv_size(vector) / sizeof(type)

/*!
 * \brief Returns the capacity of the given vector.
 * \def vector_capacity(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return capacity of the vector (number of allocated elements).
 */
#define vector_capacity(type, vector) \
    gv_capacity(vector) / sizeof(type)

/*!
 * \brief Adds an element to the end of the vector.
 * \def vector_push_back(type, vector, e)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \param e element to add to the vector.
 */
#define vector_push_back(type, vector, e) \
	{ type x = e; gv_pb(vector, sizeof(type), &(x)); }

/*!
 * \brief Removes an element from the end of the vector.
 * \def vector_pop_back(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 */
#define vector_pop_back(type, vector) \
	gv_pop(vector, sizeof(type))

/*!
 * \brief Returns the value of the first element of a non-empty
 * vector.
 * \def vector_front(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return a value of type \a type corresponding to the first element.
 */
#define vector_front(type, vector) \
    (*(type*)gv_at(vector, 0))

/*!
 * \brief Returns the value of the last element of a non-empty
 * vector.
 * \def vector_back(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return a value of type \a type corresponding to the last element.
 */
#define vector_back(type, vector) \
    (*(type*)gv_at(vector, sizeof(type) * (vector_size(type, vector) - 1)))

/*!
 * \brief Returns a pointer to the first element of a vector.
 * \def vector_begin(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return a pointer of type \a type* to the first element.
 */
#define vector_begin(type, vector) \
    (type*)gv_at(vector, 0)

/*!
 * \brief Returns a pointer to the last element of a vector.
 * \def vector_end(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return a pointer of type \a type* to the last element.
 */
#define vector_end(type, vector) \
    (type*)gv_at(vector, sizeof(type) * vector_size(type, vector))

/*!
 * \brief Returns a pointer to the underlying data buffer.
 * \def vector_data(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \return a pointer of type \type* to the underlying buffer.
 */
#define vector_data(type, vector) \
    (type*)gv_at(vector, 0)

/*!
 * \brief Clears the vector, resetting its content and size.
 * \def vector_clear(type, vector)
 * \param type vector data type.
 * \param vector vector object pointer.
 */
#define vector_clear(type, vector) \
    gv_clr(vector, sizeof(type))

/*!
 * \brief Resizes the vector to the new given size, changing
 * its memory print if necessary.
 * \def vector_resize(type, vector, size)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \param size new vector size.
 */
#define vector_resize(type, vector, size) \
    gv_rsz(vector, sizeof(type) * (size))

/*!
 * \brief Reserves memory for the number of given elements.
 * \def vector_reserve(type, vector, new_cap)
 * \param type vector data type.
 * \param vector vector object pointer.
 * \param new_cap new vector capacity.
 */
#define vector_reserve(type, vector, new_cap) \
    gv_rsv(vector, sizeof(type) * (size))

#endif //CVECTOR_VECTOR_H

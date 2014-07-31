/*
 * @summary: box2d assert
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef B2ASSERT_H_
#define B2ASSERT_H_


#undef b2Assert
#define b2Assert(e) ((e) ? (void)0: _b2_assert(#e, __FILE__, __LINE__))


void _b2_assert(const char* arg1, const char* arg2, int lineno);


#endif /* B2ASSERT_H_ */

/*

MIT License

Copyright (c) 2016 Guenter Prossliner

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef COBJ_PP_H
#define COBJ_PP_H

//////////////////////////////////////////////////////////////////////////
// COBJPVT_ASSERT: provides assertions to guide the user about things going wrong
#define COBJPVT_ASSERT(P_CONDTION, P_MESSAGE) typedef char COBJPVT_ASSERT_##MSG[(P_CONDTION)?1:-1]
#define COBJPVT_ERROR(P_MESSAGE) COBJPVT_ASSERT(0, P_MESSAGE)

//////////////////////////////////////////////////////////////////////////
// COBJPVT_PP_STRINGIFY: #s with previous arg expansion
#define COBJPVT_PP_STRINGIFYHLP(s)				#s
#define COBJPVT_PP_STRINGIFY(s)					COBJPVT_PP_STRINGIFYHLP(s)

//////////////////////////////////////////////////////////////////////////
// COBJ_PP_CONCAT
//	Concatenates up to 8 tokens
#define COBJPVT_PP_CONCAT_BASE_HLP(x, y) x ## y
#define COBJPVT_PP_CONCAT_BASE(x, y) COBJPVT_PP_CONCAT_BASE_HLP(x, y)

#define COBJ_PP_CONCAT(...)	\
	COBJPVT_PP_CONCAT_BASE(COBJPVT_PP_CONCATHLP_, COBJPVT_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
	

#define COBJPVT_PP_CONCATHLP_8(a,b,c,d,e,f,g,h)	a##b##c##d##e##f##g##h
#define COBJPVT_PP_CONCATHLP_7(a,b,c,d,e,f,g)	a##b##c##d##e##f##g
#define COBJPVT_PP_CONCATHLP_6(a,b,c,d,e,f)	a##b##c##d##e##f
#define COBJPVT_PP_CONCATHLP_5(a,b,c,d,e)	a##b##c##d##e
#define COBJPVT_PP_CONCATHLP_4(a,b,c,d)	a##b##c##d
#define COBJPVT_PP_CONCATHLP_3(a,b,c)	a##b##c
#define COBJPVT_PP_CONCATHLP_2(a,b)	a##b

////////////////////////////////
// COBJPVT_PP_NARG
// Thanks to Mehrwolf (http://stackoverflow.com/questions/11317474/macro-to-count-number-of-arguments/11742317#11742317)
////////////////////////////////

#define COBJPVT_PP_ARG_N( \
	_1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10,	\
	_11, _12, _13, _14, _15, _16, _17, _18, _19, _20,	\
	_21, _22, _23, _24, _25, _26, _27, _28, _29, _30,	\
	_31, _32, _33, _34, _35, _36, _37, _38, _39, _40,	\
	_41, _42, _43, _44, _45, _46, _47, _48, _49, _50,	\
	_51, _52, _53, _54, _55, _56, _57, _58, _59, _60,	\
	_61, _62, _63, N, ...) N

#define COBJPVT_PP_RSEQ_N()								\
	63, 62, 61, 60,										\
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50,				\
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40,				\
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30,				\
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20,				\
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10,				\
	9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define COBJPVT_PP_NARG_(...)							\
	COBJPVT_PP_ARG_N(__VA_ARGS__)

#define COBJPVT_PP_COMMASEQ_N()							\
	1,  1,  1,  1,										\
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,				\
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,				\
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,				\
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,				\
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,				\
	1,  1,  1,  1,  1,  1,  1,  1,  0,  0

#define COBJPVT_PP_COMMA()    ,

#define COBJPVT_PP_HASCOMMA(...)                         \
	COBJPVT_PP_NARG_(__VA_ARGS__, COBJPVT_PP_COMMASEQ_N())

#define COBJPVT_PP_NARG(...)                             \
	COBJPVT_PP_NARG_HELPER1(                             \
	COBJPVT_PP_HASCOMMA(__VA_ARGS__),                    \
	COBJPVT_PP_HASCOMMA(COBJPVT_PP_COMMA __VA_ARGS__ ()), \
	COBJPVT_PP_NARG_(__VA_ARGS__, COBJPVT_PP_RSEQ_N()))

#define COBJPVT_PP_NARG_HELPER1(a, b, N)    COBJPVT_PP_NARG_HELPER2(a, b, N)
#define COBJPVT_PP_NARG_HELPER2(a, b, N)    COBJPVT_PP_NARG_HELPER3_ ## a ## b(N)
#define COBJPVT_PP_NARG_HELPER3_01(N)    0
#define COBJPVT_PP_NARG_HELPER3_00(N)    1
#define COBJPVT_PP_NARG_HELPER3_11(N)    N




#endif /* COBJ_PP_H */
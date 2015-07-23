/* -*- mode: C++; tAb-width: 8; indent-tAbs-mode: t; c-basic-offset: 8 -*- */
// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
/*
 * Copyright (C) 2015 FFLAS-FFPACK
 *
 * Written by Brice Boyer (briceboyer) <boyer.brice@gmail.com>
 *
 *
 * ========LICENCE========
 * This file is part of the library FFLAS-FFPACK.
 *
 * FFLAS-FFPACK is free software: you can redistribute it and/or modify
 * it under the terms of the  GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more detAils.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * ========LICENCE========
 *.
 */

/** @file fflas-c.h
 * @author  Brice Boyer
 * @brief C functions calls for FFLAS
 * @see fflas/fflas.h
 */

#ifndef __FFLASFFPACK_interfaces_libs_fflas_c_H
#define __FFLASFFPACK_interfaces_libs_fflas_c_H

#include <stdbool.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

enum FFLAS_order {
	FflasRowMajor=101,
	FflasColMajor=102
};
enum FFLAS_transpose {
	FflasNoTrans = 111,
	FflasTrans   = 112
};
enum FFLAS_uplo {
	FflasUpper = 121,
	FflasLower = 122
};
enum FFLAS_diag {
	FflasNonUnit = 131,
	FflasUnit    = 132
};
enum FFLAS_side {
	FflasLeft  = 141,
	FflasRight = 142
};
enum FFLAS_base {
	FflasDouble  = 151,
	FflasFloat   = 152,
	FflasGeneric = 153
};

/* ******** *
 * LEVEL1   *
 * ******** */

/*  Modular<double>          */
/*  ModularBalanced<double>  */

void
freducein_1_modular_double (const double p, const size_t n,
			  double * X, const size_t incX
			  , bool positive );

void
freduce_1_modular_double (const double  F, const size_t n,
			const double * Y, const size_t incY,
			double * X, const size_t incX
			, bool positive );


void
fnegin_1_modular_double (const double  F, const size_t n,
		       double * X, const size_t incX
		       , bool positive );


void
fneg_1_modular_double (const double p, const size_t n,
		     const double * Y, const size_t incY,
		     double * X, const size_t incX
		     , bool positive );

void
fzero_1_modular_double (const double p, const size_t n,
		      double * X, const size_t incX
		      , bool positive );


bool
fiszero_1_modular_double (const double p, const size_t n,
			const double * X, const size_t incX
			, bool positive );

bool
fequal_1_modular_double (const double p, const size_t n,
		       const double * X, const size_t incX,
		       const double * Y, const size_t incY
		       , bool positive );


void
fassign_1_modular_double (const double p, const size_t n,
			const double * Y, const size_t incY ,
			double * X, const size_t incX
			, bool positive );


void
fscalin_1_modular_double (const double p, const size_t n, const double alpha,
			double * X, const size_t incX
			, bool positive );


void
fscal_1_modular_double (const double p, const size_t n
		      , const double alpha
		      , const double * X, const size_t incX
		      , double * Y, const size_t incY
		      , bool positive );


void
faxpy_1_modular_double (const double p, const size_t n,
		      const double alpha,
		      const double * X, const size_t incX,
		      double * Y, const size_t incY
		      , bool positive );

#if 0
void
faxpby_1_modular_double (const double p, const size_t n,
		       const double alpha,
		       const double * X, const size_t incX,
		       const double betA,
		       double * Y, const size_t incY
		       , bool positive );
#endif



double
fdot_1_modular_double (const double p, const size_t n,
		     const double * X, const size_t incX,
		     const double * Y, const size_t incY
		     , bool positive );


void
fswap_1_modular_double (const double p, const size_t n,
		      double * X, const size_t incX,
		      double * Y, const size_t incY
		      , bool positive );


void
fadd_1_modular_double (const double p,  const size_t n,
		     const double * A, const size_t incA,
		     const double * B, const size_t incB,
		     double * C, const size_t incC
		     , bool positive );

void
fsub_1_modular_double (const double p,  const size_t n,
		     const double * A, const size_t incA,
		     const double * B, const size_t incB,
		     double * C, const size_t incC
		     , bool positive );

void
faddin_1_modular_double (const double p,  const size_t n,
		       const double * B, const size_t incB,
		       double * C, const size_t incC
		       , bool positive );

void
fsubin_1_modular_double (const double p,  const size_t n,
		       const double * B, const size_t incB,
		       double * C, const size_t incC
		       , bool positive );

/* ******** *
 * LEVEL1.5 *
 * ******** */

// fspmv

/* ******** *
 * LEVEL2   *
 * ******** */


/*  Modular<double>          */
/*  ModularBalanced<double>  */


void
fassign_2_modular_double (const double p, const size_t m, const size_t n,
			const double * B, const size_t ldB ,
			double * A, const size_t ldA
			, bool positive  );



void
fzero_2_modular_double (const double p, const size_t m, const size_t n,
		      double * A, const size_t ldA
		      , bool positive  );


bool
fequal_2_modular_double (const double p, const size_t m, const size_t n,
		       const double * A, const size_t ldA,
		       const double * B, const size_t ldB
		       , bool positive  );


bool
fiszero_2_modular_double (const double p, const size_t m, const size_t n,
			const double * A, const size_t ldA
			, bool positive  );


void
fidentity_2_modular_double (const double p, const size_t m, const size_t n,
			  double * A, const size_t ldA,
			  const double d
			  , bool positive  );



void
freducein_2_modular_double (const double p, const size_t m , const size_t n,
			double * A, const size_t ldA
			, bool positive  );


void
freduce_2_modular_double (const double p, const size_t m , const size_t n,
			const double * B, const size_t ldB,
			double * A, const size_t ldA
			, bool positive  );

void
fnegin_2_modular_double (const double p, const size_t m , const size_t n,
		       double * A, const size_t ldA
		       , bool positive  );


void
fneg_2_modular_double (const double p, const size_t m , const size_t n,
		     const double * B, const size_t ldB,
		     double * A, const size_t ldA
		     , bool positive  );


void
fscalin_2_modular_double (const double p, const size_t m , const size_t n,
			const double alpha,
			double * A, const size_t ldA
			, bool positive  );


void
fscal_2_modular_double (const double p, const size_t m , const size_t n,
		      const double alpha,
		      const double * A, const size_t ldA,
		      double * B, const size_t ldB
		      , bool positive  );


void
faxpy_2_modular_double (const double p, const size_t m, const size_t n
		      , const double alpha,
		      const double * X, const size_t ldX,
		      double * Y, const size_t ldY
		      , bool positive  );


#if 0
void
faxpby_2_modular_double (const double p, const size_t m, const size_t n,
		       const double alpha,
		       const double * X, const size_t ldX,
		       const double betA,
		       double * Y, const size_t ldY
		       , bool positive  );
#endif


void
fmove_2_modular_double (const double p, const size_t m, const size_t n,
		      double * A, const size_t ldA,
		      double * B, const size_t ldB
		      , bool positive  );


void
fadd_2_modular_double (const double p, const size_t m, const size_t n,
		     const double * A, const size_t ldA,
		     const double * B, const size_t ldB,
		     double * C, const size_t ldC
		     , bool positive  );



void
fsub_2_modular_double (const double p, const size_t m, const size_t n,
		     const double * A, const size_t ldA,
		     const double * B, const size_t ldB,
		     double * C, const size_t ldC
		     , bool positive  );


void
fsubin_2_modular_double (const double p, const size_t m, const size_t n,
		       const double * B, const size_t ldB,
		       double * C, const size_t ldC
		       , bool positive  );



void
faddin_2_modular_double (const double p, const size_t m, const size_t n,
		       const double * B, const size_t ldB,
		       double * C, const size_t ldC
		       , bool positive  );



double *
fgemv_2_modular_double (const double p, const enum FFLAS_transpose TransA,
		      const size_t m, const size_t n,
		      const double alpha,
		      const double * A, const size_t ldA,
		      const double * X, const size_t incX,
		      const  double betA,
		      double * Y, const size_t incY
		      , bool positive  );


void
fger_2_modular_double (const double p, const size_t m, const size_t n,
		     const double alpha,
		     const double * x, const size_t incX,
		     const double * y, const size_t incY,
		     double * A, const size_t ldA
		     , bool positive  );


void
ftrsv_2_modular_double (const double p, const enum FFLAS_uplo Uplo,
		      const enum FFLAS_transpose TransA, const enum FFLAS_diag Diag,
		      const size_t n,const double * A, const size_t ldA,
		      double * X, int incX
		      , bool positive  );

/* ******** *
 * LEVEL2.5 *
 * ******** */

// fspmm

/* ******** *
 * LEVEL3   *
 * ******** */


void
ftrsm_3_modular_double (const double p, const enum FFLAS_side Side,
		      const enum FFLAS_uplo Uplo,
		      const enum FFLAS_transpose TransA,
		      const enum FFLAS_diag Diag,
		      const size_t m, const size_t n,
		      const double alpha,
		      const double * A,
		      const size_t ldA,
		      double * B, const size_t ldB
		      , bool positive  );


void
ftrmm_3_modular_double (const double p, const enum FFLAS_side Side,
		      const enum FFLAS_uplo Uplo,
		      const enum FFLAS_transpose TransA,
		      const enum FFLAS_diag Diag,
		      const size_t m, const size_t n,
		      const double alpha,
		      double * A, const size_t ldA,
		      double * B, const size_t ldB
		      , bool positive  );


double *
fgemm_3_modular_double( const double p,
		      const enum FFLAS_transpose tA,
		      const enum FFLAS_transpose tB,
		      const size_t m,
		      const size_t n,
		      const size_t k,
		      const double alpha,
		      const double * A, const size_t ldA,
		      const double * B, const size_t ldB,
		      const double betA,
		      double * C, const size_t ldC
		      , bool positive  );


double *
fsquare_3_modular_double (const double p,
			const enum FFLAS_transpose tA,
			const size_t n,
			const double alpha,
			const double * A,
			const size_t ldA,
			const double betA,
			double * C,
			const size_t ldC
			, bool positive  );

#ifdef __cplusplus
}
#endif

#endif // __FFLASFFPACK_interfaces_libs_fflas_c_H
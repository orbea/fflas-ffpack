/* -*- mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
/*
 * Copyright (C) 2014 the FFLAS-FFPACK group
 *
 * Written by   Bastien Vialla <bastien.vialla@lirmm.fr>
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
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 * ========LICENCE========
 *.
 */

#ifndef __FFLASFFPACK_fflas_sparse_ELL_spmm_INL
#define __FFLASFFPACK_fflas_sparse_ELL_spmm_INL

namespace FFLAS {
namespace sparse_details_impl {

// template <class Field>
// inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
//                   typename Field::ConstElement_ptr x, typename Field::Element_ptr y, FieldCategories::GenericTag) {
//     for (index_t i = 0; i < A.m; ++i) {
//         for (index_t j = 0; j < A.ld; ++j) {
//             int k = 0;
//             for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
//                 F.axpyin(y[i * blockSize + k], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * blockSize + k]);
//                 F.axpyin(y[i * blockSize + k + 1], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * blockSize + k + 1]);
//                 F.axpyin(y[i * blockSize + k + 2], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * blockSize + k + 2]);
//                 F.axpyin(y[i * blockSize + k + 3], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * blockSize + k + 3]);
//             }
//             for (; k < blockSize; ++k)
//                 F.axpyin(y[i * blockSize + k], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * blockSize + k]);
//         }
//     }
// }

template <class Field>
inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy,
                  FieldCategories::GenericTag) {
    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                F.axpyin(y[i * ldy + k], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * ldx + k]);
                F.axpyin(y[i * ldy + k + 1], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * ldx + k + 1]);
                F.axpyin(y[i * ldy + k + 2], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * ldx + k + 2]);
                F.axpyin(y[i * ldy + k + 3], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * ldx + k + 3]);
            }
            for (; k < blockSize; ++k)
                F.axpyin(y[i * ldy + k], A.dat[i * A.ld + j], x[A.col[i * A.ld + j] * ldx + k]);
        }
    }
}

// template <class Field>
// inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
//                   typename Field::ConstElement_ptr x, typename Field::Element_ptr y, FieldCategories::UnparametricTag) {
//     for (index_t i = 0; i < A.m; ++i) {
//         for (index_t j = 0; j < A.ld; ++j) {
//             int k = 0;
//             for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
//                 y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//                 y[i * blockSize + k + 1] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 1];
//                 y[i * blockSize + k + 2] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 2];
//                 y[i * blockSize + k + 3] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 3];
//             }
//             for (; k < blockSize; ++k)
//                 y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//         }
//     }
// }

template <class Field>
inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy,
                  FieldCategories::UnparametricTag) {
    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
                y[i * ldy + k + 1] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 1];
                y[i * ldy + k + 2] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 2];
                y[i * ldy + k + 3] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 3];
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

#ifdef __FFLASFFPACK_USE_SIMD

// template <class Field, class LFunc, class SFunc>
// inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
//                   typename Field::ConstElement_ptr x, typename Field::Element_ptr y, LFunc &&lfunc, SFunc &&sfunc,
//                   FieldCategories::UnparametricTag) {
//     using simd = Simd<typename Field::Element>;
//     using vect_t = typename simd::vect_t;

//     for (index_t i = 0; i < A.m; ++i) {
//         for (index_t j = 0; j < A.ld; ++j) {
//             vect_t vx1, vx2, vy1, vy2, vdat;
//             int k = 0;
//             vdat = simd::set1(A.dat[i * A.ld + j]);
//             for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
//                 vy1 = lfunc(y + i * blockSize + k);
//                 vy2 = lfunc(y + i * blockSize + k + simd::vect_size);
//                 vy1 = lfunc(x + A.col[i * A.ld + j] * blockSize + k);
//                 vy2 = lfunc(x + A.col[i * A.ld + j] * blockSize + k + simd::vect_size);
//                 sfunc(y + i * blockSize + k, simd::fmadd(vy1, vx1, vdat));
//                 sfunc(y + i * blockSize + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
//             }
//             for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
//                 vy1 = lfunc(y + i * blockSize + k);
//                 vy1 = lfunc(x + A.col[i * A.ld + j] * blockSize + k);
//                 sfunc(y + i * blockSize + k, simd::fmadd(vy1, vx1, vdat));
//             }
//             for (; k < blockSize; ++k)
//                 y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//         }
//     }
// }

template <class Field>
inline void fspmm_simd_aligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;

    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2, vdat;
            int k = 0;
            vdat = simd::set1(A.dat[i * A.ld + j]);
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vy2 = simd::load(y + i * ldy + k + simd::vect_size);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::load(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::store(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
                simd::store(y + i * ldy + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                simd::store(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

template <class Field>
inline void fspmm_simd_unaligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;

    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2, vdat;
            int k = 0;
            vdat = simd::set1(A.dat[i * A.ld + j]);
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vy2 = simd::loadu(y + i * ldy + k + simd::vect_size);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::storeu(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
                simd::storeu(y + i * ldy + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                simd::storeu(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

#endif

// template <class Field>
// inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
//                   typename Field::ConstElement_ptr x, typename Field::Element_ptr y, const int64_t kmax) {
//     index_t block = (A.ld) / kmax;
//     for (index_t i = 0; i < A.m; ++i) {
//         index_t j_loc = 0, j = 0;
//         for (index_t l = 0; l < (index_t)block; ++l) {
//             j_loc += kmax;
//             for (; j < j_loc; ++j) {
//                 int k = 0;
//                 for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
//                     y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//                     y[i * blockSize + k + 1] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 1];
//                     y[i * blockSize + k + 2] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 2];
//                     y[i * blockSize + k + 3] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 3];
//                 }
//                 for (; k < blockSize; ++k) {
//                     y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//                 }
//             }
//             // TODO : replace with freduce
//             for (int k = 0; k < blockSize; ++k) {
//                 F.reduce(y[i * blockSize + k]);
//             }
//         }
//         for (; j < A.ld; ++j) {
//             int k = 0;
//             for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
//                 y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//                 y[i * blockSize + k + 1] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 1];
//                 y[i * blockSize + k + 2] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 2];
//                 y[i * blockSize + k + 3] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k + 3];
//             }
//             for (; k < blockSize; ++k) {
//                 y[i * blockSize + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * blockSize + k];
//             }
//         }
//         // TODO : replace with freduce
//         for (int k = 0; k < blockSize; ++k) {
//             F.reduce(y[i * blockSize + k]);
//         }
//     }
// }

template <class Field>
inline void fspmm(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy,
                  const int64_t kmax) {
    index_t block = (A.ld) / kmax;
    for (index_t i = 0; i < A.m; ++i) {
        index_t j_loc = 0, j = 0;
        for (index_t l = 0; l < (index_t)block; ++l) {
            j_loc += kmax;
            for (; j < j_loc; ++j) {
                int k = 0;
                for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                    y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
                    y[i * ldy + k + 1] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 1];
                    y[i * ldy + k + 2] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 2];
                    y[i * ldy + k + 3] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 3];
                }
                for (; k < blockSize; ++k) {
                    y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
                }
            }
            // TODO : replace with freduce
            for (int k = 0; k < blockSize; ++k) {
                F.reduce(y[i * ldy + k]);
            }
        }
        for (; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
                y[i * ldy + k + 1] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 1];
                y[i * ldy + k + 2] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 2];
                y[i * ldy + k + 3] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k + 3];
            }
            for (; k < blockSize; ++k) {
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
            }
        }
        // TODO : replace with freduce
        for (int k = 0; k < blockSize; ++k) {
            F.reduce(y[i * ldy + k]);
        }
    }
}

#ifdef __FFLASFFPACK_USE_SIMD

template <class Field>
inline void fspmm_simd_aligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy,
                  const int64_t kmax) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;
    index_t block = (A.ld) / kmax;
    for (index_t i = 0; i < A.m; ++i) {
        index_t j_loc = 0, j = 0;
        for (index_t l = 0; l < (index_t)block; ++l) {
            j_loc += kmax;
            for (; j < j_loc; ++j) {
                vect_t vx1, vx2, vy1, vy2, vdat;
            int k = 0;
            vdat = simd::set1(A.dat[i * A.ld + j]);
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vy2 = simd::load(y + i * ldy + k + simd::vect_size);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::load(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::store(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
                simd::store(y + i * ldy + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                simd::store(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
            }
            // TODO : replace with freduce
            for (int k = 0; k < blockSize; ++k) {
                F.reduce(y[i * ldy + k]);
            }
        }
        for (; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2, vdat;
            int k = 0;
            vdat = simd::set1(A.dat[i * A.ld + j]);
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vy2 = simd::load(y + i * ldy + k + simd::vect_size);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::load(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::store(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
                simd::store(y + i * ldy + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                simd::store(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
        }
        // TODO : replace with freduce
        for (int k = 0; k < blockSize; ++k) {
            F.reduce(y[i * ldy + k]);
        }
    }
}

template <class Field>
inline void fspmm_simd_unaligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL> &A, int blockSize,
                  typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy,
                  const int64_t kmax) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;
    index_t block = (A.ld) / kmax;
    for (index_t i = 0; i < A.m; ++i) {
        index_t j_loc = 0, j = 0;
        for (index_t l = 0; l < (index_t)block; ++l) {
            j_loc += kmax;
            for (; j < j_loc; ++j) {
                vect_t vx1, vx2, vy1, vy2, vdat;
            int k = 0;
            vdat = simd::set1(A.dat[i * A.ld + j]);
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vy2 = simd::loadu(y + i * ldy + k + simd::vect_size);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::storeu(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
                simd::storeu(y + i * ldy + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                simd::storeu(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
            }
            // TODO : replace with freduce
            for (int k = 0; k < blockSize; ++k) {
                F.reduce(y[i * ldy + k]);
            }
        }
        for (; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2, vdat;
            int k = 0;
            vdat = simd::set1(A.dat[i * A.ld + j]);
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vy2 = simd::loadu(y + i * ldy + k + simd::vect_size);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::storeu(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
                simd::storeu(y + i * ldy + k + simd::vect_size, simd::fmadd(vy2, vx2, vdat));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                simd::storeu(y + i * ldy + k, simd::fmadd(vy1, vx1, vdat));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += A.dat[i * A.ld + j] * x[A.col[i * A.ld + j] * ldx + k];
        }
        // TODO : replace with freduce
        for (int k = 0; k < blockSize; ++k) {
            F.reduce(y[i * ldy + k]);
        }
    }
}

#endif // SIMD

// template <class Field, class Func>
// inline void fspmm_zo(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
//                      typename Field::ConstElement_ptr x, typename Field::Element_ptr y, Func &&func) {
//     for (index_t i = 0; i < A.m; ++i) {
//         for (index_t j = 0; j < A.ld; ++j) {
//             int k = 0;
//             for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
//                 func(y[i * blockSize + k], x[A.col[i * A.ld + j] * blockSize + k]);
//                 func(y[i * blockSize + k + 1], x[A.col[i * A.ld + j] * blockSize + k + 1]);
//                 func(y[i * blockSize + k + 2], x[A.col[i * A.ld + j] * blockSize + k + 2]);
//                 func(y[i * blockSize + k + 3], x[A.col[i * A.ld + j] * blockSize + k + 3]);
//             }
//             for (; k < blockSize; ++k)
//                 func(y[i * blockSize + k], x[A.col[i * A.ld + j] * blockSize + k]);
//         }
//     }
// }

template <class Field>
inline void fspmm_mone(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::GenericTag) {
    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                F.subin(y[i * ldy + k], x[A.col[i * A.ld + j] * ldx + k]);
                F.subin(y[i * ldy + k + 1], x[A.col[i * A.ld + j] * ldx + k + 1]);
                F.subin(y[i * ldy + k + 2], x[A.col[i * A.ld + j] * ldx + k + 2]);
                F.subin(y[i * ldy + k + 3], x[A.col[i * A.ld + j] * ldx + k + 3]);
            }
            for (; k < blockSize; ++k)
                F.subin(y[i * ldy + k], x[A.col[i * A.ld + j] * ldx + k]);
        }
    }
}

template <class Field>
inline void fspmm_one(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::GenericTag) {
    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                F.addin(y[i * ldy + k], x[A.col[i * A.ld + j] * ldx + k]);
                F.addin(y[i * ldy + k + 1], x[A.col[i * A.ld + j] * ldx + k + 1]);
                F.addin(y[i * ldy + k + 2], x[A.col[i * A.ld + j] * ldx + k + 2]);
                F.addin(y[i * ldy + k + 3], x[A.col[i * A.ld + j] * ldx + k + 3]);
            }
            for (; k < blockSize; ++k)
                F.addin(y[i * ldy + k], x[A.col[i * A.ld + j] * ldx + k]);
        }
    }
}

template <class Field>
inline void fspmm_mone(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                y[i * ldy + k] -= x[A.col[i * A.ld + j] * ldx + k];
                y[i * ldy + k + 1] -= x[A.col[i * A.ld + j] * ldx + k + 1];
                y[i * ldy + k + 2] -= x[A.col[i * A.ld + j] * ldx + k + 2];
                y[i * ldy + k + 3] -= x[A.col[i * A.ld + j] * ldx + k + 3];
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] -= x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

template <class Field>
inline void fspmm_one(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 4); k += 4) {
                y[i * ldy + k] += x[A.col[i * A.ld + j] * ldx + k];
                y[i * ldy + k + 1] += x[A.col[i * A.ld + j] * ldx + k + 1];
                y[i * ldy + k + 2] += x[A.col[i * A.ld + j] * ldx + k + 2];
                y[i * ldy + k + 3] += x[A.col[i * A.ld + j] * ldx + k + 3];
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

#ifdef __FFLASFFPACK_USE_SIMD

// template <class Field, class LFunc, class SFunc, class VectFunc, class ScalFunc>
// inline void fspmm_zo(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
//                      typename Field::ConstElement_ptr x, typename Field::Element_ptr y, VectFunc &&vfunc,
//                      ScalFunc &&scalfunc, LFunc &&lfunc, SFunc &&sfunc) {
//     using simd = Simd<typename Field::Element>;
//     using vect_t = typename simd::vect_t;

//     for (index_t i = 0; i < A.m; ++i) {
//         for (index_t j = 0; j < A.ld; ++j) {
//             vect_t vx1, vx2, vy1, vy2;
//             int k = 0;
//             for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
//                 vy1 = lfunc(y + i * blockSize + k);
//                 vy2 = lfunc(y + i * blockSize + k + simd::vect_size);
//                 vy1 = lfunc(x + A.col[i * A.ld + j] * blockSize + k);
//                 vy2 = lfunc(x + A.col[i * A.ld + j] * blockSize + k + simd::vect_size);
//                 sfunc(y + i * blockSize + k, vfunc(vy1, vx1));
//                 sfunc(y + i * blockSize + k + simd::vect_size, vfunc(vy2, vx2));
//             }
//             for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
//                 vy1 = lfunc(y + i * blockSize + k);
//                 vy1 = lfunc(x + A.col[i * A.ld + j] * blockSize + k);
//                 sfunc(y + i * blockSize + k, vfunc(vy1, vx1));
//             }
//             for (; k < blockSize; ++k)
//                 scalfunc(y[i * blockSize + k], x[A.col[i * A.ld + j] * blockSize + k]);
//         }
//     }
// }

template <class Field>
inline void fspmm_one_simd_aligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;

    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2;
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vy2 = simd::load(y + i * ldy + k + simd::vect_size);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::load(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::store(y + i * ldx + k, simd::add(vy1, vx1));
                simd::store(y + i * ldx + k + simd::vect_size, simd::add(vy2, vx2));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldy + k);
                simd::store(y + i * ldx + k, simd::add(vy1, vx1));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

template <class Field>
inline void fspmm_one_simd_unaligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;

    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2;
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vy2 = simd::loadu(y + i * ldy + k + simd::vect_size);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::storeu(y + i * ldx + k, simd::add(vy1, vx1));
                simd::storeu(y + i * ldx + k + simd::vect_size, simd::add(vy2, vx2));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldy + k);
                simd::storeu(y + i * ldx + k, simd::add(vy1, vx1));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] += x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

template <class Field>
inline void fspmm_mone_simd_aligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;

    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2;
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vy2 = simd::load(y + i * ldy + k + simd::vect_size);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::load(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::store(y + i * ldx + k, simd::sub(vy1, vx1));
                simd::store(y + i * ldx + k + simd::vect_size, simd::sub(vy2, vx2));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::load(y + i * ldy + k);
                vx1 = simd::load(x + A.col[i * A.ld + j] * ldy + k);
                simd::store(y + i * ldx + k, simd::sub(vy1, vx1));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] -= x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

template <class Field>
inline void fspmm_mone_simd_unaligned(const Field &F, const Sparse<Field, SparseMatrix_t::ELL_ZO> &A, int blockSize,
                     typename Field::ConstElement_ptr x, int ldx, typename Field::Element_ptr y, int ldy, FieldCategories::UnparametricTag) {
    using simd = Simd<typename Field::Element>;
    using vect_t = typename simd::vect_t;

    for (index_t i = 0; i < A.m; ++i) {
        for (index_t j = 0; j < A.ld; ++j) {
            vect_t vx1, vx2, vy1, vy2;
            int k = 0;
            for (; k < ROUND_DOWN(blockSize, 2 * simd::vect_size); k += 2 * simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vy2 = simd::loadu(y + i * ldy + k + simd::vect_size);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k);
                vx2 = simd::loadu(x + A.col[i * A.ld + j] * ldx + k + simd::vect_size);
                simd::storeu(y + i * ldx + k, simd::sub(vy1, vx1));
                simd::storeu(y + i * ldx + k + simd::vect_size, simd::sub(vy2, vx2));
            }
            for (; k < ROUND_DOWN(blockSize, simd::vect_size); k += simd::vect_size) {
                vy1 = simd::loadu(y + i * ldy + k);
                vx1 = simd::loadu(x + A.col[i * A.ld + j] * ldy + k);
                simd::storeu(y + i * ldx + k, simd::sub(vy1, vx1));
            }
            for (; k < blockSize; ++k)
                y[i * ldy + k] -= x[A.col[i * A.ld + j] * ldx + k];
        }
    }
}

#endif

} // ell_details

} // FFLAS

#endif //  __FFLASFFPACK_fflas_ELL_spmm_INL
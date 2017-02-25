/*
 * SPARX source code package
 *
 * Copyright (C) 2016, 2017 CryptoLUX (https://www.cryptolux.org)
 *
 * Written by Daniel Dinu <dumitru-daniel.dinu@uni.lu>
 *
 * You may use this work under the terms of a Creative Commons CC0 1.0 
 * License/Waiver or the Apache Public License 2.0, at your option. The terms of
 * these licenses can be found at:
 *
 * - CC0 1.0 Universal : http://creativecommons.org/publicdomain/zero/1.0
 * - Apache 2.0        : http://www.apache.org/licenses/LICENSE-2.0
 *
 * You should have received a copy of both of these licenses along with this
 * software. If not, they may be obtained at the above URLs.
 */

#ifndef MSP_MACROS_H
#define MSP_MACROS_H


#include "stringify.h"


#define CV1 #1
#define CV8 #8
#define CV12 #12


#define EKS_STORE_ROUND_KEYS_(k0, k1, k2, k3, k4, k5) \
    mov k0, 0(r14)                               \n\t \
    mov k1, 2(r14)                               \n\t \
                                                      \
    mov k2, 4(r14)                               \n\t \
    mov k3, 6(r14)                               \n\t \
                                                      \
    mov k4, 8(r14)                               \n\t \
    mov k5, 10(r14)                              \n\t \
                                                      \
    add CV12, r14                                \n\t


#define EKS_ROUND_KEYS_(k0, k1, k2, k3, k4, k5, k6, k7, temp, c) \
    add c, k7                                               \n\t \
                                                                 \
                                                                 \
    swpb k0                                                 \n\t \
    rla k0                                                  \n\t \
    adc k0                                                  \n\t \
                                                                 \
    add k1, k0                                              \n\t \
                                                                 \
    rla k1                                                  \n\t \
    adc k1                                                  \n\t \
    rla k1                                                  \n\t \
    adc k1                                                  \n\t \
                                                                 \
    xor k0, k1                                              \n\t \
                                                                 \
                                                                 \
    add k0, k2                                              \n\t \
    add k1, k3                                              \n\t \
                                                                 \
                                                                 \
    mov k7, temp                                            \n\t \
    mov k5, k7                                              \n\t \
    mov k3, k5                                              \n\t \
    mov k1, k3                                              \n\t \
    mov temp, k1                                            \n\t \
                                                                 \
    mov k6, temp                                            \n\t \
    mov k4, k6                                              \n\t \
    mov k2, k4                                              \n\t \
    mov k0, k2                                              \n\t \
    mov temp, k0                                            \n\t


#define EKS_WHITENING_KEYS_(k0, k1, k7, c) \
    swpb k0                           \n\t \
    rla k0                            \n\t \
    adc k0                            \n\t \
                                           \
    add k1, k0                        \n\t \
                                           \
    rla k1                            \n\t \
    adc k1                            \n\t \
    rla k1                            \n\t \
    adc k1                            \n\t \
                                           \
    xor k0, k1                        \n\t \
                                           \
    add c, k7                         \n\t


#define ENC_ADD_ROUND_KEY_(b0, b1, rk) \
    mov @r14+, rk                 \n\t \
    xor rk, b0                    \n\t \
                                       \
    mov @r14+, rk                 \n\t \
    xor rk, b1                    \n\t

#define DEC_ADD_ROUND_KEY_(b0, b1, rk) \
    mov @r14+, rk                 \n\t \
    xor rk, b0                    \n\t \
                                       \
    mov @r14+, rk                 \n\t \
    xor rk, b1                    \n\t \
                                       \
    sub CV8, r14                  \n\t


#define ENC_A_(b0, b1) \
    swpb b0       \n\t \
    rla b0        \n\t \
    adc b0        \n\t \
                       \
    add b1, b0    \n\t \
                       \
    rla b1        \n\t \
    adc b1        \n\t \
    rla b1        \n\t \
    adc b1        \n\t \
                       \
    xor b0, b1    \n\t

#define DEC_A_(b0, b1) \
    xor b0, b1    \n\t \
                       \
    bit CV1, b1   \n\t \
    rrc b1        \n\t \
    bit CV1, b1   \n\t \
    rrc b1        \n\t \
                       \
    sub b1, b0    \n\t \
                       \
    swpb b0       \n\t \
    bit CV1, b0   \n\t \
    rrc b0        \n\t


#define L_(b0, b1, b2, b3, temp) \
    mov b0, temp            \n\t \
    xor b1, temp            \n\t \
                                 \
    swpb temp               \n\t \
    xor temp, b0            \n\t \
    xor temp, b1            \n\t \
                                 \
    xor b2, b0              \n\t \
    xor b3, b1              \n\t

#define ENC_L_(b0, b1, b2, b3, t0, t1, t2) \
    mov b0, t0                        \n\t \
    mov b1, t1                        \n\t \
                                           \
    L_(b0, b1, b2, b3, t2)                 \
                                           \
    mov t0, b2                        \n\t \
    mov t1, b3                        \n\t

#define DEC_L_(b0, b1, b2, b3, t0, t1, t2) \
    mov b2, t0                        \n\t \
    mov b3, t1                        \n\t \
                                           \
    L_(b2, b3, b0, b1, t2)                 \
                                           \
    mov t0, b0                        \n\t \
    mov t1, b1                        \n\t


#define ENC_ADD_WHITENING_KEY_(b0, b1, rk) \
    mov @r14+, rk                     \n\t \
    xor rk, b0                        \n\t \
                                           \
    mov @r14+, rk                     \n\t \
    xor rk, b1                        \n\t


#define DEC_ADD_WHITENING_KEY_(b0, b1, rk) \
    mov @r14+, rk                     \n\t \
    xor rk, b0                        \n\t \
                                           \
    mov @r14+, rk                     \n\t \
    xor rk, b1                        \n\t \
                                           \
    sub CV8, r14                      \n\t



#define EKS_STORE_ROUND_KEYS(k0, k1, k2, k3, k4, k5) \
    STR(EKS_STORE_ROUND_KEYS_(k0, k1, k2, k3, k4, k5))


#define EKS_ROUND_KEYS(k0, k1, k2, k3, k4, k5, k6, k7, temp, c) \
    STR(EKS_ROUND_KEYS_(k0, k1, k2, k3, k4, k5, k6, k7, temp, c))


#define EKS_WHITENING_KEYS(k0, k1, k7, c) \
    STR(EKS_WHITENING_KEYS_(k0, k1, k7, c))


#define ENC_ADD_ROUND_KEY(b0, b1, rk) \
    STR(ENC_ADD_ROUND_KEY_(b0, b1, rk))

#define DEC_ADD_ROUND_KEY(b0, b1, rk) \
    STR(DEC_ADD_ROUND_KEY_(b0, b1, rk))


#define ENC_A(b0, b1) \
    STR(ENC_A_(b0, b1))

#define DEC_A(b0, b1) \
    STR(DEC_A_(b0, b1))


#define L(b0, b1, b2, b3, temp) \
    STR(L_(b0, b1, b2, b3, temp))

#define ENC_L(b0, b1, b2, b3, t0, t1, t2) \
    STR(ENC_L_(b0, b1, b2, b3, t0, t1, t2))

#define DEC_L(b0, b1, b2, b3, t0, t1, t2) \
    STR(DEC_L_(b0, b1, b2, b3, t0, t1, t2))


#define ENC_ADD_WHITENING_KEY(b0, b1, rk) \
    STR(ENC_ADD_WHITENING_KEY_(b0, b1, rk))

#define DEC_ADD_WHITENING_KEY(b0, b1, rk) \
    STR(DEC_ADD_WHITENING_KEY_(b0, b1, rk))


#endif /* MSP_MACROS_H */

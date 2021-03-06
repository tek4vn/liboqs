// SPDX-License-Identifier: MIT

/* qTesla-p-I */

#include "sig_qtesla.h"

#ifdef OQS_ENABLE_SIG_qTesla_p_I

#define _qTESLA_p_I_

#if defined(WITH_AVX2) && !defined(_WIN32)
#define poly_ntt_asm oqs_sig_qteslapi_poly_ntt_asm
#define poly_pmul_asm oqs_sig_qteslapi_poly_pmul_asm
#define poly_intt_asm oqs_sig_qteslapi_poly_intt_asm
#include "external/avx2/consts.c"
#include "external/avx2/s_consts.c"
#include "external/avx2/gauss.c"
#include "external/avx2/pack.c"
#include "external/avx2/poly.c"
#include "external/avx2/sample.c"
#include "external/avx2/sign.c"
#else
#include "external/portable/consts.c"
#include "external/portable/gauss.c"
#include "external/portable/pack.c"
#include "external/portable/poly.c"
#include "external/portable/sample.c"
#include "external/portable/sign.c"
#endif

OQS_API OQS_STATUS OQS_SIG_qTesla_p_I_keypair(uint8_t *public_key, uint8_t *secret_key) {
	int rv = crypto_sign_keypair(public_key, secret_key);
	if (rv == 0) {
		return OQS_SUCCESS;
	} else {
		return OQS_ERROR;
	}
}

OQS_API OQS_STATUS OQS_SIG_qTesla_p_I_sign(uint8_t *signature, size_t *signature_len, const uint8_t *message, size_t message_len, const uint8_t *secret_key) {
	int rv = crypto_sign(signature, (long long unsigned int *) signature_len, message, message_len, secret_key);
	if (rv == 0) {
		return OQS_SUCCESS;
	} else {
		return OQS_ERROR;
	}
}

OQS_API OQS_STATUS OQS_SIG_qTesla_p_I_verify(const uint8_t *message, size_t message_len, const uint8_t *signature, size_t signature_len, const uint8_t *public_key) {
	int rv = crypto_sign_open((unsigned char *) message, message_len, signature, signature_len, public_key);
	if (rv == 0) {
		return OQS_SUCCESS;
	} else {
		return OQS_ERROR;
	}
}

#endif

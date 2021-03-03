/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 *
 * Author: Seppo Ingalsuo <seppo.ingalsuo@linux.intel.com>
 */

/* PDM decimation FIR filters */

#ifndef __SOF_AUDIO_COEFFICIENTS_PDM_DECIM_PDM_DECIM_TABLE_H__
#define __SOF_AUDIO_COEFFICIENTS_PDM_DECIM_PDM_DECIM_TABLE_H__

#include "pdm_decim_fir.h"

#include "pdm_decim_int32_02_4323_5100_010_095.h"
#include "pdm_decim_int32_02_4375_5100_010_095.h"
#include "pdm_decim_int32_03_4375_5100_010_095.h"
#include "pdm_decim_int32_04_4318_5100_010_095.h"
#include "pdm_decim_int32_05_4325_5100_010_095.h"
#include "pdm_decim_int32_06_4172_5100_010_095.h"
#include "pdm_decim_int32_08_4156_5301_010_090.h"
#include "pdm_decim_int32_10_4156_5345_010_090.h"
#include "pdm_decim_int32_12_4156_5345_010_090.h"

/* Note 1: Higher spec filter must be before lower spec filter
 * if there are multiple filters for a decimation factor. The first
 * filter is skipped if the length is too much vs. overrun limit. If
 * other order the better filter would be never selected.
 *
 * Note 2: The introduction order of FIR decimation factors is the selection
 * preference order. The decimation factor 5 and 10 (2*5) cause a often less
 * compatible output sample rate for CIC so they are not used if there other
 * suitable nearby values.
 *
 * The naming scheme of coefficients set is:
 * <type>_<decim factor>_<rel passband>_<rel stopband>_<ripple>_<attenuation>
 */
struct pdm_decim *fir_list[] = {
	&pdm_decim_int32_02_4375_5100_010_095,
	&pdm_decim_int32_02_4323_5100_010_095,
	&pdm_decim_int32_03_4375_5100_010_095,
	&pdm_decim_int32_04_4318_5100_010_095,
	&pdm_decim_int32_06_4172_5100_010_095,
	&pdm_decim_int32_05_4325_5100_010_095,
	&pdm_decim_int32_08_4156_5301_010_090,
	&pdm_decim_int32_12_4156_5345_010_090,
	&pdm_decim_int32_10_4156_5345_010_090,
	NULL, /* This marks the end of coefficients */
};

#endif /* __SOF_AUDIO_COEFFICIENTS_PDM_DECIM_PDM_DECIM_TABLE_H__ */

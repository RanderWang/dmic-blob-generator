// SPDX-License-Identifier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may do so under either license.
//
// Copyright(c) 2021 Intel Corporation. All rights reserved.
//
// Authors: Seppo Ingalsuo <seppo.ingalsuo@linux.intel.com>
// Authors: Rander Wang <rander.wang@linux.intel.com>

#ifndef SOF_IPC4_DMIC_H
#define SOF_IPC4_DMIC_H

enum sof_ipc_frame {
	SOF_IPC_FRAME_S16_LE = 0,
	SOF_IPC_FRAME_S24_4LE,
	SOF_IPC_FRAME_S32_LE,
	SOF_IPC_FRAME_FLOAT,
	/* other formats here */
};

#define BIT(x) ((1) << x)
#define SET_BIT(b, x)		(((x) & 1) << (b))
#define SET_BITS(b_hi, b_lo, x)	\
	(((x) & ((1ULL << ((b_hi) - (b_lo) + 1ULL)) - 1ULL)) << (b_lo))

#define SOF_DAI_INTEL_DMIC_NUM_CTRL 4
#define DMIC_HW_VERSION		1
#define DMIC_HW_CONTROLLERS	2
#define DMIC_HW_IOCLK		38400000
#define DMIC_HW_FIFOS		2

#define DMIC_UNMUTE_CIC		1	/* Unmute CIC at 1 ms */
#define DMIC_UNMUTE_FIR		2	/* Unmute FIR at 2 ms */

/* Parameters used in modes computation */
#define DMIC_HW_BITS_CIC		26
#define DMIC_HW_BITS_FIR_COEF		20
#define DMIC_HW_BITS_FIR_GAIN		20
#define DMIC_HW_BITS_FIR_INPUT		22
#define DMIC_HW_BITS_FIR_OUTPUT		24
#define DMIC_HW_BITS_FIR_INTERNAL	26
#define DMIC_HW_BITS_GAIN_OUTPUT	22
#define DMIC_HW_FIR_LENGTH_MAX		250
#define DMIC_HW_CIC_SHIFT_MIN		-8
#define DMIC_HW_CIC_SHIFT_MAX		4
#define DMIC_HW_FIR_SHIFT_MIN		0
#define DMIC_HW_FIR_SHIFT_MAX		8
#define DMIC_HW_CIC_DECIM_MIN		5
#define DMIC_HW_CIC_DECIM_MAX		31 /* Note: Limited by BITS_CIC */
#define DMIC_HW_FIR_DECIM_MIN		2
#define DMIC_HW_FIR_DECIM_MAX		20 /* Note: Practical upper limit */
#define DMIC_HW_SENS_Q28		Q_CONVERT_FLOAT(1.0, 28) /* Q1.28 */
#define DMIC_HW_PDM_CLK_MIN		100000 /* Note: Practical min value */
#define DMIC_HW_DUTY_MIN		20 /* Note: Practical min value */
#define DMIC_HW_DUTY_MAX		80 /* Note: Practical max value */

#define DMIC_HIGH_RATE_MIN_FS	64000
#define DMIC_HIGH_RATE_OSR_MIN	40

/* Minimum OSR is always applied for 48 kHz and less sample rates */
#define DMIC_MIN_OSR  50

#define DMIC_MAX_MODES 50

/* These are used as guideline for configuring > 48 kHz sample rates. The
 * minimum OSR can be relaxed down to 40 (use 3.84 MHz clock for 96 kHz).
 */
#define DMIC_HIGH_RATE_MIN_FS	64000
#define DMIC_HIGH_RATE_OSR_MIN	40

/* Used for scaling FIR coefficients for HW */
#define DMIC_HW_FIR_COEF_MAX ((1 << (DMIC_HW_BITS_FIR_COEF - 1)) - 1)
#define DMIC_HW_FIR_COEF_Q (DMIC_HW_BITS_FIR_COEF - 1)

/* Internal precision in gains computation, e.g. Q4.28 in int32_t */
#define DMIC_FIR_SCALE_Q 28

/* Used in unmute ramp values calculation */
#define DMIC_HW_FIR_GAIN_MAX ((1 << (DMIC_HW_BITS_FIR_GAIN - 1)) - 1)

/* OUTCONTROL0 bits */
#define OUTCONTROL0_TIE_BIT	BIT(27)
#define OUTCONTROL0_SIP_BIT	BIT(26)
#define OUTCONTROL0_FINIT_BIT	BIT(25)
#define OUTCONTROL0_FCI_BIT	BIT(24)
#define OUTCONTROL0_TIE(x)	SET_BIT(27, x)
#define OUTCONTROL0_SIP(x)	SET_BIT(26, x)
#define OUTCONTROL0_FINIT(x)	SET_BIT(25, x)
#define OUTCONTROL0_FCI(x)	SET_BIT(24, x)
#define OUTCONTROL0_BFTH(x)	SET_BITS(23, 20, x)
#define OUTCONTROL0_OF(x)	SET_BITS(19, 18, x)
#define OUTCONTROL0_IPM(x)	SET_BITS(17, 16, x)
#define OUTCONTROL0_TH(x)	SET_BITS(5, 0, x)

/* OUTCONTROL1 bits */
#define OUTCONTROL1_TIE_BIT	BIT(27)
#define OUTCONTROL1_SIP_BIT	BIT(26)
#define OUTCONTROL1_FINIT_BIT	BIT(25)
#define OUTCONTROL1_FCI_BIT	BIT(24)
#define OUTCONTROL1_TIE(x)	SET_BIT(27, x)
#define OUTCONTROL1_SIP(x)	SET_BIT(26, x)
#define OUTCONTROL1_FINIT(x)	SET_BIT(25, x)
#define OUTCONTROL1_FCI(x)	SET_BIT(24, x)
#define OUTCONTROL1_BFTH(x)	SET_BITS(23, 20, x)
#define OUTCONTROL1_OF(x)	SET_BITS(19, 18, x)
#define OUTCONTROL1_IPM(x)	SET_BITS(17, 16, x)
#define OUTCONTROL1_TH(x)	SET_BITS(5, 0, x)

/* CIC_CONTROL bits */
#define CIC_CONTROL_SOFT_RESET_BIT	BIT(16)
#define CIC_CONTROL_CIC_START_B_BIT	BIT(15)
#define CIC_CONTROL_CIC_START_A_BIT	BIT(14)
#define CIC_CONTROL_MIC_B_POLARITY_BIT	BIT(3)
#define CIC_CONTROL_MIC_A_POLARITY_BIT	BIT(2)
#define CIC_CONTROL_MIC_MUTE_BIT	BIT(1)
#define CIC_CONTROL_STEREO_MODE_BIT	BIT(0)

#define CIC_CONTROL_SOFT_RESET(x)	SET_BIT(16, x)
#define CIC_CONTROL_CIC_START_B(x)	SET_BIT(15, x)
#define CIC_CONTROL_CIC_START_A(x)	SET_BIT(14, x)
#define CIC_CONTROL_MIC_B_POLARITY(x)	SET_BIT(3, x)
#define CIC_CONTROL_MIC_A_POLARITY(x)	SET_BIT(2, x)
#define CIC_CONTROL_MIC_MUTE(x)		SET_BIT(1, x)
#define CIC_CONTROL_STEREO_MODE(x)	SET_BIT(0, x)

/* CIC_CONFIG bits */
#define CIC_CONFIG_CIC_SHIFT(x)		SET_BITS(27, 24, x)
#define CIC_CONFIG_COMB_COUNT(x)	SET_BITS(15, 8, x)

/* CIC_CONFIG masks */
#define CIC_CONFIG_CIC_SHIFT_MASK	MASK(27, 24)
#define CIC_CONFIG_COMB_COUNT_MASK	MASK(15, 8)

/* MIC_CONTROL bits */
#define MIC_CONTROL_PDM_EN_B_BIT	BIT(1)
#define MIC_CONTROL_PDM_EN_A_BIT	BIT(0)
#define MIC_CONTROL_PDM_CLKDIV(x)	SET_BITS(15, 8, x)
#define MIC_CONTROL_PDM_SKEW(x)		SET_BITS(7, 4, x)
#define MIC_CONTROL_CLK_EDGE(x)		SET_BIT(3, x)
#define MIC_CONTROL_PDM_EN_B(x)		SET_BIT(1, x)
#define MIC_CONTROL_PDM_EN_A(x)		SET_BIT(0, x)

/* MIC_CONTROL masks */
#define MIC_CONTROL_PDM_CLKDIV_MASK	MASK(15, 8)

/* FIR_CONTROL_A bits */
#define FIR_CONTROL_A_START_BIT			BIT(7)
#define FIR_CONTROL_A_ARRAY_START_EN_BIT	BIT(6)
#define FIR_CONTROL_A_MUTE_BIT			BIT(1)
#define FIR_CONTROL_A_START(x)			SET_BIT(7, x)
#define FIR_CONTROL_A_ARRAY_START_EN(x)		SET_BIT(6, x)
#define FIR_CONTROL_A_DCCOMP(x)			SET_BIT(4, x)
#define FIR_CONTROL_A_MUTE(x)			SET_BIT(1, x)
#define FIR_CONTROL_A_STEREO(x)			SET_BIT(0, x)

/* FIR_CONFIG_A bits */
#define FIR_CONFIG_A_FIR_DECIMATION(x)		SET_BITS(20, 16, x)
#define FIR_CONFIG_A_FIR_SHIFT(x)		SET_BITS(11, 8, x)
#define FIR_CONFIG_A_FIR_LENGTH(x)		SET_BITS(7, 0, x)

/* DC offset compensation time constants */
#define DCCOMP_TC0	0
#define DCCOMP_TC1	1
#define DCCOMP_TC2	2
#define DCCOMP_TC3	3
#define DCCOMP_TC4	4
#define DCCOMP_TC5	5
#define DCCOMP_TC6	6
#define DCCOMP_TC7	7

/* DC_OFFSET_LEFT_A bits */
#define DC_OFFSET_LEFT_A_DC_OFFS(x)		SET_BITS(21, 0, x)

/* DC_OFFSET_RIGHT_A bits */
#define DC_OFFSET_RIGHT_A_DC_OFFS(x)		SET_BITS(21, 0, x)

/* OUT_GAIN_LEFT_A bits */
#define OUT_GAIN_LEFT_A_GAIN(x)			SET_BITS(19, 0, x)

/* OUT_GAIN_RIGHT_A bits */
#define OUT_GAIN_RIGHT_A_GAIN(x)		SET_BITS(19, 0, x)

/* FIR_CONTROL_B bits */
#define FIR_CONTROL_B_START_BIT			BIT(7)
#define FIR_CONTROL_B_ARRAY_START_EN_BIT	BIT(6)
#define FIR_CONTROL_B_MUTE_BIT			BIT(1)
#define FIR_CONTROL_B_START(x)			SET_BIT(7, x)
#define FIR_CONTROL_B_ARRAY_START_EN(x)		SET_BIT(6, x)
#define FIR_CONTROL_B_DCCOMP(x)			SET_BIT(4, x)
#define FIR_CONTROL_B_MUTE(x)			SET_BIT(1, x)
#define FIR_CONTROL_B_STEREO(x)			SET_BIT(0, x)

/* FIR_CONFIG_B bits */
#define FIR_CONFIG_B_FIR_DECIMATION(x)		SET_BITS(20, 16, x)
#define FIR_CONFIG_B_FIR_SHIFT(x)		SET_BITS(11, 8, x)
#define FIR_CONFIG_B_FIR_LENGTH(x)		SET_BITS(7, 0, x)

/* DC_OFFSET_LEFT_B bits */
#define DC_OFFSET_LEFT_B_DC_OFFS(x)		SET_BITS(21, 0, x)

/* DC_OFFSET_RIGHT_B bits */
#define DC_OFFSET_RIGHT_B_DC_OFFS(x)		SET_BITS(21, 0, x)

/* OUT_GAIN_LEFT_B bits */
#define OUT_GAIN_LEFT_B_GAIN(x)			SET_BITS(19, 0, x)

/* OUT_GAIN_RIGHT_B bits */
#define OUT_GAIN_RIGHT_B_GAIN(x)		SET_BITS(19, 0, x)

/* FIR coefficients */
#define FIR_COEF_A(x)				SET_BITS(19, 0, x)
#define FIR_COEF_B(x)				SET_BITS(19, 0, x)

#define Q_MULTS_32X32(px, py, qx, qy, qp) \
	((px) * (py) >> (((qx) + (qy) - (qp))))

/* Fractional multiplication with shift and round
 * Note that the parameters px and py must be cast to (int64_t) if other type.
 */
#define Q_MULTSR_32X32(px, py, qx, qy, qp) \
	((((px) * (py) >> ((qx) + (qy) - (qp) - 1)) + 1) >> 1)

/* Convert a float number to fractional Qnx.ny format. Note that there is no
 * check for nx+ny number of bits to fit the word length of int. The parameter
 * qy must be 31 or less.
 */
#define Q_CONVERT_FLOAT(f, qy) \
	((int32_t)(((const double)f) * ((int64_t)1 << (const int)qy) + 0.5))

#define DMIC_MAX(x, y) ((x) > (y)) ? (x) : (y)
#define DMIC_MIN(x, y) ((x) < (y)) ? (x) : (y)

/* Saturation */
#define SATP_INT32(x) (((x) > INT_MAX) ? INT_MAX : (x))
#define SATM_INT32(x) (((x) < INT_MIN) ? INT_MIN : (x))

/* Get max and min signed integer values for N bits word length */
#define DMIC_INT_MAX(N)	((int64_t)((1ULL << ((N) - 1)) - 1))
#define DMIC_INT_MIN(N)	((int64_t)(-((1ULL << ((N) - 1)) - 1) - 1))

/* HW FIR pipeline needs 5 additional cycles per channel for internal
 * operations. This is used in MAX filter length check.
 */
#define DMIC_FIR_PIPELINE_OVERHEAD 5

/*
 * If there is only one PDM controller configuration passed,
 * the other (missing) one is configured by the driver just by
 * clearing CIC_CONTROL.SOFT_RESET bit.
 * The driver needs to make sure that all mics are disabled
 * before starting to program PDM controllers.
 */
struct sof_fir_config
{
	uint32_t fir_control;
	uint32_t fir_config;
	uint32_t dc_offset_left;
	uint32_t dc_offset_right;
	uint32_t out_gain_left;
	uint32_t out_gain_right;
	uint32_t rsvd_2[2];
};

/*
 * Note that FIR array may be provided in either packed or unpacked format.
 * see FIR_COEFFS_PACKED_TO_24_BITS.
 * Since in many cases all PDMs are programmed with the same FIR settings,
 * it is possible to provide it in a single copy inside the BLOB and refer
 * to that from other PDM configurations \see reuse_fir_from_pdm.
 */
struct sof_pdm_ctrl_cfg
{
	uint32_t cic_control;
	uint32_t cic_config;
	uint32_t rsvd_0;
	uint32_t mic_control;
	/* this field is used on platforms with SoundWire, otherwise ignored */
	uint32_t pdmsm;
	//! Index of another PDMCtrlCfg to be used as a source of FIR coefficients.
	/*!
	  \note The index is 1-based, value of 0 means that FIR coefficients
	     array fir_coeffs is provided by this item.
	  This is a very common case that the same FIR coefficients are used
	  to program more than one PDM controller. In this case, fir_coeffs array
	  may be provided in a single copy following PdmCtrlCfg #0 and be reused
	  by PdmCtrlCfg #1 by setting reuse_fir_from_pdm to 1 (1-based index).
	*/
	uint32_t reuse_fir_from_pdm;
	uint32_t rsvd_1[2];
	struct sof_fir_config fir_config[2];

	/*
	 * Array of FIR coefficients, channel A goes first, then channel B.
	 * Actual size of the array depends on the number of active taps of the
	 * FIR filter for channel A plus the number of active taps of the FIR filter
	 * for channel B (see FIR_CONFIG) as well as on the form (packed/unpacked)
	 * of values.
	 */
	uint32_t fir_coeffs[0];
};

struct sof_dmic_config_blob
{
    /* time-slot mappings */
    uint32_t ts_group[4];

    /* expected value is 1-3ms. typical value is 1ms */
    uint32_t clock_on_delay;

    /*
	 * PDM channels to be programmed using data from channel_cfg array.
	 * i'th bit = 1 means that configuration for PDM channel # i is provided
	 */
    uint32_t channel_ctrl_mask;

    //! PDM channel configuration settings
    /*!
      Actual number of items depends on channel_ctrl_mask (# of 1's).
    */
    uint32_t channel_cfg;

    //! PDM controllers to be programmed using data from pdm_ctrl_cfg array.
    /*!
      i'th bit = 1 means that configuration for PDM controller # i is provided.
    */
    uint32_t pdm_ctrl_mask;

    //! PDM controller configuration settings
    /*!
      Actual number of items depends on pdm_ctrl_mask (# of 1's).
    */
    struct sof_pdm_ctrl_cfg pdm_ctrl_cfg[0];
} ;

struct sof_gtw_attributes {
	// Gateway data requested in low power memory.
	uint32_t lp_buffer_alloc : 1;

	//Gateway data requested in register file memory.
	uint32_t alloc_from_reg_file : 1;

	// Reserved field
	uint32_t _rsvd : 30;
} ;

//DMIC gateway configuration data
struct sof_dmic_config_data
{
    struct sof_gtw_attributes gtw_attributes;
    struct sof_dmic_config_blob dmic_config_blob;
} ;

struct decim_modes {
	int16_t clkdiv[DMIC_MAX_MODES];
	int16_t mcic[DMIC_MAX_MODES];
	int16_t mfir[DMIC_MAX_MODES];
	int num_of_modes;
};

struct matched_modes {
	int16_t clkdiv[DMIC_MAX_MODES];
	int16_t mcic[DMIC_MAX_MODES];
	int16_t mfir_a[DMIC_MAX_MODES];
	int16_t mfir_b[DMIC_MAX_MODES];
	int num_of_modes;
};

struct dmic_configuration {
	struct pdm_decim *fir_a;
	struct pdm_decim *fir_b;
	int clkdiv;
	int mcic;
	int mfir_a;
	int mfir_b;
	int cic_shift;
	int fir_a_shift;
	int fir_b_shift;
	int fir_a_length;
	int fir_b_length;
	int32_t fir_a_scale;
	int32_t fir_b_scale;
};

struct pdm_controllers_configuration {
	uint32_t cic_control;
	uint32_t cic_config;
	uint32_t mic_control;
	uint32_t fir_control_a;
	uint32_t fir_config_a;
	uint32_t dc_offset_left_a;
	uint32_t dc_offset_right_a;
	uint32_t out_gain_left_a;
	uint32_t out_gain_right_a;
	uint32_t fir_control_b;
	uint32_t fir_config_b;
	uint32_t dc_offset_left_b;
	uint32_t dc_offset_right_b;
	uint32_t out_gain_left_b;
	uint32_t out_gain_right_b;
};


#endif

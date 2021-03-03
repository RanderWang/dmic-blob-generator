typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;

struct sof_ipc_dai_dmic_pdm_ctrl {
	uint16_t id;		/**< PDM controller ID */

	uint16_t enable_mic_a;	/**< Use A (left) channel mic (0 or 1)*/
	uint16_t enable_mic_b;	/**< Use B (right) channel mic (0 or 1)*/

	uint16_t polarity_mic_a; /**< Optionally invert mic A signal (0 or 1) */
	uint16_t polarity_mic_b; /**< Optionally invert mic B signal (0 or 1) */

	uint16_t clk_edge;	/**< Optionally swap data clock edge (0 or 1) */
	uint16_t skew;		/**< Adjust PDM data sampling vs. clock (0..15) */

	uint16_t reserved[3];	/**< Make sure the total size is 4 bytes aligned */
} ;

struct sof_ipc_dai_dmic_params {
	uint32_t driver_ipc_version;	/**< Version (1..N) */

	uint32_t pdmclk_min;	/**< Minimum microphone clock in Hz (100000..N) */
	uint32_t pdmclk_max;	/**< Maximum microphone clock in Hz (min...N) */

	uint32_t fifo_fs;	/**< FIFO sample rate in Hz (8000..96000) */
	uint32_t reserved_1;	/**< Reserved */
	uint16_t fifo_bits;	/**< FIFO word length (16 or 32) */
	uint16_t fifo_bits_b;	/**< Deprecated since firmware ABI 3.0.1 */

	uint16_t duty_min;	/**< Min. mic clock duty cycle in % (20..80) */
	uint16_t duty_max;	/**< Max. mic clock duty cycle in % (min..80) */

	uint32_t num_pdm_active; /**< Number of active pdm controllers. */
				 /**< Range is 1..SOF_DAI_INTEL_DMIC_NUM_CTRL */

	uint32_t wake_up_time;      /**< Time from clock start to data (us) */
	uint32_t min_clock_on_time; /**< Min. time that clk is kept on (us) */
	uint32_t unmute_ramp_time;  /**< Length of logarithmic gain ramp (ms) */

	/* reserved for future use */
	uint32_t reserved[5];

	/**< PDM controllers configuration */
	struct sof_ipc_dai_dmic_pdm_ctrl pdm[4];
} ;

/* general purpose DAI configuration */
struct sof_ipc_dai_config {
	uint32_t type;		/**< DAI type - enum sof_ipc_dai_type */
	uint32_t dai_index;	/**< index of this type dai */

	/* physical protocol and clocking */
	uint16_t format;	/**< SOF_DAI_FMT_ */
	uint16_t reserved16;	/**< alignment */

	/* reserved for future use */
	uint32_t reserved[8];

	/* HW specific data */
	struct sof_ipc_dai_dmic_params dmic;
} __packed;

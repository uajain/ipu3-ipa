/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Incorporate equivalent structures for the AIC algorithms without requiring
 * all of the header based implementation provided by the IA AIQ library
 * headers.
 */

#include <string>

#include <libcamera/geometry.h>
#include <libcamera/ipa/ipu3_ipa_interface.h>

#include <linux/intel-ipu3.h>

#include "kbl_aic.h"

#include "aiq/aiq_results.h"
#include "binary_data.h"
#include "ipu3_isp_pipe.h"

#ifndef IPA_IPU3_AIC_H
#define IPA_IPU3_AIC_H

namespace libcamera::ipa::ipu3::aic {

class AIC
{
public:
	~AIC();

	int init(BinaryData &aiqb);
	void reset();
	int run(ipu3_uapi_params *params);
	aic_config_t *GetAicConfig();
	void updateRuntimeParams(aiq::AiqResults &results);
	std::string version();
	int configure(const struct IPAConfigInfo &configInfo);

private:
	/** \todo: Only a single AIC_MODE is supported currently. */
	std::unique_ptr<KBL_AIC> skyCam_;
	std::unique_ptr<IPU3ISPPipe> pipe_;

	ia_cmc_t *iaCmc_;

	/* IPU3AICRuntimeParams pointer contents */
	ia_aiq_output_frame_parameters_t runtimeOutFrameParams_;
	aic_resolution_config_parameters_t runtimeResCfgParams_;
	aic_input_frame_parameters_t runtimeInFrameParams_;
	ia_rectangle runtimeParamsRec_;
	IPU3AICRuntimeParams runtimeParams_;
};

} /* namespace libcamera::ipa::ipu3::aic */

#endif /* IPA_IPU3_AIC_H */


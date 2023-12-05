/*
 Copyright (C) 2016 Susi Lehtola

 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/


#include "util.h"

#define XC_MGGA_C_LMF_TMHF          735 /* TMHF local mixing function (common) */
#define XC_MGGA_C_LMF_TMHF3P          736 /* TMHF local mixing function (common) */

typedef struct{
  double beta, lambda, parc;
} mgga_c_lmf_tmhf_params;

static void
mgga_c_lmf_tmhf_init(xc_func_type *p)
{
  assert(p!=NULL && p->params == NULL);
  p->params = libxc_malloc(sizeof(mgga_c_lmf_tmhf_params));
}

#define LMF_TMHF_N_PARS 3
static const char  *lmf_tmhf_names[LMF_TMHF_N_PARS]  = {"beta", "lambda", "parc"};
static const char  *lmf_tmhf_desc[LMF_TMHF_N_PARS]   = {
  "beta",
  "lambda", 
  "decay parameter in the exponent of mixing function"
};

static const double lmf_tmhf_values[LMF_TMHF_N_PARS] = {
  79.873, 0.6866, 0.180
};

static const double lmf_tmhf3p_values[LMF_TMHF_N_PARS] = {
  265.25, 1.0, 0.215
};

#include "maple2c/mgga_exc/mgga_c_ldme_common.c"
#include "work_mgga.c"

#ifdef __cplusplus
extern "C"
#endif
const xc_func_info_type xc_func_info_mgga_c_lmf_tmhf = {
  XC_MGGA_C_LMF_TMHF,
  XC_CORRELATION,
  "TMHF local mixing function (common)",
  XC_FAMILY_MGGA,
  {&xc_ref_Holzer2022, NULL, NULL, NULL, NULL},
  XC_FLAGS_3D | XC_FLAGS_NEEDS_TAU | MAPLE2C_FLAGS,
  1e-15,
  {LMF_TMHF_N_PARS, lmf_tmhf_names, lmf_tmhf_desc, lmf_tmhf_values, set_ext_params_cpy},
  mgga_c_lmf_tmhf_init, NULL,
  NULL, NULL, &work_mgga,
};

#ifdef __cplusplus
extern "C"
#endif
const xc_func_info_type xc_func_info_mgga_c_lmf_tmhf3p = {
  XC_MGGA_C_LMF_TMHF3P,
  XC_CORRELATION,
  "TMHF3P local mixing function (common)",
  XC_FAMILY_MGGA,
  {&xc_ref_Holzer2022, NULL, NULL, NULL, NULL},
  XC_FLAGS_3D | XC_FLAGS_NEEDS_TAU | MAPLE2C_FLAGS,
  1e-15,
  {LMF_TMHF_N_PARS, lmf_tmhf_names, lmf_tmhf_desc, lmf_tmhf3p_values, set_ext_params_cpy},
  mgga_c_lmf_tmhf_init, NULL,
  NULL, NULL, &work_mgga,
};


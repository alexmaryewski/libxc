/*
 Copyright (C) 2008 M.A.L. Marques

 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "util.h"

#define XC_MGGA_X_TM          540 /* Tao and Mo 2016 exchange */
#define XC_MGGA_X_TMHF          737 /* Tao and Mo 2016 exchange */

#include "maple2c/mgga_exc/mgga_x_tm.c"
#include "work_mgga.c"

#define TM_N_PAR 2

typedef struct{
  double beta, lambda;
} mgga_x_tm_params;

static void
mgga_x_tm_init(xc_func_type *p)
{
  assert(p!=NULL && p->params == NULL);
  p->params = libxc_malloc(sizeof(mgga_x_tm_params));
}

static const char  *tm_names[TM_N_PAR]  = {"beta", "lambda",};
static const char  *tm_desc[TM_N_PAR]   = {"beta", "lambda"};

/* TMHF coefficients for TM semilocal exchange (2022): 
  10.1063/5.0100439 */
static const double tmhf_values[TM_N_PAR] = {265.25, 1.0};

/* Original TM coefficients (2016) */
static const double tm_values[TM_N_PAR] = {79.873, 0.6866};


#ifdef __cplusplus
extern "C"
#endif
const xc_func_info_type xc_func_info_mgga_x_tmhf = {
  XC_MGGA_X_TMHF,
  XC_EXCHANGE,
  "Tao and Mo exchange from TMHF local hybrid (2022)",
  XC_FAMILY_MGGA,
  {&xc_ref_Holzer2022, NULL, NULL, NULL, NULL},
  XC_FLAGS_3D | XC_FLAGS_NEEDS_TAU | MAPLE2C_FLAGS,
  1e-15,
  {TM_N_PAR, tm_names, tm_desc, tmhf_values, set_ext_params_cpy},
  mgga_x_tm_init, NULL,
  NULL, NULL, &work_mgga,
};

#ifdef __cplusplus
extern "C"
#endif
const xc_func_info_type xc_func_info_mgga_x_tm = {
  XC_MGGA_X_TM,
  XC_EXCHANGE,
  "Tao and Mo exchange (2016)",
  XC_FAMILY_MGGA,
  {&xc_ref_Tao2016_073001, NULL, NULL, NULL, NULL},
  XC_FLAGS_3D | XC_FLAGS_NEEDS_TAU | MAPLE2C_FLAGS,
  1e-15,
  {TM_N_PAR, tm_names, tm_desc, tm_values, set_ext_params_cpy},
  mgga_x_tm_init, NULL,
  NULL, NULL, &work_mgga,
};



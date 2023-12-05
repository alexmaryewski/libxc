/*
 Copyright (C) 2016 Susi Lehtola

 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/


#include "util.h"

#define XC_MGGA_C_LDME_COMMON          735 /* TMHF local mixing function (common) */

#include "maple2c/mgga_exc/mgga_c_ldme_common.c"
#include "work_mgga.c"

#ifdef __cplusplus
extern "C"
#endif
const xc_func_info_type xc_func_info_mgga_c_ldme_common = {
  XC_MGGA_C_LDME_COMMON,
  XC_CORRELATION,
  "TMHF local mixing function (common)",
  XC_FAMILY_MGGA,
  {&xc_ref_Holzer2022, NULL, NULL, NULL, NULL},
  XC_FLAGS_3D | XC_FLAGS_NEEDS_TAU | MAPLE2C_FLAGS,
  1e-15,
  {0, NULL, NULL, NULL, NULL},
  NULL, NULL,
  NULL, NULL, &work_mgga,
};

// TODO: AFAIK, no initialization is needed,
//       but is that really so?
//
// static void
// mgga_c_ldme_common_init(xc_func_type *p)
// {
//   static int   funcs_id  [1] = {XC_MGGA_C_LDME_COMMON};
//   static double funcs_coef[1] = {1.0};

//   xc_mix_init(p, 1, funcs_id, funcs_coef);

//   // p->nlc_b = 15.7;
//   // p->nlc_C = 0.0093;
// }

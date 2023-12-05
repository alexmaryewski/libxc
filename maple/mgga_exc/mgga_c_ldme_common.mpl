(*
 Copyright (C) 2017 M.A.L. Marques
               2019 Susi Lehtola
               2022 Christof Holzer

 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
*)

(* type: mgga_exc *)

(* total density *)
n  := (rs) -> 3/(4*Pi*rs^3):

(* convention of libxc *)
tp := (rs, z, xt) -> tt(rs, z, xt):

(* tm_lambda := 0.6866: *)
(* tm_beta   := 79.873: *)

(* below Equation (6) of Tao-Mo *) 
tm_p  := x -> (X2S*x)^2:
tm_y  := x -> (2.0*tm_lambda - 1.0)^2 * tm_p(x):

(* Equation (7) of Tao-Mo *)
tm_f0 := x -> (1 + 10*(70*tm_y(x)/27) + tm_beta*tm_y(x)^2)^(1/10):

(* after Equation (9) of Tao-Mo *)
tm_R  := (x, t) -> 1 + 595*(2.0*tm_lambda - 1)^2 * tm_p(x)/54 \
   - (t - 3.0*(tm_lambda^2 - tm_lambda + 1/2)*(t - K_FACTOR_C - x^2/72))/K_FACTOR_C:

tm_fx_DME := (x, t) -> 1/tm_f0(x)^2 + 7*tm_R(x, t)/(9*tm_f0(x)^4):

(* build correlation length from our hole approximation (|U_a|^-1 + |U_b|^-1) *)
f_DME := (rs, z, x, t) -> 1/m_abs(2*X_FACTOR_C*n_spin(rs, z)^(1/3)*tm_fx_DME(x, t))
                       +  1/m_abs(2*X_FACTOR_C*n_spin(rs,-z)^(1/3)*tm_fx_DME(x, t)):

(* map unto interval 0..1 using exponent *)
chyf_f := (rs, z, xt, xs0, xs1, ts0, ts1)  -> 1-exp(-parc*f_DME(rs, z, 2^(1/3)*xt, 2^(2/3)*t_total(z, ts0, ts1))):

(* density is intrinsically multiplied afterwards, undo this *)
f := (rs, z, xt, xs0, xs1, u0, u1, t0, t1) -> chyf_f(rs, z, xt, xs0, xs1, t0, t1)/n(rs):
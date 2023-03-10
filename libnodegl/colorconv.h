/*
 * Copyright 2019-2022 GoPro Inc.
 * Copyright 2019-2022 Clément Bœsch <u pkh.me>
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef COLORCONV_H
#define COLORCONV_H

#include "image.h"
#include "params.h"

#define NGLI_COLORCONV_SPACE_SRGB   0
#define NGLI_COLORCONV_SPACE_HSL    1
#define NGLI_COLORCONV_SPACE_HSV    2

extern const struct param_choices ngli_colorconv_colorspace_choices;

int ngli_colorconv_get_ycbcr_to_rgb_color_matrix(float *dst, const struct color_info *info, float scale);

void ngli_colorconv_srgb2linear(float *dst, const float *srgb);
void ngli_colorconv_hsl2linear(float *dst, const float *hsl);
void ngli_colorconv_hsv2linear(float *dst, const float *hsv);

void ngli_colorconv_hsl2srgb(float *dst, const float *hsl);
void ngli_colorconv_hsv2srgb(float *dst, const float *hsv);

void ngli_colorconv_linear2srgb(float *dst, const float *rgb);

#endif

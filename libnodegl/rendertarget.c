/*
 * Copyright 2018-2022 GoPro Inc.
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

#include "gpu_ctx.h"
#include "rendertarget.h"

struct rendertarget *ngli_rendertarget_create(struct gpu_ctx *gpu_ctx)
{
    return gpu_ctx->cls->rendertarget_create(gpu_ctx);
}

int ngli_rendertarget_init(struct rendertarget *s, const struct rendertarget_params *params)
{
    return s->gpu_ctx->cls->rendertarget_init(s, params);
}

void ngli_rendertarget_freep(struct rendertarget **sp)
{
    if (!*sp)
        return;
    (*sp)->gpu_ctx->cls->rendertarget_freep(sp);
}

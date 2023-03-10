/*
 * Copyright 2019-2022 GoPro Inc.
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
#include "pipeline.h"

struct pipeline *ngli_pipeline_create(struct gpu_ctx *gpu_ctx)
{
    return gpu_ctx->cls->pipeline_create(gpu_ctx);
}

int ngli_pipeline_init(struct pipeline *s, const struct pipeline_params *params)
{
    return s->gpu_ctx->cls->pipeline_init(s, params);
}

int ngli_pipeline_set_resources(struct pipeline *s, const struct pipeline_resources *resources)
{
    return s->gpu_ctx->cls->pipeline_set_resources(s, resources);
}

int ngli_pipeline_update_attribute(struct pipeline *s, int index, const struct buffer *buffer)
{
    return s->gpu_ctx->cls->pipeline_update_attribute(s, index, buffer);
}

int ngli_pipeline_update_uniform(struct pipeline *s, int index, const void *value)
{
    return s->gpu_ctx->cls->pipeline_update_uniform(s, index, value);
}

int ngli_pipeline_update_texture(struct pipeline *s, int index, const struct texture *texture)
{
    return s->gpu_ctx->cls->pipeline_update_texture(s, index, texture);
}

int ngli_pipeline_update_buffer(struct pipeline *s, int index, const struct buffer *buffer, int offset, int size)
{
    return s->gpu_ctx->cls->pipeline_update_buffer(s, index, buffer, offset, size);
}

void ngli_pipeline_draw(struct pipeline *s, int nb_vertices, int nb_instances)
{
    s->gpu_ctx->cls->pipeline_draw(s, nb_vertices, nb_instances);
}

void ngli_pipeline_draw_indexed(struct pipeline *s, const struct buffer *indices, int indices_format, int nb_indices, int nb_instances)
{
    s->gpu_ctx->cls->pipeline_draw_indexed(s, indices, indices_format, nb_indices, nb_instances);
}

void ngli_pipeline_dispatch(struct pipeline *s, int nb_group_x, int nb_group_y, int nb_group_z)
{
    s->gpu_ctx->cls->pipeline_dispatch(s, nb_group_x, nb_group_y, nb_group_z);
}

void ngli_pipeline_freep(struct pipeline **sp)
{
    if (!*sp)
        return;
    (*sp)->gpu_ctx->cls->pipeline_freep(sp);
}

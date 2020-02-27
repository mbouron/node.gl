#
# Copyright 2020 GoPro Inc.
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

TEXTURE_TEST_NAMES =        \
    3d                      \
    clear_and_scissor       \
    cubemap                 \
    cubemap_from_mrt        \
    data                    \
    data_animated           \
    data_unaligned_row      \
    mipmap                  \

ifneq ($(DISABLE_TESTS_SAMPLES),yes)
TEXTURE_TEST_NAMES +=       \
    cubemap_from_mrt_msaa   \

endif

$(eval $(call DECLARE_REF_TESTS,texture,$(TEXTURE_TEST_NAMES)))

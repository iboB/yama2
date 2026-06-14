# Copyright (c) Borislav Stanimirov
# SPDX-License-Identifier: MIT
#
add_library(yama INTERFACE)
add_library(yama::yama ALIAS yama)

target_sources(yama
    INTERFACE FILE_SET HEADERS FILES
)

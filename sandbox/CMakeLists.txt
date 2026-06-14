# Copyright (c) Borislav Stanimirov
# SPDX-License-Identifier: MIT
#
add_executable(yama-sandbox
    sandbox.cpp
)
target_link_libraries(yama-sandbox PRIVATE yama::yama)
set_target_properties(yama-sandbox PROPERTIES FOLDER sandbox)

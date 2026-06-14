# Copyright (c) Borislav Stanimirov
# SPDX-License-Identifier: MIT
#
CPMAddPackage(gh:iboB/picobench@2.8.0)

macro(yama_benchmark name)
    set(tgt bench-yama-${name})
    add_executable(${tgt})
    set_target_properties(${tgt} PROPERTIES FOLDER bench)
    target_sources(${tgt} PRIVATE ${ARGN})
    target_link_libraries(${tgt} PRIVATE yama::yama picobench::picobench)
    add_custom_target(
        run-${tgt}
        COMMAND ${tgt}
    )
    set_target_properties(run-${tgt} PROPERTIES FOLDER bench)
endmacro()

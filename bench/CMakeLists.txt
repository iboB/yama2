# Copyright (c) Borislav Stanimirov
# SPDX-License-Identifier: MIT
#
CPMAddPackage(gh:iboB/picobench@2.9.0)
CPMAddPackage(gh:iboB/splat@1.3.5)
CPMAddPackage(gh:iboB/itlib@1.12.2)

macro(yama_benchmark name)
    set(tgt bench-yama-${name})
    add_executable(${tgt})
    set_target_properties(${tgt} PROPERTIES FOLDER bench)
    target_sources(${tgt} PRIVATE b-${name}.cpp)
    target_link_libraries(${tgt} PRIVATE yama::yama picobench::picobench splat::splat itlib::itlib)
    add_custom_target(
        run-${tgt}
        COMMAND ${tgt}
    )
    # set_target_properties(run-${tgt} PROPERTIES FOLDER bench)
endmacro()

add_subdirectory(poc)

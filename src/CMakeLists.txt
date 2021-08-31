project(src)

set(
        src

        main.cpp
        token.cpp
        scanner.cpp
        parser.cpp
        file.cpp
        error.cpp
        position.cpp
        util.cpp
        ast/expr.cpp
        ast/block_expr.cpp
        ast/expr_group.cpp
        ast/ident.cpp
        ast/binary_expr.cpp
        ast/unary_expr.cpp
        ast/bad_expr.cpp
        ast/basic_lit.cpp
        ast/paren_expr.cpp
        ast/call_expr.cpp
        ast/field_list.cpp
        ast/return_expr.cpp
        ast/decl/fun_decl_expr.cpp
        ast/decl/decl_expr.cpp
        ast/decl/var_decl_expr.cpp
        ast/decl/val_decl_expr.cpp
        ast/decl/expr_list.cpp
        code_generator.cpp
        ast/script.cpp
)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(crane ${src})

llvm_map_components_to_libnames(llvm_libs support core orcjit native irreader)

target_link_libraries(crane ${llvm_libs})

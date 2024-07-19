# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(qiqqa_backendTests LANGUAGES CXX)

# ---- Tests ----

add_executable(qiqqa_backend_test source/qiqqa_backend_test.cpp)
target_link_libraries(qiqqa_backend_test PRIVATE qiqqa_backend_lib)
target_compile_features(qiqqa_backend_test PRIVATE cxx_std_20)

add_test(NAME qiqqa_backend_test COMMAND qiqqa_backend_test)

# ---- End-of-file commands ----

add_folders(Test)

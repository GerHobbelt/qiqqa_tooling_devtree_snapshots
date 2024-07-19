install(
    TARGETS qiqqa_backend_exe
    RUNTIME COMPONENT qiqqa_backend_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()

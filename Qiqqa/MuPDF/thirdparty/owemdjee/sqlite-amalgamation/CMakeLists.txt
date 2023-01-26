cmake_minimum_required(VERSION 3.8)
project(SQLite3
    VERSION   3.40.0
    LANGUAGES C
    )

include(GNUInstallDirs)

# Helpers for debugging CMakeFiles
include(CMakePrintHelpers)

#------------------------------------------------------------------------------
# build options and optional modules:
option(SQLITE_ENABLE_DBSTAT_VTAB    "enables dbstat virtual table"                    ON)
option(SQLITE_ENABLE_FTS3           "enables full text searches version 3"            OFF)
option(SQLITE_ENABLE_FTS4           "enables full text searches version 3 & 4"        ON)
option(SQLITE_ENABLE_FTS5           "enables full text searches version 5"            ON)
option(SQLITE_ENABLE_GEOPOLY        "enables Geopoly extension"                       OFF)
option(SQLITE_ENABLE_ICU            "enables international components for unicode"    OFF)
option(SQLITE_ENABLE_MATH_FUNCTIONS "enables the built-in SQL math functions"         ON)
option(SQLITE_ENABLE_RBU            "enables resumable bulk update extension"         ON)
option(SQLITE_ENABLE_RTREE          "enables R*TRee index extension"                  ON)
option(SQLITE_ENABLE_STAT4          "enhances query planner under certain situations" OFF)
option(SQLITE_USE_URI               "enables the default URI filename processing"     OFF)

option(SQLITE_ENABLE_API_ARMOR               "enables API armor: more rigorous API invocation checking"     ON)
option(SQLITE_ENABLE_EXPENSIVE_ASSERT        "enables expensive checks of the mapping hash table"     OFF)
option(SQLITE_ENABLE_FTS3_PARENTHESIS        "enables using the new parser for FTS3, i.e. same syntax for FTS4 and FTS3 queries"     ON)
option(SQLITE_ENABLE_SQLLOG                  "enables SQLite activity logging via xSqllog callback"     ON)
option(SQLITE_LOG_CACHE_SPILL                "enables SQLite spill page logging"     ON)
option(SQLITE_ENABLE_IOTRACE                 "enables I/O tracing via sqlite3IoTrace (a pointer to a printf-like routine used to print I/O tracing messages"     ON)
option(SQLITE_ENABLE_SELECTTRACE             "enables the Select query generator tracing logic"     ON)
option(SQLITE_ENABLE_WHERETRACE              "enables the Where query generator tracing logic"     ON)
option(SQLITE_PERFORMANCE_TRACE              "enables the SQLite performance tracing logic"     ON)
option(SQLITE_LOCK_TRACE                     "enables the print out of information about all locking operations"     ON)
option(SQLITE_USE_FCNTL_TRACE                "enables fcntl() tracing logic"     ON)
option(SQLITE_FORCE_OS_TRACE                 "enables tracing logic for OS level API calls done by SQLite"     ON)
option(SQLITE_ENABLE_OVERSIZE_CELL_CHECK     "enables the Btree oversized page checks on startup / database open"     ON)
option(SQLITE_DEBUG                          "enables SQLite debugging APIs, etc."     ON)
option(SQLITE_ENABLE_ATOMIC_WRITE            "enables both non-atomic and atomic writes"     ON)
option(SQLITE_ENABLE_BATCH_ATOMIC_WRITE      "enables both non-atomic and atomic batch writes"     ON)
option(SQLITE_ENABLE_COLUMN_METADATA         "enables the sqlite3_column_* column metadata APIs"     ON)
option(SQLITE_ENABLE_COLUMN_USED_MASK        "enables identification of the table/index columns used for a cursor"     ON)
option(SQLITE_ENABLE_COSTMULT                "enables the cost multiplier in the query compiler"     ON)
option(SQLITE_ENABLE_CURSOR_HINTS            "enables providing hints to the cursor"     ON)
option(SQLITE_ENABLE_HIDDEN_COLUMNS          "enables the use of the __hidden__ table column"     OFF)
option(SQLITE_ENABLE_STMT_SCANSTATUS         "enables the Prepared Statement Scan Status feature"     ON)
option(SQLITE_ENABLE_PREUPDATE_HOOK          "enables the pre-update hook: a callback function that is invoked prior to each [INSERT], [UPDATE], and [DELETE] operation on a database table"     ON)
option(SQLITE_ENABLE_UNLOCK_NOTIFY           "enables the invocation of a user-defined callback when the connection currently holding the required lock relinquishes it"     ON)
option(SQLITE_ENABLE_MEMORY_MANAGEMENT       "enables enhanced memory management: attempt to release as much non-essential memory as possible when release/cleanup APIs are invoked"     ON)
option(SQLITE_ENABLE_NORMALIZE               "enables the normalization of SQL queries"     ON)
option(SQLITE_ENABLE_NULL_TRIM               "enables the trimming of records with trailing NULL columns"     OFF)
option(SQLITE_ENABLE_EXPLAIN_COMMENTS        "enables EXPLAIN comments for enhanced readability"     ON)
option(SQLITE_EXPLAIN_ESTIMATED_ROWS         "enables the inclusion of row estimates in the EXPLAIN and EXPLAIN QUERY PLAN queries"     ON)
option(SQLITE_ENABLE_UNKNOWN_SQL_FUNCTION    "enables the automatic substituted of 'unknown' in place of any unrecognized function name when doing an EXPLAIN or EXPLAIN QUERY PLAN"     ON)
option(SQLITE_ENABLE_QPSG                    "enables the Query Planner Stability Guarantee"     OFF)
option(SQLITE_ENABLE_SESSION                 "enables the sqlite3session extension"     ON)
option(SQLITE_ENABLE_SNAPSHOT                "enables database snapshot support"     ON)
option(SQLITE_ENABLE_SORTER_REFERENCES       "enables the external sort optimization for large table column values"     ON)
option(SQLITE_DEFAULT_AUTOMATIC_INDEX        "enables automatic indexes"     OFF)
option(SQLITE_DEFAULT_AUTOVACUUM             "enables automatic 'PRAGMA auto_vacuum = 1' for all tables"     OFF)
option(SQLITE_UNLINK_AFTER_CLOSE             "enables the delete-on-close feature"     ON)
option(SQLITE_OMIT_DECLTYPE                  "omit declared type of columns"                   ON)
option(SQLITE_OMIT_JSON                      "disables JSON SQL functions"                     OFF)

option(SQLITE_RECOMMENDED_OPTIONS   "compile by SQLite3 recommended options"          ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Release or Debug?" FORCE)
endif()

#------------------------------------------------------------------------------

# SQLite3 as static library:
add_library(${PROJECT_NAME} STATIC sqlite3.c sqlite3.h ${CMAKE_BINARY_DIR}/sqlite_features_config.h sqlite_cfg.h)
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME   sqlite3
    PUBLIC_HEADER sqlite3.h
    DEBUG_POSTFIX d
    )
target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PUBLIC # inject user's options
    $<BUILD_INTERFACE:
		_HAVE_SQLITE_CONFIG_H
    >
    )

# platform/compiler specific settings
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
elseif(WIN32 AND ${CMAKE_SIZEOF_VOID_P} LESS 8) # this is a 32bit windows
    option(BUILD_WITH_XPSDK "build for old 32bit (WinXP/2003) targets" OFF)
    if(BUILD_WITH_XPSDK)
        target_compile_definitions(${PROJECT_NAME} PUBLIC
            $<BUILD_INTERFACE:
                -DSQLITE_OS_WINRT=0 -D_WIN32_WINNT=0x0502 -DWINVER=0x0502
            >
            )
    endif()
endif()

#------------------------------------------------------------------------------
configure_file(sqlite_features_config.h.in ${CMAKE_BINARY_DIR}/sqlite_features_config.h)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
install(EXPORT  ${PROJECT_NAME}Config
    NAMESPACE   SQLite::
    DESTINATION cmake
    )
install(FILES
    ${CMAKE_BINARY_DIR}/sqlite_features_config.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

#------------------------------------------------------------------------------
# SQLite3 shell application:
option(BUILD_SHELL "build SQLite3 shell application" ON)
if(BUILD_SHELL)
    add_executable(shell_app shell.c user_code.c sqlite3.h ${CMAKE_BINARY_DIR}/sqlite_features_config.h sqlite_cfg.h)
    set_target_properties(shell_app PROPERTIES OUTPUT_NAME sqlite3)
    target_include_directories(shell_app PRIVATE ${CMAKE_BINARY_DIR})
    target_include_directories(shell_app PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(shell_app PRIVATE ${PROJECT_NAME})
    if(UNIX)
        if(CMAKE_BUILD_TYPE STREQUAL Release)
            add_custom_command(TARGET shell_app POST_BUILD
                COMMAND ${CMAKE_STRIP} sqlite3
                )
        endif()
    elseif(MSVC)
        option(BUILD_SHELL_STATIC "build shell by static c/c++ runtime" ON)
        foreach(flag CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_DEBUG)
            if(BUILD_SHELL_STATIC)
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            else()
                string(REGEX REPLACE "/MT" "/MD" ${flag} "${${flag}}")
            endif()
            set(${flag} "${${flag}}" CACHE STRING "msvc flags" FORCE)
        endforeach()
    endif()
    install(TARGETS shell_app
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
endif()

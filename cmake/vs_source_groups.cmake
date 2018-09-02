
function(_generate_vs_source_groups GROUP_NAME TOP_DIRECTORY CURRENT_SUBDIRECTORY RESULT_FILES)

    file(GLOB headers 
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.h
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.hpp
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.hh
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.hxx
    )

    file(GLOB sources 
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.c
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.cpp
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.cc
         ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*.cxx
    )

    string(REPLACE "/" "\\" subgroups "${CURRENT_SUBDIRECTORY}")

    source_group("${GROUP_NAME}\\${subgroups}" FILES ${headers} ${sources})

    list(APPEND result_files ${headers} ${sources})

    file(GLOB childs RELATIVE ${TOP_DIRECTORY} ${TOP_DIRECTORY}/${CURRENT_SUBDIRECTORY}/*)

    foreach(child ${childs})
        if(IS_DIRECTORY ${TOP_DIRECTORY}/${child})
            _generate_vs_source_groups("${GROUP_NAME}" "${TOP_DIRECTORY}" "${child}" res)
            list(APPEND result_files ${res})
        endif()
    endforeach()

    set(${RESULT_FILES} ${result_files} PARENT_SCOPE)
endfunction()

function(generate_vs_source_groups GROUP_NAME TOP_DIRECTORY RESULT_FILES)
    _generate_vs_source_groups("${GROUP_NAME}" "${TOP_DIRECTORY}" "" ${RESULT_FILES})
    set(${RESULT_FILES} "${${RESULT_FILES}}" PARENT_SCOPE)
endfunction()
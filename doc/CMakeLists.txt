find_package(Doxygen)

set(DOXYFILE ${DOC_DIR}/Doxyfile)

if(DOXYGEN_FOUND)
  configure_file(${DOXYFILE}.in ${DOXYFILE} @ONLY)

  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()

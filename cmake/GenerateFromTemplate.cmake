file(READ "${INPUT}" FILE_CONTENT)
configure_file("${TEMPLATE}" "${OUTPUT}" @ONLY)

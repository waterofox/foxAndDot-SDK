#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MbedTLS::mbedcrypto" for configuration "Debug"
set_property(TARGET MbedTLS::mbedcrypto APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MbedTLS::mbedcrypto PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/mbedcryptod.lib"
  )

list(APPEND _cmake_import_check_targets MbedTLS::mbedcrypto )
list(APPEND _cmake_import_check_files_for_MbedTLS::mbedcrypto "${_IMPORT_PREFIX}/lib/mbedcryptod.lib" )

# Import target "MbedTLS::mbedx509" for configuration "Debug"
set_property(TARGET MbedTLS::mbedx509 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MbedTLS::mbedx509 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/mbedx509d.lib"
  )

list(APPEND _cmake_import_check_targets MbedTLS::mbedx509 )
list(APPEND _cmake_import_check_files_for_MbedTLS::mbedx509 "${_IMPORT_PREFIX}/lib/mbedx509d.lib" )

# Import target "MbedTLS::mbedtls" for configuration "Debug"
set_property(TARGET MbedTLS::mbedtls APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MbedTLS::mbedtls PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/mbedtlsd.lib"
  )

list(APPEND _cmake_import_check_targets MbedTLS::mbedtls )
list(APPEND _cmake_import_check_files_for_MbedTLS::mbedtls "${_IMPORT_PREFIX}/lib/mbedtlsd.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

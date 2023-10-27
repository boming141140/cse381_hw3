if(NOT EXISTS "D:/Desktop/hw3_cse381/HW3/build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: D:/Desktop/hw3_cse381/HW3/build/install_manifest.txt")
endif()

file(READ "D:/Desktop/hw3_cse381/HW3/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "C:/Users/12698/winlibs-x86_64-mcf-seh-gcc-13.1.0-llvm-16.0.2-mingw-w64ucrt-11.0.0-r1/mingw64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif()
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif()
endforeach()

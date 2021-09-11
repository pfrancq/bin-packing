#ok, this file contain specific project definition
# - dependency checks
# - file to compile
# - sub project,
# - ...

#normaly all def in CMakeLists.txt
PROJECT(rbp CXX)

R_LOAD_DEPENDENCY("R" "R_LIB" "r")

SET(SUB_PROJECT rbp)
ADD_SUBDIRECTORY(rbp)

###file to install
##keep this macro for galilei based project in a standard place
INSTALL(FILES rbpmacro.cmake DESTINATION share/r)

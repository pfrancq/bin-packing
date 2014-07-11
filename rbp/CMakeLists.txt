PROJECT(rbp)
INCLUDE_DIRECTORIES(.)

SET(rbp_TARGET_SOURCES
	rbp.cpp
	rbpproblem.cpp
)

SET(rbp_INST_INCLUDES
	rbp.h
	rchromobp.h
	rchromobp.hh
	rfirstfitdesheuristic.h
	rfirstfitdesheuristic.hh
	rgroupbp.h
	rgroupbp.hh
	rinstbp.h
	rinstbp.hh
	rbpproblem.h
)

INCLUDE_DIRECTORIES(${rp_INCLUDES})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

IF(WIN32)
    ADD_LIBRARY(rbp STATIC ${rbp_TARGET_SOURCES})
    SET_TARGET_PROPERTIES(rbp PROPERTIES LINK_FLAGS "/NODEFAULTLIB:MSVCRTD;MSVCRT;LIBCMT;LIBCMTD")
    TARGET_LINK_LIBRARIES(rbp roptimization rmath rcore)
ELSE(WIN32)
    ADD_LIBRARY(rbp SHARED ${rbp_TARGET_SOURCES})
    TARGET_LINK_LIBRARIES(rbp roptimization rcore rmath dl)
ENDIF(WIN32)

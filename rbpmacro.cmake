MACRO(DO_RBP_R_LIB_INCLUDE _libPath)
        INCLUDE_DIRECTORIES("${_libPath}/rbp")
	    INCLUDE_DIRECTORIES("${_libPath}/build")
        
        LINK_DIRECTORIES(${_libPath}/build/rbp ${_libPath}/rbp/lib)
ENDMACRO(DO_RBP_R_LIB_INCLUDE)

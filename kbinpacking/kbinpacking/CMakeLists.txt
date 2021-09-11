PROJECT(kbinpacking)
INCLUDE_DIRECTORIES(.)

SET (KBINPACKING_SOURCES
	main.cpp
	kbinpacking.cpp
	kappoptions.cpp
	kbpprjview.cpp
	qdrawgroups.cpp
	kbpgaview.cpp
	
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

KDE4_HANDLE_AUTOMOC(${KBINPACKING_SOURCES})

KDE4_ADD_UI_FILES(KBINPACKING_SOURCES
	kappoptions.ui
	kbpprjview.ui
	kbpgaview.ui
	qdrawgroups.ui
)


KDE4_ADD_EXECUTABLE(kbinpacking ${KBINPACKING_SOURCES})
TARGET_LINK_LIBRARIES(kbinpacking rbp roptimization rcore rcoreqt roptimizationqt rmath ${KDE4_KDEUI_LIBS} ${KDE4_KDECORE_LIBS} ${KDE4_KPARTS_LIBS})


########### install files ###############
install(TARGETS kbinpacking ${INSTALL_TARGETS_DEFAULT_ARGS})
install( FILES kbinpacking.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install(FILES kbinpackingui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kbinpacking )
install(FILES kbinpackingui.rc  DESTINATION  /usr/share/kde4/apps/kbinpacking )
kde4_install_icons(${ICON_INSTALL_DIR})
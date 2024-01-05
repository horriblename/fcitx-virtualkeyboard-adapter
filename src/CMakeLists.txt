add_library(virtualkeyboardadapter MODULE
	VirtualKeyboardAdapter.cpp)

target_link_libraries(virtualkeyboardadapter
	Fcitx5::Core
)

install(TARGETS virtualkeyboardadapter DESTINATION "${FCITX_INSTALL_ADDONDIR}")
configure_file(virtualkeyboardadapter.conf.in virtualkeyboardadapter.conf)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/virtualkeyboardadapter.conf" 
	DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon"
)

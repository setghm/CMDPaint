file(GLOB EXAMPLE_SOURCES "./*.cpp")

foreach (EXAMPLE_FILE ${EXAMPLE_SOURCES})

	get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)

	add_executable(${EXAMPLE_NAME}
		"../../loader/cpp-loader/bytecolor_loader.hpp"
		"../../loader/cpp-loader/bytecolor_loader.cpp"
		${EXAMPLE_FILE}
	)

	set_target_properties(${EXAMPLE_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
	)

	target_include_directories(${EXAMPLE_NAME} PRIVATE "../../loader/cpp-loader")

	file(GLOB BYTECOLOR_IMAGES "../*.bytecolor")
	file(COPY ${BYTECOLOR_IMAGES} DESTINATION "${CMAKE_BINARY_DIR}/examples")

endforeach()

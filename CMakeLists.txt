# CMDPaint
# setghm (c) 2024
#
cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMDPaint")

include_directories("src/")

list(APPEND SOURCE_FILES
	"src/main.cpp"
	
	"src/app/App.cpp"
	"src/app/App.hpp"
	"src/app/Configuration.hpp"

	"src/core/core.hpp"
	"src/core/framework.hpp"
	"src/core/console/Console.cpp"
	"src/core/console/Console.hpp"
	"src/core/input/input.hpp"
	"src/core/controls/controls.hpp"
	"src/core/controls/Button.cpp"
	"src/core/controls/Button.hpp"
	"src/core/controls/Divider.cpp"
	"src/core/controls/Divider.hpp"
	"src/core/controls/Edit.cpp"
	"src/core/controls/Edit.hpp"
	"src/core/controls/Label.cpp"
	"src/core/controls/Label.hpp"
	"src/core/controls/Element.hpp"

	"src/components/components.hpp"
	"src/components/ComponentTypes.hpp"
	"src/components/canvas/Canvas.cpp"
	"src/components/canvas/Canvas.hpp"
	"src/components/canvas/CanvasActions.cpp"
	"src/components/canvas/CanvasActions.hpp"
	"src/components/file_manager/FileManager.cpp"
	"src/components/file_manager/FileManager.hpp"
	"src/components/helpers/ComponentHelpers.cpp"
	"src/components/helpers/ComponentHelpers.hpp"
	"src/components/user_interface/UserInterface.cpp"
	"src/components/user_interface/UserInterface.hpp"
)

add_executable (CMDPaint ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMDPaint PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.

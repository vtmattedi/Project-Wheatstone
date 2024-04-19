# Set the include directories for the subfolder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the header files to the project
set(HEADER_FILES
    Logger.h
    # Add more header files here
)

# Add the header files to the project's target
#target_sources(App1 STATIC IMPORTED ${HEADER_FILES})
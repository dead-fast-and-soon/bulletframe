
# include() macro
# stores all arguments in PROJ_INCLUDES variable
# ===============================================

set(BF_SOURCES "" CACHE INTERNAL "lists")

macro(add_sources)
	set(BF_SOURCES ${BF_SOURCES} ${ARGV} CACHE INTERNAL "lists")
endmacro()

set(BF_LINKS "" CACHE INTERNAL "lists")

macro(add_libs)
	set(BF_LINKS ${BF_LINKS} ${ARGV} CACHE INTERNAL "lists")
	foreach(ARG ${ARGN})
		add_dependencies(${PROJECT_NAME} ${ARG})
		target_link_libraries(${PROJECT_NAME} ${ARG})
	endforeach()
endmacro()

# Entity Interface
# ===============================================

add_sources("entity.cpp")

# Engine Interface
# ===============================================

# bf_include(engine.cpp)

# Event Bus (Subscribe / Post System)
# ===============================================

add_sources("eventbus.cpp")

# Bullet Class
# ===============================================

add_sources("bullet.cpp")

# Add to add_library
# ===============================================

add_library(${PROJECT_NAME} SHARED ${BF_SOURCES})

# Link Libraries
# ===============================================

add_libs("octal")
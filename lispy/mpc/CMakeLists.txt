file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.c include/*.h)
add_library(mpc STATIC ${srcs})
target_include_directories(mpc PUBLIC include)

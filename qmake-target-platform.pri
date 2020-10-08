linux {
  CONFIG += PLATFORM_LINUX
# message(PLATFORM_LINUX)

  # Make QMAKE_TARGET arch available for linux
  !contains(QT_ARCH, x86_64) {
     QMAKE_TARGET.arch = x86
  } else {
    QMAKE_TARGET.arch = x86_64
  }

  linux-g++{
    CONFIG += COMPILER_GCC
#   message(COMPILER_GCC)
  }

  contains(QMAKE_TARGET.arch, x86_64) {
    CONFIG += PROCESSOR_x64
#   message(PROCESSOR_x64)
  } else {
    CONFIG += PROCESSOR_x86
#   message(PROCESSOR_x86)
  }

   CONFIG(debug, release|debug) {
      CONFIG += BUILD_DEBUG
#     message(BUILD_DEBUG)
   } else {
      CONFIG += BUILD_RELEASE
#     message(BUILD_RELEASE)
   }
}


# system -> Use the default minimal C++ runtime library.
# stlport_static -> Use STLport built as a static library.
# stlport_shared -> Use STLport built as a shared library.
# gnustl_static -> Use GNU libstdc++ as a static library.

# APP_STL := gnustl_static
APP_STL := stlport_shared
APP_CPPFLAGS += -frtti
# APP_ABI := armeabi armeabi-v7a
# APP_PLATFORM := android-8
APP_MODULES := cocos2d cocosdenshion vanillaworld  
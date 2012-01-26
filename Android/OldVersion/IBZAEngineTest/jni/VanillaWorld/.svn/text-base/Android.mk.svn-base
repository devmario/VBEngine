# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libworld
LOCAL_SRC_FILES :=\
    Other/adler32.c\
    Other/compress.c\
    Other/crc32.c\
    Other/deflate.c\
    Other/gzio.c\
    Other/infback.c\
    Other/inffast.c\
    Other/inflate.c\
    Other/inftrees.c\
    Other/ioapi.c\
    Other/png.c\
    Other/pngerror.c\
    Other/pnggccrd.c\
    Other/pngget.c\
    Other/pngmem.c\
    Other/pngpread.c\
    Other/pngread.c\
    Other/pngrio.c\
    Other/pngrtran.c\
    Other/pngrutil.c\
    Other/pngset.c\
    Other/pngtrans.c\
    Other/pngvcrd.c\
    Other/pngwio.c\
    Other/pngwrite.c\
    Other/pngwtran.c\
    Other/pngwutil.c\
    Other/trees.c\
    Other/uncompr.c\
    Other/unzip.c\
    Other/zutil.c\
	Util/Array.c\
	Util/Tween.c\
	Display/Core/Vector.c\
	Display/Core/Color.c\
	Display/Core/Matrix.c\
	Display/Core/Plane.c\
	Display/Core/Polygon.c\
	Display/Core/Quaternion.c\
	Display/Object/Camera.c\
	Display/Object/Light.c\
	Display/Object/Model.c\
	Display/Object/ModelCollision.c\
	Display/Object/ModelEvent.c\
	Display/Object/ModelManager.c\
	Display/Object/ModelMatrix.c\
	Display/Object/ModelTree.c\
	Display/Object/ObjFileForModel.c\
	Display/UI/Button.c\
	Util/PNGDecoder.c\
	Util/Debug.c

LOCAL_LDLIBS := -lz

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

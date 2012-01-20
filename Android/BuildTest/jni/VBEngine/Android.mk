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

LOCAL_MODULE    := libvanillaworld
LOCAL_SRC_FILES :=\
Core/Color/VBColor.c\
Core/Color/VBColorG.c\
Core/Color/VBColorGA.c\
Core/Color/VBColorRGB.c\
Core/Color/VBColorRGBA.c\
Core/Linear/VBAABB.c\
Core/Linear/VBLine2D.c\
Core/Linear/VBMatrix2D.c\
Core/Linear/VBMatrix2DWrapper.c\
Core/Linear/VBSpline2DBezierCubic.c\
Core/Linear/VBTriangle2D.c\
Core/Linear/VBVector2D.c\
Display/VBCamera2D.c\
Display/VBDisplay2D.c\
Display/VBDrawable2D.c\
Display/VBImage.c\
Display/VBModel2D.c\
Display/VBTexture.c\
IO/VBFile.c\
IO/VBObjectFile2D.c\
IO/VBObjectFile2DFrame.c\
IO/VBObjectFile2DKeyFrame.c\
IO/VBObjectFile2DKeyFrameElement.c\
IO/VBObjectFile2DLibrary.c\
IO/VBObjectFile2DLibraryNameID.c\
IO/VBObjectFile2DTexcoord.c\
IO/VBObjectFile2DTransition.c\
IO/VBPNGFile.c\
IO/VBSystem.c\
IO/VBTouch.c\
IO/VBEngineFileInfo.c\
Other/png/png.c\
Other/png/pngerror.c\
Other/png/pnggccrd.c\
Other/png/pngget.c\
Other/png/pngmem.c\
Other/png/pngpread.c\
Other/png/pngread.c\
Other/png/pngrio.c\
Other/png/pngrtran.c\
Other/png/pngrutil.c\
Other/png/pngset.c\
Other/png/pngtrans.c\
Other/png/pngvcrd.c\
Other/png/pngwio.c\
Other/png/pngwrite.c\
Other/png/pngwtran.c\
Other/png/pngwutil.c\
Other/zlib/adler32.c\
Other/zlib/compress.c\
Other/zlib/crc32.c\
Other/zlib/deflate.c\
Other/zlib/gzio.c\
Other/zlib/infback.c\
Other/zlib/inffast.c\
Other/zlib/inflate.c\
Other/zlib/inftrees.c\
Other/zlib/ioapi.c\
Other/zlib/trees.c\
Other/zlib/uncompr.c\
Other/zlib/unzip.c\
Other/zlib/zutil.c\
Util/VBArrayList.c\
Util/VBArrayVector.c\
Util/VBDebug.c\
Util/VBMath.c\
Util/VBString.c\
VBEngine.c\
   
LOCAL_CFLAGS := -std=c99 -DANDROID_NDK -DDISABLE_IMPORTGL -DUSE_FILE32API

LOCAL_LDLIBS := -lz -lGLESv1_CM -ldl -llog

include $(BUILD_SHARED_LIBRARY)


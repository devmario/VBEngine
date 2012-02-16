#!/bin/sh

# set environment parameters
XCODE_PROJECT_ROOT="/Users/younkyuna/github/GelatoMania/GelatoManiaNew"
XCODE_PROJECT_FILE_NAME="gelatomania.xcodeproj"
ANDROID_PROJECT_ROOT="/Users/vb/github/GelatoManiaAndroid/GelatoManiaTest"
COCOS2DX_ROOT="/Users/vb/github/VBEngine/Android/Cocos2dx-version/cocos2d-1.0.1-x-0.9.1"
VBENGINE_ROOT="/Users/vb/github/VBEngine/src"
APP_NAME="GelatoMania"

# generate plist
generate_plist() {
	echo "Generate plist Start"
	plutil -convert xml1 -o - $XCODE_PROJECT_ROOT/$XCODE_PROJECT_FILE_NAME/project.pbxproj >> temp.plist
}

# run GenerateAndroidProject
run() {
	echo "GenerateAndroidProject Start"
	./GenerateAndroidProject $XCODE_PROJECT_ROOT $ANDROID_PROJECT_ROOT $COCOS2DX_ROOT $VBENGINE_ROOT
}

ndk_build() {
	echo "ndk-build start"
	ndk-build -C $ANDROID_PROJECT_ROOT
}

package_build() {
	echo "package build start"
	# cd $ANDROID_PROJECT_ROOT
	# android update project -n $APP_NAME -t 4 -p .
	# ant debug
	# adb install -r bin/$APP_NAME-debug.apk
}

generate_plist
run
# ndk_build
# package_build
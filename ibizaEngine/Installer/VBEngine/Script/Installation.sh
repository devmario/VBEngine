#!/bin/sh

# installation.sh
# 
#
# Created by wonhee jang on 11. 1. 22..
# Copyright 2011 vanilla breeze. All rights reserved.

# 플래쉬 커맨드 인클루드
cp -r /VBEngine/Script/flash/jsflLibs /$HOME/Library/Application\ Support/Adobe/Flash\ CS5/en_US/Configuration/Commands/jsflLibs

# 플래쉬 커맨드
mv /VBEngine/Script/flash/ImportObj.jsfl /$HOME/Library/Application\ Support/Adobe/Flash\ CS5/en_US/Configuration/Commands
mv /VBEngine/Script/flash/ExportObj.jsfl /$HOME/Library/Application\ Support/Adobe/Flash\ CS5/en_US/Configuration/Commands

# 포토샵 플러그인
cp -r /VBEngine/PlugIn/VBExternalForPhotoshop.framework /Applications/Adobe\ Photoshop\ CS5/Plug-ins/VBExternalForPhotoshop.framework
# 플래쉬 플러그인
cp -r /VBEngine/PlugIn/VBFlashPlugIn.bundle /$HOME/Library/Application\ Support/Adobe/Flash\ CS5/en_US/Configuration/External\ Libraries/VBFlashPlugIn.bundle

# 플래쉬 워크스페이스
mv /VBEngine/Workspace/flash/current.txt /$HOME/Library/Application\ Support/Adobe/Flash\ CS5/en_US/Configuration/Workspace/current.txt
mv /VBEngine/Workspace/flash/VB\ Game\ Engine.xml /$HOME/Library/Application\ Support/Adobe/Flash\ CS5/en_US/Configuration/Workspace/VB\ Game\ Engine.xml

# 불필요한 파일 삭제
rm -rf /VBEngine/Workspace
rm -rf /VBEngine/Script/flash
rm -rf /VBEngine/PlugIn
rm /VBEngine/Script/installation.sh
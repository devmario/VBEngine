//
//  main.m
//  GenerateAndroidProject
//
//  Created by Na YounKyu on 12. 2. 2..
//  Copyright (c) 2012 VanillaBreeze. All rights reserved.
//

#import <Foundation/Foundation.h>

NSString* Xcode_Project_Root;
NSString* Xcode_Product_Name;
NSString* Xcode_App_Name;
NSString* Android_Project_Root;
NSString* Android_Jni_Game_Src_Root;
NSString* Android_Jni_Root;
NSString* Android_Src_Root;
NSString* Android_Src_Java_Root;
NSString* Android_Res_Root;
NSString* Cocos2dX_Root;
NSString* VBEngine_Root;

NSMutableDictionary* dict;

NSMutableString* mkStr;

NSString* rootKey;
NSString* mainKey;
NSDictionary* objectsDict;
NSDictionary* rootDict;
NSArray* targetArr;

NSFileManager* fileMgr;

void MakeFolderTree();

NSString* getProductName(); 
NSString* getAppName();

void CopyResources();
bool CopyResourceFile(NSDictionary* _rootDict, NSString* key, NSString* fileRefKey, NSString* pathPtr);

void CopySources();
void CopySourceFile(NSString* path);

void CopyHeaders();
void CopyHeaderFile(NSString* path);

void CopyLibs();
void CreateTemplate();

int main (int argc, const char * argv[])
{

    @autoreleasepool {
        
        if (argc < 5) {
            printf("[Usage] GenerateAndroidProject [xcode project root] [android project root]");
            return 0;
        }
        
        NSLog(@"\n##### Generate Android Project Start #####\n");
        
        dict = [[NSMutableDictionary alloc] initWithContentsOfFile:@"temp.plist"];
        if (dict == nil) {
            printf("error! temp.list not exist");
            return 0;
        }
        
        rootKey = [dict objectForKey:@"rootObject"];
        objectsDict = [dict objectForKey:@"objects"];
        rootDict = [objectsDict objectForKey:rootKey];
        mainKey = [rootDict objectForKey:@"mainGroup"];
        targetArr = [rootDict objectForKey:@"targets"];
        
        Xcode_Product_Name = getProductName();
        Xcode_App_Name = getAppName();
        Xcode_Project_Root = [NSString stringWithFormat:@"%s", argv[1]];
        Android_Project_Root = [NSString stringWithFormat:@"%s", argv[2]];
        Android_Jni_Root = [NSString stringWithFormat:@"%s/jni", argv[2]];
        Android_Jni_Game_Src_Root = [NSString stringWithFormat:@"%@/GameLogic", Android_Jni_Root];
        Android_Src_Root = [NSString stringWithFormat:@"%s/src", argv[2]];
        Android_Src_Java_Root = [NSString stringWithFormat:@"%@/com/vanillabreeze/%@", Android_Src_Root, Xcode_Product_Name];
        Android_Res_Root = [NSString stringWithFormat:@"%s/assets", argv[2]];
        Cocos2dX_Root = [NSString stringWithFormat:@"%s", argv[3]];
        VBEngine_Root = [NSString stringWithFormat:@"%s", argv[4]];
        
        fileMgr = [NSFileManager defaultManager];
        
        // TODO: 게임로직 make파일 생성(Android.mk)
        mkStr = [[NSMutableString alloc] init];
        [mkStr appendString:@"LOCAL_PATH := $(call my-dir)\n"];
        [mkStr appendString:@"include $(CLEAR_VARS)\n"];
        [mkStr appendString:@"LOCAL_MODULE := gamelogic\n\n"];
        [mkStr appendString:@"LOCAL_SRC_FILES := \\\n"];
        
        // TODO: 안드로이드 프로젝트 소스트리 생성
        MakeFolderTree();
        
        // TODO: 리소스 파일들 복사
        CopyResources();
        
        // TODO: 소스 파일들 복사
        CopySources();
        
        // TODO: 게임로직 make파일 저장(Android.mk)
        [mkStr appendString:@"\n\n\nLOCAL_C_INCLUDES := $(LOCAL_PATH)/../Cocos2dx \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../Cocos2dx/platform \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../Cocos2dx/include \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../CocosDenshion \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../CocosDenshion/include \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/Core/Color \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/Core/Linear \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/Display \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/IO \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/Other/png \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/Other/zlib \\\n"];
        [mkStr appendString:@"\t\t$(LOCAL_PATH)/../VBEngine/Util\n\n"];
        [mkStr appendString:@"LOCAL_CFLAGS := -DANDROID_NDK\n\n"];
        [mkStr appendString:@"LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \\\n"];
        [mkStr appendString:@"\t\t-lcocos2d -lcocosdenshion -lvanillaworld -llog -lGLESv1_CM -ljnigraphics\n\n"];
        [mkStr appendString:@"include $(BUILD_SHARED_LIBRARY)"];
        [mkStr writeToFile:[NSString stringWithFormat:@"%s/Android.mk", [Android_Jni_Game_Src_Root UTF8String]] atomically:YES encoding:NSASCIIStringEncoding error:nil];
        
        // TODO: 헤더 파일들 복사
        CopyHeaders();
        
        // TODO: 라이브러리 소스 파일들 복사(Cocos2dx, CocosDenshion, VBEngine)
        CopyLibs();
        
        // CreateTemplate();
        
        [dict release];
        [mkStr release];
        
        system("rm temp.plist");
        
        NSLog(@"\n##### Generate Android Project Success #####\n");
    }
    return 0;
}

void MakeFolderTree()
{
    if (![fileMgr fileExistsAtPath:Android_Project_Root]) {
        system([[NSString stringWithFormat:@"mkdir %@", Android_Project_Root] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:Android_Jni_Root]) {
        system([[NSString stringWithFormat:@"mkdir %@", Android_Jni_Root] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:Android_Jni_Game_Src_Root]) {
        system([[NSString stringWithFormat:@"mkdir %@", Android_Jni_Game_Src_Root] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:Android_Src_Root]) {
        system([[NSString stringWithFormat:@"mkdir %@", Android_Src_Root] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/%@", Android_Src_Root, @"com"]]) {
        system([[NSString stringWithFormat:@"mkdir %@/%@", Android_Src_Root, @"com"] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/%@/%@", Android_Src_Root, @"com", @"vanillabreeze"]]) {
        system([[NSString stringWithFormat:@"mkdir %@/%@/%@", Android_Src_Root, @"com", @"vanillabreeze"] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@", Android_Src_Java_Root]]) {
        system([[NSString stringWithFormat:@"mkdir %@", Android_Src_Java_Root] UTF8String]);
    }
    
    if (![fileMgr fileExistsAtPath:Android_Res_Root]) {
        system([[NSString stringWithFormat:@"mkdir %@", Android_Res_Root] UTF8String]);
    }
}

void CopyResources()
{
    NSLog(@">>>>> Copy Resource Files Start <<<<<");
    for (int i=0; i<[targetArr count]; i++) 
    {
        NSString* targetKey = [targetArr objectAtIndex:i];
        NSDictionary* targetDict = [objectsDict objectForKey:targetKey];
        NSArray* buildPhaseArr = [targetDict objectForKey:@"buildPhases"];
        
        for (int j=0; j<[buildPhaseArr count]; j++) 
        {
            NSDictionary* filesDict = [objectsDict objectForKey:[buildPhaseArr objectAtIndex:j]];
            
            if ([[filesDict objectForKey:@"isa"] isEqualToString:@"PBXResourcesBuildPhase"])
            {
                NSArray* filesArr = [filesDict objectForKey:@"files"];
                for (int k=0; k<[filesArr count]; k++) 
                {
                    NSDictionary* fileDict = [objectsDict objectForKey:[filesArr objectAtIndex:k]];
                    NSDictionary* source = [objectsDict objectForKey:[fileDict objectForKey:@"fileRef"]];
                    if ([[source objectForKey:@"lastKnownFileType"] isEqualToString:@"image.png"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"file"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.javascript"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"text.plist.xml"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"text"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"text.json"])
                    {
                        NSString* tmpSrcPath = [[NSString alloc] init];
                        CopyResourceFile(objectsDict, mainKey, [fileDict objectForKey:@"fileRef"], tmpSrcPath);
                        [tmpSrcPath release];
                    }
                }
            }
        }
    }
    NSLog(@">>>>> Copy Resource Files End <<<<<");
}

bool CopyResourceFile(NSDictionary* _objectsDict, NSString* _mainKey, NSString* fileRefKey, NSString* pathPtr)
{
    NSDictionary* dict = [_objectsDict objectForKey:_mainKey];
    NSString* path = [dict objectForKey:@"path"];
    
    if (path) {
        pathPtr = [pathPtr stringByAppendingFormat:@"/%@", path];
    }
    
    NSArray* children = [dict objectForKey:@"children"];
    if (children)
    {
        for (int i=0; i<[children count]; i++)
        {
            NSString* childKey = [children objectAtIndex:i];
            
            bool success = CopyResourceFile(_objectsDict, childKey, fileRefKey, pathPtr);
            if (success)
            {
                return true;
            }
        }
    }
    else
    {
        if ([_mainKey isEqualToString:fileRefKey])
        {
            // Copy Res file to Assets
            NSString* cmd = [NSString stringWithFormat:@"cp -a %@%@ %@", Xcode_Project_Root, pathPtr, Android_Res_Root];
            system([cmd UTF8String]);
            //NSLog(@"DEBUG %@", cmd);
            return true;
        }
    }
    return false;
}

bool MakePathSrc(NSDictionary* _root, NSString* _key, NSString* _fileRef, NSString* _pathPtr) {
    
    NSDictionary* _dict = [_root objectForKey:_key];
    
    NSString* _path = [_dict objectForKey:@"path"];
    
    if(_path) {
        _pathPtr = [_pathPtr stringByAppendingFormat:@"/%@", _path];
    }
    
    NSArray* _children = [_dict objectForKey:@"children"];
    
    if(_children) {
        for(int i = 0; i < [_children count]; i++) {
            NSString* _childKey = [_children objectAtIndex:i];
            bool success = MakePathSrc(_root, _childKey, _fileRef, _pathPtr);
            if(success) {
                return true;
            }
        }
    } else {
        if([_key isEqualToString:_fileRef]) {
            CopySourceFile([_pathPtr copy]);
            return true;
        } else {
            
        }
    }
    return false;
}

void CopySources()
{
    NSLog(@">>>>> Copy Source Files Start <<<<<");
    for (int i=0; i<[targetArr count]; i++) 
    {
        NSString* targetKey = [targetArr objectAtIndex:i];
        NSDictionary* targetDict = [objectsDict objectForKey:targetKey];
        NSArray* buildPhaseArr = [targetDict objectForKey:@"buildPhases"];
        
        for (int j=0; j<[buildPhaseArr count]; j++) 
        {
            NSDictionary* filesDict = [objectsDict objectForKey:[buildPhaseArr objectAtIndex:j]];
            
            if ([[filesDict objectForKey:@"isa"] isEqualToString:@"PBXSourcesBuildPhase"])
            {
                NSArray* filesArr = [filesDict objectForKey:@"files"];
                for (int k=0; k<[filesArr count]; k++) 
                {
                    NSDictionary* fileDict = [objectsDict objectForKey:[filesArr objectAtIndex:k]];
                    NSDictionary* source = [objectsDict objectForKey:[fileDict objectForKey:@"fileRef"]];
                    if ([[source objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.cpp.cpp"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.c"] ||
                        [[source objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"])
                    {
                        NSString* _tmpSrcPath = [[NSString alloc] init];
                        bool res = MakePathSrc(objectsDict, mainKey, [fileDict objectForKey:@"fileRef"], _tmpSrcPath);
                        [_tmpSrcPath release];
                    }
                }
            }
        }
    }
    NSLog(@">>>>> Copy Source Files End <<<<<");
}

NSString* getProductName()
{
    NSArray* targetArr = [rootDict objectForKey:@"targets"];
    NSString* targetKey = [targetArr objectAtIndex:0];
    NSDictionary* targetDict = [objectsDict objectForKey:targetKey];
    
    return [targetDict objectForKey:@"productName"];
}

NSString* getAppName() 
{
    NSArray* targetArr = [rootDict objectForKey:@"targets"];
    NSString* targetKey = [targetArr objectAtIndex:0];
    NSDictionary* targetDict = [objectsDict objectForKey:targetKey];
    
    return [targetDict objectForKey:@"name"];
}

void CopySourceFile(NSString* path)
{
    // TODO: Xcode Project 내 실제 소스 파일이 존재하는지 여부 체크
    if ([fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/%@", 
                                   Xcode_Project_Root, path]])
    {
        // TODO: cocos2dx 소스 제외 (안드로이드용 cocos2dx로 대체)
        if (strstr([[NSString stringWithFormat:@"%@", path] UTF8String], "cocos2dx")) {
            return;
        }
        
        // TODO: CocosDenshion 소스 제외 (안드로이드용 CocosDenshion로 대체)
        if (strstr([[NSString stringWithFormat:@"%@", path] UTF8String], "CocosDenshion")) {
            return;
        }
        
        // TODO: VBEngine 소스 제외 (안드로이드용 VBEngine로 대체)
        if (strstr([[NSString stringWithFormat:@"%@", path] UTF8String], "VBEngine")) {
            return;
        }
        
        { // Android.mk 빌드 파일에 추가
            char *p = NULL;
            const char *delim = "/";
            char _path[128] = {0,};
            p = strtok((char*)[path UTF8String], delim);
            while (p) {
                p = strtok(NULL, delim);
                if (p) {
                    strcpy(_path, p);
                }
            }
            NSString* src = [[NSString alloc] initWithFormat:@"\t%s\\\n", _path];
            [mkStr appendString:src];
            [src release];
        }
        
        // TODO: 게임로직 소스 파일 복사 
        NSString* cmd = [NSString stringWithFormat:@"cp -a %@/%@ %@", 
                         Xcode_Project_Root, path, Android_Jni_Game_Src_Root];
        system([cmd UTF8String]);
        //NSLog(@"DEBUG %@", cmd);
    }
}

void CopyHeaderFile(NSString* path)
{
    // TODO: Xcode Project 내 실제 소스 파일이 존재하는지 여부 체크
    if ([fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/%@/%@", 
                                   Xcode_Project_Root, Xcode_Product_Name, path]])
    {
        // TODO: cocos2dx 소스 제외
        if (strstr([[NSString stringWithFormat:@"%@", path] UTF8String], "cocos2dx")) {
            return;
        }
        
        // TODO: 소스 파일 복사 
        NSString* cmd = [NSString stringWithFormat:@"cp -a %@/%@/%@ %@", 
                         Xcode_Project_Root, Xcode_Product_Name, path, Android_Jni_Game_Src_Root];
        system([cmd UTF8String]);
    }
}

void CopyHeaders()
{
    NSLog(@">>>>> Copy Headers Start <<<<<");
    NSDictionary* _objects = [dict objectForKey:@"objects"];
    
    NSArray *arr = [_objects allKeys];
    
    for (int i=0; i<[arr count]; i++) 
    {   
        NSString *key = [arr objectAtIndex:i];
        NSDictionary *dic = [_objects objectForKey:key];
        NSArray *child = [dic objectForKey:@"children"];
        if (child) 
        {
            for (int i=0; i<[child count]; i++) 
            {
                NSString *child_key = [child objectAtIndex:i];
                NSDictionary *child_dict = [_objects objectForKey:child_key];
                
                if ([[child_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                { // 헤더파일을 찾은 경우    
                    CopyHeaderFile([child_dict objectForKey:@"path"]);
                }
                else if ([child_dict objectForKey:@"children"])
                { // 안에 children 이 있는 경우
                    NSArray *child2 = [child_dict objectForKey:@"children"];
                    for (int i=0; i<[child2 count]; i++) 
                    {
                        NSString *child2_key = [child2 objectAtIndex:i];
                        NSDictionary *child2_dict = [_objects objectForKey:child2_key];
                        
                        if ([[child2_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                        { // 헤더파일을 찾은 경우    
                            CopyHeaderFile([child2_dict objectForKey:@"path"]);
                        }
                        else if ([child2_dict objectForKey:@"children"])
                        { // 안에 children 이 있는 경우
                            NSArray *child3 = [child2_dict objectForKey:@"children"];
                            for (int i=0; i<[child3 count]; i++)
                            {
                                NSString *child3_key = [child3 objectAtIndex:i];
                                NSDictionary *child3_dict = [_objects objectForKey:child3_key];
                                
                                if ([[child3_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                { // 헤더파일을 찾은 경우    
                                    CopyHeaderFile([child3_dict objectForKey:@"path"]);
                                }
                                else if ([child3_dict objectForKey:@"children"])
                                { // 안에 children 이 있는 경우
                                    NSArray *child4 = [child3_dict objectForKey:@"children"];
                                    for (int i=0; i<[child4 count]; i++)
                                    {
                                        NSString *child4_key = [child4 objectAtIndex:i];
                                        NSDictionary *child4_dict = [_objects objectForKey:child4_key];
                                        
                                        if ([[child4_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                        { // 헤더파일을 찾은 경우
                                            CopyHeaderFile([child4_dict objectForKey:@"path"]);
                                        }
                                        else if ([child4_dict objectForKey:@"children"])
                                        { // 안에 children 이 있는 경우
                                            NSArray *child5 = [child4_dict objectForKey:@"children"];
                                            for (int i=0; i<[child5 count]; i++)
                                            {
                                                NSString *child5_key = [child5 objectAtIndex:i];
                                                NSDictionary *child5_dict = [_objects objectForKey:child5_key];
                                                
                                                if ([[child5_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                                { // 헤더파일을 찾은 경우
                                                    CopyHeaderFile([child5_dict objectForKey:@"path"]);
                                                }
                                                else if ([child5_dict objectForKey:@"children"])
                                                { // 안에 children 이 있는 경우
                                                    NSArray *child6 = [child5_dict objectForKey:@"children"];
                                                    for (int i=0; i<[child6 count]; i++)
                                                    {
                                                        NSString *child6_key = [child6 objectAtIndex:i];
                                                        NSDictionary *child6_dict = [_objects objectForKey:child6_key];
                                                        
                                                        if ([[child6_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                                        { // 헤더파일을 찾은 경우
                                                            CopyHeaderFile([child6_dict objectForKey:@"path"]);
                                                        }
                                                        else if ([child6_dict objectForKey:@"children"])
                                                        { // 안에 children 이 있는 경우
                                                            NSArray *child7 = [child6_dict objectForKey:@"children"];
                                                            for (int i=0; i<[child7 count]; i++)
                                                            {
                                                                NSString *child7_key = [child7 objectAtIndex:i];
                                                                NSDictionary *child7_dict = [_objects objectForKey:child7_key];
                                                                
                                                                if ([[child7_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                                                { // 헤더파일을 찾은 경우
                                                                    CopyHeaderFile([child7_dict objectForKey:@"path"]);
                                                                }
                                                                else if ([child7_dict objectForKey:@"children"])
                                                                { // 안에 children 이 있는 경우
                                                                    NSArray *child8 = [child7_dict objectForKey:@"children"];
                                                                    for (int i=0; i<[child8 count]; i++)
                                                                    {
                                                                        NSString *child8_key = [child8 objectAtIndex:i];
                                                                        NSDictionary *child8_dict = [_objects objectForKey:child8_key];
                                                                        
                                                                        if ([[child8_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                                                        { // 헤더파일을 찾은 경우
                                                                            CopyHeaderFile([child8_dict objectForKey:@"path"]);
                                                                        }
                                                                        else if ([child8_dict objectForKey:@"children"])
                                                                        { // 안에 children 이 있는 경우
                                                                            NSArray *child9 = [child8_dict objectForKey:@"children"];
                                                                            for (int i=0; i<[child9 count]; i++)
                                                                            {
                                                                                NSString *child9_key = [child8 objectAtIndex:i];
                                                                                NSDictionary *child9_dict = [_objects objectForKey:child9_key];
                                                                                
                                                                                if ([[child9_dict objectForKey:@"lastKnownFileType"] isEqualToString:@"sourcecode.c.h"]) 
                                                                                { // 헤더파일을 찾은 경우
                                                                                    CopyHeaderFile([child9_dict objectForKey:@"path"]);
                                                                                }
                                                                                else if ([child9_dict objectForKey:@"children"])
                                                                                { // 여기 까지는 안오는 것 같음...
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    NSLog(@">>>>> Copy Headers End <<<<<");
}

void CopyLibs()
{
    NSLog(@">>>>> Copy Libs Start <<<<<");
    
    NSString* cmd;
    
    BOOL isFile;
    BOOL isDir;
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/vbHttp.h", Android_Jni_Game_Src_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/vbHTTP.h %@", Android_Jni_Game_Src_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/VBModel.h", Android_Jni_Game_Src_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/VBModel.h %@", Android_Jni_Game_Src_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/mongoDBUtil.h", Android_Jni_Game_Src_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/mongoDBUtil.h %@", Android_Jni_Game_Src_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/project.properties", Android_Project_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/project.properties %@", Android_Project_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/Android.mk", Android_Jni_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/Android.mk %@", Android_Jni_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/Application.mk", Android_Jni_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/Application.mk %@", Android_Jni_Root];
        system([cmd UTF8String]);
    }
    
    /*isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/main.cpp", Android_Jni_Game_Src_Root]];
    if (!isFile) {
        cmd = [NSString stringWithFormat:@"cp -a libs/main.cpp %@", Android_Jni_Game_Src_Root];
        system([cmd UTF8String]);
    }*/
    
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/Cocos2dx", Android_Jni_Root]];
    if (isFile == false) {
        cmd = [NSString stringWithFormat:@"cp -R %@ %@/Cocos2dx", Cocos2dX_Root, Android_Jni_Root];
        system([cmd UTF8String]);        
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/CocosDenshion", Android_Jni_Root] isDirectory:&isDir];
    if (isFile == false && isDir == false) {
        cmd = [NSString stringWithFormat:@"cp -r libs/CocosDenshion %@", Android_Jni_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/VBEngine", Android_Jni_Root]];
    if (isFile == false) {
        cmd = [NSString stringWithFormat:@"cp -R %@ %@/VBEngine", VBEngine_Root, Android_Jni_Root];
        system([cmd UTF8String]);
    }
    
    isFile = [fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/org", Android_Src_Root] isDirectory:&isDir];
    if (isFile == false && isDir == false) {
        cmd = [NSString stringWithFormat:@"cp -r libs/org %@", Android_Src_Root];
        system([cmd UTF8String]);
    }
    
    cmd = [NSString stringWithFormat:@"cp -r libs/res %@", Android_Project_Root];
    system([cmd UTF8String]);
    
    cmd = [NSString stringWithFormat:@"cp -a libs/MobageSDK/images/* %@", Android_Res_Root];
    system([cmd UTF8String]);
    
    NSLog(@">>>>> Copy Libs End <<<<<");
}

void CreateTemplate()
{
    NSLog(@">>>>> CreateTemplate Start <<<<<");
    
    if (![fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/%@Activity.java", Android_Src_Java_Root, Xcode_App_Name]]) {
        // 자바 Activity파일이 없다면 생성! 
        NSMutableString* mutStr = [[NSMutableString alloc] init];
        [mutStr appendFormat:@"package com.vanillabreeze.%@;\n\n", Xcode_Product_Name];
        [mutStr appendString:@"import org.cocos2dx.lib.Cocos2dxActivity;\n"];
        [mutStr appendString:@"import org.cocos2dx.lib.Cocos2dxGLSurfaceView;\n"];
        [mutStr appendString:@"import android.os.Bundle;\n"];
        [mutStr appendString:@"import android.widget.EditText;\n\n"];
        [mutStr appendFormat:@"public class %@Activity extends Cocos2dxActivity{\n", Xcode_App_Name];
        [mutStr appendString:@"\tprivate Cocos2dxGLSurfaceView mGLView;\n\n"];
        [mutStr appendString:@"\tprotected void onCreate(Bundle savedInstanceState){\n"];
        [mutStr appendString:@"\t\tsuper.onCreate(savedInstanceState);\n\n"];
        [mutStr appendString:@"\t\t// get the packageName,it's used to set the resource path\n"];
        [mutStr appendString:@"\t\tString packageName = getApplication().getPackageName();\n"];
        [mutStr appendString:@"\t\tsuper.setPackageName(packageName);\n\n"];
        [mutStr appendString:@"\t\tsetContentView(R.layout.game_demo);\n"];
        [mutStr appendString:@"\t\tmGLView = (Cocos2dxGLSurfaceView) findViewById(R.id.game_gl_surfaceview);\n"];
        [mutStr appendString:@"\t\tmGLView.setTextField((EditText)findViewById(R.id.textField));\n\n"];
        [mutStr appendString:@"\t\t// Get the size of the mGLView after the layout happens\n"];
        [mutStr appendFormat:@"\t\tmGLView.post(new Runnable() {\n\n"];
        [mutStr appendFormat:@"\t\t\t@Override\n"];
        [mutStr appendFormat:@"\t\t\tpublic void run() {\n"];
        [mutStr appendFormat:@"\t\t\t\tCocos2dxActivity.screenHeight = mGLView.getHeight();\n"];
        [mutStr appendFormat:@"\t\t\t\tCocos2dxActivity.screenWidth = mGLView.getWidth();\n"];
        [mutStr appendFormat:@"\t\t\t}\n"];
        [mutStr appendFormat:@"\t\t});\n"];
        [mutStr appendString:@"\t}\n"];
        [mutStr appendFormat:@"\t\n\n"];
        [mutStr appendFormat:@"\t@Override\n"];
        [mutStr appendFormat:@"\tprotected void onPause() {\n"];
        [mutStr appendFormat:@"\t\tsuper.onPause();\n"];
        [mutStr appendFormat:@"\t\tmGLView.onPause();\n"];
        [mutStr appendFormat:@"\t}\n\n"];
        [mutStr appendFormat:@"\t@Override\n"];
        [mutStr appendFormat:@"\tprotected void onResume() {\n"];
        [mutStr appendFormat:@"\t\tsuper.onResume();\n"];
        [mutStr appendFormat:@"\t\tmGLView.onResume();\n"];
        [mutStr appendFormat:@"\t}\n\n"];
        [mutStr appendFormat:@"\tstatic {\n"];
        [mutStr appendFormat:@"\t\tSystem.loadLibrary(\"stlport_shared\");\n"];
        [mutStr appendFormat:@"\t\tSystem.loadLibrary(\"cocos2d\");\n"];
        [mutStr appendFormat:@"\t\tSystem.loadLibrary(\"cocosdenshion\");\n"];
        [mutStr appendFormat:@"\t\tSystem.loadLibrary(\"vanillaworld\");\n"];
        [mutStr appendFormat:@"\t\tSystem.loadLibrary(\"gamelogic\");\n"];
        [mutStr appendFormat:@"\t}\n"];
        [mutStr appendFormat:@"}\n"];
        [mutStr writeToFile:[NSString stringWithFormat:@"%s/%@Activity.java", [Android_Src_Java_Root UTF8String], Xcode_App_Name] atomically:YES encoding:NSASCIIStringEncoding error:nil];
        [mutStr release];
    }
    
    if (![fileMgr fileExistsAtPath:[NSString stringWithFormat:@"%@/AndroidManifest.xml", Android_Project_Root]]) {
        // 안드로이드 메니페스트 파일이 없다면 생성! 
        NSMutableString* mutStr2 = [[NSMutableString alloc] init];
        [mutStr2 appendString:@"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"];
        [mutStr2 appendString:@"<manifest\n"];
        [mutStr2 appendString:@"\txmlns:android=\"http://schemas.android.com/apk/res/android\"\n"];
        [mutStr2 appendFormat:@"\tpackage=\"com.vanillabreeze.%@\"\n", Xcode_Product_Name];
        [mutStr2 appendString:@"\tandroid:versionCode=\"1\"\n"];
        [mutStr2 appendString:@"\tandroid:versionName=\"1.0\">\n"];
        [mutStr2 appendString:@"\t<uses-permission android:name=\"android.permission.WRITE_EXTERNAL_STORAGE\" />\n"];
        [mutStr2 appendString:@"\t<uses-permission android:name=\"android.permission.INTERNET\"/>\n"];
        [mutStr2 appendString:@"\t<application\n"];
        [mutStr2 appendString:@"\t\tandroid:debuggable=\"true\"\n"];
        [mutStr2 appendString:@"\t\tandroid:icon=\"@drawable/icon\"\n"];
        [mutStr2 appendString:@"\t\tandroid:label=\"@string/app_name\">\n"];
        [mutStr2 appendString:@"\t\t<activity\n"];
        [mutStr2 appendFormat:@"\t\t\tandroid:name=\".%@Activity\"\n", Xcode_App_Name];
        [mutStr2 appendString:@"\t\t\tandroid:label=\"@string/app_name\"\n"];
        [mutStr2 appendString:@"\t\t\tandroid:screenOrientation=\"landscape\"\n"];
        [mutStr2 appendString:@"\t\t\tandroid:theme=\"@android:style/Theme.NoTitleBar.Fullscreen\""];
        [mutStr2 appendString:@"\t\t\tandroid:configChanges=\"orientation|keyboard|keyboardHidden\">\n"];
        [mutStr2 appendString:@"\t\t\t<intent-filter>\n"];
        [mutStr2 appendString:@"\t\t\t\t<action android:name=\"android.intent.action.MAIN\" />\n"];
        [mutStr2 appendString:@"\t\t\t\t<category android:name=\"android.intent.category.LAUNCHER\" />\n"];
        [mutStr2 appendString:@"\t\t\t</intent-filter>\n"];
        [mutStr2 appendString:@"\t\t</activity>\n"];
        [mutStr2 appendString:@"\t</application>\n"];
        [mutStr2 appendString:@"\t<supports-screens android:largeScreens=\"true\"\n"];
        [mutStr2 appendString:@"\t\tandroid:smallScreens=\"true\"\n"];
        [mutStr2 appendString:@"\t\tandroid:anyDensity=\"true\"\n"];
        [mutStr2 appendString:@"\t\tandroid:normalScreens=\"true\"/>\n"];
        [mutStr2 appendString:@"\t<uses-feature android:glEsVersion=\"0x00020000\"/>\n"];
        [mutStr2 appendString:@"\t<uses-sdk android:minSdkVersion=\"5\"/>\n"];
        [mutStr2 appendString:@"</manifest>\n"];
        [mutStr2 writeToFile:[NSString stringWithFormat:@"%s/AndroidManifest.xml", [Android_Project_Root UTF8String]] atomically:YES encoding:NSASCIIStringEncoding error:nil];
        [mutStr2 release];
    }
    
    NSLog(@">>>>> CreateTemplate End <<<<<");
}

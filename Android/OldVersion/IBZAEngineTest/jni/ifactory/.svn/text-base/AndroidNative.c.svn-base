#include "AndroidNative.h"

// 추가 header files
#include "Sample.h"
// 추가 전역변수
Sample game;

/////////////////////////////////////
// Game Method Interface
/////////////////////////////////////
void nativeInitGame(JNIEnv* env, jobject thiz) {
	LOGV("nativeInitGame");

	if(isInit < 0) {
		importGLInit();
		initSample(&game,NULL,   480 , 800 , false);
		isInit = 1;
	}
}

void nativeRender(JNIEnv* env) {
	if (currTick == 0 && oldTick == 0) {
		currTick = _getTime();
		oldTick = _getTime();
	} else {
		currTick = _getTime();
	}
	float deltaTime = (currTick - oldTick) / 1000.0f;
	if (deltaTime >= 0.030f) {
		deltaTime = 0.030f;
	}
	renderSample(&game, deltaTime);
	oldTick = currTick;
}

 // method for Java event - reize window 
void nativeResize(JNIEnv* env, jobject thiz, jint w, jint h) {
	WindowWidth = w;
	WindowHeight = h;
}

void nativeTouch(JNIEnv* env, jobject thiz, jfloat jx, jfloat jy, jint type) {
	LOGV("nativeTouch");
	TouchType touchType;
	switch (type) {
		case 0:
			touchType = TouchTypeCancel;
		break;
		case 1: 
			touchType = TouchTypeBegan;
		break;
		case 2:
			touchType = TouchTypeMove;
		break;
		case 3:
			touchType = TouchTypeEnd;
		break;
	}
	 //LOGV("guns Touch %i types %i " ,  0 , _type);
	 //bool ModelManagerTouch(ModelManager* manager,Vector2D touch, void* touchID, TouchType touchType,  unsigned char tabCount)
	 //ModelManagerTouch(&game.mManager, Vector2DInit((float) x, (float) y), 1,touchType, 1);

	playSound("result_board_eff");
	playMusic("gelatomania_bgm");
	
}
 
 // method for Java - pause 
void nativePause(JNIEnv* env, jobject thiz) {
	LOGV("native pauseGame");
}
 // method for Java - resume 
void nativeResume(JNIEnv* env, jobject thiz) {
	LOGV("native nativeResume");
}

 // method for Java - close 
void nativeDestroy(JNIEnv* env) {
	LOGV("Destroy");
	importGLDeinit();
    freeFileList(fileList);
	// freeGame(&game);
}


/////////////////////////////////////
// Android Init & Resource Setting
/////////////////////////////////////
void nativeInit(JNIEnv* env, jobject thiz) {
	gelatoObject = thiz;
	gelatoClass = (*env)->GetObjectClass(env, thiz);
}

void nativeLoadXML(JNIEnv* env, jobject thiz, jobject object) {
	//LOGV("nativeLoadXML");

	jclass clazz = (*env)->FindClass(env, "Util/XMLData");
	if (clazz == NULL) {
		LOGE("nativeLoadXML : find class failed");
		return;
	}
	StageField* field = (StageField*) calloc(1, sizeof(StageField));
	jfieldID fieldID = NULL;
	jintArray* arryPointer = NULL;
	jint* arry = NULL;
	int size = 0;
	int i = 0;
	// stages
	fieldID = (*env)->GetFieldID(env, clazz, "stages", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->stages = (*env)->GetIntField(env, object, fieldID);

	// icecreamball
	fieldID = (*env)->GetFieldID(env, clazz, "icecreamball", "[I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	arryPointer = (jintArray*) (*env)->GetIntField(env, object, fieldID);
	arry = (*env)->GetIntArrayElements(env, arryPointer, NULL);
	size = (*env)->GetArrayLength(env, arryPointer);
	for (i = 0; i < size; i++) {
		field->icecreamball[0][i] = arry[i];
	}
	(*env)->ReleaseIntArrayElements(env, arryPointer, arry, 0);

	// icecreamballTwo
	fieldID = (*env)->GetFieldID(env, clazz, "icecreamballTwo", "[I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	arryPointer = (jintArray*) (*env)->GetIntField(env, object, fieldID);
	arry = (*env)->GetIntArrayElements(env, arryPointer, NULL);
	size = (*env)->GetArrayLength(env, arryPointer);
	for (i = 0; i < size; i++) {
		field->icecreamball[1][i] = arry[i];
	}
	(*env)->ReleaseIntArrayElements(env, arryPointer, arry, 0);

	// icecreamPattern
	fieldID = (*env)->GetFieldID(env, clazz, "icecreamPattern", "[I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	arryPointer = (jintArray*) (*env)->GetIntField(env, object, fieldID);
	arry = (*env)->GetIntArrayElements(env, arryPointer, NULL);
	size = (*env)->GetArrayLength(env, arryPointer);
	for (i = 0; i < size; i++) {
		field->icecreamPattern[0][i] = arry[i];
	}
	(*env)->ReleaseIntArrayElements(env, arryPointer, arry, 0);

	// icecreamPatternTwo
	fieldID = (*env)->GetFieldID(env, clazz, "icecreamPatternTwo", "[I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	arryPointer = (jintArray*) (*env)->GetIntField(env, object, fieldID);
	arry = (*env)->GetIntArrayElements(env, arryPointer, NULL);
	size = (*env)->GetArrayLength(env, arryPointer);
	for (i = 0; i < size; i++) {
		field->icecreamPattern[1][i] = arry[i];
	}
	(*env)->ReleaseIntArrayElements(env, arryPointer, arry, 0);

	// icecreamEye
	fieldID = (*env)->GetFieldID(env, clazz, "icecreamEye", "[I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	arryPointer = (jintArray*) (*env)->GetIntField(env, object, fieldID);
	arry = (*env)->GetIntArrayElements(env, arryPointer, NULL);
	size = (*env)->GetArrayLength(env, arryPointer);
	for (i = 0; i < size; i++) {
		field->icecreamEye[0][i] = arry[i];
	}
	(*env)->ReleaseIntArrayElements(env, arryPointer, arry, 0);

	// icecreamEyeTwo
	fieldID = (*env)->GetFieldID(env, clazz, "icecreamEyeTwo", "[I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	arryPointer = (jintArray*) (*env)->GetIntField(env, object, fieldID);
	arry = (*env)->GetIntArrayElements(env, arryPointer, NULL);
	size = (*env)->GetArrayLength(env, arryPointer);
	for (i = 0; i < size; i++) {
		field->icecreamEye[1][i] = arry[i];
	}
	(*env)->ReleaseIntArrayElements(env, arryPointer, arry, 0);

	// icenum
	fieldID = (*env)->GetFieldID(env, clazz, "icenum", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->icenum = (*env)->GetIntField(env, object, fieldID);

	// icepattern
	fieldID = (*env)->GetFieldID(env, clazz, "icepattern", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->icepattern = (*env)->GetBooleanField(env, object, fieldID);

	// icepatterntwo
	fieldID = (*env)->GetFieldID(env, clazz, "icepatterntwo", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->icepatterntwo = (*env)->GetBooleanField(env, object, fieldID);

	// iceeyes
	fieldID = (*env)->GetFieldID(env, clazz, "iceeyes", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->iceeyes = (*env)->GetBooleanField(env, object, fieldID);

	// iceeyestwo
	fieldID = (*env)->GetFieldID(env, clazz, "iceeyestwo", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->iceeyestwo = (*env)->GetBooleanField(env, object, fieldID);

	// milkcream
	fieldID = (*env)->GetFieldID(env, clazz, "milkcream", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->milkcream = (*env)->GetIntField(env, object, fieldID);

	// cherry
	fieldID = (*env)->GetFieldID(env, clazz, "cherry", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->cherry = (*env)->GetIntField(env, object, fieldID);

	// chocochips
	fieldID = (*env)->GetFieldID(env, clazz, "chocochips", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->chocochips = (*env)->GetIntField(env, object, fieldID);

	// nuts
	fieldID = (*env)->GetFieldID(env, clazz, "nuts", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->nuts = (*env)->GetIntField(env, object, fieldID);

	// candy
	fieldID = (*env)->GetFieldID(env, clazz, "candy", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->candy = (*env)->GetIntField(env, object, fieldID);

	// leftspoid
	fieldID = (*env)->GetFieldID(env, clazz, "leftspoid", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->leftspoid = (*env)->GetIntField(env, object, fieldID);

	// rightspoid
	fieldID = (*env)->GetFieldID(env, clazz, "rightspoid", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->rightspoid = (*env)->GetIntField(env, object, fieldID);

	// iceice
	fieldID = (*env)->GetFieldID(env, clazz, "iceice", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->iceice = (*env)->GetIntField(env, object, fieldID);

	// leftcorncount
	fieldID = (*env)->GetFieldID(env, clazz, "leftcorncount", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->leftcorncount = (*env)->GetIntField(env, object, fieldID);

	// leftcorn_v
	fieldID = (*env)->GetFieldID(env, clazz, "leftcorn_v", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->leftcorn_v = (*env)->GetIntField(env, object, fieldID);

	// leftcorn_c
	fieldID = (*env)->GetFieldID(env, clazz, "leftcorn_c", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->leftcorn_c = (*env)->GetIntField(env, object, fieldID);

	// leftcorn_b
	fieldID = (*env)->GetFieldID(env, clazz, "leftcorn_b", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->leftcorn_b = (*env)->GetIntField(env, object, fieldID);

	// leftcorn_g
	fieldID = (*env)->GetFieldID(env, clazz, "leftcorn_g", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->leftcorn_g = (*env)->GetIntField(env, object, fieldID);

	// rightcorncount
	fieldID = (*env)->GetFieldID(env, clazz, "rightcorncount", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->rightcorncount = (*env)->GetIntField(env, object, fieldID);

	// rightcorn_v
	fieldID = (*env)->GetFieldID(env, clazz, "rightcorn_v", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->rightcorn_v = (*env)->GetIntField(env, object, fieldID);

	// rightcorn_c
	fieldID = (*env)->GetFieldID(env, clazz, "rightcorn_c", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->rightcorn_c = (*env)->GetIntField(env, object, fieldID);

	// rightcorn_b
	fieldID = (*env)->GetFieldID(env, clazz, "rightcorn_b", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->rightcorn_b = (*env)->GetIntField(env, object, fieldID);

	// rightcorn_g
	fieldID = (*env)->GetFieldID(env, clazz, "rightcorn_g", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->rightcorn_g = (*env)->GetIntField(env, object, fieldID);

	// centercorncount
	fieldID = (*env)->GetFieldID(env, clazz, "centercorncount", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->centercorncount = (*env)->GetIntField(env, object, fieldID);

	// centercorn_v
	fieldID = (*env)->GetFieldID(env, clazz, "centercorn_v", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->centercorn_v = (*env)->GetIntField(env, object, fieldID);

	// centercorn_c
	fieldID = (*env)->GetFieldID(env, clazz, "centercorn_c", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->centercorn_c = (*env)->GetIntField(env, object, fieldID);

	// centercorn_b
	fieldID = (*env)->GetFieldID(env, clazz, "centercorn_b", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->centercorn_b = (*env)->GetIntField(env, object, fieldID);

	// centercorn_g
	fieldID = (*env)->GetFieldID(env, clazz, "centercorn_g", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->centercorn_g = (*env)->GetIntField(env, object, fieldID);

	// lowmans check out
	// TUB_BIG_VANILLA
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_BIG_VANILLA", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_BIG_VANILLA = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_BIG_CHOCO
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_BIG_CHOCO", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_BIG_CHOCO = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_BIG_BERRY
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_BIG_BERRY", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_BIG_BERRY = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_BIG_GREEN
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_BIG_GREEN", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_BIG_GREEN = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_SMALL_VANILLA
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_SMALL_VANILLA", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_SMALL_VANILLA = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_SMALL_CHOCO
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_SMALL_CHOCO", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_SMALL_CHOCO = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_SMALL_BERRY
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_SMALL_BERRY", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_SMALL_BERRY = (*env)->GetBooleanField(env, object, fieldID);

	// TUB_SMALL_GREEN
	fieldID = (*env)->GetFieldID(env, clazz, "TUB_SMALL_GREEN", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->TUB_SMALL_GREEN = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_H_VANILLA
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_H_VANILLA", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_H_VANILLA = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_H_CHOCO
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_H_CHOCO", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_H_CHOCO = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_H_BERRY
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_H_BERRY", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_H_BERRY = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_L_VANILLA
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_L_VANILLA", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_L_VANILLA = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_L_CHOCO
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_L_CHOCO", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_L_CHOCO = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_L_BERRY
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_L_BERRY", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_L_BERRY = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_H_GREEN
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_H_GREEN", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_H_GREEN = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_L_GREEN
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_L_GREEN", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_L_GREEN = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_R_VANILLA
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_R_VANILLA", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_R_VANILLA = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_R_CHOCO
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_R_CHOCO", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_R_CHOCO = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_R_BERRY
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_R_BERRY", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_R_BERRY = (*env)->GetBooleanField(env, object, fieldID);

	// SPOON_R_GREEN
	fieldID = (*env)->GetFieldID(env, clazz, "SPOON_R_GREEN", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SPOON_R_GREEN = (*env)->GetBooleanField(env, object, fieldID);

	// RING_VERTICAL
	fieldID = (*env)->GetFieldID(env, clazz, "RING_VERTICAL", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->RING_VERTICAL = (*env)->GetBooleanField(env, object, fieldID);

	// RING_HORIZON
	fieldID = (*env)->GetFieldID(env, clazz, "RING_HORIZON", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->RING_HORIZON = (*env)->GetBooleanField(env, object, fieldID);

	// SUNGLASS
	fieldID = (*env)->GetFieldID(env, clazz, "SUNGLASS", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->SUNGLASS = (*env)->GetBooleanField(env, object, fieldID);

	// CAP_OBJ
	fieldID = (*env)->GetFieldID(env, clazz, "CAP_OBJ", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CAP_OBJ = (*env)->GetBooleanField(env, object, fieldID);

	// ICE_OBJ
	fieldID = (*env)->GetFieldID(env, clazz, "ICE_OBJ", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->ICE_OBJ = (*env)->GetBooleanField(env, object, fieldID);

	// PATTERN_CAST
	fieldID = (*env)->GetFieldID(env, clazz, "PATTERN_CAST", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->PATTERN_CAST = (*env)->GetBooleanField(env, object, fieldID);

	// MIX_OBJ
	fieldID = (*env)->GetFieldID(env, clazz, "MIX_OBJ", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->MIX_OBJ = (*env)->GetBooleanField(env, object, fieldID);

	// MASK_OBJ
	fieldID = (*env)->GetFieldID(env, clazz, "MASK_OBJ", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->MASK_OBJ = (*env)->GetBooleanField(env, object, fieldID);

	// CenterMilkCream
	fieldID = (*env)->GetFieldID(env, clazz, "CenterMilkCream", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterMilkCream = (*env)->GetBooleanField(env, object, fieldID);

	// CenterCherry
	fieldID = (*env)->GetFieldID(env, clazz, "CenterCherry", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterCherry = (*env)->GetBooleanField(env, object, fieldID);

	// CenterChocochips
	fieldID = (*env)->GetFieldID(env, clazz, "CenterChocochips", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterChocochips = (*env)->GetBooleanField(env, object, fieldID);

	// CenterNuts
	fieldID = (*env)->GetFieldID(env, clazz, "CenterNuts", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterNuts = (*env)->GetBooleanField(env, object, fieldID);

	// CenterCandy
	fieldID = (*env)->GetFieldID(env, clazz, "CenterCandy", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterCandy = (*env)->GetBooleanField(env, object, fieldID);

	// CenterSpoid_v
	fieldID = (*env)->GetFieldID(env, clazz, "CenterSpoid_v", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterSpoid_v = (*env)->GetBooleanField(env, object, fieldID);

	// CenterSpoid_c
	fieldID = (*env)->GetFieldID(env, clazz, "CenterSpoid_c", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterSpoid_c = (*env)->GetBooleanField(env, object, fieldID);

	// CenterSpoid_b
	fieldID = (*env)->GetFieldID(env, clazz, "CenterSpoid_b", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterSpoid_b = (*env)->GetBooleanField(env, object, fieldID);

	// CenterSpoid_g
	fieldID = (*env)->GetFieldID(env, clazz, "CenterSpoid_g", "Z");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->CenterSpoid_g = (*env)->GetBooleanField(env, object, fieldID);

	// defalutTime
	fieldID = (*env)->GetFieldID(env, clazz, "DefaultTime", "F");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->defaultTime = (*env)->GetFloatField(env, object, fieldID);

	// defaultMove
	fieldID = (*env)->GetFieldID(env, clazz, "DefaultMove", "I");
	if (fieldID == NULL) {
		LOGE("nativeLoadXML : find class field failed");
		return;
	}
	field->defaultMove = (*env)->GetIntField(env, object, fieldID);

}

void nativeLoadResInfo(JNIEnv* env, jobject thiz, jobjectArray paths, jobjectArray fds, jlongArray offs, jlongArray lengs) {
	jclass cls = (*env)->GetObjectClass(env, thiz);

	int size = (*env)->GetArrayLength(env, fds);
	jclass fdClass = (*env)->FindClass(env, "java/io/FileDescriptor");
	jfieldID fdClassDescriptorFieldID = (*env)->GetFieldID(env, fdClass, "descriptor", "I");

	jlong* offArray = (*env)->GetLongArrayElements(env, offs, 0);
	jlong* lengArray = (*env)->GetLongArrayElements(env, lengs, 0);

	if (fileList == NULL) fileList = getFileListInstance();

	int i;
	for (i=0; i<size; i++) {
		jstring jpath = (jstring) (*env)->GetObjectArrayElement(env, paths, i);
		const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
		
		jobject jfd = (*env)->GetObjectArrayElement(env, fds, i);
		int fd = (*env)->GetIntField(env, jfd, fdClassDescriptorFieldID);
//		LOGV("fd first %i", fd);
		long off = *(offArray + i);
		long leng = *(lengArray + i);

		FileInfo* fileInfo = getFileInfoInstance();

//		LOGV("jni %s", path);
		fileInfo->path = calloc(strlen(path) + 1, sizeof(char));
		sprintf(fileInfo->path, "%s", path);
		fileInfo->fd = fd;
		fileInfo->off = off;
		fileInfo->leng = leng;
//		LOGV("jni %s", fileInfo->path);
		addFileInfo(fileList, fileInfo);

		(*env)->ReleaseStringUTFChars(env, jpath, path);
	}
}

////////////////////////////////////////
//   java method call
////////////////////////////////////////
void saveRecord(int score) {
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "saveRecord", "(I)V");
	if (mid != 0) {
		(*g_env)->CallVoidMethod(g_env, gelatoObject, mid, score);
	}
}

jint loadRecord() {
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "loadRecord", "()I");
	if (mid != 0) {
		return (jint)(*g_env)->CallIntMethod(g_env, gelatoObject, mid);
	}
}

void playSound(const char* soundCode) {
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "playSound", "(Ljava/lang/String;)V");
	if (mid != 0) {
		jstring str = (*g_env)->NewStringUTF(g_env, soundCode);
		(*g_env)->CallVoidMethod(g_env, gelatoObject, mid, str);
	}
}

void playMusic(const char* soundCode) {
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "playMusic", "(Ljava/lang/String;)V");
	if (mid != 0) {
		jstring str = (*g_env)->NewStringUTF(g_env, soundCode);
		(*g_env)->CallVoidMethod(g_env, gelatoObject, mid, str);
	}
}

void startMusic() {
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "startMusic", "()V");
	if (mid != 0) {	
		(*g_env)->CallVoidMethod(g_env, gelatoObject, mid);
	}
}

void stopMusic() {	
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "stopMusic", "()V");
	if (mid != 0) {
		(*g_env)->CallVoidMethod(g_env, gelatoObject, mid);
	}
}

void pauseMusic() {
	jmethodID mid = (*g_env)->GetMethodID(g_env, gelatoClass, "pauseMusic", "()V");
	if (mid != 0) {
		(*g_env)->CallVoidMethod(g_env, gelatoObject, mid);
	}
}


/**
 @file Core/VBString.h
 @brief VBEngine의 VBString 구조체타입과 여러 함수들.
 @author
 <table>
 <tr><th>Developer</th><th>Role</th><th>Email</th></tr>
 <tr><td>장원희</td><td>Main Programmer</td><td>mario@vanillabreeze.com</td></tr>
 <tr><td>김희동</td><td>Programmer</td><td>welivehere@vanillabreeze.com</td></tr>
 <tr><td>박두철</td><td>Programmer</td><td>encjf@vanillabreeze.com</td></tr>
 </table>
 @version 1.0
 @section License
 Copyright 2011 vanilla breeze. All rights reserved.
 */

#ifndef __VBString_H__
#define __VBString_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	/**
	 @brief String 관련 VBString 구조체타입.
	 */
	typedef struct VBString VBString;
	
	/**
	 @brief String 관련 VBString 구조체.
	 
	 String은 문자열을 나타내는 데이터 유형입니다.\n
	 String은 프리미티브 문자열 값 유형을 조작하는 데 사용할 수 있는 메서드와 속성을 제공합니다.\n
	 String 관련 함수를 사용하면 모든 객체의 값을 String 데이터 유형 객체로 변환할 수 있습니다.
	 
	 */
	struct VBString {
		/*!
		 String의 길이
		 */
		VBUShort len;
		/*!
		 String data
		 */
		void* data;
	};
	
	/**
	 @brief VBString의 메모리를 할당합니다.
	 
	 <b>Example</b>
	 <table bgcolor="#DDDDDD">
		<tr>
			<td>
				<i>VBEngine에서는 메모리의 할당과 동시에 초기화를 할 수 있습니다.<i> \n\n
				VBString* str = VBStringInit(VBStringAlloc());
	 
				참고 사항 \n
				<a href="file:///Users/welivehere/Desktop/html/_v_b_string_8h.html#a418b4a73ab610d7f722acc7a4d165702">메모리 초기화</a>
			</td>
		</tr>
	 </table>
	 
	 @return 메모리가 할당된 VBString를 반환합니다.
	 */
	VBString* VBStringAlloc(void);
	/**
	 @brief VBString을 초기화합니다.
	 
	 <b>Example</b>
	 <table bgcolor="#DDDDDD">
        <tr>
            <td>
                VBEngine에서는 메모리의 할당과 동시에 초기화를 할 수 있습니다. \n\n
                VBString* str = VBStringInit(VBStringAlloc());
	 
                참고 사항 \n

            <a href="file:///Users/welivehere/Desktop/html/_v_b_string_8h.html#a418b4a73ab610d7f722acc7a4d165702">메모리 할당</a>
            </td>
        </tr>
	 </table>
	 
	 @param _str VBString.
     @return 초기화된 VBString을 반환합니다.
	 */
	VBString* VBStringInit(VBString* _str);
	
	/**
	 @brief VBString의 값을 c문자열 상수로 초기화합니다. 
	 @param _str VBString.
	 @param _cstr 문자열 상수.
     @return _cstr로 초기화된 VBString을 반환합니다.
	 */
	VBString* VBStringInitWithCString(VBString* _str, const VBChar* _cstr);
	
	/**
	 @brief	VBString의 값을 c문자열 상수와 그 뒤로 오는 인자들로 형식화된 문자열로 초기화합니다.
	 @param _str VBString.
	 @param _max_fmt_len 형식화될 문자열의 최대길이.
	 
	 이 수가 실제 완성될 데이터 사이즈 보다 작으면 올바르게 작동하지 않습니다.\n
	 실제로 이 수가 데이터 사이즈를 말하는것은 아닙니다.\n
	 이함수를 호출하면서 잠시 사용하게될 메모리 스택 사이즈 입니다.
	 @param _fmt 포맷변환 가능한 문자열 상수
	 @param ... 변환할 아규먼트들
     @return 형식화된 문자열로 초기화된 VBString을 반환합니다.
	 */
	VBString* VBStringInitWithCStringFormat(VBString* _str, const VBChar* _fmt, ...);
	
	/**
	 @brief VBString의 메모리를 해제합니다. 
	 
	 <b>Example</b>
	 <table bgcolor="#DDDDDD" width="1225">
        <tr>
            <td>
                <i>VBEngine에서는 메모리를 할당한 경우 해제를 반드시 수행하셔야 합니다.</i> \n\n
                VBStringFree(&str);
            </td>
        </tr>
	 </table>
	 
	 @param _str VBString.
	 */
	void VBStringFree(VBString** _str);
	
	/**
	 @brief VBString의 값을 c문자열 상수로 초기화하고 문자열 포인터를 구하여 복사합니다.
	 @param _str VBString.
     @return 새로 할당되고 문자열이 복사된 VBString을 반환합니다.
	 */
	VBString* VBStringCopy(VBString* _str);
	
	/**
	 @brief VBString의 값을 c문자열 상수로 설정합니다. 
	 @param _str VBString.
	 @param _cstr 문자열 상수.
	 */
	void VBStringSetCString(VBString* _str, const VBChar* _cstr);
	
	/**
	 @brief VBString의 값에 다른 문자열 상수를 추가합니다.
	 @param _str VBString.
	 @param _cstr 추가되는 문자열 상수.
	 */
	void VBStringAddCString(VBString* _str, const VBChar* _cstr);
	
	/**
	 @brief	VBString의 값을 c문자열 상수와 그 뒤로 오는 인자들로 형식화된 문자열로 설정합니다.
	 @param _str VBString.
	 @param _max_fmt_len 형식화될 문자열의 최대길이.
	 
	 이 수가 실제 완성될 데이터 사이즈 보다 작으면 올바르게 작동하지 않습니다.\n
	 실제로 이 수가 데이터 사이즈를 말하는것은 아닙니다.\n
	 이함수를 호출하면서 잠시 사용하게될 메모리 스택 사이즈 입니다.
	 @param _fmt 포맷변환 가능한 문자열 상수
	 @param ... 변환할 아규먼트들
	 */
	void VBStringSetCStringFormat(VBString* _str, const VBChar* _fmt, ...);
	
	/**
	 @brief	c문자열 상수와 그 뒤로 오는 인자들로 형식화된 문자열만들어 VBString의 값에 추가합니다.
	 @param _str VBString.
	 @param _max_fmt_len 형식화될 문자열의 최대길이.
	 
	 이 수가 실제 완성될 데이터 사이즈 보다 작으면 올바르게 작동하지 않습니다.\n
	 실제로 이 수가 데이터 사이즈를 말하는것은 아닙니다.\n
	 이함수를 호출하면서 잠시 사용하게될 메모리 스택 사이즈 입니다.
	 @param _fmt 포맷변환 가능한 문자열 상수
	 @param ... 변환할 아규먼트들
	 */
	void VBStringAddCStringFormat(VBString* _str, const VBChar* _fmt, ...);
	
	/**
	 @brief 문자열 포인터를 구합니다. 
	 @param _str VBString.
     @return 문자열의 포인터
	 */
	VBChar* VBStringGetCString(VBString* _str);
	
	/**
	 @brief VBString의 문자열 길이를 구합니다. 
	 @param _str VBString.
	 @return VBString 문자열의 길이를 반환합니다. 
	 */
	VBUShort VBStringGetLength(VBString* _str);
	
	/**
	 @brief VBString의 문자열 데이터에서 해당 위치의 문자를 구합니다. 
	 @param _str VBString.
	 @param _at 가져오려는 문자의 위치
	 @return 문자열 데이터에서 해당 위치의 문자를 반환합니다.
	 
	 해당 위치에 문자가 존재하지 않거나 문자열의 범위를 벗어나는 아규먼트를 넘길경우 '\0'문자를 반환합니다.
	 */
	VBChar VBStringGetCharAt(VBString* _str, VBUShort _at);
	
	/**
	 @brief VBString의 문자열 데이터의 문자를 해당 위치를 지정합니다.
	 @param _str VBString.
	 @param _at 지정하려는 위치.
	 @param _char 문자열 데이터에 저장하려는 문자.
	 */
	void VBStringSetCharAt(VBString* _str, VBUShort _at, VBChar _char);
	
	/**
	 @brief 2개의 VBString이 같은지 비교합니다.
	 @param _str_1 비교하려는 첫번쨰 VBString.
	 @param _str_2 비교하려는 두번째 VBString.
	 @return 첫번째 VBString의 값과 두번째 VBString의 값이 같으면 값이 VBTrue이고, 같지 않으면 VBFalse입니다.
	 */
	VBBool VBStringIsEqual(VBString* _str_1, VBString* _str_2);
    
	/**
	 @brief VBString의 문자열 데이터를 문자열 상수값과 같은지 비교합니다.
	 @param _str VBString.
	 @param _cstr 문자열 상수
     @return 두 문자열이 같으면 VBTrue, 다르면 VBFalse
	 */
	VBBool VBStringIsEqualToCString(VBString* _str, const VBChar* _cstr);
	
	/**
	 @brief VBString의 문자열을 검색하여 문자열의 위치를 반환합니다.
	 @param _str VBString 검색할 하위 문자열.
	 @param _of_str 선택 요소로서, 검색을 시작할 인덱스.
     @return 검색 성공시 index를 실패시 -1을 반환합니다.
	 */
	VBLong VBStringIndexOf(VBString* _str, VBString* _of_str);
	
	/**
	 @brief VBString의 문자열을 검색하여 문자열 상수값이 발견된 위치를 반환합니다.
	 @param _str VBString.
	 @param _of_cstr 선택 요소로서, 검색을 시작할 인덱스.
     @return 검색 성공시 index를 실패시 -1을 반환합니다.
	 */
	VBLong VBStringIndexOfCString(VBString* _str, const VBChar* _of_cstr);
	
	/**
	 @brief 문자열을 오른쪽에서 왼쪽으로 검색하여 마지막 문자열 상수값을 반환합니다.
	 @param _str VBString.
	 @param _of_str 반환된 문자열 상수값.
     @return 검색 성공시 index를 실패시 -1을 반환합니다.
	 */
	VBLong VBStringLastIndexOf(VBString* _str, VBString* _of_str);
	
	/**
	 @brief 문자열을 오른쪽에서 왼쪽으로 검색하고 시작 인덱스 앞에서 값이 마지막으로 나타난 인덱스를 반환합니다.
	 @param _str VBString.
	 @param _of_cstr 반환된 문자열 상수값.
     @return 검색 성공시 index를 실패시 -1을 반환합니다.
	 */
	VBLong VBStringLastIndexOfCString(VBString* _str, const VBChar* _of_cstr);
	
	/**
	 @brief start 문자부터 end 문자 바로 앞까지 모든 문자가 포함된 문자열을 반환합니다.
	 @param _str VBString.
	 @param _start 슬라이스 시작점의 인덱스.
	 @param _end 슬라이스 끝점의 인덱스.
	 */
	void VBStringSlice(VBString* _str, VBUShort _start, VBUShort _end);
	
	/**
	 @brief 복사된 VBString의 값의 start 문자부터 end 문자 바로 앞까지 모든 문자가 포함된 문자열을 반환합니다.
	 @param _str VBString.
	 @param _start 슬라이스 시작점의 인덱스.
	 @param _end 슬라이스 끝점의 인덱스.
     @return 지정한 위치의 문자열을 반환합니다.
	 */
	VBString* VBStringSliceAndCopy(VBString* _str, VBUShort _start, VBUShort _end);
	
	/**
	 @brief 이 문자열의 모든 대문자를 소문자로 변환한 복사본을 반환합니다.
	 @param _str VBString.
	 */
	void VBStringLowerCase(VBString* _str);
	
	/**
	 @brief 이 문자열의 모든 소문자를 대문자로 변환한 복사본을 반환합니다.
	 @param _str VBString.
	 */
	void VBStringUpperCase(VBString* _str);	
    /**
	 @brief 지정된 _start 인덱스에서 시작하여 _len에 지정된 길이의 문자로 구성된 하위 문자열을 반환합니다. 원래 문자열은 수정되지 않습니다.
	 @param _str VBString.
     @param _start 하위 문자열을 만드는 데 사용할 첫 번째 문자의 인덱스를 지정하는 정수입니다
     @param _len 만들려는 하위 문자열의 문자 수입니다. 기본값은 허용되는 최대값입니다. 
	 */
	void VBStringSubstr(VBString* _str, VBUShort _start, VBUShort _len);
    
#ifdef __cplusplus
}
#endif

#endif
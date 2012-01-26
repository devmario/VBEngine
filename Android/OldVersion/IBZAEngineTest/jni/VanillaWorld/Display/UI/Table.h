#ifndef __TABLE_H__
#define __TABLE_H__

//version 1.0
//editor 장원희
//update date 2010.4.14

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdbool.h>
	
#include "../Object/Model.h"
	
#pragma mark -
#pragma mark Table example
	
#pragma mark -
#pragma mark Table define
	
	//매프레임당 y스크롤 힘 감소값
#define TABLE_Y_SCROLL_FORCE_MULTIPLY 0.95
	
	//끝에 걸렷을경우의 매프레임당 y스크롤 힘 감소값
#define TABLE_Y_END_SCROLL_FORCE_MULTIPLY 0.9
	
	//y스크롤 끝에 걸릴때 되돌아 가는 속도값
#define TABLE_MIN_MAX_Y_SCROLL_SPEED 0.2
	
	//y스크롤 끝에 걸릴는 정밀도 값
#define TABLE_MIN_MAX_Y_SCROLL_DETAIL 0.1
	
	//row state
	enum {
		//열이 선택되어있는지 여부
		TableRowStateSelect =		0x01,
		//포커스가 되어있는지 여부
		TableRowStateFocus =			0x10
	};
	typedef unsigned char TableRowState;
	
	typedef struct TableRow TableRow;
	typedef struct Table Table;
	
	typedef struct TableAddRowEvent TableAddRowEvent;
	typedef struct TableRemoveRowEvent TableRemoveRowEvent;
	typedef struct TableSelectRowEvent TableSelectRowEvent;
	typedef struct TableFocusRowEvent TableFocusRowEvent;
	
#pragma mark -
#pragma mark TableRow
	
	//테이블라인 구조체
	struct TableRow {
		//데이터 관련
		unsigned short index;			//row의 인덱스
		void* data;						//표시해줄 데이터
		TableRowState state;			//row의 상태

		//개발자가 접근하여 사용하는 데이터
		void* temporaryData;			//동적으로 생성할 메모리 포인터
		
		//디스플레이 관련
		Model* model;					//model
		Vector3D* hitVertex;			//충돌
		
		//이벤트 관련
		void* touchID;					//터치 ID
		void* parentTableView;			//tableView 타겟
	};
	
#pragma mark -
#pragma mark Table event	
	
	//화면에 나올때 콜백
	struct TableAddRowEvent {
		void* userReference;
		void (*event)(void* userReference, TableRow* row);
	};
	
	TableAddRowEvent TableAddRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row));
	
	//화면에 사라질때 콜백
	struct TableRemoveRowEvent {
		void* userReference;
		void (*event)(void* userReference, TableRow* row);
	};
	
	TableRemoveRowEvent TableRemoveRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row));
	
	//선택시 콜백
	//select:열이 선택되어있는가 여부
	struct TableSelectRowEvent {
		void* userReference;
		void (*event)(void* userReference, TableRow* row, bool selected);
	};
	
	TableSelectRowEvent TableSelectRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row, bool selected));
	
	
	//터치 다운 업 콜백
	//focus:열이 포커싱 되어있는가 여부
	struct TableFocusRowEvent {
		void* userReference;
		void (*event)(void* userReference, TableRow* row, bool focus);
	};
	
	TableFocusRowEvent TableFocusRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row, bool focus));
	
#pragma mark -
#pragma mark Table
	
	//테이블 구조체
	struct Table {
		//디스플레이 데이터
		Model* model;					//model
		Model* maskModel;				//mask
		Vector3D* vertex;				//vertex
		
		//테이블 정보
		unsigned short visibleRow;		//보이는 라인수
		signed long selectedIndex;		//현재 선택된 인덱스
		Array* datas;					//data
		
		//스크롤
		float Y;						//현재 스크롤된 y위치
		float preY;						//이전 y위치
		float maxY;						//스크롤 최대치
		float minY;						//스크롤 최소치
		float forceY;					//y스크롤 힘
		float preTouchY;				//이전 터치Y
		float touchY;					//터치 Y
		
		//테이블 열
		Array* rows;					//tableRow(눈에 보이는 갯수만큼만 생성함)
		float rowHeight;				//tableRow 높이
		
		//색상
		ColorRGBA maskColor;			//mask color
		ColorRGBA bgColor;				//background color
		
		TableRowState* state;			//row의 상태를 저장하는 배열 포인터

		void* touchID;						//터치 ID
		
		TableAddRowEvent addRowEvent;		//작동 콜백(나올때 메모리 생성후 그려야함)
		TableRemoveRowEvent removeRowEvent;	//작동 콜백(사라질때 메모리 해제)
		
		TableSelectRowEvent selectRowEvent;	//선택 이벤트
		TableFocusRowEvent focusRowEvent;	//터치 이벤트
	};
	
#pragma mark -
#pragma mark Table init and free
	
	
	//초기화
	//table:struct pointer
	//datas:열 데이터들
	//width:table 넓이
	//height:table 높이
	//rowHeight:열 높이
	//bgColor:백그라운드 칼라
	//maskColor:마스크 칼라(실제 칼라링하지는 않음)
	//addRowEvent:열 메모리 생성 add 이벤트
	//removeRowEvent:열 메모리 해제 remove 이벤트
	//isSelectable:선택할수 있는가 여부
	bool TableInit(Table* table, Array* datas,
				   float width, float height, float rowHeight,
				   ColorHexRGBA maskColor, ColorHexRGBA bgColor,
				   TableAddRowEvent addRowEvent, TableRemoveRowEvent removeRowEvent,
				   bool isSelectable);
	
	//해제
	//table:struct pointer
	bool TableFree(Table* table);
	
#pragma mark -
#pragma mark Table event
	
	//row 선택(선택,선택해제)시 발생하는 콜백 등록
	//table:struct pointer
	//selectRowEvent:열 선택시 콜백
	bool TableAddSelectRowEvent(Table* table, TableSelectRowEvent selectRowEvent);
	
	//row 선택(선택,선택해제)시 발생하는 콜백 삭제
	//table:struct pointer
	bool TableRemoveSelectRowEvent(Table* table);
	
	//row 포커스시 발생하는 콜백 등록
	//table:struct pointer
	//focusRowEvent:열 포커스시 콜백
	bool TableAddFocusRowEvent(Table* table, TableFocusRowEvent focusRowEvent);
	
	//row 포커스시 발생하는 콜백 삭제
	//table:struct pointer
	bool TableRemoveFocusRowEvent(Table* table);
	
#pragma mark -
#pragma mark Table get,set
	
	//열의 인덱스(row가 표시해주는 data의 인덱스)를 가져오는 함수
	//table:struct pointer
	//row:struct pointer
	//return:열이 표시해주는 data의 인덱스
	int TableGetRowIndex(Table* table, TableRow* row);
	
	//열 선택하거나 선택 해제
	//table:struct pointer
	//index:data의 인덱스
	//select:열의 선택 여부
	bool TableSelectRowAtIndex(Table* table, int index, bool selected);
	
	//열 선택하거나 선택 해제
	//table:struct pointer
	//row:struct pointer
	//select:열의 선택 여부
	bool TableSelectRow(Table* table, TableRow* row, bool selected);
	
	//열 포커싱하거나 포커싱 해제
	//table:struct pointer
	//index:data의 인덱스
	//focus:열의 포커싱 여부
	bool TableFocusRowAtIndex(Table* table, int index, bool focus);
	
	//열 포커싱하거나 포커싱 해제
	//table:struct pointer
	//row:struct pointer
	//focus:열의 포커싱 여부
	bool TableFocusRow(Table* table, TableRow* row, bool focus);
	
	void TableUpdate(Table *table);
	
#ifdef __cplusplus
}
#endif


#endif

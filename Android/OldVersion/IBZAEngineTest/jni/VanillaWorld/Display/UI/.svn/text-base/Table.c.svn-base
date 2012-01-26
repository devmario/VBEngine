#include "Table.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TableAddRowEvent TableAddRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row)) {
	TableAddRowEvent returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.event = event;
	return returnEvent;
}

TableRemoveRowEvent TableRemoveRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row)) {
	TableRemoveRowEvent returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.event = event;
	return returnEvent;
}

TableSelectRowEvent TableSelectRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row, bool selected)) {
	TableSelectRowEvent returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.event = event;
	return returnEvent;
}

TableFocusRowEvent TableFocusRowEventInit(void* userReference, void (*event)(void* userReference, TableRow* row, bool focus)) {
	TableFocusRowEvent returnEvent;
	returnEvent.userReference = userReference;
	returnEvent.event = event;
	return returnEvent;
}

//row가 삭제되고 다시 붙을때(스크롤시) row를 실제 데이터에 맞게 셋팅해주는 함수
void _TableSetRow(Table* table, TableRow* row, int index) {
	//인뎃스 셋팅
	row->index = index;
	//터치 초기화
	row->touchID = NULL;
	//data와 row state셋팅
	row->data = ArrayObjectAtIndex(table->datas, index);
	if(row->data) {
		row->state = table->state[index];
	} else {
		row->state = 0;
	}
}

void TableUpdate(Table *table) {
	//y값을 셋팅함
	if(table->touchID == NULL) {
		//터치가 없을경우(TouchType_End, TouchType_Cancel) 물리 적용
		if(table->Y > (table->maxY - TABLE_MIN_MAX_Y_SCROLL_DETAIL)) {
			//스크롤이 끝(아래)에 닿았을 경우
			//물리량의 변화
			table->forceY *= TABLE_Y_END_SCROLL_FORCE_MULTIPLY;
			table->Y += table->forceY;
			//최대 값으로 이동
			table->Y += (table->maxY - table->Y) * TABLE_MIN_MAX_Y_SCROLL_SPEED;
		} else if(table->Y < (table->minY + TABLE_MIN_MAX_Y_SCROLL_DETAIL)) {
			//스크롤이 끝(위)에 닿았을 경우
			//물리량의 변화
			table->forceY *= TABLE_Y_END_SCROLL_FORCE_MULTIPLY;
			table->Y += table->forceY;
			//최소 값으로 이동
			table->Y += (table->minY - table->Y) * TABLE_MIN_MAX_Y_SCROLL_SPEED;
		} else {
			//물리량 감소
			table->forceY *= TABLE_Y_SCROLL_FORCE_MULTIPLY;
			table->Y += table->forceY;
		}
	} else {
		//터치가 있을경우(TouchType_Began, TouchType_Move) 한번 이동
		table->Y += table->forceY;
		table->forceY = 0.0;
	}
	
	//row가 화면의 끝에서 벗어나서 화면에서 사라졋을 경우 반대쪽으로 이동시키기 위한 루프
	int i = 0;
	for(; i < table->visibleRow; i++) {
		TableRow* row = (TableRow*)ArrayObjectAtIndex(table->rows, i);
		//row에 스크롤 적용
		*row->model->matrix = Matrix3DTranslate(*row->model->matrix, Vector3DInit(0.0, table->Y - table->preY, 0.0));
		
		if(row->model->matrix->m42 < -table->rowHeight) {
			//row가 화면 위쪽으로 사라질때
			table->removeRowEvent.event(table->removeRowEvent.userReference, row);
			//remove이벤트 발생후 화면 아래쪽으로 이동
			*row->model->matrix = Matrix3DTranslate(*row->model->matrix, Vector3DInit(0.0, table->visibleRow * table->rowHeight, 0.0));
			
			//row가 표시할 데이터가 바뀌었으므로 실제 데이터에 맡게 셋팅
			int index = TableGetRowIndex(table, row);
			_TableSetRow(table, row, index);
			
			//add이벤트 발생
			table->addRowEvent.event(table->addRowEvent.userReference, row);
		} else if(row->model->matrix->m42 > table->vertex[2].y) {
			//row가 화면 아래쪽으로 사라질때
			table->removeRowEvent.event(table->removeRowEvent.userReference, row);
			//remove이벤트 발생후 화면 위쪽으로 이동
			*row->model->matrix = Matrix3DTranslate(*row->model->matrix, Vector3DInit(0.0, -table->visibleRow * table->rowHeight, 0.0));
			
			//row가 표시할 데이터가 바뀌었으므로 실제 데이터에 맡게 셋팅
			int index = TableGetRowIndex(table, row);
			_TableSetRow(table, row, index);
			
			//add이벤트 발생
			table->addRowEvent.event(table->addRowEvent.userReference, row);
		}
	}
	
	//translate를 위한 이전 y위치 저장
	table->preY = table->Y;
}

void _TableTouchEvent(void *userReference, ModelEventTouchArgument argument) {
	Table* table = (Table*)userReference;
	
	
	//이벤트 시작(기존 이벤트가 없고, 히트되어있고, 터치 타입이 다운일경우)
	if(table->touchID == NULL && (argument.isHit == true && argument.touchType == TouchTypeBegan)) {
		table->touchID = argument.touchID;
		//이벤트가 있다면
		//현재 터치되어있는 포인트를 화면에서의 포인트가아닌 물체에서의 포인트로 바꿈
		//스크롤 관련 속성 초기화(TouchType_Began)
		table->forceY = 0.0;
		table->preTouchY = table->touchY = argument.hitVector->y;
	}
	
	if(table->touchID == argument.touchID) {
		table->touchY = argument.hitVector->y;
		table->forceY += table->touchY - table->preTouchY;
		//이벤트 삭제
		if(argument.touchType == TouchTypeEnd || argument.touchType == TouchTypeCancel) {
			table->touchID = NULL;
		}
		
		table->preTouchY = table->touchY;
	}
}

void _TableRowTouchEvent(void *userReference, ModelEventTouchArgument argument) {
	TableRow* row = (TableRow*)userReference;
	Table* table = (Table*)row->parentTableView;
	
	//테이블뷰 안을 터치다운 된 상태이고 열에 대하여 기존 이벤트가 없고, 히트되어있고, 터치 타입이 다운일경우
	if(table->touchID == argument.touchID && (!row->touchID && (argument.isHit && argument.touchID == TouchTypeBegan))) {
		row->touchID = argument.touchID;
		//포커스 인
		TableFocusRowAtIndex(table, row->index, true);
	}
	if(row->touchID == argument.touchID) {
		if(argument.touchType != TouchTypeBegan) {
			//포커스 아웃(터치가 움직이거나 땟을경우)
			TableFocusRowAtIndex(table, row->index, false);
			row->touchID = NULL;
		}
		if((argument.touchType == TouchTypeEnd || argument.touchType == TouchTypeCancel)) {
			//열 선택
			TableSelectRowAtIndex(table, row->index, true);
		}
	}
}

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
			   bool isSelectable) {
	//메모리 0으로 채움
	memset(table, 0, sizeof(Table));
	
	//초기화 할때 변환이 필요없는 속성 채우기
	table->selectedIndex = -1;					//처음에 선택이 안되어 있는상태로 불러옴
	table->datas = datas;
	table->rowHeight = rowHeight;
	table->addRowEvent = addRowEvent;
	table->removeRowEvent = removeRowEvent;
	
	//스크롤할수있는 최대 및 최소값 셋팅
	table->minY = height - (table->datas->length * table->rowHeight);
	table->maxY = 0.0;
	
	//OpenGLtableView 마스크와 충돌을 위한 vertex셋팅
	table->vertex = calloc(4, sizeof(Vector3D));
	table->vertex[1].x = table->vertex[3].x = width;
	table->vertex[2].y = table->vertex[3].y = height;
	
	//mask color
	table->maskColor = ColorHexRGBAToRGBAColor(maskColor);
	
	//bg color
	table->bgColor = ColorHexRGBAToRGBAColor(bgColor);
	
	//top model 생성
	table->model = malloc(sizeof(Model));
	ModelInitWithVertex(table->model, 0, NULL, NULL, NULL, 2, NULL, 0);
	//ModelSetColor(table->model, table->bgColor);
	
	//top sprite에 필요한 콜백 이벤트 등록
	ModelEventTouchArgument touchArgument;
	ModelAddEventTouch(table->model, 
					   ModelEventTouchInit(table, 
										   touchArgument, _TableTouchEvent), 2, table->vertex, true, true, false, false);
	
	//mask sprite 생성
	table->maskModel = malloc(sizeof(Model));
	ModelInitWithVertex(table->maskModel, 4, table->vertex, NULL, NULL, 2, NULL, 0);
	
	//row state
	table->state = calloc(table->datas->length, sizeof(TableRowState));
	
	//보여지는 라인 길이
	table->visibleRow = ceilf(height / rowHeight) + 1;
	
	//OpenGLtableRow array 생성(데이터 배열이 아닌 눈에보이는 row의 배열)
	table->rows = malloc(sizeof(Array));
	ArrayInit(table->rows);
	
	//라인수 만큼 OpenGLtableRow생성
	int i = 0;
	for(; i < table->visibleRow; i++) {
		//OpenGLtableRow메모리 생성
		TableRow* row = calloc(1, sizeof(TableRow));
		
		//array에 push
		ArrayPushObject(table->rows, row);
		
		//row hit Vertex
		row->hitVertex = calloc(4, sizeof(Vector3D));
		row->hitVertex[1].x = row->hitVertex[3].x = width;
		row->hitVertex[0].y = row->hitVertex[2].y = table->rowHeight;
		
		//row sprite(비어있고 히트만 체크)
		row->model = malloc(sizeof(Model));
		ModelInitWithVertex(row->model, 0, NULL, NULL, NULL, 0, NULL, 0);
		
		//row data, index, state설정
		_TableSetRow(table, row, i);
		
		//parent타겟 설정
		row->parentTableView = table;
		
		if(isSelectable) {
			//row 터치 이벤트 콜백 등록
			ModelEventTouchArgument touchArgument;
			ModelAddEventTouch(row->model, 
							   ModelEventTouchInit(row, 
												   touchArgument, 
												   _TableRowTouchEvent), 
							   2, 
							   row->hitVertex, 
							   false, 
							   false, 
							   false, 
							   false);
		}
		
		//row y position
		*row->model->matrix = Matrix3DTranslate(*row->model->matrix , Vector3DInit(0.0, i * table->rowHeight, 0.0));
		
		//화면에 add및 data setting, addEvent콜백 송출
		ModelAdd(table->model, row->model);
		table->addRowEvent.event(table->addRowEvent.userReference, row);
	}
	
	//마스킹 적용
	ModelSetMask(table->model, table->maskModel);
	return true;
}

//해제
//table:struct pointer
bool TableFree(Table* table) {
	//마스킹 해제
	ModelRemoveMask(table->model);
	
	//row배열요소 삭제
	while(table->rows->length) {
		//row를 배열에서 삭제
		TableRow* row = (TableRow*)ArrayObjectAtIndex(table->rows, 0);
		ArrayPopObjectAtIndex(table->rows, 0);
		
		//row sprite 제거, removeEvent콜백 송출 및 sprite release, free
		ModelRemove(table->model, row->model);
		table->removeRowEvent.event(table->removeRowEvent.userReference, row);
		ModelFree(row->model);
		free(row->model);
		
		//row vertex 메모리 free
		free(row->hitVertex);
		
		//row 메모리 free
		free(row);
	}
	//row배열 해제
	ArrayFree(table->rows);
	free(table->rows);
	
	//top sprite 해제
	ModelFree(table->model);
	free(table->model);
	
	//mask 해제
	ModelFree(table->maskModel);
	free(table->maskModel);
	
	//vertex 해제
	free(table->vertex);
	
	//row state 해제
	free(table->state);
	return true;
}

#pragma mark -
#pragma mark Table event

//row 선택(선택,선택해제)시 발생하는 콜백 등록
//table:struct pointer
//selectRowEvent:열 선택시 콜백
bool TableAddSelectRowEvent(Table* table, TableSelectRowEvent selectRowEvent) {
	table->selectRowEvent = selectRowEvent;
	return true;
}

//row 선택(선택,선택해제)시 발생하는 콜백 삭제
//table:struct pointer
bool TableRemoveSelectRowEvent(Table* table) {
	table->selectRowEvent.userReference = NULL;
	table->selectRowEvent.event = NULL;
	return true;
}

//row 포커스시 발생하는 콜백 등록
//table:struct pointer
//focusRowEvent:열 포커스시 콜백
bool TableAddFocusRowEvent(Table* table, TableFocusRowEvent focusRowEvent) {
	table->focusRowEvent = focusRowEvent;
	return true;
}

//row 포커스시 발생하는 콜백 삭제
//table:struct pointer
bool TableRemoveFocusRowEvent(Table* table) {
	table->focusRowEvent.userReference = NULL;
	table->focusRowEvent.event = NULL;
	return true;
}

#pragma mark -
#pragma mark Table get,set

//열의 인덱스(row가 표시해주는 data의 인덱스)를 가져오는 함수
//table:struct pointer
//row:struct pointer
//return:열이 표시해주는 data의 인덱스
int TableGetRowIndex(Table* table, TableRow* row) {
	return (int)roundf((row->model->matrix->m42 - table->Y) / table->rowHeight);
}

//열 선택하거나 선택 해제
//table:struct pointer
//index:data의 인덱스
//select:열의 선택 여부
bool TableSelectRowAtIndex(Table* table, int index, bool selected) {
	int i;
	
	if(table->selectedIndex != index) {
		
		//tableView row state설정
		if(index != -1) {
			if(((table->state[index] & TableRowStateSelect) == TableRowStateSelect) != selected) {
				table->state[index] ^= TableRowStateSelect;
			}
		} else {
			if((table->state[table->selectedIndex] & TableRowStateSelect) == TableRowStateSelect) {
				table->state[table->selectedIndex] ^= TableRowStateSelect;
			}
		}
		
		//select된 tableView row state deselect
		if(table->selectedIndex > -1) {
			if((table->state[table->selectedIndex] & TableRowStateSelect) == TableRowStateSelect) {
				table->state[table->selectedIndex] ^= TableRowStateSelect;
			}
		}
		
		TableRow* row;
		for(i = 0; i < table->rows->length; i++) {
			row = ArrayObjectAtIndex(table->rows, i);
			if(index == row->index) {
				//row 선택
				if(((row->state & TableRowStateSelect) == TableRowStateSelect) != selected) {
					row->state ^= TableRowStateSelect;
					if(table->selectRowEvent.event) {
						table->selectRowEvent.event(table->selectRowEvent.userReference, row, selected);
					}
				}
			} else {
				//선택되어있는 row는 풀어줌
				if((row->state & TableRowStateSelect) == TableRowStateSelect) {
					row->state ^= TableRowStateSelect;
					if(table->selectRowEvent.event) {
						table->selectRowEvent.event(table->selectRowEvent.userReference, row, false);
					}
				}
			}
		}
		
		table->selectedIndex = index;
	}
	return true;
}

//열 선택하거나 선택 해제
//table:struct pointer
//row:struct pointer
//select:열의 선택 여부
bool TableSelectRow(Table* table, TableRow* row, bool selected) {
	int index = TableGetRowIndex(table, row);
	TableSelectRowAtIndex(table, index, selected);
	return true;
}

//열 포커싱하거나 포커싱 해제
//table:struct pointer
//index:data의 인덱스
//focus:열의 포커싱 여부
bool TableFocusRowAtIndex(Table* table, int index, bool focus) {
	int i;
	
	//tableView row state설정
	if(((table->state[index] & TableRowStateFocus) == TableRowStateFocus) != focus) {
		table->state[index] ^= TableRowStateFocus;
	}
	
	for(i = 0; i < table->rows->length; i++) {
		TableRow* row = ArrayObjectAtIndex(table->rows, i);
		if(index == row->index) {
			//row 포커싱인또는 포커싱아웃
			if(((row->state & TableRowStateFocus) == TableRowStateFocus) != focus) {
				row->state ^= TableRowStateFocus;
				if(table->focusRowEvent.event) {
					table->focusRowEvent.event(table->focusRowEvent.userReference, row, focus);
				}
			}
		}
	}
	return true;
}

//열 포커싱하거나 포커싱 해제
//table:struct pointer
//row:struct pointer
//focus:열의 포커싱 여부
bool TableFocusRow(Table* table, TableRow* row, bool focus) {
	int index = TableGetRowIndex(table, row);
	TableFocusRowAtIndex(table, index, focus);
	return true;
}

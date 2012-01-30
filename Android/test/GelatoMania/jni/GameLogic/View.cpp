#include <iostream>
#include "View.h"

View::View() {
    top = new VBModel();
}

View::~View() {
    if(top) {
        delete top;
        top = NULL;
    }
}

void View::Update(float _deltaTime) {
    
}

void View::touchBegin(CCTouch* _touch, CCPoint _location) {
    
}

void View::touchMove(CCTouch* _touch, CCPoint _location) {
    
}

void View::touchEnd(CCTouch* _touch, CCPoint _location) {
    
}

void View::touchCancel(CCTouch* _touch, CCPoint _location) {
    
}
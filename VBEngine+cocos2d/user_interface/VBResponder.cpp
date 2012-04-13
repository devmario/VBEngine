#include "VBResponder.h"

using namespace std;

list<VBResponder*>* _responders = new list<VBResponder*>();

void VBResponder::RegistResponder() {
	responder_iterator = _responders->insert(_responders->end(), this);
}

void VBResponder::UnregistResponder() {
	_responders->erase(responder_iterator);
}

void VBResponderTouchBegin(CCTouch* _touch) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		_responder->TouchBegin(_touch);
		_it++;
	}
}

void VBResponderTouchMove(CCTouch* _touch) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		_responder->TouchMove(_touch);
		_it++;
	}
}

void VBResponderTouchEnd(CCTouch* _touch) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		_responder->TouchEnd(_touch);
		_it++;
	}
}

void VBResponderTouchCancel(CCTouch* _touch) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		_responder->TouchCancel(_touch);
		_it++;
	}
}
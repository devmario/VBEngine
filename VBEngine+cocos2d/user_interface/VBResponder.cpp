#include "VBResponder.h"

using namespace std;

list<VBResponder*>* _responders = new list<VBResponder*>();

void VBResponder::RegistResponder() {
	is_active = true;
	responder_iterator = _responders->insert(_responders->end(), this);
}

void VBResponder::UnregistResponder() {
	is_active = false;
	_responders->erase(responder_iterator);
}

void VBResponderTouchBegin(CCTouch* _touch, std::string _tag) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		if(_responder->GetResponderTag() == _tag) {
			if(_responder->GetIsActive())
				_responder->TouchBegin(_touch);
		}
		_it++;
	}
}

void VBResponderTouchMove(CCTouch* _touch, std::string _tag) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		if(_responder->GetResponderTag() == _tag) {
			if(_responder->GetIsActive())
				_responder->TouchMove(_touch);
		}
		_it++;
	}
}

void VBResponderTouchEnd(CCTouch* _touch, std::string _tag) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		if(_responder->GetResponderTag() == _tag) {
			if(_responder->GetIsActive())
				_responder->TouchEnd(_touch);
		}
		_it++;
	}
}

void VBResponderTouchCancel(CCTouch* _touch, std::string _tag) {
	list<VBResponder*>::iterator _it = _responders->begin();
	while(_it != _responders->end()) {
		VBResponder* _responder = *_it;
		if(_responder->GetResponderTag() == _tag) {
			if(_responder->GetIsActive())
				_responder->TouchCancel(_touch);
		}
		_it++;
	}
}
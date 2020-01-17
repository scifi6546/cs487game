#include "pch.h"
#include "gamelib_object.hpp"

namespace GameLib
{
	Object::Object() {}

	Object::~Object() {}

	void Object::rename(const char* newName) {
		_setName(newName);
	}

	void Object::updatemeta() {
		_setDesc(_updateDesc());
		_setInfo(_updateInfo());
	}
}
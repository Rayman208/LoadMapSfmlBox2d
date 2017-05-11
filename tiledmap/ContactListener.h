#pragma once

#include <Box2D\Box2D.h>
#include <iostream>

using namespace std;

class ContactListener: public b2ContactListener
{
public:
	ContactListener() {}
	~ContactListener() {}

	virtual void BeginContact(b2Contact* aContact);
	virtual void EndContact(b2Contact* aContact) {}

};


#pragma once

#include <Box2D\Box2D.h>
#include <iostream>

using namespace std;

class ContactListener: public b2ContactListener
{
private:
	b2World* _world;
public:
	ContactListener(b2World* world);
	~ContactListener(); 

	virtual void BeginContact(b2Contact* aContact);
	virtual void EndContact(b2Contact* aContact);

	void SetWorld(b2World* world) { _world = world; }
	b2World* GetWorld() { return _world; }
};


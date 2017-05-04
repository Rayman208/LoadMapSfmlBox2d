#include "ContactListener.h"


ContactListener::ContactListener(b2World * world)
{
	_world = world;
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact * aContact)
{
	b2Fixture* fixtureA = aContact->GetFixtureA();
	b2Fixture* fixtureB = aContact->GetFixtureB();

	char* userDataA = (char*)fixtureA->GetBody()->GetUserData();
	char* userDataB = (char*)fixtureB->GetBody()->GetUserData();

	cout << userDataA << endl;
	cout << userDataB << endl;
}

void ContactListener::EndContact(b2Contact * aContact)
{
}

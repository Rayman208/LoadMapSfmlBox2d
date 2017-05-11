#include "ContactListener.h"


void ContactListener::BeginContact(b2Contact * aContact)
{
	b2Fixture* fixtureA = aContact->GetFixtureA();
	b2Fixture* fixtureB = aContact->GetFixtureB();

	string userDataA ((char*)fixtureA->GetBody()->GetUserData());
	string userDataB ((char*)fixtureB->GetBody()->GetUserData());

	cout << userDataA.c_str() << endl;
	cout << userDataB.c_str() << endl;

	if (userDataA == "money")
	{
 		fixtureA->GetBody()->SetUserData("erase");
	}

	if (userDataB == "money")
	{
		fixtureB->GetBody()->SetUserData("erase");
	}
}


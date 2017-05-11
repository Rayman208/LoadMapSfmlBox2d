#include "Level.h"
#include <Box2D\Box2D.h>

#include "ContactListener.h"

const float PtM = 0.04f;
const float MtP = 25.0f;

b2Body* CreateSquareBody(b2World &world, float x, float y, float w, float h, string userData, b2BodyType type)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape polygonShape;

	float hw = (w / 2.0f), hh = (h / 2.0f);

	bodyDef.position = b2Vec2((x+hw)*PtM, (y+hh)*PtM);
	bodyDef.type = type;

	polygonShape.SetAsBox(hw*PtM, hh*PtM);
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.7f;

	b2Body *body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	
	char *_userData = new char[userData.size()+1];
	for (int i = 0; i < userData.size()+1; i++)
	{
		_userData[i] = userData[i];
	}
	body->SetUserData(_userData);

	return body;
}

void SetViewToPlayer(View &view, b2Vec2 position, Vector2i levelSize, Vector2i windowSize)
{
	double x = position.x*MtP;
	double y = position.y*MtP;
	if (x < windowSize.x/2) x = windowSize.x/2;
	if (x > levelSize.x - windowSize.x / 2) x = levelSize.x - windowSize.x / 2;

	if (y > levelSize.y - windowSize.y/2) y = levelSize.y - windowSize.y/2;
	if (y < windowSize.y / 2) y = windowSize.y/2;

	view.setCenter(x, y);
}

void main()
{
	int score = 0;

	Level lvl;
	lvl.LoadLevel("map.tmx");
	Vector2i windowSize(480, 480);
	
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "Sergey");
	window.setFramerateLimit(60);

	View view(FloatRect(0,lvl.GetLevelSize().y-windowSize.y, windowSize.x, windowSize.y));

	Texture playerTexture;
	playerTexture.loadFromFile("sonic.png");

	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);

	playerSprite.setOrigin
	(
		lvl.GetPlayer().width / 2,
		lvl.GetPlayer().height / 2
	);

	Texture moneyTexture;
	moneyTexture.loadFromFile("money.png");

	Sprite moneySprite;
	moneySprite.setTexture(moneyTexture);

	moneySprite.setOrigin
	(
		16,16
	);

	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);
	ContactListener ñontactListener;
	world.SetContactListener(&ñontactListener);

	for (int i = 0; i < lvl.GetObjectsCount(); i++)
	{
		Object temp = lvl.GetObjectByIndex(i);
		
		CreateSquareBody(world, 
			temp.x, temp.y, 
			temp.width, temp.height, 
			temp.name,
			b2BodyType::b2_staticBody);
	}

	b2Body *playerBody = CreateSquareBody(world,
		lvl.GetPlayer().x, lvl.GetPlayer().y,
		lvl.GetPlayer().width, lvl.GetPlayer().height,
		lvl.GetPlayer().name,
		b2BodyType::b2_dynamicBody);

	while (window.isOpen())
	{
		Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				window.close();
			}
			if (evt.type == Event::KeyPressed)
			{
				switch (evt.key.code)
				{
				case Keyboard::Key::Left:
					playerBody->ApplyForceToCenter(b2Vec2(-50.f, 0), true);
					break;

				case Keyboard::Key::Right:
					playerBody->ApplyForceToCenter(b2Vec2(50.f, 0), true);
					break;

				case Keyboard::Key::Space:
					playerBody->ApplyForceToCenter(b2Vec2(0.f, -150.f), true);
					break;
				}
			}
		}
		world.Step(1.0f / 60.0f, 8, 3);

		for (b2Body *cur = world.GetBodyList(); cur != NULL; cur = cur->GetNext())
		{
			string name((char*)cur->GetUserData());
			if (name == "erase")
			{
				score++;
				cout << "score = " << score << endl;
				world.DestroyBody(cur);
				break;
			}
		}

		SetViewToPlayer(view, playerBody->GetPosition(),lvl.GetLevelSize(),windowSize);

		window.setView(view);
		window.clear();
		for (int i = 0; i < lvl.GetTilesCount(); i++)
		{
			window.draw(lvl.GetTileByIndex(i));
		}

		for (b2Body *cur = world.GetBodyList(); cur != NULL; cur = cur->GetNext())
		{
			string name((char*)cur->GetUserData());
			if (name == "money")
			{
				moneySprite.setPosition(cur->GetPosition().x*MtP, cur->GetPosition().y*MtP);
				window.draw(moneySprite);
			}
		}

		playerSprite.setPosition
		(
			playerBody->GetPosition().x*MtP,
			playerBody->GetPosition().y*MtP
		);

		window.draw(playerSprite);

		window.display();
	}
}
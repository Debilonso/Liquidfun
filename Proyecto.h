#pragma once
#ifndef _PROYECTO_H
#define _PROYECTO_H

class ProyectoFluidos : public Test
{
public:
	void FistTest()
	{
		b2Vec2 gravity(0.0f, -9.81f);
		m_world->SetGravity(gravity);
		b2BodyDef groundBodyDef;
		b2BodyDef groundBodyDef2;
		groundBodyDef.type = b2_dynamicBody;
		groundBodyDef.position.Set(0.0f, 40.0f);
		groundBodyDef2.position.Set(0.0f, 0.0f);
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
		b2Body* groundBody2 = m_world->CreateBody(&groundBodyDef2);
		b2PolygonShape barra;
		b2CircleShape circle;
		barra.SetAsBox(10.0f, 1.0f);
		circle.m_radius = 2.5f;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.9f;
		groundBody->CreateFixture(&fixtureDef);
		groundBody2->CreateFixture(&barra, 1.0f);

	}

	ProyectoFluidos()
	{
		b2Vec2 gravity(0.0f, -9.81f);
		m_world->SetGravity(gravity);
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);
		//creando el suelo.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 4.0f);
		b2Body* body = m_world->CreateBody(&bodyDef);
		b2PolygonShape groundBox2;
		groundBox2.SetAsBox(5.0f, 5.0f);
		body->CreateFixture(&groundBox2, 0.0f);
		//se crea una caja encima del suelo.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		body->CreateFixture(&fixtureDef);
		//se crea una caja dentro de la otra caja.
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		//Es cuantas veces por unidad de tiempo analisa las velocidades para asegurarse de que se muevan los objetos correctamente.
		int32 positionIterations = 2;
		//Es cauntas veces por unidad de tiempo revisa las posiciones para asegurar que no haya sobreposision entre los objetos.
		for (int32 i = 0; i < 60; ++i)
		{
			m_world->Step(timeStep, velocityIterations, positionIterations);
			b2Vec2 position = body->GetPosition();
			float32 angle = body->GetAngle();
			printf("%4.2f %4.2f %4.2f\\n", position.x, position.y, angle);
		}


	}
	
	
	static Test* Create()
	{
		return new ProyectoFluidos;
	}
};
#endif
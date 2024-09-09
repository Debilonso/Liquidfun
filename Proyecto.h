#pragma once
#ifndef _PROYECTO_H
#define _PROYECTO_H

class ProyectoFluidos : public Test
{
public:
	ProyectoFluidos()
	{
		b2Vec2 gravity(0.0f, -9.81f);
		m_world->SetGravity(gravity);
		//se pone la gravedad.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(150.0f, 10.0f);
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
		//Es cuantas veces por unidad de tiempo revisa las posiciones para asegurar que no haya sobreposision entre los objetos.
		for (int32 i = 0; i < 60; ++i)
		{
			m_world->Step(timeStep, velocityIterations, positionIterations);
			//La linea de arriba ejecuta un paso en la simulación.
			b2Vec2 position = body->GetPosition();
			float32 angle = body->GetAngle();
			printf("%4.2f %4.2f %4.2f\\n", position.x, position.y, angle);
		}
		//el for calcula lo que hace en cada paso la simulación 
		b2ParticleSystem* m_particleSystem;
		const b2ParticleSystemDef particleSystemDef;
		m_particleSystem = m_world->CreateParticleSystem(&particleSystemDef); 
		//se crea un sistema de particulas, que es un conjunto de particulas.
		int k_maxParticleCount = 2000;
		m_particleSystem->SetMaxParticleCount(k_maxParticleCount);
		//la linea anterior pone el maximo de particulas que puede tener el sistema de particulas, eliminando las mas viejas cuando se supera.
		b2ParticleDef particle1;
		particle1.flags = b2_elasticParticle;
		particle1.color.Set(0, 0, 255, 255);
		//Importante la linea anterior le pone el color a la particula,acordarse de cambiarlo por algo que ponga el color segun la velocidad.
		particle1.position.Set(7, 5);
		int tempIndex = m_particleSystem->CreateParticle(particle1);
		//es agrega una particula al sistema de particula.
		b2ParticleSystem* m_particleSystems[10];
		int NUM_PARTICLE_SYSTEMS = 10;
		const b2ParticleSystemDef particleSystemDef2;
		for (int i = 0; i < NUM_PARTICLE_SYSTEMS; ++i) {
			m_particleSystems[i] = m_world->CreateParticleSystem(&particleSystemDef);
			m_particleSystems[i]->SetMaxParticleCount(k_maxParticleCount);
			b2ParticleDef particula_i;
			particula_i.flags = b2_elasticParticle;
			particula_i.color.Set(0, 0, 255, 255);
			particula_i.position.Set(i, 0);
			int tempIndex = m_particleSystem->CreateParticle(particula_i);
		}
		//se crean varios sistemas de particulas a la vez.

		b2ParticleGroupDef pd;
		b2PolygonShape shape;
		shape.SetAsBox(10, 5);
		pd.shape = &shape;
		pd.flags = b2_elasticParticle;
		pd.angle = -0.5f;
		pd.angularVelocity = 2.0f;
		for (int32 i = 0; i < 5; i++)
		{
			pd.position.Set(20 * i, 40);
			pd.color.Set(i * 255 / 5, 255 - i * 255 / 5, 128, 255);
			m_particleSystem->CreateParticleGroup(pd);
		}
		//se crear tres rectangulos de diferentes colores que son grupos de particulas.
	}
	//se debe crear una función propia para saber cuando una particula esta atascada y que hacer en ese caso.
	
	static Test* Create()
	{
		return new ProyectoFluidos;
	}
};
#endif

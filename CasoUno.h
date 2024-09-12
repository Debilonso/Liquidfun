#pragma once
#ifndef _CASO_UNO_H
#define _CASO_UNO_H

class ProyectoCasoUno : public Test
{
public:
	b2PolygonShape DestroyBox;
	b2Transform transformDestruction;
	b2ParticleSystem* m_particleSystems[100];
	int NUM_PARTICLES = 100;

	ProyectoCasoUno()
	{
		b2Vec2 gravity(0.0f, -9.81f);
		m_world->SetGravity(gravity);
		//se pone la gravedad.
		b2BodyDef floorBodyDef;
		floorBodyDef.position.Set(0.0f, -10.0f);
		b2Body* floorBody = m_world->CreateBody(&floorBodyDef);
		b2PolygonShape floorBox;
		floorBox.SetAsBox(150.0f, 10.0f);
		floorBody->CreateFixture(&floorBox, 0.0f);
		//creando el suelo.
		b2BodyDef rigthWallBodyDef;
		rigthWallBodyDef.position.Set(160.0f, 85.0f);
		b2Body* rigthWallBody = m_world->CreateBody(&rigthWallBodyDef);
		b2PolygonShape rigthWallBox;
		rigthWallBox.SetAsBox(10.0f, 105.0f);
		rigthWallBody->CreateFixture(&rigthWallBox, 0.0f);
		//se crea la pared de la derecha.
		b2BodyDef roofBodyDef;
		roofBodyDef.position.Set(10.0f, 200.0f);
		b2Body* roofBody = m_world->CreateBody(&roofBodyDef);
		b2PolygonShape roofBox;
		roofBox.SetAsBox(160.0f, 10.0f);
		roofBody->CreateFixture(&roofBox, 0.0f);
		//se crea el techo de la caja.
		//creando el suelo
		b2BodyDef leftBodyDef;
		leftBodyDef.position.Set(-160.0f, 90.0f);
		b2Body* leftBody = m_world->CreateBody(&leftBodyDef);
		b2PolygonShape leftBox;
		leftBox.SetAsBox(10.0f, 120.0f);
		leftBody->CreateFixture(&leftBox, 0.0f);
		//creando la pared de la izquierda de la caja.
		const b2ParticleSystemDef particleSystemDef2;
		for (int i = 0; i < NUM_PARTICLES; ++i) {
			m_particleSystems[i] = m_world->CreateParticleSystem(&particleSystemDef2);
			m_particleSystems[i]->SetMaxParticleCount(1000);
			b2ParticleDef particula_i;
			particula_i.flags = b2_elasticParticle;
			particula_i.color.Set(0, 0, 255, 255);
			particula_i.position.Set(i, 0);
			int tempIndex = m_particleSystems[i]->CreateParticle(particula_i);
			b2Vec2* velocidad =m_particleSystems[i]->GetVelocityBuffer();
			m_particleSystems[i]->SetRadius(0.25f);
			m_particleSystems[i]->SetMaxParticleCount(1000);
		}
	}

	virtual void Step(Settings* settings)
	{
		Test::Step(settings);
		/*
		for (int i = 0; i < NUM_PARTICLE_SYSTEMS; ++i) {
			m_particleSystems[i]->DestroyParticlesInShape(DestroyBox, transformDestruction);
		}
		*/
		DestroyBox = b2PolygonShape();
		DestroyBox.SetAsBox(30.0f, 30.0f);
		b2Transform transformDestruction;
		b2Vec2 posicionDestroy = b2Vec2(50.0f, -10.0f);
		transformDestruction.Set(posicionDestroy, 0);
		//printf("entro\n");
		b2Vec2 pos(20.0f, 150.0f);
		for (int i = 0; i < NUM_PARTICLES; ++i) {
			b2Vec2* posicionesParticulas = m_particleSystems[i]->GetPositionBuffer();
			for (int j = 0; j < 1; j++) {
				//printf("Posicion %f %f\n", posicionesParticulas[j].x, posicionesParticulas[j].y);
				if (DestroyBox.TestPoint(transformDestruction, posicionesParticulas[j]))
				{
					m_particleSystems[i]->DestroyParticle(j);
					//printf("destruyo\n");
				}
			}
		}
		//Toda esta parte es la función para destruir las particulas que toquen un box especifico.
		//por eso se debe hacer en el step que es la función que llama por cada paso.
		
	}

	void ColorVel(b2ParticleColor Colors,b2Vec2 velocidad) {
		//función para cambiar el color de las particulas segun la velovidad.
		double velx = velocidad.x;
		double vecy = velocidad.y;
		Colors.Set(velx, vecy, 2* vecy, 2/ velx);
	}
	static Test* Create()
	{
		return new ProyectoCasoUno;
	}
};
#endif

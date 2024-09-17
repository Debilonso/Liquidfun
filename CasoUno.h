#pragma once
#ifndef _CASO_UNO_H
#define _CASO_UNO_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <valarray>
#include <vector>

const int N = 100;
const int pasos = 100;

double radio = 0.25;
double pointsY = 0.0;
double pointsX = 0.0;

class ProyectoCasoUno : public Test
{
public:
	int Tiempo = 0;
	b2PolygonShape DestroyBox;
	b2Transform transformDestruction;
	const b2ParticleSystemDef particleSystemDef;
	b2ParticleSystem* particleSystem = m_world->CreateParticleSystem(&particleSystemDef);
	// construimos la rejilla,
	const double dx = 0.01;
	const double dy = 0.01;
	const double dt = 0.005;
	const double c = 1.0;   //velocidad de propagacion de la onda
	//construir la barrera, 
	const int barrera_x = 50;
	const int orificio_y1 = 45;
	const int orificio_y2 = 55;
	const double barrera_amplitud = 0.0;  //por las condiciones de la barrera queremos que al chocar el valor de la amplitud se haga cero
	//implementacion del metodo de diferncias finitas
	double u_present[N][N];
	double u_past[N][N];
	double u_future[N][N];

	double Resultados[N][N][pasos];

	ProyectoCasoUno()
	{
		b2Vec2 gravity(0.0f, 0.0f);
		m_world->SetGravity(gravity);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				b2ParticleDef particula_i;
				particula_i.flags = b2_elasticParticle;
				particula_i.color.Set(0, 0, 255, 255);
				particula_i.position.Set(i/2, j/2);
				int tempIndex = particleSystem->CreateParticle(particula_i);
				b2Vec2* velocidad = particleSystem->GetVelocityBuffer();
				particleSystem->SetRadius(radio*0.5);
				particleSystem->SetMaxParticleCount(1000000000);
			}
		}	
		amplitud();
	}

	virtual void Step(Settings* settings)
	{
		Test::Step(settings);

		if (Tiempo >= 0)
		{ 
			b2ParticleColor* ColoresArreglo = particleSystem->GetColorBuffer();
			for (int i = 1; i < N-1; i++) {
				for (int j = 1; j < N-1; j++) {
					//TODO revisar si tiene bien el id.
					int id = (i* N + j);
					ColoresArreglo[id] = ColorAmp(i, j, Tiempo);		
				}
			}

			//printf("tiempo %d \n", Tiempo);
			if (Tiempo == pasos-1) {
				Tiempo = 0;		
			}
			else {
				Tiempo = Tiempo + 1;
			}
			
		}
	}

	void amplitud() {
		// Onda inicial y condiciones de la barrera
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				u_present[i][j] = 0.0;
				u_past[i][j] = 0.0; //se requiere porque necesitamos el punto anterior para implementar el método
				// Fuente de onda inicial en el centro de la rejilla
				if (i == N / 2 && j == N / 2) {
					u_present[i][j] = 1.0;  // Amplitud inicial
				}
			}
		}

		// Propagación
		for (int t = 0; t < pasos; ++t) {  // pasos de tiempo a gusto
			for (int i = 1; i < N - 1; ++i) {
				for (int j = 1; j < N - 1; ++j) {
					
					// Condición para la barrera vertical con un orificio
					if (i == barrera_x) {
						if (j >= orificio_y1 && j <= orificio_y2) {  // Orificio en la barrera
							// La onda puede pasar por el orificio
							u_future[i][j] = 2 * u_present[i][j] - u_past[i][j] + c * c * dt * dt * ((u_present[i + 1][j] - 2 * u_present[i][j] + u_present[i - 1][j]) / (dx * dx) +
								(u_present[i][j + 1] - 2 * u_present[i][j] + u_present[i][j - 1]) / (dy * dy));
						}
						else {  // Resto de la barrera
							u_future[i][j] = barrera_amplitud;  // Onda detenida
						}
					}
					else {  // Puntos fuera de la barrera
						u_future[i][j] = 2 * u_present[i][j] - u_past[i][j] + c * c * dt * dt * ((u_present[i + 1][j] - 2 * u_present[i][j] + u_present[i - 1][j]) / (dx * dx) +
							(u_present[i][j + 1] - 2 * u_present[i][j] + u_present[i][j - 1]) / (dy * dy));
					}
					Resultados[i][j][t] = u_future[i][j];
				}
				printf("\n");
			}

			// Actualización para el siguiente paso de tiempo
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					u_past[i][j] = u_present[i][j];
					u_present[i][j] = u_future[i][j];
				}
			}
		}
	}

	b2ParticleColor ColorAmp(int i, int j,int pasos) {
		//función para cambiar el color de las particulas segun la amplitud del metodo de diferencias finitas.
		double amplitud = pow(Resultados[i][j][pasos],1.0/10.0)*255.0;
		b2ParticleColor ColorFinal(amplitud, amplitud, amplitud, 255);
		return ColorFinal;
	}

	static Test* Create()
	{
		return new ProyectoCasoUno;
	}
};
#endif

/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

#include "Thread.h"
#include "Parque.h"

class Carro: public Thread {
public:
	Carro(Parque &p);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	Parque &getParque();

	void run();
private:
	static int capacidade;
	int voltas;
	int nPassageiros;
	Parque &parque;
};

#endif /* CARRO_H_ */

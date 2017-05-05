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

/*
extern bool lock1;
extern bool lock2;
extern bool lock3;
*/

class Carro: public Thread {
public:
	Carro(Parque &p);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
    int getNPassageiros();
    void entraPassageiro();
    void saiPassageiro();
	Parque &getParque();
    void setLocks(bool *, bool *, bool *);
    void setSenha(int *);
	void run();
private:
	static int capacidade;
	int voltas;
	int nPassageiros;
    bool *lock1;
    bool *lock2;
    bool *lock3;
    int *senha;
	Parque &parque;
};

#endif /* CARRO_H_ */
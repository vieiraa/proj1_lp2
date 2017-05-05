/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "Thread.h"
#include "Carro.h"

class Passageiro: public Thread {
public:
	Passageiro(Carro &c, int);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
    void setValores(int *, int *);
    void setLocks(int *, int *, int *);
    int getMyId();
    
	void run();
private:
	Carro &carro;
    int *lock1;
    int *lock2;
    int *lock3;
    int *ticket;
    int *senha;
    int myTicket;
    int myId;
};

#endif /* PASSAGEIRO_H_ */

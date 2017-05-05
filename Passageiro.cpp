/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_NUM_VOLTAS 10

Passageiro::Passageiro(Carro &c, int myId) : carro(c) {
    this->myId = myId;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    fprintf(stderr, "Passageiro %d entrando no carro...\n", getMyId());
    
    if(carro.getNPassageiros() == 4) {
        carro.entraPassageiro();
        *lock1 = 0;
        return;
    }
    else {
        carro.entraPassageiro();
        __sync_fetch_and_add(senha, 1);
        while(*lock1)fprintf(stderr, "Passageiro %d...\n", getMyId());
    }
}

void Passageiro::esperaVoltaAcabar() {
    fprintf(stderr, "Passageiro %d esperando volta acabar...\n", getMyId());
    while(__sync_lock_test_and_set(lock2, 1));
}

void Passageiro::saiDoCarro() {
    fprintf(stderr, "Passageiro %d saindo do relampago marquinhos...", getMyId());
    if(carro.getNPassageiros() == 1) {
        fprintf(stderr, "why\n");
        carro.saiPassageiro();
        *lock3 = 0;
        __sync_fetch_and_add(senha, 1);
        return;
    }
    
    carro.saiPassageiro();
    fprintf(stderr, "total agora de passageiros %d\n\n\n\n...", carro.getNPassageiros());
    while(*lock3);
}

void Passageiro::passeiaPeloParque() {
    fprintf(stderr, "Passageiro %d vegetando...\n", getMyId());
    sleep(10);
}

bool Passageiro::parqueFechado() {
	if (carro.getNVoltas() <= MAX_NUM_VOLTAS)
		return false;

	return true;
}

void Passageiro::setValores(int *ticket, int *senha) {
    this->ticket = ticket;
    this->senha  = senha;
}

void Passageiro::setLocks(int *lock1, int *lock2, int *lock3) {
    this->lock1 = lock1;
    this->lock2 = lock2;
    this->lock3 = lock3;
}

int Passageiro::getMyId() {
    return myId;
}

void Passageiro::run() {
	while (!parqueFechado()) {
        myTicket = __sync_fetch_and_add(ticket, 1);

        while(myTicket != *senha);
            fprintf(stderr, "Passageiro %d tentando entrar com %d = %d...\n", getMyId(), myTicket, *senha);

		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de passageiros no parque
}
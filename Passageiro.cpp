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
    if(carro.getNPassageiros() == 0) {
        carro.entraPassageiro();
        __sync_lock_release(lock1);
        return;
    }

    carro.entraPassageiro();
}

void Passageiro::esperaVoltaAcabar() {
    fprintf(stderr, "Passageiro %d esperando volta acabar...\n", getMyId());
    while(__sync_lock_test_and_set(lock2, 1));
}

void Passageiro::saiDoCarro() {
    fprintf(stderr, "Passageiro %d saindo do relampago marquinhos...\n", getMyId());
    if(carro.getNPassageiros() == 1) {
        carro.saiPassageiro();
        __sync_lock_release(lock3);
    }

    carro.saiPassageiro();
}

void Passageiro::passeiaPeloParque() {
    __sync_fetch_and_add(ticket, 1);
    fprintf(stderr, "Passageiro %d vegetando...\n", getMyId());
    __sync_fetch_and_add(senha, 1);
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

void Passageiro::setLocks(bool *lock1, bool *lock2, bool *lock3) {
    this->lock1 = lock1;
    this->lock2 = lock2;
    this->lock3 = lock3;
}

int Passageiro::getMyId() {
    return myId;
}

void Passageiro::run() {
	while (!parqueFechado()) {

        while(*ticket != *senha)
            fprintf(stderr, "Passageiro %d tentando entrar com %d = %d...\n", getMyId(), *ticket, *senha);;

		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de passageiros no parque
}


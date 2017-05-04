/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int Carro::capacidade = 0;

Carro::Carro(Parque &p) : parque(p) {
	this->voltas = 0;
	Carro::capacidade = p.getNumPassageiros() / 2;
	this->nPassageiros = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
    while(__sync_lock_test_and_set(lock1, 1));
    fprintf(stderr, "Esperando encher...\n");
}

void Carro::daUmaVolta() {
    fprintf(stderr, "Dando uma volta...\n");
    sleep(5);
    __sync_lock_release(lock2);
}

void Carro::esperaEsvaziar() {
    fprintf(stderr, "Esperando esvaziar...\n");
    while(__sync_lock_test_and_set(lock3, 1));
}

int Carro::getNVoltas() {
	return voltas;
}

int Carro::getNPassageiros() {
    return nPassageiros;
}

void Carro::entraPassageiro() {
    __sync_fetch_and_add(&nPassageiros, 1);
}

void Carro::saiPassageiro() {
    __sync_fetch_and_add(&nPassageiros, -1);
}

Parque &Carro::getParque() {
	return parque;
}

void Carro::setLocks(bool *lock1, bool *lock2, bool *lock3) {
    this->lock1 = lock1;
    this->lock2 = lock2;
    this->lock3 = lock3;
}

void Carro::run() {
	while (parque.getNumPassageiros() > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;
	}
}

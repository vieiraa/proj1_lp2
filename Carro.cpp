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
    fprintf(stderr, "Esperando encher...\n");
    while(__sync_lock_test_and_set(lock1, 1)) fprintf(stderr, "enchendo...\n");
}

void Carro::daUmaVolta() {
    fprintf(stderr, "Dando uma volta...\n");
    sleep(5);
    *lock2 = 0;
}

void Carro::esperaEsvaziar() {
    fprintf(stderr, "Esperando esvaziar...\n");
    while(__sync_lock_test_and_set(lock3, 1)) ;//fprintf(stderr, "encerrando...\n");
;
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

void Carro::setLocks(int *lock1, int *lock2, int *lock3) {
    this->lock1 = lock1;
    this->lock2 = lock2;
    this->lock3 = lock3;
}

void Carro::setSenha(int *senha) {
    this->senha = senha;
}

void Carro::run() {
    __sync_fetch_and_add(senha, 1);
    
	while (1) {
        if(voltas >= 10)
            break;
        
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();
        
		voltas++;
        fprintf(stderr, "Volta de número %d...\n\n\n", voltas);
	}
	
	fprintf(stderr, "\n\nTODAS AS %d VOLTAS FORAM CONCLUIDAS\n\n", voltas);
}
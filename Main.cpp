#include <iostream>
#include "include/Carro.h"
#include "include/Passageiro.h"
#include "include/Parque.h"

#define NUM_THREADS 2

using namespace std;

bool lock1 = false;
bool lock2 = false;
bool lock3 = false;

int ticket = 1;
int  senha = 1;

int main() {
    Parque parque(NUM_THREADS);
    Carro carro(parque);
    Passageiro *passageiro[NUM_THREADS];
    
    carro.start();
    carro.setLocks(&lock1, &lock2, &lock3);
    
    for(int i = 0; i < NUM_THREADS; i++) {
        passageiro[i] = new Passageiro(carro, (i+1));
        passageiro[i]->start();
        passageiro[i]->setLocks(&lock1, &lock2, &lock3);
        passageiro[i]->setValores(&ticket, &senha);
        ticket++;
    }
    
    carro.run();
    
    for(int i = 0; i < NUM_THREADS; i++)
        passageiro[i]->run();
    
    carro.join();
    
	return 0;
}

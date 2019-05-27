#include <iostream>
#include "arvore.h"
#include "Pilha.cpp"

using namespace std;

noArv * criaVazia(){
    return NULL;
}

noArv* arv_Cria(int chave , noArv* esq2 , noArv* dir2){
    struct noArv * novo = new struct noArv;

    novo->dado = chave;
    novo->dir = dir2;
    novo->esq = esq2;

    return novo;
}

bool arv_vazia(struct noArv * no){
    return (no == NULL);
}

void arv_imprime(struct noArv * no){
    if(no == NULL){
        return;
    }else{
        cout << no->dado << endl;
        arv_imprime(no->esq);
        arv_imprime(no->dir);
    }
}

noArv * arv_libera(struct noArv * no){
    if(no != NULL){
        no->esq = arv_libera(no->esq);
        no->dir = arv_libera(no->dir);
        delete no;
    }
    return NULL;
}

int arv_altura(struct noArv * no){
    if(no == NULL){
        return 0;
    }else{
        int alt_esq = arv_altura(no->esq);
        int alt_dir = arv_altura(no->dir);

        if(alt_esq > alt_dir){
            return 1 + alt_esq;
        }else{
            return 1 + alt_dir;
        }
    }
}

noArv * espelho(struct noArv * no){
    if(no == NULL){
        return NULL;
    }else{
        struct noArv * novo = new struct noArv;
        novo->dado = no->dado;
        novo->dir = espelho(no->esq);
        novo->esq = espelho(no->dir);
        return novo;
    }
}

int arv_maior(struct noArv * no){
	if(no == NULL){
        return 0;
    }else if(no->dir == NULL && no->esq == NULL){
        return no->dado;
    }else{
        int esq = arv_maior(no->esq);
        int dir = arv_maior(no->dir);  
    
        if(esq >= dir){
            if(no->dado >= esq){
                return no->dado;
            }else{
                return esq;
            }
        }else{
            if(no->dado >= dir){
                return no->dado;
            }else{
                return dir;
            }
        }
    }
}

int eh_completa(struct noArv * no){
    if(no == NULL || (no->esq != NULL && no->dir == NULL)){
        return 1;
    }else if(no->esq == NULL && no->dir != NULL){
        return 0;
    }else{
        int esq = eh_completa(no->esq);
        int dir = eh_completa(no->dir);

        if(esq == 0 || dir == 0){
            return 0;
        }else{
            return 1;
        }
    }
}

bool eh_avl(struct noArv * no){
    if(no == NULL){
        return true;
    }else{
        int esq = arv_altura(no->esq);
        int dir = arv_altura(no->dir);

        if(esq - dir > 1 || esq - dir < -1){
            return false;
        }else{
            return true;
        }
    }
}

int num_nos_arv_it(struct noArv * no){
    if(no == NULL){
        return 0;
    }

    Pilha * p = new Pilha();
    p->push(no);
    int total = 0;

    while(!p->isEmpty()){
        no = (struct noArv *) p->pop();
        if(no != NULL){
            total++;
            p->push(no->dir);
            p->push(no->esq);
        }
    }

    delete p;
    return total;
}
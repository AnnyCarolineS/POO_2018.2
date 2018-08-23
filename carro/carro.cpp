#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/*
kilometragem=0
tanque=0(max. 10 litros)
passageiros=0 (max. 2 pessoas)
*/
struct Carro{
    float gasolina;
    float gasolinaMax;
    int passageiro;
    int passageiroMax;
    float kilometragem;

    bool in(){
        if(this->passageiroMax <= this->passageiro){
        cout<<"Operaçao nao permitida \n";
        return false;
        }else{
        this->passageiro+=1;
        return true;
        }
    }

    bool out(){
        if(this->passageiroMax < this->passageiro || this->passageiro == 0){
        cout<<"Operaçao nao permitida "<< endl;
        return false;
        }else{
            this->passageiro-=1;
            return true;
        }
    }

    void abastecer(float litros){
        this->gasolina+=litros;
        if(this->gasolina > this->gasolinaMax){
            this->gasolina=this->gasolinaMax;
        }
    }

    bool dirigir(float distancia){
        if(this->passageiro>=1){
            if(this->gasolina*10 >distancia){
                    this->kilometragem+=distancia;
                    this->gasolina=(gasolina*10-distancia)/10;
            }else{
                cout<<"gasolina insulficiente "<<endl;
            }
        }
        else{
            cout<<"Nao ha ninguem no carro "<<endl;
        }
    }
    void show(){
        cout<<endl<<"passageiro :"<<this->passageiro;
        cout<<endl<<"gasolina :"<<this->gasolina;
        cout<<endl<<"km : "<<this->kilometragem<<endl;
    }

};

int main(){
    Carro car1={0,10,0,2,0};
    string opcao;

        while(true){
        cout << "\n Opcoes:\n andar \n show \n abastacer \n desembarcar \n embarcar \n";
        cin >> opcao;

        if(opcao=="abastecer"){
            int litros;
            cin>>litros;
            car1.abastecer(litros);
        }
        if(opcao=="desembarcar"){
            car1.out();
        }
         if(opcao=="embarcar"){
            car1.in();
        }
        if(opcao=="show"){
            car1.show();
        }
        if (opcao == "andar"){
            int distancia;
            cin>>distancia;
            car1.dirigir(distancia);
        }
    }
}

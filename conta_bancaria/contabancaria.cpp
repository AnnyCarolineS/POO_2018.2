#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

template <class T>
T read(){
        T t;
        cin>>t;
        return t;
}

class Operacao{
public:
    string descricao;
    float valor;
    float saldo;

    Operacao(string descricao = "  ",float valor = 0, float saldo = 0){
        this->descricao = descricao;
        this->valor = valor;
        this->saldo = saldo;

    }
    string toString(){
        stringstream ss;
        ss<<setw(10)<<descricao<<setw(7)<<valor<<":"<<setw(5)<<saldo <<endl;
        return ss.str();
    }
};

class Conta{
public:   
    int nexId;
    float saldo =0;
    int numero;
    vector<Operacao> extrato;
   
    Conta(int newId = 0){
        this->nexId = newId;
    }
    string toString(){
        stringstream ss;
        for(int i=0; i<(int)extrato.size();i++){
            ss<<i<<":";
            ss<<extrato[i].toString();
        }  
        return ss.str();
    }

    float getSaldo(){
        return this->saldo;
    }
    int getnexId(){
        return this->nexId;
    }
    void setnexId(int nexId){
        this->nexId = nexId;
    }
    bool saque(float valor){
        if((this->saldo < valor) || (valor < 0)){ 
            cout<<"Saldo insuficiente " <<endl;
            return false;
        }   
        this->saldo -= valor;
        this->extrato.push_back(Operacao("saque", -valor,getSaldo()));
        return true;    
    }
    bool tarifa(float valor){
        this->saldo -= valor;
        this->extrato.push_back(Operacao("tarifa",-valor,getSaldo()));
        return true;
    }
    bool deposito(float valor){
        if(valor < 0){
            cout<<"Valor invalido" <<endl; 
            return false;
        }    
        this->saldo += valor;
        this->extrato.push_back(Operacao("deposito", valor,getSaldo()));
        return true;
    }
    vector<Operacao> getExtrato(){
        return this->extrato;
    }
    // bool extornar(){
    //     int vector[]={1, 3};
    //     //cin>>vector;

    //     for(int i=0;i<-2;i++){
    //         if(validateTarifa(i)){
    //             float aux;
    //             aux = extrato[i].valor;
    //             cout<<aux<<"sucess"<<endl;
    //             return true;
    //             aux=0;
    //         }else{
    //             cout<<"failure"<<endl;
    //             return false;
    //         }
    //     }
        
    // }
    // bool validateTarifa(int i){
    //     if(extrato[i].descricao == "tarifa") return true;
    //     else return false;
    //}
    void extratoN(int i){
        int j=0;
        if(i>(int)extrato.size()) cout<<"erro"<<endl;
        else{
            for(int j=(int)extrato.size()-i;j<(int)extrato.size();j++){
                cout<<j<<":"<<extrato[j].toString();
            }
            cout<<"sucess"<<endl;
            return;
        }
    }   
    void setExtrato(string operacao,float valor,float saldo){
        this->extrato.push_back(Operacao(operacao,valor,saldo));
        cout<<"sucess "<<endl;
    }

};

class Controller{
public:    
    Conta conta;
    void exec(){
        while(true){
            string op;
            cin>>op;

            if(op == "fim") break;
            else if(op == "help"){
                cout<< "init _id "<<endl
                    <<"saldo"<<endl
                    <<"show"<<endl
                    << "saque _valor "<<endl
                    <<" deposito _valor"<<endl
                    <<" tarifa _valor"<<endl
                    //<<" extornar _valores"<<endl
                    <<" extrato "<<endl
                    <<" extratoN _qtd"<<endl
                    <<"help" <<endl
                    <<"fim " <<endl;
            }
            else if(op == "init"){
                conta = Conta(read<int>());
                conta.setExtrato("Abertura ",0,0);
            }
            else if(op == "show"){
                cout<<"Conta : "<<conta.getnexId() << endl
                    <<"Saldo : "<<conta.getSaldo()<<endl;
            }
            else if(op == "saldo"){
                cout<<conta.getSaldo()<<endl;
            }
            else if(op == "deposito"){
                if(conta.deposito(read<float>())) cout<<"sucess"<<endl;
            }
            else if(op == "saque"){
                if(conta.saque(read<float>())) cout<<"sucess"<<endl;
            }
            // else if(op == "extornar"){
            //     string line;
            //     getline(cin,line);
            //     conta.extornar();
            // }
            else if(op == "extrato"){
                cout<<conta.toString()<<endl;
            }
            else if(op == "extratoN"){
                conta.extratoN(read<int>());
            }
            else if(op == "tarifa"){
                if(conta.tarifa(read<float>()))cout<<"sucess"<<endl;
            }
        }
    }    
};

int main(){
    Controller control;
    control.exec();
    return 0;
}
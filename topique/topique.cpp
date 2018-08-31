#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Passageiro{
    string nome;
    int idade;

    Passageiro(string nome = "fulano", int idade = 0){
        this->nome = nome;
        this->idade = idade;
    }
    string toString(){
        stringstream ss;
        ss << this->nome << ":" << this->idade;
        return ss.str();
    }
};

struct Topiq{

    vector<Passageiro*> cadeiras;
    int lot,pref;
    Topiq(int lot = 0, int pref=0):
        cadeiras(lot, nullptr)
    {
        this->pref=pref;
        this->lot=lot;
    }

   ~Topiq(){
        for(Passageiro* pass : cadeiras)
            delete(pass);
    }
    string toString(){
        stringstream ss;
        int i =0;
        ss << "[ ";
        for(Passageiro * passageiro : cadeiras){
            if(passageiro == nullptr){
                if(i < pref)
                    ss << "@ ";
                else 
                    ss<< "# ";
            }    
            else{
                if(i < pref)
                    ss<<"@"<< passageiro->toString() << " ";
                else
                    ss<<"#"<< passageiro->toString() << " ";
            }
                
            i+=1;
        }
        ss << "]";
        return ss.str();
    }
    bool in(Passageiro* passageiro){
        if((int)cadeiras.size() == 0){
            cout<<"fail: Topique não inicializada "<<endl;
            return false;
        }
        if(passageiro->idade > 60){
            for(int i=0;i<pref;i++){
                if(cadeiras[i]==nullptr){
                    cadeiras[i]=passageiro;
                    return true;
                }
            }
            for(int j=pref;j<lot;j++){
                if((cadeiras[j])==nullptr){
                    cadeiras[j]=passageiro;
                    return true;
                }
            }                
        }    
        else if(passageiro->idade < 60){
            for(int i=pref;i<lot;i++){
                if(cadeiras[i]==nullptr){
                    cadeiras[i]=passageiro;
                    return true;
                }                
            }
             for(int j=0;j<pref;j++){
                if((cadeiras[j])==nullptr){
                    cadeiras[j]=passageiro;
                    return true;
                }
            }
        }
        cout<<"Topique esta cheia" << endl;
        return false;
    }
    bool out(Passageiro* passageiro,string name){
        for(int i=0;i<lot;i++){
            if((cadeiras[i]!=nullptr)&&(passageiro->nome==cadeiras[i]->nome)){
                delete cadeiras[i];
                cadeiras[i]=nullptr;
                return true;
            }                
        } 
        cout<<"A pessoa nao esta na topique"<<endl;
        return false;
    }  
};

int main(){
    Topiq topiq;
    string op;
    int pref;
    int lot;

    cout<<"Digite a lotação e a qtd de cadeiras preferenciais : " <<endl;
    cin>>lot>>pref;

    while(true){

        cin>>op;

        if(op == "end")
            break;
        else if(op == "help"){
            cout << "show; init; in; out" << endl;
        }else if(op == "show"){
            cout << topiq.toString() << endl;
        }else if(op == "init"){
            topiq = Topiq(lot,pref);
            cout << "topiq criada com " << lot << " cadeiras" << endl;
        }else if(op == "in"){
            string nome;
            int idade;
            cout<<"Digite o nome e a idade : " <<endl;
            cin >> nome >> idade;
            if(topiq.in(new Passageiro(nome,idade)))
                cout << "done" << endl;    
        }else if(op == "out"){
            string nome;
            cout <<"Digite o nome da pessoa que deseja retirar: " <<endl;
            cin>>nome;
            if(topiq.out(new Passageiro(nome,0),nome))
                cout<<"done"<<endl;
                
        }

    }
   
} 

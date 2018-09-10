#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
struct Fone{
 
    string operadora;
    string telefone;

    Fone(string operadora="", string telefone= ""){
        this->operadora=operadora;
        this->telefone=telefone;
    }

    string toString(){
        stringstream ss;
        ss<< operadora << ":"<<telefone;
        return ss.str();
    }
};
struct Contato{
    
    string nome;
    vector<Fone*> fone;
    Contato(string nome= "Vazio"){
        this->nome=nome;
    }
    
    string toString(){
        stringstream ss; 
        ss<<nome<<" >";
        for(int i=0; i<(int)fone.size();i++){
            ss << "[";
            ss << i << ":";
            ss<<fone[i]->toString();
            ss << "]";
        }  
        return ss.str();
    }
    bool validate(string telefone){
        for(int i=0;i<(int)telefone.size();i++){
            if(telefone[i]=='0'||telefone[i]=='1' ||telefone[i]=='2'||telefone[i]=='3'||telefone[i]=='4'||telefone[i]=='5'||telefone[i]=='6'||telefone[i]=='7'||telefone[i]=='8'||telefone[i]=='9'||telefone[i]=='('||telefone[i]==')'||telefone[i]=='.'){
                continue;
            }
            return false;
        }
        return true;
        
    }
    bool add(string operadora, string telefone){
        if(validate(telefone)){
            fone.push_back(new Fone(operadora,telefone));
            return true;
        }
        return false;
    }
    bool rmv(int indice){
        if(indice>fone.size()){
            return false;
        }
        fone.erase(fone.begin()+indice);
        return true;
    }

};

int main(){
    Contato contato;
    string opcao;
    

    while(true){
        cin>>opcao;
        if(opcao=="init"){
            string nome;
            cin>>nome;
            contato=Contato(nome);
            cout<<"sucess" <<endl;
        }else if(opcao=="show"){
            cout<<contato.toString()<<endl;

        }else if(opcao=="add"){

            string operadora;
            string telefone;
            cin>>operadora>>telefone;
            if(contato.add(operadora,telefone)){
                cout<<"sucess"<<endl;
            }else{
                cout<<"failure: Fone invalido"<<endl;
            }
        }else if(opcao=="help"){
            cout<<"init - show - add - rm - help \n";
        }else if(opcao=="rmv"){
            int indice;
            cin>>indice;
            if(contato.rmv(indice)){
                cout<<"sucess"<<endl;
            }else{
                cout<<"failure : Indice invalido"<<endl;
            }

        }
    }


}
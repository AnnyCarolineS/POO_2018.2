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
    static bool validate(string telefone){
        for(int i=0;i<(int)telefone.size();i++){
            if(telefone[i]=='0'||telefone[i]=='1' ||telefone[i]=='2'||telefone[i]=='3'||telefone[i]=='4'||telefone[i]=='5'||telefone[i]=='6'||telefone[i]=='7'||telefone[i]=='8'||telefone[i]=='9'||telefone[i]=='('||telefone[i]==')'||telefone[i]=='.'){
                continue;
            }
            return false;
        }
        return true;
        
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
    bool add(string operadora, string telefone){
        if(Fone::validate(telefone)){
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
    bool update(string linha){
        stringstream ss(linha);
        fone.clear();
        string txt;
        Fone fone;
        while(ss>>txt){ 
            stringstream ss(txt);
            string operadora,telefone;
            getline(ss,operadora,':');
            getline(ss,telefone,' ');
            if(Fone::validate(telefone)){
                add(operadora,telefone);
            }
        }
        return true;
    } 

};

int main(){
    Contato contato;
    string opcao;
    string txt;
    

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
            cout<<"init - show - add - rmv - update - help \n";
        }else if(opcao=="rmv"){
            int indice;
            cin>>indice;
            if(contato.rmv(indice)){
                cout<<"sucess"<<endl;
            }else{
                cout<<"failure : Indice invalido"<<endl;
            }

        }else if(opcao=="update"){
            string line;
            getline(cin,line);
            stringstream ss(line);
            string palavra;
            ss >> palavra;
            contato=Contato(palavra);

            string up;
            getline(ss,up);
            cout<<up<<endl;
            if(contato.update(up))
            cout<<"success"<<endl;
        }
    }


}
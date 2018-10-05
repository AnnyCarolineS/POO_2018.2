#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
template <class T>
T read(){
        T t;
        cin>>t;
        return t;
}

class Devedor{
	string nome;
	int divida;

public:
	Devedor(string nome = "", int divida = 0){
		this->nome = nome;
		this->divida = divida;
	}
	int getDivida(){
		return this->divida;
	}
	void setDivida(int valor){
		this->divida += valor;
	}
	string getNome(){
		
		return this->nome;
	}
	void setNome(string nome){
		this->nome =nome;
	}

	string toString(){
		stringstream ss;
		ss<<" "<<this->nome<<":"<<-this->divida<<" ";
		return ss.str();
	}



};
class Agiota{
	int valor;
	map<string, Devedor> devedor;
	vector<Devedor> historico;

public:
	Agiota(int valor = 0 ){

		if(valor < 0) cout<<"valor invalido" <<endl;
		else this->valor = valor;
	}	

	bool addDevedor(string apelido="",string nome = ""){
		auto posicao = devedor.find(apelido);
		if(posicao == devedor.end()){
			devedor.insert(make_pair(apelido, Devedor(nome)));
			devedor.find(apelido)->second.setNome(nome);
			return true;
		}
		return false;
	}
	bool emprestar(string linha = ""){
		stringstream ss(linha);
		string apelido;
		ss>>apelido;
		int money;
		ss >> money;
				
		if(this->valor > money && devedor.find(apelido)!= devedor.end() && money > 0){
			devedor.find(apelido)->second.setDivida(money);
			this->valor -= money; 
			historico.push_back(Devedor(apelido));
			historico[((int) historico.size())-1].setDivida(money);
			return true;
		}
		return false;
	}
	string toString(){
        stringstream ss;
        for(pair<string, Devedor> par : devedor){
            ss <<par.first<<":"<<par.second.toString()<<endl;
		}   
            ss << "Agiota: "<<valor<<endl;
        return ss.str();
	}

	bool receber(string apelido = "" ,int money=0){
		if(devedor.find(apelido) != devedor.end() && devedor.find(apelido)->second.getDivida() + money >= 0 && money > 0 && devedor.find(apelido)->second.getDivida() >= money){
			devedor.find(apelido)->second.setDivida(-money);
			this->valor += money;
			historico.push_back(Devedor(apelido));
			historico[((int)historico.size())-1].setDivida(-money);
			return true;

		}
		return false;
	}
	bool remover(string apelido = ""){
		devedor.erase(apelido);
		for(int i=((int)historico.size())-1; i>=0 ; i--){

                if(historico[i].getNome()==apelido){
                    historico.erase(historico.begin()+i);
                	
                }
            }
    
		return true;	

	}
	bool filtrar(string apelido = " "){
		stringstream ss(apelido);
		int it = 0;

		for(auto auxiliar: historico){
			if(apelido == auxiliar.getNome()){
				ss<<"id:" << it<<" " ;
				ss<<"[" ;
				ss<< auxiliar.toString();
				ss<<"]"<<endl;
			}
			it++;
		}
		cout << ss.str() <<endl;
	}
	bool historico2(){
		stringstream ss;
		int i=0;
		for(auto it: historico){
			ss<<"id:"<<i<<" ";
			ss<<"[";
			ss<<it.toString();
			ss<<"]"<<endl;
			i++;
		}
		cout<<ss.str();
	}
};
struct Controller{
public:    
    Agiota agiota;
    void exec(){
        while(true){
            string op;
            cin>>op;

            if(op == "end") break;
            else if(op == "help"){
                cout<< "init _valor "<<endl
                    <<"filtrar"<<endl
                    << "add _apelido _nome"<<endl
                    <<"emprestar _apelido _valor"<<endl
                    <<"resumo"<<endl
                    <<" historico"<<endl
                    <<"receber" <<endl
					<<"matar _apelido"<<endl
                    <<"fim " <<endl;
            }
            else if(op == "init"){
				int valor =0;
				cin>>valor;
                agiota = Agiota(valor);
				cout<<"Sucess"<<endl;
            }
            else if(op == "add"){
				string linha;
				getline(cin,linha);
				stringstream ss(linha);
				string apelido;
				ss>>apelido;
				string nome;
				getline(ss,nome);
				
                if(agiota.addDevedor(apelido,nome)) cout <<" Sucess " <<endl;
				else cout<<"Devedor ja existe "<<endl;
            }
			else if(op == "emprestar"){
				string linha;
				getline(cin,linha);

                if(agiota.emprestar(linha)) cout <<" Sucess " <<endl;
				else cout<<"inválido "<<endl;
			}
			else if(op == "resumo"){
				cout<<agiota.toString();
			}
			else if(op == "receber"){
				string linha;
				getline(cin,linha);
				stringstream ss(linha);
				string apelido;
				ss>>apelido;
				int money;
				ss >> money;
				if(agiota.receber(apelido,money)) cout<<"Sucess"<<endl;
				else cout<<"Valor inválido"<<endl;
			}
			else if(op == "matar"){
				string apelido;
				cin>>apelido;
				if(agiota.remover(apelido)) cout<<"Sucess"<<endl;
				else cout<<"Devedor invalido"<<endl;
			}
			else if(op == "filtrar"){
				string apelido;
				cin>>apelido;
				if(agiota.filtrar(apelido)) cout<<"Sucess" <<endl;
				else cout<<"Devedor inválido"<<endl;
			}
			else if(op == "historico"){
				agiota.historico2();
			}
		}		
    }    
};
int main(){
	Controller controller;
	controller.exec();

	return 0;
}
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class Tamagotchi{
    int energyM,hungryM,cleanM;
    int energy,hungry,clean;
    int diamond,age;
    bool Pet_vivo;

public:

    Tamagotchi(int E=0, int H=0, int C=0){
        this->energy=E;
        this->energyM=E;
        this->hungry=H;
        this->hungryM=H;
        this->clean=C;
        this->cleanM=C;
        diamond=0;
        age=0;
        Pet_vivo=true;
    }

    void setEnergy(int E){
        if(E<=0){
            energy=0;
            cout<<"Sem energia : o pet morreu" <<endl;
        }
        else if(E>energyM)
            energy=energyM;
        else energy = E;
    }
    int getEnergy(){
        return energy;
    }
    // int getEnergyM(){
    //     return energyM;
    // }
    void setHungry(int H){
        if(H<=0){
        hungry=0;
        cout<<"Passou fome: o pet morreu" <<endl;
        }
        else if(H>hungryM)
            hungry=hungryM;
        else hungry = H;
    }
    int getHungry(){
        return hungry;
    }
    // int getHungryM(){
    //     return hungryM;
    // }
    void setClean(int C){
        if(C<=0){
            clean=0;
            cout<<"Sujo: pet morreu"<<endl;
        }else if (C>cleanM)
            clean=cleanM;
        else clean = C;    
    }
    int getClean(){
        return clean;
    }
    // int getCleanM(){
    //     return cleanM;
    // }
    string toString(){
        stringstream ss;
        ss << "Energy :" <<energy <<" - " << energyM <<endl
           << "Hungry :"<<hungry<<" - " <<hungryM<<endl
           << "Clean :"<<clean<<" - " <<cleanM<<endl
           <<"Diamond :"<<diamond <<endl
           <<"Age :" <<age<<endl;
        return ss.str();   
    }
    bool vidaPet(){
        if(Pet_vivo)
            return true;
        cout<<"Seu pet esta morto " <<endl;
        return false;   
    }

    void jogar(){
        if(vidaPet()){
            setEnergy(getEnergy()-2);
            setHungry(getHungry() -1);
            setClean(getClean() -3);
            diamond +=1;
            age +=1;
        }
        else return;    
    }
    void limpar(){
        if(vidaPet()){
            setEnergy(getEnergy()-3);
            setHungry(getHungry() -1);
            setClean(cleanM);
            age +=2;
        }
        else return;  
    }
    void comer(){
        if(vidaPet()){
            setEnergy(getEnergy()-1);
            setHungry(getHungry() +4);
            setClean(getClean() -2);
            age +=1;
        }
        else return;  
    }
    void domir(){
        if(!vidaPet()) return;
        else if(energyM - getEnergy() < 5 ){
            cout<<"Pet sem sono"<<endl;
            return;
        }
        setEnergy(energyM);
        setHungry(getHungry() -1);
        age += energyM - getEnergy();
    }

};

struct Controller{
    Tamagotchi tamagotchi;

    
    void shell(string line){
        stringstream ss(line);
        string opcao;
        ss>>opcao;

        if(opcao == "show"){
            cout << tamagotchi.toString() << endl;
        }else if(opcao == "init"){
            int energy, hungry, clean;
            ss >> energy >> hungry >> clean;
            tamagotchi = Tamagotchi(energy, hungry, clean);
        }else if(opcao == "play"){
            tamagotchi.jogar();
        }else if(opcao == "eat"){
            tamagotchi.comer();
        }else if(opcao == "clean"){
            tamagotchi.limpar();
        }else if(opcao == "sleep"){
            tamagotchi.domir();
        }else if(opcao == "help"){
            cout<<"init \n play \n eat \n clean \n sleep \n help \n end \n"<<endl;      
        }else{
        cout << "fail: operacao invalida" << endl;
        }
    }
    void exec(){
        string line;
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                break;
            shell(line);
        }
    }

};

int main(){
    Controller controller;
    controller.exec();
    return 0;
}
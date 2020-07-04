#include <iostream> 
#include <fstream> 
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;
#define INDICETABELA 3
#define DESLOCAMENTO 5
#define NUMERODEPAGINAS 2
#define ENDERECAMENTO (INDICETABELA+DESLOCAMENTO)
#define TAMANHODAPAGINA pow(2,DESLOCAMENTO)
#define TAMANHOPRINCIPAL TAMANHODAPAGINA*NUMERODEPAGINAS
#define TAMANHOSECUNDARIA TAMANHODAPAGINA*20
//**********************************************CLASSES************************************************************************
class Page{
    private:
        bool P;//Bit presente ou ausente
        bool R;//Bit de pagina referenciada
        bool M;//Bit de página Modificada
        string quadro;//bits do quadro de página
    public:
    bool getP(){
        return P;
    }
    void setP(bool p){
        P = p;
    }
    bool getR(){
        return R;
    }
    bool setR(bool r){
        R = r;
    }
    bool getM(){
        return M;
    }
    void setM(bool m){
        M = m;
    }
    string getQuadro(){
        return quadro;
    }
    void setQuadro(string q){
        quadro = q;
    }
};

class No{
public:
    Page *pagina;
    No *prox;
    No *ant;
    No *getProx(){
        return prox;
    }
    void setProx(No *p){
        prox = p;
    }
    No *getAnt(){
        return ant;
    }
    void setAnt(No *a){
        ant = a;
    }
    void setPagina(Page *p){
        pagina = p;
    }
    Page *getPagina(){
        return pagina;
    }
};

class Process
{
public:
    vector<Page*> table;
    string id;
};
//***********************************VARIAVEIS GLOBAIS***********************************
int usedMemory = 0;
No *mainMemory = NULL;
int bitMap[NUMERODEPAGINAS];
//*****************************FIM DAS VARIAVEIS GLOBAIS*********************************












//*****************************************METODOS AUXILIARES***************************************************//
int charToInt(char a){//converte um char to int
    return (a - '0');
}
string intToChar(int i){
    string aux = "";
    string r = "";
    while(i > 1){
        aux += to_string(i%2);
        i = i/2;
    }
    if(i == 1){
        aux += to_string(1);
    }else{
        aux += to_string(0);
    }
    for(int j = 0;j < INDICETABELA-aux.size();j++){
        r += "0";
    }
    for(int j = aux.size()-1;j >= 0;j--){
        r += aux[j];
    }
    return r;
}
int getIndex(string bits){///Converte string binaria para int EX: 111 = 7
    int r = 0;
    int j = 0;
    bits.erase(INDICETABELA,DESLOCAMENTO);
    for (int i = bits.size()-1; i >= 0; i--){
        r += charToInt(bits[i])*pow(2,j);
        j++;
    }
    return r;
}
//**********************************METODO QUE SIMULA A MMU**************************************************************************
string logicToFisic(string logic,vector<Page*> pages){//Converte um endereço lógico em um endereço físico, papel semelhante a da MMU
    string aux = logic;
    int index = getIndex(aux);
    string fisic;
    if(index >= pages.size()){
        return "FORA DO PROCESSO";
    }
    if(pages[index]->getP()){
        fisic = pages[index]->getQuadro();
        fisic += logic.erase(0,INDICETABELA);
        return fisic;
    }else{
        return "PAGE NOT FOUND ERRO";
    }
}
//******************************FIM DA MMU********************************************************************************************

vector<Page*> createPageTable(int s){//Cria a tabela de página de um processo recem criado ou seja nenhuma página está na memoria ainda
    vector<Page*> r;
    for(int i = 0;i < s;i++){//O new Page() precisa estar detro do for para nao copiar o endereço e a madança em uma pagina nao impactar em todas
        Page *aux = new Page();
        aux->setM(false);
        aux->setP(false);
        aux->setR(false);
        string a = "";
        for(int i = 0;i < INDICETABELA;i++){
            a += "0";
        }
        aux->setQuadro(a);
        r.push_back(aux);
    }
    return r;
}

void insertNode(No *n){//Insere um no nosso relogio, quando ainda há espaço disponivel

    usedMemory += TAMANHODAPAGINA;
    cout <<"PAGINA INSERIDA NA MEMORIA \n";
    int i = 0;    
    while(bitMap[i] != 0){
        i++;
    }
    bitMap[i] = 1;
    if(mainMemory == NULL){
        n->getPagina()->setQuadro(intToChar(i));
        n->setProx(n);
        n->setAnt(n);
        mainMemory = n;
    }else{
        n->getPagina()->setQuadro(intToChar(i));
        n->setProx(mainMemory->getProx());
        mainMemory->getProx()->setAnt(n);
        mainMemory->setProx(n);
        n->setAnt(mainMemory);
    }
}
void swapNode(No *n){//Substitui um no por outro
    n->setProx(mainMemory->getProx());
    n->setAnt(mainMemory->getAnt());
    n->getPagina()->setQuadro(mainMemory->getPagina()->getQuadro());
    mainMemory = n;

}
void clockChange(No *enter){//Basicamente realiza a operação do relógio
    cout << "\nEXECUTANDO ALGORITMO DO RELOGIO \n";
    while(true){
        if(mainMemory->getPagina()->getP() == true){//pagina que estava no ponteiro do relogia havia sido referenciada, relogio anda
            cout << "Ponteiro estava referenciado \n";
            mainMemory->getPagina()->setP(false);
            mainMemory = mainMemory->getProx();
        }else{//pagina pode ser removida
            cout << "Ponteiro nao estava referenciado, a pagina sera retirada da memoria para que a nova entre \n";
            mainMemory->getPagina()->setP(false);
            mainMemory->getPagina()->setR(false);
            if(mainMemory->getPagina()->getM()){
                cout << "A pagina estava modificada, as mudancas foram salvas e ela foi removida da memoria primaria \n";
            }
            mainMemory->getPagina()->setM(false);
            swapNode(enter);
            break;
        }
    }
}

int read(vector<Process> *pro,char a,string pid,string op){//interpreta os dados lidos e realiza as ações necessárias
    Process processAux;
    vector<Process> processes = *pro;
    int pageNumber;
    if(a == 'C'){
        stringstream g(op);
        g >> pageNumber;
        if(pageNumber*TAMANHODAPAGINA > TAMANHOSECUNDARIA){
            //ERRO
            cout << "ERRO: O processo e muito grande e portanto nao pode ser enderecado";
            return -1;
        }    
        processAux.table = createPageTable(pageNumber);
        processAux.id = pid;
        processes.push_back(processAux);
        *pro = processes;
        cout << "O processo " << pid << " foi criado, e tem " << op << " paginas\n";
        //Basicamente a criação do processo está feita
    }else{
        cout << "LEITURA OU ESCRITA \n";
        int flag = 1;
        for(int i =0; i < processes.size();i++){
            if(pid == processes[i].id){
                flag = 0;
                processAux = processes[i];
                break;
            }
            if(i == processes.size()-1){
                flag = 1;
            }
        }
        if(flag == 1){
            cout << "ERRO: Processo nao encontrado";
            return -1;
        }
        cout << "PROCESSO: "<< pid << "\n";
        if(logicToFisic(op,processAux.table) == "PAGE NOT FOUND ERRO"){
            //Caso em que a página referenciada ainda não esta na RAM
            cout <<logicToFisic(op,processAux.table) << "\n";
            int index = getIndex(op);
            No *novo = new No();
            novo->pagina = (processAux.table[getIndex(op)]);
            novo->getPagina()->setR(true);
            novo->getPagina()->setP(true);
            //Aqui inseriremos o processo na memoria fisica, por meio de substituição ou inserindo diretamente
            if(usedMemory < TAMANHOPRINCIPAL){
                //Neste bloco estamos no caso em que podemos inserir diretamente na memoria fisica
                insertNode(novo);
            }else{
                clockChange(novo);
                //algoritmo de substituição de paginas
            }
            
        }else{//Caso em que a página já esta na ram
            if(logicToFisic(op,processAux.table) == "FORA DO PROCESSO"){
                cout << "TENTATIVA DE ACESSO A AREA EXTERNA AO PROCESSO NEGADA";
                return -1;
            }
            cout << "Memoria FISICA ACESSADA NA POSICAO:" << logicToFisic(op,processAux.table) << "\n";
            cout << "PAGINA FOI MARCADA COMO REFERENCIADA \n";
            processAux.table[getIndex(op)]->setR(true);//marca a página como referenciada
            if(a == 'W'){
                processAux.table[getIndex(op)]->setM(true);//marca a página como modificada
                cout << "PAGINA FOI MARCADA COMO MODIFICADA\n";
            }
            
        }
        
    }
}

int main(void){

    for (int i = 0; i < NUMERODEPAGINAS; i++){
        bitMap[i] = 0;//inicializa o bitMap com zeros
    }
    ifstream infile;
    infile.open("in8.txt");

    vector<Process> processes;//Vetor que representa os processos ativos
    char a;//Char que armazena a operação q será escolhida
    string pid;//
    string op;
    while(1){
        infile >> pid >> a >> op;
        if(pid == "exit"){
            cout << "\n FIM DA EXECUCAO \n";
            break;
        }
        read(&processes,a,pid,op);
        cout << "\n\n";
    }
    //cout << mainMemory->getPagina()->getQuadro();
        //Processo encontrado, realizar a devida operação
        //Procedimento de entrada e saida,
}
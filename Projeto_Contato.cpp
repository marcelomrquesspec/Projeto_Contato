//Marcelo Marques Araujo CB3005631

#include <iostream>
#include <ctime>
#include <string>


using namespace std;

#define QUANT_CONTATOS 5

class Data
{
    private:
        int dia;
        int mes;
        int ano;

    public:
        Data(int dia, int mes, int ano)
        {
            this->dia = dia;
            this->mes = mes;
            this->ano = ano;
        }

        Data()
        {
            this->dia = 10;
            this->mes = 6;
            this->ano = 2000;
        }
        void setDia(int dia)
        {
            this->dia = dia;
        }

        void setMes(int mes)
        {
            this->mes = mes;
        }

        void setAno(int ano)
        {
            this->ano = ano;
        }
        int getDia()
        {
            return this->dia;
        }

        int getMes()
        {
            return this->mes;
        }

        int getAno()
        {
            return this->ano;
        }
        string getData()
        {
            string diaFormat = to_string(this->dia);
            diaFormat.insert(0, 2 - diaFormat.size(), '0');

            string mesFormat = to_string(this->mes);
            mesFormat.insert(0, 2 - mesFormat.size(), '0');

            string anoFormat = to_string(this->ano);
            anoFormat.insert(0, 4 - anoFormat.size(), '0');

            return diaFormat + "/" + 
                mesFormat + "/" +
                anoFormat;
        }

        Data* dia_seguinte()
        {
            Data *ds;
            int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            ds = new Data(this->dia, this->mes, this->ano);

            if (ds->ano % 4 == 0)
            {
                diasNoMes[1]++;
            }

            ds->dia++;
            if (ds->dia > diasNoMes[ds->mes - 1])
            {
                ds->dia = 1;
                ds->mes++;
                if(ds->mes > 12)
                {
                    ds->mes = 1;
                    ds->ano++;
                }
            }

            return ds;
        }
};

class Contato{
    private:
        string email;
        string nome;
        string telefone;
        Data* dtnasc;
    public:
        Contato(string nome, string email, string telefone, Data* dataNascimento){
            this->email = email;
            this->nome = nome;
            this->telefone = telefone;
            this->dtnasc = dataNascimento; 
        }
        Contato(){
            this->email = "";
            this->nome = "";
            this->telefone = "";
            this->dtnasc = new Data(); 
        }
        string getEmail()
        {
            return this->email;
        }
        string getNome()
        {
            return this->nome;
        }
        string getTelefone()
        {
            return this->telefone;
        }
        Data* getDataNascimento()
        {
            return this->dtnasc;
        }
        void setEmail(string email)
        {
            this->email = email;
        }
        void setNome(string nome)
        {
            this->nome = nome;
        }
        void setTelefone(string telefone)
        {
            this->telefone = telefone;
        }
        void setDataNascimento(Data* data)
        {
            this->dtnasc = data;
        }
        int idade(){

            time_t t = time(NULL);
	        tm* timePtr = localtime(&t);

            int anoAtual = timePtr->tm_year + 1900;
            int mesAtual = timePtr->tm_mon + 1;
            int diaAtual = timePtr->tm_mday;

            if(mesAtual > this->dtnasc-> getMes()){
                return anoAtual - this->dtnasc-> getAno();
            } else if(mesAtual < this->dtnasc-> getMes()){
                return anoAtual - this->dtnasc-> getAno() - 1;
            }else {
                if(diaAtual >= this->dtnasc-> getDia()){
                    return anoAtual - this->dtnasc-> getAno();
                }else {
                    return anoAtual - this->dtnasc-> getAno() - 1;
                }
            }
        }
        string formatar(){
			string contatoFormat = "Nome: " + this->getNome() + "\n" +
  	  	  	  	   "Email: " + this->getEmail() + "\n" +
  	  	  	  	   "Telefone: " + this->getTelefone() + "\n" +
				   "Idade: " + to_string(this->idade());
			return contatoFormat;
		}
};

#pragma region Fun��es
void separador(){
    cout << endl << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << "=";
    }
    cout << endl << endl;
    
}


string inputNome(int numeroContato){
    string nome;

    cout << "Nome do " + to_string(numeroContato) + "� contato: ";
    cin >> nome;

    return nome;
}

string inputEmail(int numeroContato){
    string email;

    cout << "Email do " + to_string(numeroContato) + "� contato: ";
    cin >> email;

    return email;
}

string inputTelefone(int numeroContato){
    string telefone;

    cout << "Telefone do " + to_string(numeroContato) + "� contato: ";
    cin >> telefone;

    return telefone;
}

Data* inputDataNascimento(int numeroContato){
    int dia, mes, ano;

    do
    {
        cout << "Dia nascimento do " + to_string(numeroContato) + "� contato: ";
        cin >> dia;

        if(dia < 0 || dia > 31){
            cout << endl << "Dia do nascimento  invalida, por favor digite um valor entre 1 e 31!"  << endl << endl;
        }

    } while (dia < 0 || dia > 31);

    do
    {
        cout << "Mes de nascimento do" + to_string(numeroContato) + "� contato: ";
        cin >> mes;

        if(mes < 0 || mes > 12){
            cout << "M�s do nascimento  invalida, por favor digite um valor entre 1 e 12!"  << endl << endl;
        }

    } while (mes < 0 || mes > 12);

    do
    {
        cout << "Ano nascimento do " + to_string(numeroContato) + "� contato: ";
        cin >> ano;

        if(ano < 0){
            cout << "Ano do nascimento  invalida, por favor digite um valor maior que zero !"  << endl << endl;
        }

    } while (ano < 0);

    return new Data(dia, mes, ano);
}

void preencherContato(Contato* contato, int numeroContato){
    contato->setNome(inputNome(numeroContato));
    contato->setEmail(inputEmail(numeroContato));
    contato->setTelefone(inputTelefone(numeroContato));
    contato->setDataNascimento(inputDataNascimento(numeroContato));
}
#pragma endregion

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");

    Contato* contatos[QUANT_CONTATOS];

    for(int i = 0; i < QUANT_CONTATOS; ++i){
    	contatos[i] = new Contato();
        preencherContato(contatos[i], i + 1);
        separador();
    }

     for (int i = 0; i < QUANT_CONTATOS; i++)
     {
     	cout << contatos[i]->formatar() << endl;
        separador();
     }
     

    return 0;
}

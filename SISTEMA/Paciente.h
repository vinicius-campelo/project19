//#-------------------------------------------#
//# Criação: Vinicius Campelo, Valeria Cunha; #
//# Data: 11/2020 / UNIP: PIM-IV;             #
//# Classe: Paciente.h;                       #
//#-------------------------------------------#

#include "Dados.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define ANO_ATUAL 2020 //modifica essa linha ano atual
#define MES_ATUAL 11   //modificar essa linha mes atual
/*
  Calcula a idade atual.
*/
int CalculaIdade(DadosPaciente usuario)
{
    int _idade_aniversariante=0, _mes_aniversariante=0;

    _mes_aniversariante = MES_ATUAL + 1;
	_idade_aniversariante = ANO_ATUAL - usuario.ano;

    //verifica se o mes e maior ao mes atual;
	if(_mes_aniversariante > usuario.mes){
        usuario.idade = _idade_aniversariante;
      }else{
        usuario.idade = (_idade_aniversariante - 1);
	}
    return usuario.idade;
}

/*
  Verifica se usuario fez login
  com as credeciais ja cadastradas
  Usuario:"UNIP", Senha:"1234";
*/
bool FazerLogin(DadosPaciente verifica)
{
    if (strcmp(verifica.usuario, "UNIP") == 0 && strcmp(verifica.senha, "1234") == 0)
    {
        return true;
      }else{
        return false;
    }
}


/*
   Gravar CEP/IDADE em um arquivo separado.
*/
bool GravaCepIdade(DadosPaciente cadastrar){

    FILE *arquivo;
    arquivo = fopen("CADASTRO_ESPECIFICO.txt", "ab");

    if (arquivo == NULL) {
        return false;
    }

    fprintf(arquivo, "CEP: %s  - IDADE: %d\n", cadastrar.cep, CalculaIdade(cadastrar));
      if(arquivo != NULL){
        fclose(arquivo);
        return true;
      }else{
        fclose(arquivo);
        return false;
     }
}

/*  CADASTRAR PACIENTE
	Cadastrar todos os dados de paciente
	indiferente de ter comorbidade ou está
	no grupo de risco em arquivo.txt.
*/
bool CadastraPaciente(DadosPaciente cadastrar){

      FILE *arquivo;
	  //ABRE O ARQUIVO CADASTRO_TOTAL PARA GRAVAÇÃO NO FINAL DO ARQUIVO
	  //CASO TENHA ALGUMA INFORMAÇÃO
      arquivo = fopen("CADASTRO_TOTAL.txt", "ab");
        if (arquivo == NULL) {
            return false;
        }
		//CALCULA IDADE
        int idade = CalculaIdade(cadastrar);

            fprintf(arquivo, "%s,", cadastrar.nome);
            fprintf(arquivo, "%s,", cadastrar.cpf);
            fprintf(arquivo, "%s,", cadastrar.telefone);
            fprintf(arquivo, "%s NUMERO:%d. %s %s-%s,", cadastrar.endereco, cadastrar.numero, cadastrar.bairro, cadastrar.cidade, cadastrar.estado);
            fprintf(arquivo, "%s,", cadastrar.cep);
            fprintf(arquivo, "%d/%d/%d,", cadastrar.dia, cadastrar.mes, cadastrar.ano);
            fprintf(arquivo, "%s,", cadastrar.email);
            fprintf(arquivo, "%d/%d/%d,", cadastrar.dia_c, cadastrar.mes_c, cadastrar.ano_c);
            fprintf(arquivo, "%s,", cadastrar.comorbidade);
            fprintf(arquivo, "%d", idade);

          if(arquivo != NULL){
            fclose(arquivo);
            return true;
          }else{
            fclose(arquivo);
            return false;
    }

}
//FUNCAO CONSULTAR PACIENTE
bool ConsultaPaciente(char consultaNome[30]){

  int i=0;
  FILE *arquivo;
  char string[2000]={0};
  //VETOR DE CARACTERES
  char texto[10][30] = {"NOME","CPF","TELEFONE","ENDERECO","CEP","DATA_NASCIMENTO",
						"EMAIL","DATA_CADASTRO_COMORBIDADE","COMORBIDADE","IDADE"};

    if(consultaNome[0] != '0')
    {		//ABRE O ARQUIVO CADASTRO_TOTAL.TXT PARA LEITURA E RETORNO
        if ((arquivo=fopen ("CADASTRO_TOTAL.txt", "rb")) != NULL)
        {
            //LER UMA STRING COM ESPACO %[^\n] DE UM ARQUIVO E A PROXIMA STRING \n^\n]\n
            while( (fscanf(arquivo, "%[^\n]\n", &string))!=EOF) // VERIFICA SE O FIM DO ARQUIVO
            {
            	//strtok DEVOLVE UM PONTEIRO PARA A PROXIMA PALAVRA (DELIMITADOR)
                char *dados_paciente = strtok(string, ",");
				//RETORNA A POSIÇÃO DA PRIMEIRA OCORRENCIA VINDA DA PRIMEIRA CADEIA
				//DE TEXTO DO ARQUIVO LIDO E COMPARA COM DIGITADO
                if(strstr(string, consultaNome)!=0)
                {
                    while(dados_paciente != NULL)
                    {		//IMPRIME CONFORME O DELIMITADOR E RETORNA PARA PROXIMA POSIÇÃO
							printf("%s: %s\n",texto[i], dados_paciente);
                        	dados_paciente = strtok(NULL, ",");
                        	i++;
				    }
                }
            }
               fclose(arquivo); //FECHA ARQUIVO
            return true;
        }
         return true;
    }
}


//FUNCAO CONSULTA CEP E IDADE
bool ConsultaCEPIdade(){

   FILE *arquivo;
   char string[150];

   	//ABRE O ARQUIVO CADASTRO_TOTAL.TXT PARA LEITURA E RETORNO
    if ((arquivo=fopen ("CADASTRO_ESPECIFICO.txt", "r")) != NULL)
    {
            //LER UMA STRING COM ESPACO %[^\n] DE UM ARQUIVO E A PROXIMA STRING \n
            while( (fscanf(arquivo, "%[^\n]\n", &string))!=EOF) // VERIFICA SE O FIM DO ARQUIVO
            {
            	printf("%s\n", string);
            }
            return true;
    }else{

    	printf("Arquivo nao encontrado!\n");
    	fclose(arquivo);
        return false;
	}

   fclose(arquivo);
}


//cabecalho do sistema.
static void Cabecalho(){
    printf( "#------------------------------------------------------------------#\n");
    printf( "#------------------------------------------------------------------#\n");
    printf( "# SISTEMA PARA CADASTRO DE PACIENTES DIAGNOSTICADOS COM A COVID-19 #\n");
    printf( "#------------------------------------------------------------------#\n");
    printf( "#------------------------------------------------------------------#\n");
    system("color 3F");//MUDA A COR DA TELA DOS
}

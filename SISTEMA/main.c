//#-------------------------------------------#
//# Criação: Vinicius Campelo, Valeria Cunha; #
//# Data: 11/2020 / UNIP: PIM-IV;             #
//# >> main.c;                                #
//#-------------------------------------------#
//BIBLIOTECAS
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "Paciente.h"
#include "Dados.h"

#define MAX_AUTO 1

void delete();
//INICIO DO SISTEMA
int main (void)
{
        bool status = false;
        int entrada = -1, status_comorbidade = -1;
        char temp;

        DadosPaciente info; //INSTANCIANDO STRUCT

        do{
        //LOGIN E SENHA DO SISTEMA (CLASSE PACIENTE.H) LOGIN:"UNIP", SENHA:"1234";
        Cabecalho();
        printf("\x1B[93mDigite seu login: ");//muda a cor do texto
        gets(info.usuario);

        printf("Digite sua senha: ");
        gets(info.senha);

        //Verifica se o usuario existe e retorna true ou false.
        status = FazerLogin(info);
        if(! status){
            system("cls");
        }

       }while(status != true);


        do{

            #ifdef WIN32
              system ("cls");
              Cabecalho();
            #endif
            //Menu do Sistema
            printf("0 - Sair do Sistema\n1 - Cadastrar Paciente\n2 - Consultar Tabela de CEP/IDADE\n3 - Consultar Paciente por Nome\n");
            printf("> ");
            scanf("%d", &entrada);
            //CADASTRAR PACIENTE
            if(entrada == 1){
            #ifdef WIN32
              system ("cls");
              Cabecalho();
            #endif
                //MUDAR A COR DA TELA DO DOS
                system("color 4F");
                printf("\nCADASTRAR PACIENTE\n");


                DadosPaciente paciente;//INSTANCIANDO STRUCT
                delete(paciente);

                printf("Digite o nome do paciente: ");//NOME DO PACIENTE
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.nome);

                printf("Digite o CPF somente numeros: ");//CPF: 00000000000
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.cpf);

                printf("Digite o telefone do paciente somente numeros com DDD: ");//TELEFONE (99)999999999
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.telefone);

                printf("Digite o logradouro ex. Av. Casa. Lt, Rua: ");//ENDEREÇO
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.endereco);

                printf("Digite o numero: ");//NUMERO DA RESIDENCIA
                scanf("%d", &paciente.numero);

                printf("Digite o bairro: ");//BAIRRO
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.bairro);

                printf("Digite a cidade: ");//CIDADE
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.cidade);

                printf("Digite o estado: ");//ESTADO
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.estado);

                printf("Digite o CEP: ");//CEP
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.cep);

                printf("Digite o dia de nascimento: ");//DIA DE NASCIMENTO PACIENTE
                scanf("%d", &paciente.dia);

                printf("Digite o mes de nascimento: ");//MES DE NASCIMENTO PACIENTE
                scanf("%d", &paciente.mes);

                printf("Digite o ano de nascimento: ");//ANO DE NASCIMENTO PACIENTE
                scanf("%d", &paciente.ano);

                printf("Digite o email: ");//EMAIL
                scanf("%c",&temp);
                scanf("%[^\n]", paciente.email);

                printf("Digite o dia do diagnostico: ");//DIA CADASTRO COMORBIDADE
                scanf("%d", &paciente.dia_c);

                printf("Digite o mes do diagnostico: ");//MES CADASTRO COMORBIDADE
                scanf("%d", &paciente.mes_c);

                printf("Digite o ano do diagnostico: ");//ANO CADASTRO COMORBIDADE
                scanf("%d", &paciente.ano_c);

                do{
                    //MENU CADASTRO DE COMORBIDADE
                    printf("[1] - Paciente sem comorbidade\n[2] - Paciente com comorbidade\n");
                    printf("> ");
                    scanf("%i", &status_comorbidade);


                    if(status_comorbidade == 2)
                    {
                        printf("Digite a comorbidade do paciente: ");
                        scanf("%s%*[^\n]", &paciente.comorbidade);
                        status_comorbidade = 0;
                      }else{
                        strcpy(paciente.comorbidade , "SEM COMORBIDADE");
                        status_comorbidade = 0;
                    }
                }while(status_comorbidade != 0);


                //CADASTRAR PACIENTE GRUPO DE RISCO
                if(CalculaIdade(paciente) > 65){
                        //FUNCAO GRAVAR CEP E IDADE      FUNCAO CADASTRAR PACIENTE
                    if(GravaCepIdade(paciente) == true && CadastraPaciente(paciente) == true){
                        printf("Paciente cadastrado com sucesso!\n");
                        printf("Idade igual a: %d anos\nPertence ao grupo de risco\n", CalculaIdade(paciente));
                    }else{
                        printf("Nao foi possivel cadastrar o paciente!\n");
                    }

                }else{
                    //CADASTRAR PACIENTE FORA DO GRUPO DE RISCO
                    if(CadastraPaciente(paciente)==true){
                        printf("Paciente cadastrado com sucesso!\n");
                    }else{
                        printf("Nao foi possivel cadastrar o paciente!\n");
                    }
                }

                #ifdef WIN32
                  system ("PAUSE");
                  system ("cls");
                 #endif

            }else if(entrada == 2){
            //LISTAR DADOS DE PACIENTES CEP/IDADE

                #ifdef WIN32
                    system ("cls");
                    Cabecalho();
                #endif

                printf("\nLISTAR DADOS DA SECRETARIA DE SAUDE\n\n");
                //FUNCAO CONSULTAR CEP/IDADE
                ConsultaCEPIdade();
				printf( "\n\n#------------------------------------------------------------------#\n\n");
                #ifdef WIN32
                    system ("PAUSE");
                    system ("cls");
                #endif

            }else if(entrada == 3){
             //CONSULTAR PACIENTES CADASTRADOS
                int valorDigitado = -1;
                //DadosPaciente consulta;
                char n[30];
                do{
                   #ifdef WIN32
                    system ("cls");
                    Cabecalho();
                   #endif


                    printf("Digite o nome do paciente: ");
                    scanf("%s%*[^\n]", &n);
                    //FUNCAO CONSULTAR PACIENTE
                    ConsultaPaciente(n);

                    printf( "#------------------------------------------------------------------#\n");
                    printf("\nDigite 1 para continuar ou 0 para sair: ");
                    scanf("%d", &valorDigitado);

                }while(valorDigitado !=0);

            }

          }while(entrada !=0);//SAIR

    return 0;
}

void delete(DadosPaciente *p)
{
    int i;
    for(i=0;i<MAX_AUTO;i++){
	    strcpy(p[i].usuario, "\0");
	    strcpy(p[i].senha, "\0");
	    strcpy(p[i].nome, "\0");
	    strcpy(p[i].cpf, "\0");
	    strcpy(p[i].telefone, "\0");
	    strcpy(p[i].endereco, "\0");
	    p[i].numero = 0;
	    strcpy(p[i].bairro, "\0");
	    strcpy(p[i].cidade, "\0");
	    strcpy(p[i].estado, "\0");
	    strcpy(p[i].cep, "\0");
	    p[i].dia = 0;
	    p[i].mes = 0;
	    p[i].ano = 0;
	    p[i].idade = 0;
	    strcpy(p[i].email, "\0");
	    p[i].dia_c = 0; //DIA CADASTRO COMORBIDADE
	    p[i].mes_c = 0; //MES CADASTRO COMORBIDADE
	    p[i].ano_c = 0; //ANO CADASTRO COMORBIDADE
	    strcpy(p[i].comorbidade, "\0");
    }
}

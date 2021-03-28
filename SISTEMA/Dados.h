//#-------------------------------------------#
//# Criação: Vinicius Campelo, Valeria Cunha; #
//# Data: 11/2020 / UNIP: PIM-IV;             #
//# Struct Dados.h;                           #
//#-------------------------------------------#

#ifndef DADOS_H
#define DADOS_H
typedef struct{

    char usuario[10];
    char senha[10];
    char nome[40];
    char cpf[15];
    char telefone[15];
    char endereco[40];
    int numero;
    char bairro[30];
    char cidade[40];
    char estado[10];
    char cep[15];
    char email[60];
    char comorbidade[30];
    int dia, mes, ano; //DIA/MES/ANO ANIVERSARIO
    int idade;
    int dia_c; //DIA CADASTRO COMORBIDADE
    int mes_c; //MES CADASTRO COMORBIDADE
    int ano_c; //ANO CADASTRO COMORBIDADE
}DadosPaciente;
#endif // DADOS_H

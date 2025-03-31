/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4                                 */
/*             Objetivo: <<  Manipulação de Pilha - Implementado HP12c  >>          */
/*                                                                                  */
/*                                  Autora: Heloísa Pichelli Souza                  */
/*                                                                   Data:30/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MaxSize 4  

typedef struct 
{
    float Data[MaxSize];
    char Expr[MaxSize][50];
    int Top;
} Pilha;

Pilha* CriarPilha() 
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->Top = -1;
    return p;
}

int PilhaVazia(Pilha* p) 
{
    return p->Top == -1;
}

int PilhaCheia(Pilha* p) 
{
    return p->Top == MaxSize - 1;
}

void Push(Pilha* p, float Valor, const char* Expr) 
{
    if (PilhaCheia(p)) 
    { 
        printf("Erro: Pilha cheia! Não é possível adicionar mais elementos.\n");
        return;
    }

    p->Top++;
    p->Data[p->Top] = Valor;
    strcpy(p->Expr[p->Top], Expr);
}

float Pop(Pilha* p, char* Expr) 
{
    if (PilhaVazia(p)) 
    {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(Expr, p->Expr[p->Top]);
    return p->Data[p->Top--];
}

float Top(Pilha* p, char* Expr) 
{
    if (PilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(Expr, p->Expr[p->Top]);
    return p->Data[p->Top];
}

int IsNumber(const char* String) 
{
    char* Endptr;
    strtof(String, &Endptr);
    return *Endptr == '\0';
}

void CalcularRPN(char* Expressao) 
{
    Pilha* pilha = CriarPilha();
    char* string = strtok(Expressao, " ");
    
    while (string != NULL) 
    {
        if (IsNumber(string)) 
        {
            float num = atof(string);
            char temp[20];
            sprintf(temp, "%.2f", num);
            Push(pilha, num, temp);
        } 
        else 
        {
            if (pilha->Top < 1) 
            {
                printf("Erro: Expressão inválida!\n");
                free(pilha);  
                return;
            }
            char exprX[50], exprY[50];
            float Y = Pop(pilha, exprY);
            float X = Pop(pilha, exprX);
            float T = 0;
            char Z = string[0];
            char novaExpr[150];
            
            switch (Z) 
            {
                case '+': T = X + Y; break;
                case '-': T = X - Y; break;
                case '*': T = X * Y; break;
                case '/':
                    if (Y == 0) 
                    {
                        printf("Erro: Divisão por zero!\n");
                        free(pilha); 
                        return;
                    }
                    T = X / Y;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    free(pilha); 
                    return;
            }
            
            snprintf(novaExpr, sizeof(novaExpr), "(%s %c %s)", exprX, Z, exprY);
            Push(pilha, T, novaExpr);
        }
        string = strtok(NULL, " ");
    }
    
    if (pilha->Top != 0) 
    {
        printf("Erro: Expressão inválida!\n");
        free(pilha);  
        return;
    }
    
    char resultadoExpr[100];
    float resultadoFinal = Pop(pilha, resultadoExpr);
    printf("\nResultado: %s = %.2f\n", resultadoExpr , resultadoFinal);
    free(pilha);  
}

int main() 
{
    char expressao[MaxSize * 20];
    Pilha* pilha = NULL;  

    pilha = CriarPilha();  
    printf("Digite a expressão RPN (Ex.: 3 4 + 5 -):\n");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0; 
    CalcularRPN(expressao);  

    return 0;
}

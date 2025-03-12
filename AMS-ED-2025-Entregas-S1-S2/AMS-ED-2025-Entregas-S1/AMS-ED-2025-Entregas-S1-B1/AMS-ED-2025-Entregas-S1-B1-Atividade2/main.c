/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-Atividade 2                       */
/*             Objetivo: <<Manipulacao de Array com ponteiro>>                      */
/*                                                                                  */
/*                                  Autora: Heloísa Pichelli Souza                  */
/*                                                                   Data:06/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Candidato 
{
    char nome[15];
    float PE[4];
    float AC[5];
    float PP[10];
    float EB[3];
    float NF;
    struct Candidato *Proximo;
};

float SomaNotasCentrais(float *PtrNotas, int Tamanho) 
{
    float Soma = 0, Maior = PtrNotas[0], Menor = PtrNotas[0];
    int i;
    
    for (i = 0; i < Tamanho; i++) 
    {
        Soma += PtrNotas[i];
        if (PtrNotas[i] > Maior) Maior = PtrNotas[i];
        if (PtrNotas[i] < Menor) Menor = PtrNotas[i];
    }
    return (Soma - Maior - Menor); 
}

void InserirCandidato(struct Candidato **Inicio, char nome[], float PE[], float AC[], float PP[], float EB[]) {
    struct Candidato *NovoCandidato = (struct Candidato*)malloc(sizeof(struct Candidato));
    if (NovoCandidato == NULL) {
        printf("Não foi possível alocar na memória\n");
        return;
    }

    strcpy(NovoCandidato->nome, nome);
    memcpy(NovoCandidato->PE, PE, 4 * sizeof(float));
    memcpy(NovoCandidato->AC, AC, 5 * sizeof(float));
    memcpy(NovoCandidato->PP, PP, 10 * sizeof(float));
    memcpy(NovoCandidato->EB, EB, 3 * sizeof(float));

    float MediaPE = SomaNotasCentrais(PE, 4); 
    float MediaAC = SomaNotasCentrais(AC, 5);  
    float MediaPP = SomaNotasCentrais(PP, 10); 
    float MediaEB = SomaNotasCentrais(EB, 3);  

    NovoCandidato->NF = (MediaPE * 0.3f) + (MediaAC * 0.1f) +
                        (MediaPP * 0.4f) + (MediaEB * 0.2f);
    
    NovoCandidato->Proximo = *Inicio;
    *Inicio = NovoCandidato;
}

void Classificacao(struct Candidato **Inicio) 
{
    struct Candidato *i, *j;
    float TempNF;
    char TempNome[15];

    for (i = *Inicio; i != NULL; i = i->Proximo) 
    {
        for (j = i->Proximo; j != NULL; j = j->Proximo) 
        {
            if (i->NF < j->NF) 
            {
                TempNF = i->NF;
                i->NF = j->NF;
                j->NF = TempNF;
                strcpy(TempNome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, TempNome);
            }
        }
    }
}

void ExibirRanking(struct Candidato *Inicio) 
{
    struct Candidato *ptr = Inicio;
    printf("Os 5 melhores candidatos são: \n");
    for (int i = 0; i < 5 && ptr != NULL; i++) {
        printf("%dº %s - Nota Final: %.2f \n", i + 1, ptr->nome, ptr->NF);
        ptr = ptr->Proximo;
    }
}

int main()
{
    struct Candidato *Inicio = NULL;
    int NumCandidatos = 0; 
    int Continuar = 1;

    while (Continuar == 1) {
        char nome[50];
        float PE[4], AC[5], PP[10], EB[3];
        
        printf("Candidatos adicionados até o momento: %d\n", NumCandidatos);
        printf("Digite o nome do candidato: ");
        scanf("%s", nome);

        printf("Digite 4 notas para Prova Escrita:\n");
        for (int Quant = 0; Quant < 4; Quant++) {
            scanf("%f", &PE[Quant]);
        }

        printf("Digite 5 notas para Análise Curricular:\n");
        for (int Quant = 0; Quant < 5; Quant++) {
            scanf("%f", &AC[Quant]);
        }

        printf("Digite 10 notas para Prova Prática:\n");
        for (int Quant = 0; Quant < 10; Quant++) {
            scanf("%f", &PP[Quant]);
        }

        printf("Digite 3 notas para Entrevista em Banca:\n");
        for (int Quant = 0; Quant < 3; Quant++) {
            scanf("%f", &EB[Quant]);
        }

        InserirCandidato(&Inicio, nome, PE, AC, PP, EB);
        NumCandidatos++;

        if (NumCandidatos >= 50) {
            printf("Limite de 50 candidatos atingido. \n");
            break;
        }

        printf("\nVocê deseja adicionar mais um candidato? (1 para SIM, 0 para NÃO): ");
        scanf("%d", &Continuar);
    }

    Classificacao(&Inicio);
    ExibirRanking(Inicio);

    return 0;
}

#include <stdio.h>

    float FuncaoDesconto(float *PtrPreco, float Desconto, int EmPorcentagem) 
    {
    float ValorDesconto;
    
        if (EmPorcentagem) 
        {
        ValorDesconto = (*PtrPreco*(Desconto/100)); 
        } 
        else 
        {
        ValorDesconto = Desconto;
        }

    *PtrPreco -= ValorDesconto;
    return 0;
    }

    void main() 
    {
        float Preco, Desconto;
        int EmPorcentagem;
    
        printf("Insira o preço do produto: R$ ");
        scanf("%f", &Preco);
    
        printf("Aplique um desconto ao preço do produto: ");
        scanf("%f", &Desconto);
    
        printf("O desconto é em porcentagem? (1 para Sim, 0 para Não): ");
        scanf("%d", &EmPorcentagem);
    
        printf("\nPreço original: R$ %.2f\n", Preco);
        
        FuncaoDesconto(&Preco, Desconto, EmPorcentagem);
    
        if (EmPorcentagem) 
        {
            printf("Desconto aplicado: %.2f%%\n", Desconto);
        }
        else 
        {
            printf("Desconto aplicado: R$ %.2f\n", Desconto);
        }
        printf("Preço final: R$ %.2f\n", Preco);
    }




#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    clock_t start, end;
    double timeUsed;
    start = clock();
    FILE *fp;
    fp = fopen("../testes_adaptados/teste8-6.txt","r");

    int nCidades, cargaCaminhao;

    fscanf(fp,"%d", &nCidades);

    fscanf(fp,"%d", &cargaCaminhao);

    float matCidades[nCidades][nCidades];
    int demandaCidade[nCidades];
    int verifcarCidade[nCidades];
    int soma = 0, qtdCaminhoes;

    for (int i = 0; i < nCidades; i++){
        fscanf(fp,"%d", &demandaCidade[i]);
        soma = soma + demandaCidade[i];
    }

    qtdCaminhoes = soma/cargaCaminhao;

    for (int i = 0; i < nCidades; i++){
        verifcarCidade[i] = 0;
        for (int j = 0; j < nCidades; j++){
            fscanf(fp,"%f", &matCidades[i][j]);
        }
    }

    puts("---------------------SOLUCAO PRV-------------------------");
    int tamVetor = nCidades  + qtdCaminhoes -2;
    int vetorDeRota[tamVetor], melhorOpcao[tamVetor], melhorValor;
    int verificador = 0, pDemanda = 1, disTotal, aux[tamVetor], i;

    for (int i=0;i<tamVetor;i++){
        if (i<nCidades-1){
            vetorDeRota[i]=i+1;

        }else{
            vetorDeRota[i]=0;
        }
    }

    for(i=0;i<tamVetor;i++){
        aux[i]=0;
    }

    i= 0;
    while (i<tamVetor){
        if  (aux[i] < i){
            if (i%2){
                int posicao = aux[i];
                int auxTroca = vetorDeRota[posicao];
                vetorDeRota[posicao] = vetorDeRota[i];
                vetorDeRota[i] = auxTroca;
            }else{
                int posicao = 0;
                int auxTroca = vetorDeRota[posicao];
                vetorDeRota[posicao] = vetorDeRota[i];
                vetorDeRota[i] = auxTroca;
            }
            aux[i] += 1;
            i = 0;

        }else{
            aux[i]=0;
            i += 1;
        }

        disTotal = 0;
        int possivel = 0, possivel2 = 1, cargaAtual = cargaCaminhao;
        for(int k = 0; k < tamVetor-1; k++){
            int p1 = vetorDeRota[k], p2 = vetorDeRota[k+1];
            if (p1 != p2){
                if (vetorDeRota[k] == 0){
                    cargaAtual = cargaCaminhao;
                }
                if (demandaCidade[p2] <= cargaAtual){
                    cargaAtual -= demandaCidade[p2];
                }else{
                    possivel = 1;
                }

                if (k == 0){
                    disTotal += matCidades[0][p2];
                }else if (k == tamVetor-2){
                    disTotal += matCidades[p1][0];
                }else{
                    disTotal += matCidades[p1][p2];
                    possivel2 = 0;
                }
            }
        }

        if (possivel == 0 && possivel2 == 0){
            if (verificador == 0){
                melhorValor = disTotal;
                for(int k = 0; k < tamVetor; k++){
                    melhorOpcao[k] = vetorDeRota[k];
                }
                verificador = 1;
            }else{
                if (disTotal < melhorValor){
                    melhorValor = disTotal;
                    for(int k = 0; k < tamVetor; k++){
                        melhorOpcao[k] = vetorDeRota[k];
                    }
                }
            }
        }
    }

    printf("%d", 0);
    for (int i = 0; i < tamVetor; i++){
        printf("%d", melhorOpcao[i]);
    }
    printf("%d", 0);

    puts("\n");
    puts("---------------------TEMPO USADO-------------------------");
    end = clock();
    timeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f %s", timeUsed, "\n");

    return 0;
}
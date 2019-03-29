//Lista 1 -- ED2 2019.1
//Nícalo Ribeiro - 16/0016169
//Algoritmos de Buscas

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
 

void imprimeVetor();
void realizarBuscaSequencial();
void realizarBuscaBinaria();
void mostrarDesempenho();

void preencheVetor();
void copiaVetor(int *vetorOriginal, int *vetorCopia, int tamanho);
void ordenarVetor(); //selection sort

int buscaSequencial(int busca);
int buscaBinaria(int busca);

int tamanho, *vetor = NULL, *vetorOrdenado = NULL;
double *resultadoBuscaSequencial = NULL, *resultadoBuscaBinaria = NULL;
int numeroDeBuscasSequenciais = 0, numeroDeBuscasBinarias = 0;

int main(){
  
    printf("Digite o tamanho do vetor :\n");
    scanf("%d", &tamanho);

    vetor = (int *)malloc(tamanho * sizeof(int));
    vetorOrdenado = (int *)malloc(tamanho * sizeof(int));
    resultadoBuscaSequencial = (double *)malloc(numeroDeBuscasSequenciais * sizeof(double));
    resultadoBuscaBinaria = (double *)malloc(numeroDeBuscasBinarias * sizeof(double));
    
    if(vetor == NULL || vetorOrdenado == NULL){
        printf("Erro ao criar vetor\nFim do programa\n");
        exit(1);
    }else{
        printf("Vetor Criado\n");
    }

    if(resultadoBuscaSequencial == NULL || resultadoBuscaBinaria == NULL){
        printf("Erro ao criar vetor de resultados\nFim do programa\n");
        exit(1);
    }else{
        printf("Vetor de Resultados criado\n\n");
    }

    preencheVetor();
    ordenarVetor(); 

    int opcao;   
    
    do{
        printf("\n|\t\tMENU\n");
        printf("|\t\t----\n");
        printf("|Escolha uma das opcões :\n");
        printf("|1-Visualizar Vetor\n");
        printf("|2-Realizar Busca Sequencial (vetor não ordenado)\n");
        printf("|3-Realizar busca binária (vetor ordenado)\n");
        printf("|4-Mostrar desempenhos\n");
        printf("|0-Sair\n");
        scanf("%d", &opcao);
        switch (opcao){

            case 1:
                imprimeVetor();
                break;
            case 2:
                realizarBuscaSequencial();
                break;
            case 3:
                realizarBuscaBinaria();
                break;
            case 4:
                mostrarDesempenho();
                break;
            case 0:
                printf("Fim do programa.\n");         
                break;
    
            default:
            printf("Digite uma opção válida\n");
            
    }
}while(opcao != 0);

    free(vetor);
    free(vetorOrdenado);
    free(resultadoBuscaSequencial);
    free(resultadoBuscaBinaria);
    
    return 0;
}

void imprimeVetor(){
    int voltar = 1;
    do{
    printf("\nVetor Original : [ ");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", vetor[i]);
    }printf("]\n\n");
        printf("Vetor Ordenado : [ ");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", vetorOrdenado[i]);
    }printf("]\n\n");
    printf("Digite < 0 > para voltar ao MENU: \n");
    scanf("%d", &voltar);
    }while(voltar);

}

void realizarBuscaSequencial(){
    int continuarBusca = 1,achou,busca;
    double duracaoSeq;
    do{
        numeroDeBuscasSequenciais++;
        resultadoBuscaSequencial = (double*)realloc(resultadoBuscaSequencial, numeroDeBuscasSequenciais * sizeof(double));
   
        printf("\nDigite o valor a ser buscado:\n");
        scanf("%d",&busca);

        srand(0);
        clock_t time;
        time = clock();
        achou = buscaSequencial(busca);
        time = clock() - time;
        duracaoSeq = ((double)time)/CLOCKS_PER_SEC;
        resultadoBuscaSequencial[numeroDeBuscasSequenciais - 1] = duracaoSeq;

        if(achou == -1){
            printf("\nO valor %d não foi encontrado. A busca durou %lf segundos\n",busca,duracaoSeq);
        }else{
            printf("\nO valor %d foi encontrado na posição %d em uma busca que durou %lf segundos\n",busca,achou,duracaoSeq);
        }
    
        printf("\nDeseja continuar buscando ? <0 Para NÃO> <Qualquer outro Número Para SIM> \n");
        scanf("%d",&continuarBusca);

    }while(continuarBusca);
    
}

void realizarBuscaBinaria(){
    int continuarBuscaBinaria = 1, achou,busca;
    double duracaoBin;
    do{
        numeroDeBuscasBinarias++;
        resultadoBuscaBinaria = (double*)realloc(resultadoBuscaBinaria, numeroDeBuscasBinarias * sizeof(double));

        printf("\nDigite o valor a ser buscado:\n");
        scanf("%d",&busca);

        srand(0);
        clock_t time;
        time = clock();
        achou = buscaBinaria(busca);
        time = clock() - time;
        duracaoBin = ((double)time)/CLOCKS_PER_SEC;
        resultadoBuscaBinaria[numeroDeBuscasBinarias - 1] = duracaoBin;

        if(achou == -1){
            printf("\nO valor %d não foi encontrado. A busca durou %lf segundos\n",busca,duracaoBin);
        }else{
            printf("\nO valor %d foi encontrado na posição %d. A busca durou %lf segundos\n",busca,achou,duracaoBin);
        }
    
        printf("\nDeseja continuar buscando ? <0 Para NÃO> <Qualquer outro Número Para SIM> \n");
        scanf("%d",&continuarBuscaBinaria);

    }while(continuarBuscaBinaria);

}

void mostrarDesempenho(){
    if(numeroDeBuscasBinarias == 0 && numeroDeBuscasSequenciais == 0){
        printf("\nNenhuma busca foi realizada ainda!\n\n");    
        return;        
    }
    int voltar = 1;
    do{
        printf("\nAté o momento foram realizadas: \n->%d buscas sequenciais \n->%d buscas binárias\n->Tamanho do vetor: %d\n", numeroDeBuscasSequenciais, numeroDeBuscasBinarias,tamanho);
        if(numeroDeBuscasSequenciais){
            printf("\nBuscas sequenciais : \n");
            for(int i = 0; i <numeroDeBuscasSequenciais; i++){
                printf("%dª Busca sequencial -> Duração de %lf segundos\n",i+1, resultadoBuscaSequencial[i]);
            }
        }

        if(numeroDeBuscasBinarias){
            printf("\nBuscas binárias : \n");
            for(int j = 0; j < numeroDeBuscasBinarias; j++){    
                printf("%dª Busca binária -> Duração de %lf segundos\n", j+1, resultadoBuscaBinaria[j]);
            }
        }
        printf("\n\nDigite < 0 > para voltar ao MENU: \n");
        scanf("%d", &voltar);
    }while(voltar);
        
}

void preencheVetor(){
    int numeroGerado , vetorAux[tamanho], repetido = 1;    
    srand(time(NULL)); 
    for(int i = 0; i < tamanho; i++){
        while(repetido){
            numeroGerado = (rand() % (tamanho*3) + 1);
            repetido = 0;
            for (int j = 0; j < tamanho; j++){
                if(numeroGerado == vetorAux[j]){
                    repetido = 1;
                }
            }        
        }        
        vetorAux[i] = numeroGerado;
        vetor[i] = vetorAux[i];
        repetido = 1;        
    }
}

void ordenarVetor(){
    copiaVetor(vetor,vetorOrdenado,tamanho);
    int i,j,min,swap;
    for(i = 0; i < (tamanho-1); i++){
        min = i;
        for(j = (i+1);j<tamanho;j++){
            if(vetorOrdenado[j] < vetorOrdenado[min]){
                min = j;
            }
        }
            swap = vetorOrdenado[min];
            vetorOrdenado[min] = vetorOrdenado[i];
            vetorOrdenado[i] = swap;
            
        }
}

void copiaVetor(int *vetorOriginal, int *vetorCopia, int tamanho){
    for(int i = 0; i < tamanho; i++){
        vetorCopia[i] = vetorOriginal[i];
    }
}

int buscaSequencial(int busca){
    for(int i = 0; i < tamanho; i++){
        if(vetor[i] == busca){
            return i;     
        }
    }
    return -1;    
}

int buscaBinaria(int busca){
    int achou = 0, fim = tamanho, inicio = 0, meio = (inicio + fim)/2;
    while((!achou) && (fim >= inicio)){
        if(busca == vetorOrdenado[meio]){
            return meio;
        }else if(busca < vetorOrdenado[meio]){
            fim = meio - 1;
        }else{
            inicio = meio + 1;            
        }

        meio = (inicio + fim)/2;        
    }
    return -1;
}

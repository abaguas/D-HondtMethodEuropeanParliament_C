#include <stdio.h>

/* directivas de pre-compilador, definicao de constantes, etc. */

#define PARTIDOS 12
#define PAISES 28
#define DIMPARTIDO 4
#define DIMPAIS 3

/* prototipos: */

void inicializa1(float votacoes[PAISES][PARTIDOS]);

void inicializa2(int eleitos[PAISES][PARTIDOS]);

int hont(float votacoes[PAISES][PARTIDOS], int eleitos[PAISES][PARTIDOS], float hondt[PAISES][PARTIDOS], int lugares,int pais);

void ppes(char partidos[PARTIDOS][DIMPARTIDO]);

void paisnome(char paises[PAISES+1][DIMPAIS], int pais);

void listaeleitos(int eleitos[PAISES][PARTIDOS], int pais);

void escrevetotal(char paises[PAISES+1][DIMPAIS], int eleitos[PAISES][PARTIDOS], int total[PARTIDOS]);


/* MAIN */

int main(){

    /* variaveis */

    char paises[PAISES+1][DIMPAIS]={"DE","AT","BE","BG","CY","HR","DK","SK","SI","ES","EE","FI","FR","GR","HU","IE","IT","LV","LT","LU","MT","NL","PL","PT","GB","CZ","RO","SE","TE"};
    char partidos[PARTIDOS][DIMPARTIDO]={"EPP","PES","LDE","EGP","ECR","ELP","ELD","EDP","EAF","EMN","ECP","AED"};
    float  lugares[PAISES]={96,18,21,17,6,11,13,13,8,54,6,13,74,21,21,11,73,8,11,6,6,26,51,21,73,21,32,20};
    float votacoes[PAISES][PARTIDOS];
    int eleitos[PAISES][PARTIDOS];
    float hondt[PAISES][PARTIDOS];
    int total[PARTIDOS]={0};
    char command;
    int pais,votos,partido,indice;

    inicializa1(votacoes);
    inicializa1(hondt);
    inicializa2(eleitos);

    while ((command = getchar()) != 'x') {
        switch (command) {

        case '+':

             /* reinicia a linha de eleitos do pais escolhido de modo a poder ser aplicado o metodo D Hont ao mesmo tempo que
                 actualiza os votos do partido e pais seleccionados e prepara a aplicacao do metodo D Hont */

             scanf("%d %d %d", &pais, &partido, &votos);
             for(indice=0; indice<PARTIDOS; indice++){
             	eleitos[pais-1][indice]=0;
             }
             votacoes[pais-1][partido-1]=votacoes[pais-1][partido-1]+votos;  /*soma ao partido os novos votos*/
             for(indice=0; indice<PARTIDOS; indice++){
             	hondt[pais-1][indice] = votacoes[pais-1][indice];  /*soma ao partido os novos votos*/
             }

             /* aplicacao do metodo D Hont ao pais escolhido */

             hont(votacoes, eleitos, hondt, lugares[pais-1], pais);
            break;

        case 'm':
            /* Chama a funcao responsavel pela execucao do comando m */

            scanf("%d",&pais);
            ppes(partidos);
            paisnome(paises, pais);
            listaeleitos(eleitos, pais);
            break;

        case 'e':
            /* Chama a funcao responsavel pela execucao do comando e */

            ppes(partidos);
            for(indice=1; indice<PAISES+1; indice++){
              paisnome(paises, indice);
              listaeleitos(eleitos, indice);
            }
            escrevetotal(paises, eleitos, total);
            break;

        default:
            printf("ERRO: Comando desconhecido\n");
        }
        getchar();
    }
    return 0;
}

/* Funcoes */

     /* Actualiza e escreve o total */
     void escrevetotal(char paises[PAISES+1][DIMPAIS], int eleitos[PAISES][PARTIDOS], int total[PARTIDOS]){
         int i,j;
     
         for(i=0; i<PARTIDOS; i++){
             total[i] = 0;
         }
         printf("%s ", paises[PAISES]);
         for(i=0; i<PARTIDOS; i++){
             for(j=0; j<PAISES; j++){
                 total[i] = total[i]+eleitos[j][i];
            }
         }
         for(i=0; i<PARTIDOS-1; i++){
             printf("%3d ", total[i]);
         }
         printf("%3d", total[PARTIDOS-1]);
         printf("\n");
     }
      
    

    /* Escreve os nomes dos PPEs */
    void ppes(char partidos[PARTIDOS][DIMPARTIDO]){   
        int i;   

        printf("   ");
        for(i=0; i<PARTIDOS; i++){
            printf("%s ", partidos[i]);
        }
        printf("\n");
    }

    /* Escreve o nome do Pais */
    void paisnome(char paises[PAISES+1][DIMPAIS], int pais){  
        printf("%s ", paises[pais-1]);
    }

    /* Escreve eleitos */
    void listaeleitos(int eleitos[PAISES][PARTIDOS], int pais){
        int i;
 
        for(i=0; i<PARTIDOS-1; i++){
            printf("%3d ", eleitos[pais-1][i]);
        }
        printf("%3d", eleitos[pais-1][PARTIDOS-1]);
        printf("\n");
    }

    /* Aplica o metodo DHont no pais respectivo */
    int hont(float votacoes[PAISES][PARTIDOS], int eleitos[PAISES][PARTIDOS], float hondt[PAISES][PARTIDOS], int lugares,int pais){
        int i,eleitotal,realmaior = 0;
        float maior=0.0; 

        for(eleitotal=0; eleitotal<lugares; eleitotal++){

           /* "maior" tem o maior valor da matriz hondt no pais respectivo */    
       
            for(i=0; i<PARTIDOS; i++) {
               if((hondt[pais-1][i])>maior) {
                   maior=(hondt[pais-1][i]);
               }
            }

           /* dos maiores valores da matriz hondt no pais respectivo, ve-se qual o partido com menos eleitos e guarda-se o valor em
              "realmaior" */
      
            realmaior=lugares;
            for(i=0; i<PARTIDOS; i++) {
                if((hondt[pais-1][i])==maior) {
                    if((eleitos[pais-1][i])<realmaior) {
                        realmaior = (eleitos[pais-1][i]);
                    }
                }
            }
            /* o primeiro partido com o quociente igual ao valor "maior" e numero de eleitos igual ao "realmaior" fica com mais um eleito
               e um novo valor para o quociente e atribuido (votos do partido/eleitos+1) */     
     
            i=0;
            while((eleitos[pais-1][i]!=realmaior) || (hondt[pais-1][i]!=maior)) {
                i++;
            }
            eleitos[pais-1][i]++;
            hondt[pais-1][i]=(votacoes[pais-1][i]/(eleitos[pais-1][i]+1));
            maior=0;
            realmaior=0;
        }
        return 0;
    }

/* Inicializacao de matrizes */

   /* Inicializa matrizes PARTIDOSxPAISES do tipo float */

   void inicializa1(float votacoes[PAISES][PARTIDOS]){
       int i,j;

       for(i=0; i<PAISES; i++) {
           for(j=0; j<PARTIDOS; j++) {
               votacoes[i][j]=0;
           }
       }
   }

   /* Inicializa matrizes PARTIDOSxPAISES do tipo int */ 

    void inicializa2(int eleitos[PAISES][PARTIDOS]){
        int i,j;

        for(i=0; i<PAISES; i++) {
            for(j=0; j<PARTIDOS; j++) {
                eleitos[i][j]=0;
            }
        }
    }

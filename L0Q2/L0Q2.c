#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 501

//Pedro Santana e Victor Gabriel

typedef struct Lista{
    int numInt;
    float numFloat;
    double x, y;
    char string[MAX];
    char tipo; //i = int; f = float; p = point; s = string;
}Lista;

int main(){
    FILE *fp_in = fopen("C:/Users/pedro/Desktop/IFBA/jose dihego/Lista 0/L0Q2/L0Q2_in.txt", "r");
    FILE *fp_out = fopen("C:/Users/pedro/Desktop/IFBA/jose dihego/Lista 0/L0Q2/L0Q2_out.txt", "w");
    int contador = 0, indiceGeral = 0;
    char listaUsuario[MAX];
    char *token;
    Lista lista[MAX];

    if(fp_in == NULL || fp_out == NULL){
        printf("Files cannot be oppened");
        return EXIT_FAILURE;
    }

    while(fgets(listaUsuario, MAX, fp_in)){
        listaUsuario[strcspn(listaUsuario, "\n")] = '\0';
        token = listaUsuario;
        
        contador = 0;
        indiceGeral = 0;

        while(*token != '\0'){
            while(isspace(*token)) token++;

            if(*token == '\0') break;

            char temp[MAX];
            int cont = 0;

            if(*token == '('){
                while(*token && *token != ')'){
                    if(!isspace(*token)) temp[cont++] = *token;
                    token++;
                }
                if(*token == ')'){
                    temp[cont++] = *token;
                    token++;
                }
                temp[cont] = '\0';
                double x, y;
                if(sscanf(temp, "(%lf,%lf)", &x, &y) == 2){
                    lista[indiceGeral].x = x;
                    lista[indiceGeral].y = y;
                    lista[indiceGeral].tipo = 'p';
                    indiceGeral++;
                }
            }else{
                while(*token && !isspace(*token)){
                    temp[cont++] = *token++;
                }
                temp[cont] = '\0';

                char *finalTemp;
                int identificado = 0;

                //SE FOR INT
                int inteiro = (int)strtol(temp, &finalTemp, 10);
                if (*finalTemp == '\0') {
                    lista[indiceGeral].tipo = 'i';
                    lista[indiceGeral].numInt = inteiro;
                    indiceGeral++;
                    identificado = 1;
                }
                //SE FOR FLOAT
                if (!identificado) {
                    float real = strtof(temp, &finalTemp);
                    if (*finalTemp == '\0') {
                        lista[indiceGeral].tipo = 'f';
                        lista[indiceGeral].numFloat = real;
                        indiceGeral++;
                        identificado = 1;
                    }
                }
                //SE FOR STRING
                if (!identificado) {
                    lista[indiceGeral].tipo = 's';
                    strncpy(lista[indiceGeral].string, temp, sizeof(lista[indiceGeral].string));
                    lista[indiceGeral].string[sizeof(lista[indiceGeral].string) - 1] = '\0';
                    indiceGeral++;
                }
            }
        }
        //CALCULAR DISTANCIA INICIO
        double distanciaInicio[MAX];
        for(int cont = 0; cont < indiceGeral; cont++){
            if(lista[cont].tipo == 'p'){
                distanciaInicio[cont] = sqrt(lista[cont].x * lista[cont].x + lista[cont].y * lista[cont].y);
            }
        }
        //ORGANIZAR POINTS
        double trocaX, trocaY, trocaDistancia;
        for(int cont = 0; cont < indiceGeral - 1; cont++){
            for(int cont2 = cont + 1; cont2 < indiceGeral; cont2++){
                if(lista[cont].tipo == 'p' && lista[cont2].tipo == 'p'){
                    if(distanciaInicio[cont] > distanciaInicio[cont2]){
                        trocaX = lista[cont2].x;
                        lista[cont2].x = lista[cont].x;
                        lista[cont].x = trocaX;

                        trocaY = lista[cont2].y;
                        lista[cont2].y = lista[cont].y;
                        lista[cont].y = trocaY;

                        trocaDistancia = distanciaInicio[cont2];
                        distanciaInicio[cont2] = distanciaInicio[cont];
                        distanciaInicio[cont] = trocaDistancia;
                    }
                }
            }
        }
        //ORGANIZAR INT
        int trocaI;
        for(int cont = 0; cont < indiceGeral - 1; cont++){
            for(int cont2 = cont + 1; cont2 < indiceGeral; cont2++){
                if(lista[cont].tipo == 'i' && lista[cont2].tipo == 'i'){
                    if(lista[cont].numInt > lista[cont2].numInt){
                        trocaI = lista[cont2].numInt;
                        lista[cont2].numInt = lista[cont].numInt;
                        lista[cont].numInt = trocaI;
                    }
                }
            }
        }
        //ORGANIZAR FLOAT
        float trocaF;
        for(int cont = 0; cont < indiceGeral - 1; cont++){
            for(int cont2 = cont + 1; cont2 < indiceGeral; cont2++){
                if(lista[cont].tipo == 'f' && lista[cont2].tipo == 'f'){
                    if(lista[cont].numFloat > lista[cont2].numFloat){
                        trocaF = lista[cont2].numFloat;
                        lista[cont2].numFloat = lista[cont].numFloat;
                        lista[cont].numFloat = trocaF;
                    }
                }
            }
        }
        //ORGANIZAR STRING
        char trocaS[MAX];
        for(int cont = 0; cont < indiceGeral - 1; cont++){
            for(int cont2 = cont + 1; cont2 < indiceGeral; cont2++){
                if(lista[cont].tipo == 's' && lista[cont2].tipo == 's'){
                    if(strcmp(lista[cont].string, lista[cont2].string) > 0){
                        strcpy(trocaS, lista[cont].string);
                        strcpy(lista[cont].string, lista[cont2].string);
                        strcpy(lista[cont2].string, trocaS);
                    }
                }
            }
        }
        //IMPRIMIR
        //STRINGS
        fprintf(fp_out, "str:");
        for(int cont = 0; cont < indiceGeral; cont++){
            if(lista[cont].tipo == 's'){
                fprintf(fp_out, "%s ", lista[cont].string);
            }
        }
        //INT
        fprintf(fp_out, "int:");
        for(int cont = 0; cont < indiceGeral; cont++){
            if(lista[cont].tipo == 'i'){
                fprintf(fp_out, "%d ", lista[cont].numInt);
            }
        }
        //FLOAT
        fprintf(fp_out, "float:");
        for(int cont = 0; cont < indiceGeral; cont++){
            if(lista[cont].tipo == 'f'){
                fprintf(fp_out, "%.2f ", lista[cont].numFloat);
            }
        }
        //POINT
        fprintf(fp_out, "p:");
        for(int cont = 0; cont < indiceGeral; cont++){
            if(lista[cont].tipo == 'p'){
                fprintf(fp_out, "(%.1f,%.1f) ", lista[cont].x, lista[cont].y);
            }
        }
        fprintf(fp_out, "\n");
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}

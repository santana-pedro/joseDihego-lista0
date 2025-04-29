#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TAM 501

//Pedro Santana e Victor Gabriel

int main(){
    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");
    char points[TAM];
    int indicePoints = 0;
    double x[TAM], y[TAM], distanciaPontos[TAM], distance = 0, shortcut, distanciaInicio[TAM];

    if (fp_in == NULL || fp_out == NULL){
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while(fgets(points, TAM, fp_in) != NULL){
        points[strcspn(points, "\n")] = '\0';
        indicePoints = 0;
        distance = 0;
        //PEGANDO POINTS
        for(int cont = 0; points[cont] != '\0'; cont++){
            if(points[cont] == '('){
                x[indicePoints] = strtod(&points[cont + 1], NULL);
            }
            if(points[cont] == ','){
                y[indicePoints] = strtod(&points[cont + 1], NULL);
                indicePoints++;
            }
        }
        //CALCULANDO DISTANCIA
        for(int cont = 0; cont < indicePoints - 1; cont++){
            distanciaPontos[cont] = sqrt(((x[cont + 1] - x[cont]) * (x[cont + 1] - x[cont]) + (y[cont + 1] - y[cont]) * (y[cont + 1] - y[cont])));
            distance += distanciaPontos[cont];
        }
        //CALCULANDO SHORTCUT
        shortcut = sqrt((((x[indicePoints - 1] - x[0]) * (x[indicePoints - 1] - x[0])) + ((y[indicePoints - 1] - y[0]) * (y[indicePoints - 1] - y[0]))));
        //DISTANCIA INICIO
        for(int cont = 0; cont < indicePoints; cont++){
            distanciaInicio[cont] = sqrt(x[cont] * x[cont] + y[cont] * y[cont]);
        }
        //ORGANIZAR
        double trocaX, trocaY, trocaDistancia;
        for(int cont = 0; cont < indicePoints; cont++){
            for(int cont2 = cont + 1; cont2 < indicePoints; cont2++){
                if(distanciaInicio[cont] > distanciaInicio[cont2]){
                    //X
                    trocaX = x[cont2];
                    x[cont2] = x[cont];
                    x[cont] = trocaX;
                    //Y
                    trocaY = y[cont2];
                    y[cont2] = y[cont];
                    y[cont] = trocaY;
                    //DISTANCIA INICIO
                    trocaDistancia = distanciaInicio[cont2];
                    distanciaInicio[cont2] = distanciaInicio[cont];
                    distanciaInicio[cont] = trocaDistancia;
                }
            }
        }
        //IMPRIMIR
        fprintf(fp_out, "points ");
        for(int cont = 0; cont < indicePoints; cont++){
            fprintf(fp_out, "(%.0f,%.0f) ", x[cont], y[cont]);
        }
        fprintf(fp_out, "distance %.2f shortcut %.2f", distance, shortcut);
        fprintf(fp_out, "\n");
    }
    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}
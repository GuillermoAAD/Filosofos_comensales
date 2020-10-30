/*
Centro Universitario de Ciencias Exactas e Ingenierías
Departamento de Ciencias Computacionales
Materia: Seminario de Uso, Adaptación y Explotación de Sistemas Operativos
Profesor: Becerra Velázquez, Violeta del Rocío
Alumno: Alcaraz Domínguez, Guillermo Augusto
Código: 217294148
Carrera: Ingeniería en informática
Sección: D02
Actividad de Aprendizaje 7
Filósofos
26 de Octubre del 2020
*/

#include <iostream>
#include <cstdlib>
#include <unistd.h>  //Para el sleep

#define numeroFilosofos 5
#define numeroPalillos numeroFilosofos
#define comidasMinimas 6

using namespace std;

//guarda el estado, si esta comiendo o pensando
int filosofos[numeroFilosofos];
//guarda el total de fichas disponibles por turno
int totalfichas = numeroFilosofos / 2;
//guarda el id de los filosofos que pueden comer en el turno
int fichas[numeroFilosofos / 2];
//guarda cuantas comidas ha hecho cada filosofo
int contadorComidas[numeroFilosofos];

int duracionDelTurno = 2;

void imprimirMesa();
void repartirFichas(int idFilosofoInicial);
void mostrarFichasRepartidas();
void terminarDeComer();
bool verSiHanComidoNVeces();
void imprimirEstadoFilosofo();
void imprimirPalillosUsados(int idFilosofo);
void imprimirComidasHechas();

int main() {
    imprimirMesa();

    int i = 1;
    int primerFichaDelTurno = 0;

    //cada iteracion es un turno de tiempo constante en el que la mayor cantidad de filosofos comen
    while(!verSiHanComidoNVeces()){

        cout << "Turno: " << i << endl << endl;

        repartirFichas(primerFichaDelTurno);

        imprimirEstadoFilosofo();

        sleep(duracionDelTurno);

        terminarDeComer();

        primerFichaDelTurno++;
        if(primerFichaDelTurno == numeroFilosofos) {
            primerFichaDelTurno = 0;
        }
        i++;
    }

    cout << "Estado final: " << endl << endl;
    imprimirComidasHechas();

    cout << "Todos los filosofos han comido minimo " << comidasMinimas << " veces" << endl << endl;

    return 0;
}

void imprimirMesa(){
    system("clear");
    cout << "                                                                               " << endl;
    cout << "          ############## PROGRAMA FILOSOFOS COMENSALES ##############          " << endl;
    cout << "                                                                               " << endl;
    cout << "                F = FILOSOFO       P = PALILLO       () = PLATO                " << endl;
    cout << "                                                                               " << endl;
    cout << "                                   # # # #                                     " << endl;
    cout << "                           F0    #    P1   #    F1                             " << endl;
    cout << "                               #  ()     ()  #                                 " << endl;
    cout << "                              #  P0       P2  #                                " << endl;
    cout << "                               #  ()     ()  #                                 " << endl;
    cout << "                           F4   #  P4 () P3 #   F2                             " << endl;
    cout << "                                 # # # # # #                                   " << endl;
    cout << "                                      F3                                       " << endl;
    cout << "                                                                               " << endl;
    sleep(duracionDelTurno);
}

void repartirFichas(int idFilosofoInicial){
    //el idFilosofoInicial tiene la primer ficha del turno

    fichas[0] = idFilosofoInicial;

    for(int i = 1; i < totalfichas; i++) {

        int idFilosofo = fichas[i - 1] + 2;

        //Con esto no sebrepasa el total de filososofos que hay
        if(idFilosofo == numeroFilosofos){
            idFilosofo = 0;
        } else if(idFilosofo ==  numeroFilosofos + 1){
            idFilosofo = 1;
        }
        fichas[i] = idFilosofo;
    }
}

void mostrarFichasRepartidas(){
    cout << "ficha para: ";
    for(int f : fichas){
        cout << f << " ";
    }
    cout << endl << endl;
}

void terminarDeComer(){
    //solo incrementa el contador de comidas de los que estan comiendo
    for(int f : fichas){
        contadorComidas[f]++;
    }
}

bool verSiHanComidoNVeces()
{
    bool todosComieronNVeces = true;
    for(int c : contadorComidas) {
        if(c < comidasMinimas) {
            todosComieronNVeces = false;
            break;
        }
    }
    return todosComieronNVeces;
}

void imprimirEstadoFilosofo(){
    //recorre por todos los filosofos para ver su estado
    for(int i = 0; i < numeroFilosofos; i++){
        bool estaComiendo = false;
        for(int f : fichas){
            if(i == f){
                estaComiendo = true;
                cout << "El filosofo " << i << " esta comiendo";
                //imprimirPalillosUsados(i);
                cout << " | Lleva "<< contadorComidas[i] << " comidas"<< endl;
                imprimirPalillosUsados(i);
                break;
            }
        }
        if(!estaComiendo) {
            cout << "El filosofo " << i << " esta pensando | Lleva "<< contadorComidas[i] << " comidas"<< endl;
        }
    }

    cout << endl << endl;
}

void imprimirPalillosUsados(int idFilosofo){
    int palilloDerecho = idFilosofo;
    int palilloIzquierdo = idFilosofo + 1;

    if(palilloIzquierdo == numeroPalillos){
        palilloIzquierdo = 0;
    }

    cout << "con los palillos " << palilloDerecho << " y " << palilloIzquierdo << endl;
}

void imprimirComidasHechas(){
    int i = 0;
    for(int c : contadorComidas){
        cout << "El filosofo " << i << " comio "<< c << " comidas"<< endl;
        i++;
    }
    cout << endl << endl;
}

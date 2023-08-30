#include<iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Carta.h"
#include "Jugador.h"
#include "Continente.h"
using namespace std;

bool tiene_espacio(string comando, string cd[]) {
    bool space = false;

    for (int i = 0; i < comando.size(); i++) {
        if (comando[i] == ' ') {
            space = true;
        }
    }
    int i = 0;
    if (space) {
        std::istringstream ss(comando);
        std::string token;
        while (std::getline(ss, token, ' ')) {
            if (i < 5) {
                cd[i] = token;
                i++;
            } else {
                break;
            }
        }
    }
    return space;
}

void limpiar(string cd[]) {
    for (int i = 0; i < 5; i++) {
        cd[i] = "";
    }
};

void imprimir_ayuda() { // Despliega el menú con comandos disponibles

    cout << "\nCOMANDOS DISPONIBLES \n"
            "inicializar \n"
            "turno \n"
            "guardar \n"
            "guardar_comprimido \n"
            "salir \n"
            "costo_conquista \n"
            "conquista_mas_barata \n"
            "ayuda \n";
}

void descripcion_comando(string c) { // Imprime descripción de comando específico

    if (c == "ayuda") { // ayuda
        cout << "El comando ayuda te permite conocer todos los comandos que puedes "
                "usar en la app o conocer uno en específico. "<< endl;
        cout << "ayuda <comando>" << endl;
    }
    else if (c == "inicializar") { // inicializar
        cout << "El comando inicializar inicializa el juego y asigna territorios a "
                "los jugadores, puedes inicializar un juego nuevo solo escribiendo 'inicializar' "
                "o cargar un juego previamente guardado asi: \n"<< endl;
        cout << "inicializar <nombre_archivo>" << endl;
    }
    else if (c == "turno") { // turno
        cout << "El comando turno realiza las operaciones dentro del turno de un "
                "jugador (obtener nuevas unidades, atacar y fortificar) \n"<< endl;
        cout << "turno <id jugador>" << endl;
    }
    else if (c == "salir") { // salir
        cout << "El comando salir finaliza la ejecución de la aplicación." << endl;
    }
    else if (c == "guardar") { // guardar
        cout << "El comando guardar te permite conservar los datos de la partida "
                "(como nombre, color del jugador, etc.) en un archivo de texto. \n"<< endl;
        cout << "guardar <nombre_archivo>" << endl;
    }
    else if (c == "guardar_comprimido") { // guardar_comprimido
        cout << "El comando guardar_comprimido permitirá guardar los datos del "
                "juego (como nombre, color del jugador, etc.) en un archivo. \n "
                "binario (.bin) comprimido."<< endl;
        cout << "guardar_comprimido <nombre_archivo>" << endl;
    }
    else if (c == "costo_conquista") { // costo_conquista
        cout << "El comando costo_conquista permite calcular el costo y la "
                "secuencia de territorios que deben ser conquistados para "
                "controlar el territorio dado por el usuario en turno. \n"<< endl;
        cout << "costo_conquista <territorio>" << endl;
    }
    else if (c == "conquista_mas_barata") { // conquista_mas_barata
        cout << "El comando conquista más barata calcula el territorio que implica "
                "el menor número de perdida de unidades en el ejército"<< endl;
    }
    else {
        cout << "Comando no disponible" << endl;
    }
}
bool turnoValido(std::vector<Jugador> jugadores, int idJ){
    std::vector<Jugador>::iterator it = jugadores.begin();
    for(it = jugadores.begin();it != jugadores.end();it++){
        if(idJ == it->getId()){
            return true;
        }
    }
    return false;
}

bool turnoCorrecto(std::vector<Jugador> jugadores, int idJ, int * numTurno){
    if(jugadores[*numTurno].getId() == idJ){
        return true;
    }
    return false;
}

bool turnonumerico(std::string turno){
    for(char c: turno){
        if(isalpha(c)){
            return true;
        }
    }
    return false;
}

void incrementarGrupo(int * numIntercambios, int * unidadesGanadas){
    if(*numIntercambios == 1){
        *unidadesGanadas = 4;
    }
    if(*numIntercambios == 2){
        *unidadesGanadas = 6;
    }
    if(*numIntercambios == 3){
        *unidadesGanadas = 8;
    }
    if(*numIntercambios == 4){
        *unidadesGanadas = 10;
    }
    if(*numIntercambios == 5){
        *unidadesGanadas = 12;
    }
    if(*numIntercambios == 6){
        *unidadesGanadas = 15;
    }
    if(*numIntercambios > 6){
        *unidadesGanadas = *unidadesGanadas + 5;
    }
}

void inicio(){

    std::cout << "            a@@@@a                                            iiii                   kkkkkkkk\n"
                 "        a@@@@@@@@@@@@a                                       i::::i                  k::::::k\n"
                 "      a@@@@@@by@@@@@@@@a                                      iiii                   k::::::k\n"
                 "    a@@@@@S@C@E@S@W@@@@@@a                                                           k::::::k\n"
                 "    @@@@@@@@@@@@@@@@@@@@@@              rrrrr   rrrrrrrrr   iiiiiii     ssssssssss    k:::::k    kkkkkkk\n"
                 "     `@@@@@@`\\\\//'@@@@@@'             r::::rrr:::::::::r  i:::::i   ss::::::::::s   k:::::k   k:::::k\n"
                 "          ,,  ||  ,,                    r:::::::::::::::::r  i::::i ss:::::::::::::s  k:::::k  k:::::k\n"
                 "         /(-\\ || /.)                   rr::::::rrrrr::::::r i::::i s::::::ssss:::::s k:::::k k:::::k\n"
                 "    ,---' /`-'||`-'\\ `----,             r:::::r     r:::::r i::::i  s:::::s  ssssss  k::::::k:::::k\n"
                 "   /( )__))   ||   ((,==( )\\            r:::::r     rrrrrrr i::::i    s::::::s       k:::::::::::k\n"
                 "_ ///_\\\\ _|| _\\ __\\ _                     r:::::r             i::::i       s::::::s    k:::::::::::k\n"
                 "    ``    `` /MM\\   ''   ''             r:::::r             i::::i ssssss   s:::::s  k::::::k:::::k\n"
                 "                                         r:::::r            i::::::is:::::ssss::::::sk::::::k k:::::k\n"
                 "                                         r:::::r            i::::::is::::::::::::::s k::::::k  k:::::k\n"
                 "                                         r:::::r            i::::::i s:::::::::::ss  k::::::k   k:::::k\n"
                 "                                         rrrrrrr            iiiiiiii  sssssssssss    kkkkkkkk    kkkkkkk\n"
              << std::endl;
}

void ganadorR(){
    cout<<"  __ _   __ _  _ __    __ _   __| |  ___   _ __ \n"
          " / _` | / _` || '_ |  / _` | / _` | / _ / | '__|\n"
          "| (_| || (_| || | | || (_| || (_| || (_) || |   \n"
          " L__, | L__,_||_| |_| L__,_| L__,_| L___/ |_|   \n"
          " |___/                                          "<<std::endl;
}

void mostrarTablero(){
    std::cout << "\n****************************************" << std::endl;
    std::cout << "*   TERRITORIOS DEL TABLERO DE JUEGO   *" << std::endl;
    std::cout << "****************************************" << std::endl;

    cout<<endl<<endl;
    cout<<"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;
    cout<<"|           . _..::__:  ,- - ._                 ,     _,.__             |"<<endl;
    cout<<"|   _.___ _ _<_>`!(._`.`-. 5  /        _._     `_ ,_/  '12 '-._.---.-.__|"<<endl;
    cout<<"|>.{    1    `-==,',._/{  /  /     2   /4_  >_,-' `10             6    _|"<<endl;
    cout<<"+   _.:--.    6  `._ )`^-.  '       , [_/(       11       4      __,/-' +"<<endl;
    cout<<"| ' '     / 2    7    8  _L        1 _,3-'  6      1      8     /. (|   |"<<endl;
    cout<<"|          |           ,'          _)_.//5_<>                _,' /  '   |"<<endl;
    cout<<"|          `. 9    4  /           [_7_'` ` (             2  <'} 5)      |"<<endl;
    cout<<"+           //        /           /   `-' ..' `:7_          _)  '       +"<<endl;
    cout<<"|             / 3    /           /       3 `:/  > /  ,-^. 9/' '         |"<<endl;
    cout<<"|              `._, /            |  5        /`'  /3|   /_/   /         |"<<endl;
    cout<<"|                 `=.---.        `._._     2 ,'    '`  |' ,- '.         |"<<endl;
    cout<<"+                   | 4  `-._         |     /          `:`<_|h--._      +"<<endl;
    cout<<"|                   (     2  >        .  1  | ,          `=2__.3-'/     |"<<endl;
    cout<<"|                    `.3    /         |     |{|              ,-.,/     .|"<<endl;
    cout<<"|                     |   ,'           / 6 / `'            ,    1 /     |"<<endl;
    cout<<"+                     |1 /              |_'                |4 __  /     +"<<endl;
    cout<<"|                     | |                                  '-'  `-'   /.|"<<endl;
    cout<<"|                     |/                                              / |"<<endl;
    cout<<"|                     /.                                             '  |"<<endl;
    cout<<"+                                                                       +"<<endl;
    cout<<"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;
}
//
// Created by Estudiante on 25/08/2023.
//

#ifndef RISK_PARTIDA_H
#define RISK_PARTIDA_H

#include "Continente.h"
#include "Carta.h"
#include "Jugador.h"
#include<list>
#include<vector>

class Partida{
private:
    int id;
    std::vector<Jugador> jugadores;
    std::list<Carta> cartas;
    std::list<Continente> tablero;
public:
    Partida(int id);
    std::vector<Jugador> get_jugadores();
    std::list<Carta> get_cartas();
    std::list<Continente> get_tablero();
    void set_id(int id);

    //funciones relacionadas a inicializar
    int countLines(std::string archivo_cartas);
    void cargarCartas(std::string archivo_cartas);
    bool buscarColorRepetido (std::string color);
    void asignarUnidades();
    void inicializarJugadores();
    bool repetido(std::string nombre);
    void inicializarTablero();
    void llenarContinentes();
    void aggConexion(int pais, int vecino);
    void cargarConexiones(std::string archivo);
    bool tableroLleno();
    bool paisLleno(int id);
    void ocuparPais(int id, int idPais, int unidades);
    Carta obtenerCarta(int idPais);
    void ubicarUnidades(bool& inicializado, int numUnidades);
    void mostrarInicializacion();

    //funciones relacionadas a atacar
    bool paisExiste(int idP);
    bool jugadorOcupaPais(int idJ, int idP);
    bool paisVecino(int paisOrigen, int paisDestino);
    bool paisAtacable(int idJ, int idP);
    bool puedeAtacar(int posJ);
    bool origenAptoParaAtaque(int posJ, int idP);
    void elegirUbicacionAtaque(int posJug, int * paisOrigen, int * paisDestino);
    int buscarAtacado(int idP);
    int lanzarDados(int numDados);
    bool quitarUnidad(int idP);
    void atacar(int posAtacante, int origen, int destino);

    //funciones relacionadas al reclamo de cartas y ubicacion de nuevas unidades
    bool puedeUbicar(int idJ);
    void ubicarNuevasUnidades(int posJ, int gana, bool propias);
    int calcularPaises(int idJ);
    void intercambioNormal(int posJ);
    void intercambioPorPaises(int posJ);
    bool intercambioPorCartasCondicionales(int posJ);
    void elegirCartasIntercambio(int posJ, std::string figura, bool mismas);
    bool ubicarUnidadesDeCartas(std::string figura, int posJ, int gana, bool mismas);
    bool intercambiarCartas(int posJ, int gana);

    //funciones relacionadas a fortificar territorio
    bool unidadesSuficientes(int posJ, int idP, int unidades);
    bool paisFortificable(int idJ, int idP);
    bool puedeFortificar(int posJ);
    bool aptoParaFortificar(int idP, int posJ);
    void moverUnidades(int posJ, int origen, int destino, int unidadesM);
    void fortificarTerritorio(int jugadorIndex);

    //funciones relacionadas a terminacion del juego y salida de jugadores
    bool jugadorVigente(int posJ);
    bool finalizado(int * ganador);

};
#endif //RISK_PARTIDA_H

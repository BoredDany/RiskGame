//
// Created by Estudiante on 25/08/2023.
//

#ifndef RISK_PARTIDA_H
#define RISK_PARTIDA_H

#include "Continente.h"
#include "Carta.h"
#include "Jugador.h"
#include "Grafo.h"
#include<list>
#include<vector>

class Partida{
private:
    int id;
    std::vector<Jugador> jugadores;
    std::list<Carta> cartas;
    std::list<Continente> tablero;
    Grafo grafo;
public:
    //consrtructores
    Partida(int id);
    //getters
    std::vector<Jugador> get_jugadores();
    std::list<Carta> get_cartas();
    std::list<Continente> get_tablero();
    Grafo get_grafo();
    //setters
    void set_id(int id);

    //operaciones de inicicialización del juego
    void aggJugador(Jugador j);
    void cargarCartas(std::string archivo_cartas);
    void asignarUnidades();
    void inicializarJugadores();
    bool buscarColorRepetido (std::string color);
    void inicializarTablero();
    bool repetido(std::string nombre);
    void llenarContinentes();
    void cargarConexiones(std::string archivo);
    void aggConexion(int pais, int vecino);
    void ubicarUnidades(bool& inicializado, int numUnidades);
    void mostrarInicializacion();

    //funciones relacionadas a atacar
    bool paisLleno(int id);
    void ocuparPais(int id, int idPais, int unidades);
    Carta obtenerCarta(int idPais);
    bool tableroLleno();
    void elegirUbicacionAtaque(int posJug, int * paisOrigen, int * paisDestino);
    bool puedeAtacar(int posJ);
    bool paisExiste(int idP);
    bool origenAptoParaAtaque(int posJ, int idP);
    bool paisAtacable(int idJ, int idP);
    bool paisVecino(int paisOrigen, int paisDestino);
    bool jugadorOcupaPais(int idJ, int idP);
    int buscarAtacado(int idP);
    void atacar(int posAtacante, int origen, int destino);
    int lanzarDados(int numDados);
    bool quitarUnidad(int idP);

    //operaciones de ubicacion de unidades
    bool paisFortificable(int idJ, int idP);
    void intercambioNormal(int posJ);
    int calcularPaises(int idJ);
    bool puedeUbicar(int idJ);
    void ubicarNuevasUnidades(int posJ, int gana, bool propias);
    void intercambioPorPaises(int posJ);
    bool intercambioPorCartasCondicionales(int posJ);
    void elegirCartasIntercambio(int posJ, std::string figura, bool mismas);
    bool intercambiarCartas(int posJ, int gana);
    bool ubicarUnidadesDeCartas(std::string figura, int posJ, int gana, bool mismas);

    //operaciones de fortificación
    bool puedeFortificar(int posJ);
    void fortificarTerritorio(int jugadorIndex);
    bool aptoParaFortificar(int idP, int posJ);
    bool unidadesSuficientes(int posJ, int idP, int unidades);
    void moverUnidades(int posJ, int origen, int destino, int unidadesM);

    //operaciones de terminación del juego
    bool jugadorVigente(int posJ);
    bool finalizado(int * ganador);

};
#endif //RISK_PARTIDA_H

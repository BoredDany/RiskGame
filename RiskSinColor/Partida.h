//
// Created by Estudiante on 25/08/2023.
//

#ifndef RISK_PARTIDA_H
#define RISK_PARTIDA_H

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
    Grafo grafo;
public:
    //consrtructores
    Partida(int id, Grafo g);

    //getters
    std::vector<Jugador> get_jugadores();
    std::list<Carta> get_cartas();
    Grafo get_grafo();

    //setters
    void set_id(int id);

    //operaciones de inicicialización del juego
    void ocupar(int idJugador, int idPais, int unidades);
    void aggJugador(Jugador j);
    void cargarTablero(std::string archivo_cartas);
    void asignarUnidades();
    void inicializarJugadores();
    bool buscarColorRepetido (std::string color);
    void cargarConexiones(std::string archivo);
    void ubicarUnidades(bool& inicializado, int numUnidades);
    void mostrarInicializacion();

    //funciones relacionadas a atacar
    Carta obtenerCarta(int idPais);
    void elegirUbicacionAtaque(int posJug, int * paisOrigen, int * paisDestino);
    int buscarAtacado(int idP);
    void atacar(int posAtacante, int origen, int destino);
    int lanzarDados(int numDados);

    //operaciones de ubicacion de unidades
    void intercambioNormal(int posJ);
    void ubicarNuevasUnidades(int posJ, int gana, bool propias);
    void intercambioPorPaises(int posJ);
    bool intercambioPorCartasCondicionales(int posJ);
    void elegirCartasIntercambio(int posJ, std::string figura, bool mismas);
    bool intercambiarCartas(int posJ, int gana);
    bool ubicarUnidadesDeCartas(std::string figura, int posJ, int gana, bool mismas);

    //operaciones de fortificación
    void fortificarTerritorio(int jugadorIndex);

    //operaciones de terminación del juego
    bool jugadorVigente(int posJ);
    bool finalizado(int * ganador);

};
#endif //RISK_PARTIDA_H

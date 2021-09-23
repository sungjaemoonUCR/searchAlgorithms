#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <map>

#include "a_star.h"

using namespace ia;

constexpr int OESTE = 0;
constexpr int ESTE = 1;

using Estado = std::array<std::array<char, 4>, 2>;
std::map<Estado, Nodo<Estado>*> ESTADOS_CONOCIDOS;

class NodoRio : public Nodo<Estado>
{
public:
    NodoRio(Estado estado) : Nodo<Estado>(estado) {}

    ListaAdyacencia<Estado> obtener_vecinos() const override
    {
        ListaAdyacencia<Estado> vecinos;

        vecinos = analizar_posibles_vecinos(_estado);
        return vecinos;
    }

    friend std::ostream& operator<<(std::ostream& out_stream, const NodoRio& nodo)
    {
        auto estado = nodo.obtener_estado();
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 4; j++)
            {
                out_stream << estado[i][j] << ' ';
            }
            out_stream << ' ';
            out_stream << ' ';
            out_stream << ' ';
        }
        return out_stream;
    }

private:

    int letra_a_posicion(char letra) const //convierte la letra del compañero a su respectiva posición
    {
        switch (letra)
        {
        case 'P':
            return 1;
        case 'C':
            return 2;
        case 'R':
            return 3;
        case 'S':
            return 4;
        default:
            return 0;
        }
    }

    Estado realizar_movimiento_acompanado(Estado estado, char companero) const
    {
        int posicion_companero = letra_a_posicion(companero);

        if(estado[OESTE][posicion_companero] == companero) //si están en el oeste
        {
            estado[ESTE][0] = 'K';
            estado[ESTE][posicion_companero] = companero;
            estado[OESTE][0] = '_';
            estado[OESTE][posicion_companero] = '_';
        } else if (estado[ESTE][posicion_companero] == companero) //si están en el este
        {
            estado[OESTE][0] = 'K';
            estado[OESTE][posicion_companero] = companero;
            estado[ESTE][0] = '_';
            estado[ESTE][posicion_companero] = '_';
        }

        return estado;
    }

    Estado realizar_movimiento_solo(Estado estado) const
    {
        if(estado[OESTE][0] == 'K') //si campesino está en el oeste
        {
            estado[ESTE][0] = 'K';
            estado[OESTE][0] = '_';
        } else if(estado[ESTE][0] == 'K') //si campesino está en el este
        {
            estado[OESTE][0] = 'K';
            estado[ESTE][0] = '_';
        }

        return estado;
    }

    bool analizar_caso_invalido(Estado posible_estado) const
    {
        if(posible_estado[OESTE][0] == '_' && posible_estado[OESTE][1] == 'P' && posible_estado[OESTE][2] == 'C') //perro solo con conejo (oeste)
            return false;
        if(posible_estado[OESTE][0] == '_' && posible_estado[OESTE][2] == 'C' && posible_estado[OESTE][3] == 'R') //conejo solo con repollo (oeste)
            return false;
        if(posible_estado[ESTE][0] == '_' && posible_estado[ESTE][1] == 'P' && posible_estado[ESTE][2] == 'C') //perro solo con conejo (este)
            return false;
        if(posible_estado[ESTE][0] == '_' && posible_estado[ESTE][2] == 'C' && posible_estado[ESTE][3] == 'R') //conejo solo con repollo (este)
            return false;
        if (posible_estado[ESTE][0] == '_' && posible_estado[ESTE][1] == 'P' && posible_estado[ESTE][2] == 'C' && posible_estado[ESTE][3] == 'R') //los 3 sin el campesino(este)
            return false;
        if (posible_estado[OESTE][0] == '_' && posible_estado[OESTE][1] == 'P' && posible_estado[OESTE][2] == 'C' && posible_estado[OESTE][3] == 'R') //los 3 sin el campesino (oeste)
            return false;
        
        return true;
    }

    bool movimiento_valido(Estado estado, char companero) const
    {
        Estado posible_estado;

        if(companero == 'S'){ //si el campesino viaja solo
            posible_estado = realizar_movimiento_solo(estado);
            return analizar_caso_invalido(posible_estado);
        } else {
            int posicion_companero = letra_a_posicion(companero);

            //Reviso si ambos se encuentran en el mismo lado del río, ya que si no es así
            //no podría realizar el movimiento
            if(estado[OESTE][0] == 'K' && estado[OESTE][posicion_companero] == companero){ 
                posible_estado = realizar_movimiento_acompanado(estado, companero);
                return analizar_caso_invalido(posible_estado);
            } else if(estado[ESTE][0] == 'K' && estado[ESTE][posicion_companero] == companero){
                posible_estado = realizar_movimiento_acompanado(estado, companero);
                return analizar_caso_invalido(posible_estado);
            } else {
                return false;
            }
        }
    }

    Nodo<Estado>* analizar_movimiento(Estado estado, char companero) const
    {
        if(movimiento_valido(estado, companero))
        {
            Estado nuevo_estado;
            if(companero == 'S'){ //si el campesino viaja solo
                nuevo_estado = realizar_movimiento_solo(estado);
            } else {
                nuevo_estado = realizar_movimiento_acompanado(estado, companero);
            }

            auto estado_vecino = ESTADOS_CONOCIDOS.find(nuevo_estado);
            if(estado_vecino == ESTADOS_CONOCIDOS.end()){
                auto resultado = ESTADOS_CONOCIDOS.insert({nuevo_estado, new NodoRio(nuevo_estado)});
                estado_vecino = resultado.first;
            }

            return estado_vecino->second;
        }

        return nullptr;
    }

    ListaAdyacencia<Estado> analizar_posibles_vecinos(Estado estado) const
    {
        ListaAdyacencia<Estado> vecinos;

        auto e1 = analizar_movimiento(estado, (char)'P');
        auto e2 = analizar_movimiento(estado, (char)'C');
        auto e3 = analizar_movimiento(estado, (char)'R');
        auto e4 = analizar_movimiento(estado, (char)'S'); //significa que el campesino (K) viaja solo

        if(e1 != nullptr)
            vecinos.push_back({1, e1});
        if(e2 != nullptr)
            vecinos.push_back({1, e2});
        if(e3 != nullptr)
            vecinos.push_back({1, e3});
        if(e4 != nullptr)
            vecinos.push_back({1, e4});

        return vecinos;
    }
};

int main()
{
    NodoRio* nodoFuente = new NodoRio(
        Estado{ {
            {'_', '_', '_', '_'},
            {'K', 'P', 'C', 'R'}
        }}
    );

    NodoRio* nodoDestino = new NodoRio(
        Estado{{
            {'K', 'P', 'C', 'R'},
            {'_', '_', '_', '_'},
        }}
    );

    ESTADOS_CONOCIDOS.insert({ nodoFuente->obtener_estado(), nodoFuente});
    ESTADOS_CONOCIDOS.insert({ nodoDestino->obtener_estado(), nodoDestino});

    auto camino = resolver_a_star(nodoFuente, nodoDestino, heuristica_dijkstra<Estado>);

    std::cout << "Camino:\n";
    for(const auto& nodo : camino){
        std::cout << *dynamic_cast<NodoRio*>(nodo) << '\n' << '\n';
    }

    for(const auto& pair : ESTADOS_CONOCIDOS){
        delete pair.second;
    }
}

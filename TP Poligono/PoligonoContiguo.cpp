#include<array>
#include<cmath>
#include<cassert>
using std::array;

struct Punto{
    double x,y;
};

struct Poligono{
    array<Punto,100> puntos;
    unsigned n{};
};

// Prototipos de funciones

double GetDistancia(const Punto&, const Punto&);                    //Obtiene la distancia entre dos puntos

double Absoluto(double);                                            //Valor absoluto

double GetPerimetro(const Poligono&);                               //Obtiene el perimetro 

bool AreNear(const double&, const double&, const double = 0.01);    //Compara doubles con esta funcion ya que los doubles no tienen presición exacta

unsigned GetCantidadDeLados(const Poligono&);                       //Obtiene la cantidad de lados del poligono

int GetPosicionPorPunto(const Poligono&, const Punto&);             //Dado un punto se muestra la posición

Punto Top(const Poligono&);                                         //TOP muestra el ultimo punto

Punto First(const Poligono&);                                       //FIRST muestra el primer punto

Punto GetPuntoPorPosicion(const Poligono&, unsigned);               //Dada una posición se muestra el punto

Poligono& Push(Poligono&, const Punto);                             //PUSH agrega un punto al final del poligono

Poligono& Pop (Poligono&);                                          //POP elimina el ultimo punto del poligono

Poligono& Add(Poligono&, const Punto&, unsigned);                   //Dada una posición se agrega un punto

Poligono& RemovePorPunto(Poligono&, const Punto);                   //Dado un punto, este se elimina

Poligono& RemovePorPosicion(Poligono&, unsigned);                   //Dada una posición se elimina un punto


int main(){

// Poligono de ejemplo
    Poligono r{{{{0, 0}, {2, 0}, {2, 2}, {0, 2}}}, 4};

    // Se realizan pruebas con las funciones
    assert(AreNear(GetPerimetro(r), 8.0));
    assert(GetCantidadDeLados(r) == 4);
    assert(Top(r).x == 0 and Top(r).y == 2);
    assert(First(r).x == 0 and First(r).y == 0);

    Pop(r);
    assert(AreNear(GetPerimetro(r), 6.0));
    assert(GetCantidadDeLados(r) == 3);
    assert(Top(r).x == 2 and Top(r).y == 0);

    Push(r, {0, 2});
    assert(AreNear(GetPerimetro(r), 8.0));
    assert(GetCantidadDeLados(r) == 4);
    assert(Top(r).x == 0 and Top(r).y == 2);

    assert(GetPuntoPorPosicion(r, 2).x == 2 and GetPuntoPorPosicion(r, 2).y == 0);
    RemovePorPunto(r, {2, 0});
    assert(GetPuntoPorPosicion(r, 2).x == 2 and GetPuntoPorPosicion(r, 2).y == 2);

    assert(GetCantidadDeLados(r) == 3);
    Add(r, {1, 1}, 3);
    Add(r, {3, 1}, 4);
    assert(GetCantidadDeLados(r) == 4);

    assert(GetPuntoPorPosicion(r, 1).x == 0 and GetPuntoPorPosicion(r, 1).y == 0);
    assert(GetPuntoPorPosicion(r, 2).x == 0 and GetPuntoPorPosicion(r, 2).y == 2);
    assert(GetPuntoPorPosicion(r, 3).x == 1 and GetPuntoPorPosicion(r, 3).y == 1);
    assert(GetPuntoPorPosicion(r, 4).x == 3 and GetPuntoPorPosicion(r, 4).y == 1);

    assert(GetPosicionPorPunto(r, {0, 0}) == 1);
    assert(GetPosicionPorPunto(r, {0, 2}) == 2);
    assert(GetPosicionPorPunto(r, {1, 1}) == 3);
    assert(GetPosicionPorPunto(r, {3, 1}) == 4);

    return 0;
}

// Desarrollo de funciones

double GetDistancia(const Punto& punto1, const Punto& punto2){                                      
    return (std::sqrt(std::pow(punto2.x - punto1.x, 2) + std::pow(punto2.y - punto1.y, 2)));
}

double Absoluto(double x){
    return (x>0) ? x : -x;
}

double GetPerimetro(const Poligono& poligono){
    double perimetro {};

    for(unsigned i{}; i < poligono.n - 1; i++)
        perimetro += GetDistancia(poligono.puntos.at(i), poligono.puntos.at(i + 1));

    perimetro += GetDistancia(poligono.puntos.at((poligono.n) - 1), poligono.puntos.at(0));

    return perimetro;
}

bool AreNear(const double a, const double b, const double tolerance){                         
    return Absoluto(a-b) < tolerance;
}

/*bool AreNear(const double a, const double b, const double delta){
    return (a - delta) <= b and (a + delta) >= b;
}*/


unsigned GetCantidadDeLados(const Poligono& poligono){
    return poligono.n;
}

int GetPosicionPorPunto(const Poligono& poligono, const Punto& punto){
    for(unsigned i{}; i<poligono.n; i++){
        if(poligono.puntos.at(i).x == punto.x and poligono.puntos.at(i).y == punto.y){
            return i+1;
        }
    }
    return -1;
}

Punto Top(const Poligono& poligono){
    return poligono.puntos.at(poligono.n-1);
}

Punto First(const Poligono& poligono){
    return poligono.puntos.at(0);
}

Punto GetPuntoPorPosicion (const Poligono& poligono, unsigned pos){
    return poligono.puntos.at(pos-1);
}

Poligono& Push(Poligono& poligono, const Punto nuevoPunto){
    if(poligono.n < poligono.puntos.size()){
        poligono.puntos.at(poligono.n) = nuevoPunto;
        poligono.n++;
    }
    return poligono;
}

Poligono& Pop(Poligono& poligono){
    if(poligono.n > 0){
        poligono.n--;
    }
    return poligono;
}

Poligono& Add(Poligono& poligono, const Punto& punto, unsigned pos) {
    if (poligono.n < poligono.puntos.size()) {
        for (unsigned i=poligono.n; i > pos; i--) {
            poligono.puntos.at(i) = poligono.puntos.at(i-1);
        }
            poligono.puntos.at(pos-1) = punto;
            poligono.n++;
        return poligono;
    }
    return poligono;
}

Poligono& RemovePorPunto(Poligono& poligono, const Punto puntoToRemove){
    for(unsigned i{}; i<poligono.n; i++){
        if(poligono.puntos.at(i).x == puntoToRemove.x and poligono.puntos.at(i).y == puntoToRemove.y){
            for(unsigned j=i; j<poligono.n; j++){
                poligono.puntos.at(j) = poligono.puntos.at(j+1);
            }
            poligono.n--;
            return poligono;
        }
    }
    return poligono;
}

Poligono& RemovePorPosicion(Poligono& poligono, unsigned pos) {
    for (unsigned i{}; i < poligono.n; i++) {
        if (i == pos-1) {
            for (unsigned j = i; j < poligono.n; j++) {
                poligono.puntos.at(j) = poligono.puntos.at(j + 1);
            }
            poligono.n--;
            return poligono;
        }
    }
    return poligono;
}
























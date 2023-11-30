#include <iostream>
#include <vector>

// Prototipos
void getPyO(const std::vector<double>& x, const std::vector<double>& y, double& pendiente, double& ordenada);

double getS(const std::vector<double>& x, const std::vector<double>& y, double pendiente, double ordenada);

void calcularSxxSyySxy(const std::vector<double>& x, const std::vector<double>& y, double& sxx, double& syy, double& sxy);

double getR2(const std::vector<double>& x, const std::vector<double>& y, double& pendiente, double& ordenada);
/*-----------------------------------------------------------------------------------------------------------------*/

int main(){
//Ejercicio 15 de ejemplo
std::vector<double> X = {60.0 , 63.0 , 70.0 , 80.0 , 90.0 , 94.0 , 100.0};
std::vector<double> Y = {1.0 , 0.0 , 4.0 , 3.0 , 5.0 , 8.0 , 7.0 , 6.0};

//Almacenamiento de pendiente y ordenada
double pendiente, ordenada;

//Calcular pendiente y ordenada
getPyO (X,Y,pendiente,ordenada);

//Calcular coef de determinación (R^2)
double R2 = getR2(X,Y,pendiente,ordenada);

//Calcular S
double s = getS (X,Y,pendiente,ordenada);

//Mostrar resultados
std::cout << "Pendiente: " << pendiente << std::endl;
std::cout << "Ordenada al origen: " << ordenada << std::endl;
std::cout << "Coeficiente de determinación (R^2): " << R2 << std::endl;
std::cout << "S: "<< s <<std::endl;
}

/*--------------------------------------------------------------------------------------------------------------------------------*/

// 1) Función para calcular la pendiente y la ordenada al origen
void getPyO(const std::vector<double>& x, const std::vector<double>& y, double& pendiente, double& ordenada) {

    if (x.size() < 2 || y.size() < 2 || x.size() != y.size()) {     //Verifica si son 2 o mas puntos y si la cantidad de datos n_x es igual a la cantidad de datos n_y.                                                                 
        return;
    }

    // Calculo sumatorias necesarias
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0, sumY2 = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
        sumY2 += y[i] * y[i];
    }

    // Calcular la pendiente
    pendiente = (x.size() * sumXY - sumX * sumY) / (x.size() * sumX2 - sumX * sumX);

    // Calcular la ordenada al origen
    ordenada = (sumY - pendiente * sumX) / x.size();
}

/*---------------------------------------------------------------------------------------------------------------------------*/

// 2) Función para calcular el valor de S (suma de los cuadrados de las diferencias)
double getS(const std::vector<double>& x, const std::vector<double>& y, double pendiente, double ordenada) {
    double s = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        double z = pendiente * x[i] + ordenada;
        s += (y[i] - z) * (y[i] - z);                                   //z es una variable de almacenamiento
    }

    return s;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

// 3) Función para calcular Sxx, Syy, y Sxy
void calcularSxxSyySxy(const std::vector<double>& x, const std::vector<double>& y, double& sxx, double& syy, double& sxy) {
    sxx = 0.0;
    syy = 0.0;
    sxy = 0.0;

    // Calcular sumatorias necesarias
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0, sumY2 = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
        sumY2 += y[i] * y[i];
    }

    // Calcular Sxx, Syy y Sxy
    sxx = sumX2 - (sumX * sumX) / x.size();
    syy = sumY2 - (sumY * sumY) / x.size();
    sxy = sumXY - (sumX * sumY) / x.size();
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/


// 4) Función para calcular el coeficiente de determinación (R^2)
double getR2( const std::vector<double>& x, const std::vector<double>& y, double& pendiente, double& ordenada){

    double sst= 0.0;    //suma de los cuadrados totales.
    double ssr= 0.0;    //suma de los cuadrados de la regresión.
    
      // Calculo sumatorias necesarias
    double sumY = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        sumY += y[i];
    }

    //Calculo de sst y ssr

    double w = sumY / y.size(); //promedio

        for(size_t i = 0; i < y.size(); ++i){

            double z = pendiente * x[i] + ordenada;   //z es una variable de almacenamiento
            sst += (y[i]-w) * (y[i]-w);
            ssr += (y[i]-z) * (y[i]-z);
        }
    //Calculo de R^2
    
    double R2 = 1 - (sst/ssr);

    return R2; 
}

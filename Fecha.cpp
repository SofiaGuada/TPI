#include <iostream>
#include <ctime>
#include "Fecha.h"
using namespace std;

Fecha::Fecha()
 : _dia(1),_mes(1),_anio(2000){ ///obligatorio para composicion
}

Fecha::Fecha(int dia, int mes, int anio){
   setDia(dia);
   setMes(mes);
   setAnio(anio);
}

int Fecha::getDia(){
   return _dia;
}

int Fecha::getMes(){
   return _mes;
}

int Fecha::getAnio(){
   return _anio;
}

void Fecha::setDia(int dia){
    if(dia>=1 && dia <=31){
     _dia=dia;
    }
     else {
         cout<<"DIA INVALIDO "<<endl;
     }
}

void Fecha::setMes(int mes){
    if(mes>=1 && mes<=12){
     _mes=mes;
}
else {
    cout<<"MES INVALIDO "<<endl;
}
}

void Fecha::setAnio(int anio){
    if(anio>2000){
    _anio=anio;
}
else {
    cout<<"ANIO INVALIDO "<<endl;
}
}

bool Fecha::validarFecha(int dia, int mes, int anio) {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasMes[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if (mes == 2 && Bisiesto(anio))
        return dia <= 29;

    return dia <= diasMes[mes];
}

void Fecha::cargarFecha(){
int dia,mes,anio;
     while (true) {
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
        if (validarFecha(dia,mes,anio)) {
            _dia = dia;
            _mes = mes;
            _anio = anio;
            break;
        }

        cout << "FECHA INVALIDA. VUELVA A INTENTAR." << endl;
    }
}

void Fecha::mostrarFecha(){
    cout<<_dia<<"/"<<_mes<<"/"<<_anio<<endl;
}

//void Fecha::cargarFechaActual() {
//    time_t t = time(nullptr);
//    tm* now = localtime(&t);
//
//    _dia = now->tm_mday;
//    _mes = now->tm_mon + 1;
//    _anio = now->tm_year + 1900;
//}


bool Fecha::operator>(Fecha& f2) {
    if (_anio > f2.getAnio()) return true;
    if (_anio < f2.getAnio()) return false;

    if (_mes > f2.getMes()) return true;
    if (_mes < f2.getMes()) return false;

    if (_dia > f2.getDia()) return true;
    return false;
}


//bool Fecha::operator<(Fecha& f2) {
//    if (_anio < f2.getAnio()) return true;
//    if (_anio > f2.getAnio()) return false;
//
//    if (_mes < f2.getMes()) return true;
//    if (_mes > f2.getMes()) return false;
//
//    return _dia < f2.getDia();
//}
bool Fecha::operator==(Fecha& f2) {
    if (_anio == f2.getAnio()&&_mes==f2.getMes()&&_dia==f2.getDia()){return true;}

    return false;
}


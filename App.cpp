#include <iostream>
#include "App.h"
using namespace std;

App::App(){
  _cantidadOpciones = 3;
}
void App::run(){
  int opcion;

  do{
    system("cls");
    opcion = seleccionOpcion();
    system("cls");
    ejecutarOpcion(opcion);
  }while(opcion != 0);
}

void App::mostrarOpciones(){
    cout<< "============================"<<endl;
    cout<< "|    GESTION DE EVENTOS    |"<<endl;
    cout<< "============================"<<endl;
    cout<< "|  1- CLIENTES             |"<<endl;
    cout<< "|  2- EVENTOS              |"<<endl;
    cout<< "|  3- PAGOS                |"<<endl;
    cout<< "----------------------------"<<endl;
    cout<< "|  0- SALIR                |"<<endl;
    cout<< "============================"<<endl;
}

int App::seleccionOpcion(){
  int opcion;
  mostrarOpciones();
  cout << "OPCION: ";
  cin >> opcion;

  while(opcion < 0 || opcion > _cantidadOpciones){
    cout << "OPCION INCORRECTAS..."<<endl;
    cout << "OPCION: ";
    cin >> opcion;
  }
  return opcion;
}

void App::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
      _menuClientes.mostrar();
  break;
  case 2:
      _menuEventos.mostrar();
    break;
  case 3:
     _menuPagos.mostrar();
    break;

  case 0:
    cout << "GRACIAS POR UTILIZAR MI APP " << endl;
    break;
  }
}

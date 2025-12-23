#include <iostream>
#include "MenuClientes.h"
using namespace std;

MenuClientes::MenuClientes()
{
   _cantidadOpciones=7;
}

void MenuClientes::mostrar(){
   int opcion;

   do{
    system("cls");
    opcion=seleccionarOpcion();
    system("cls");
    ejecutarOpcion(opcion);
    system("pause");

   }while (opcion!=0);

}
void MenuClientes::mostrarOpciones(){
   cout<<"============================="<<endl;
   cout<<"    MENU CLIENTES     "<<endl;
   cout<<"============================="<<endl;
   cout<<"1. CARGAR CLIENTE"<<endl;
   cout<<"2. MOSTRAR CLIENTE "<<endl;
   cout<<"3. BUSCAR CLIENTE "<<endl;
   cout<<"4. MODIFICAR CLIENTE "<<endl;
   cout<<"5. ORDENADO ALFABETICAMENTE "<<endl;
   cout<<"6. ELIMINAR "<<endl;
   cout<<"7. VOLVER A ACTIVAR CLIENTE "<<endl;
   cout<<"-----------------------------"<<endl;
   cout<<"0. SALIR "<<endl;

}
int MenuClientes::seleccionarOpcion(){
    int opcion;
   mostrarOpciones();
   cout<<"============================="<<endl;
   cout<<"OPCION: ";
   cin>>opcion;

   while(opcion<0|| opcion>_cantidadOpciones){
    cout<<"OPCION INCORRECTA...."<<endl;
       cout<<"OPCION: ";
       cin>>opcion;

   }
   return opcion;
}
void MenuClientes::ejecutarOpcion(int opcion){
    switch(opcion){
case 1:
    _managerCliente.CargarCliente();
    break;
 case 2:
     _managerCliente.ListarClientes();
    break;
case 3:
    _managerCliente.buscarClientes();
    break;
case 4:
    _managerCliente.modificarClientes();
    break;
case 5:
    _managerCliente.ordanadosAlfabeticamente();
    break;
case 6:
    system("cls");
    _managerCliente.eliminar();
    break;
case 7:
    _managerCliente.ActivarCliente();
    break;
case 0:
    cout<<"----------------------------------"<<endl;
    break;
    default:
        cout<<"INGRESASTE UNA OPCION INVALIDA, VUELVE A INTENTARLO!"<<endl;
    break;
    }
}

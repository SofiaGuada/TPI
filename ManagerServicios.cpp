#include <iostream>
#include <iomanip>///libreria para usar los decimales
#include "ManagerServicios.h"
#include "Necesario.h"
using namespace std;

ManagerServicios::ManagerServicios()
{
    //ctor
}

void ManagerServicios::cargarServicios(){
    int idS;
    string nombre,proveedor,descripcion;
    float costo;
    bool eliminado=false;

    idS=_repo.getNuevoIdServicio();
    cout<<"ID SERVICIOS: #"<<idS<<endl;

    cout<<"NOMBRE DE SERVICIO: ";
    nombre=cargarCadena();
        while(nombre==""){
        cout<<"NO PUEDE ESTAR VACIO "<<endl;
        cout<<"INGRESE NUEVAMENTE: ";
       nombre=cargarCadena();
    }

    cout<<"DESCRIPCION: ";
    descripcion=cargarCadena();
        while (descripcion==""){
            cout<<"NO PUEDE ESTAR VACIO "<<endl;
            cout<<"INGRESE NUEVAMENTE: ";
           descripcion=cargarCadena();
        }

    cout<<"PROVEEDOR: ";
    proveedor=cargarCadena();
        while (proveedor == ""){
        cout<<"NO PUEDE ESTAR VACIO "<<endl;
        cout<<"INGRESE NUEVAMENTE: ";
        proveedor=cargarCadena();
    }
    cout<<"PRECIO: $";
         while (true){
          if(!(cin>>costo)) {
            cout << "ERROR: Debe ingresar un numero valido "<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"INTENTE NUEVAMENTE: $";
            continue;
        }
    if(costo<=0){
        cout<<"EL PRECIO DEBE SER MAYOR A 0 "<<endl;
        cout<<"INTENTE NUEVAMENTE: $";
        continue;
    }
    break;
     }
    system("pause");
    system ("cls");

    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"ID: #"<<idS<<endl;
    cout<<"NOMBRE DE SERVICIO: "<<nombre<<endl;
    cout<<"DESCRIPCION: "<<descripcion<<endl;
    cout<<"PROVEEDOR: "<<proveedor<<endl;
    cout<<"PRECIO: $"<<costo<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  int opcion;
  cout<<"CONFIRMAR ? (1-Si / 0-No): ";
  cin>>opcion;

  while (opcion!=0 && opcion!=1){
    cout<<"OPCION INVALIDA, INGRESE (1.Si / 0.No): ";
    cin>>opcion;
  }
  if(opcion==0){
    cout<<"REGISTRO CANCELADO "<<endl;
    return;
  }
 Servicios servis(idS,nombre,descripcion,proveedor,costo,eliminado);

 if(_repo.guardar(servis)){
    cout<<"SERVICIO GUARDADO CORRECTAMENTE "<<endl;
 }
 else {
    cout<<"ERROR AL GUARDAR EL SERVICIO "<<endl;
 }
}

void ManagerServicios::mostrarServicios(Servicios servis){
    cout<<"ID SERVICIOS: #"<<servis.getIdServicio()<<endl;
    cout<<"TIPO DE SERVICIO: "<<servis.getNombreServicio()<<endl;
    cout<<"DESCRIPCION: "<<servis.getDescripcion()<<endl;
    cout<<"PROVEEDOR: "<<servis.getProveedor()<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"PRECIO: $"<<servis.getPrecio()<<endl;
    if(servis.getEliminado()){
        cout<<"ESTE SERVICIOS FUE ELIMINADO "<<endl;
    }
}

void ManagerServicios::listarServicios(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;
  for (int i = 0; i < cantidad; i++){
    Servicios servis = _repo.leer(i);
    if(!servis.getEliminado()){
    mostrarServicios(servis);
    encontrado=true;
    cout << "--------------------------" << endl;
//    system("pause");
//    system("cls");
  }
}
  if(!encontrado){
    cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
  }
}

void ManagerServicios::buscarIdServicios(){
    int idServicio;
    cout<<"BUSCAR EL SERVICIO POR ID "<<endl;
    cout<<"INGRESAR ID SERVICIOS: # (0 para cancelar):";
    while(true){
      if(!(cin>>idServicio)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(idServicio<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        continue;
    }
    if(idServicio==0){
        return;
    }

    break;
}
    cin.ignore();

    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    for (int i=0; i<cantidad; i++) {
        Servicios s = _repo.leer(i);
        if(s.getIdServicio() == idServicio){
            cout<<"-----SERVICIOS ENCONTRADO-----"<<endl;
            mostrarServicios(s);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
    }
    if(!encontrado) {
        cout<<"NO SE ENCONTRO EL SERVICIO "<<endl;
    }
}

void ManagerServicios::serviciosXproveedor(){
    int cantidad=_repo.getCantidadRegistros();
     if(cantidad==0){
        cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
        return;
     }

     string proveedor;
     cout<<"INGRESE PROVEEDOR: ";
     proveedor=cargarCadena();
     while (proveedor == "") {
        cout<<"NO PUEDE ESTAR VACIO."<<endl;
        cout<<"INGRESE NUEVAMENTE: ";
        proveedor=cargarCadena();
    }
    system("pause");
    system("cls");

     bool encontrado=false;
     for(int i=0;i<cantidad;i++){
        Servicios servi=_repo.leer(i);
        if(!servi.getEliminado()&&servi.getProveedor()==proveedor){
            cout<<"ID: #"<<servi.getIdServicio()<<" "<<servi.getNombreServicio()<<endl;
            cout<<"DESCRIPCION: "<<servi.getDescripcion()<<endl;
            cout<<" ($"<<servi.getPrecio()<<") "<<endl;
            encontrado=true;
        }
     }
     if(!encontrado){
        cout<<"NO HAY SERVICIOS CON ESE PROVEEDOR "<<endl;
     }
}



void ManagerServicios::eliminar(){
  int opcion;
  do{
  system("cls");
  cout<<"------------------------------"<<endl;
  cout<<"1. ELIMINAR SERVICIOS "<<endl;
  cout<<"2. MOSTRAR SERVICIOS ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"OPCION: ";
  cin>>opcion;
  cout<<"------------------------------"<<endl;
  system("cls");
  switch(opcion){
  case 1:
      eliminarServicios();
      break;
  case 2:
    MostrarServiciosEliminados();
    break;
  case 0:
    return;
default:
    cout<<"Opcion Invalida, Intente Nuevamente "<<endl;
    break;
   }
   system("pause");
  }while(opcion!=0);
}

void ManagerServicios::eliminarServicios(){
   int idServicio,pos;
   Servicios servis;
   char eliminar;

   cout<<"---SERVICIOS DISPONIBLES---"<<endl;
   ArchivoServicios arcS;
   int cantS=arcS.getCantidadRegistros();
   bool encontrado=false;
   for(int i=0;i<cantS;i++){
    servis=arcS.leer(i);
    if(!servis.getEliminado()){
        cout<<"ID: #"<<servis.getIdServicio()<<" "<<servis.getNombreServicio()<<" ($"<<servis.getPrecio()<<") "<<endl;
        encontrado=true;
    }
   }
   if(!encontrado){
    cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
    return;
   }

   cout<<"---- ELIMINAR SERVICIO ----"<<endl;
   cout<<"INGRESE ID SERVICIO:# (0 para cancelar): ";
   while(true){
    if(!( cin>>idServicio)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
     }
    if(idServicio<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        continue;
    }
    if(idServicio==0){
        return;
    }
    break;
 }
    pos=_repo.buscarIdServicios(idServicio);

   if(pos==-1){
    cout<<"EL SERVICIO NO EXISTE! "<<endl;
    return ;
  }
  servis= _repo.leer(pos);

  cout<<"INFORMACION DEL SERVICIO "<<endl;
  cout<<endl;
  mostrarServicios(servis);

  cout<<endl;
  cout<<"QUIERE ELIMINAR? S/N ";
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){
    servis.setEliminado(true);

  if(_repo.eliminar(pos)){
    cout<<"EL SERVICIO FUE ELIMINADO"<<endl;
  }
  else {
    cout<<"OCURRIO UN ERROR AL ELIMINAR EL SERVICIO "<<endl;
  }
  }
}

void ManagerServicios::MostrarServiciosEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cantidad;i++){
        Servicios servis=_repo.leer(i);
       if(servis.getEliminado()){
        mostrarServicios(servis);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        cout<<"NO HAY SERVICIOS ELIMINADOS "<<endl;
        return;
    }
}

void ManagerServicios::modificarServicio(){
    int id;
    int cantidad=_repo.getCantidadRegistros();
    bool encontrados=false;
    for(int i=0; i<cantidad; i++){
        Servicios servis=_repo.leer(i);
        if(!servis.getEliminado()){
            cout<<"ID: #"<<servis.getIdServicio()<<" "<<servis.getNombreServicio()<<" ($"<<servis.getPrecio()<<") "<<endl;
            encontrados=true;
        }
    }
    if(!encontrados){
        cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
        return;
    }

	cout << "INGRESE EL ID SERVICIO A MODIFICAR:# ";

 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }

    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        continue;
    }
    if(id==0){
        return;
    }
    break;
 }
	int pos = _repo.buscarIdServicios(id);

	if (pos == -1) {
		cout << "SERVICIO NO ENCONTRADO." << endl;
		return;
	}
	Servicios servis = _repo.leer(pos);
	if(!servis.getEliminado()){
	mostrarServicios(servis);
	}

int opcion;
do {
    system("cls");
    cout<<" INGRESE NUEVOS DATOS "<<endl;
    cout<<"1. MODIFICAR EL NOMBRE "<<endl;
    cout<<"2. MODIFICAR DESCRIPCION "<<endl;
    cout<<"3. MODIFICAR PROVEEDOR "<<endl;
    cout<<"4. MODIFICAR PRECIO "<<endl;
    cout<<"0. SALIR Y GUARDAR "<<endl;
    cout<<"OPCION: ";
    cin>>opcion;

    system("cls");
    switch(opcion){
 case 1:{
     string nombre;
     cout<<"NOMBRE ACTUAL: "<<servis.getNombreServicio()<<endl;
     cout<<"NUEVO NOMBRE: ";
     nombre=cargarCadena();
     while (nombre == "") {
        cout << "NO PUEDE ESTAR VACIO."<<endl;
        cout<<"INGRESE NUEVAMENTE: ";
        nombre=cargarCadena();
    }
    servis.setNombreServicio(nombre);
    break;
 }
 case 2: {
     string descripcion;
     cout<<"DESCRIPCION ACTUAL: "<<servis.getDescripcion()<<endl;
     cout<<"NUEVA DESCRIPCION: ";
     descripcion=cargarCadena();
        while (descripcion == "") {
        cout << "NO PUEDE ESTAR VACIO."<<endl;
        cout<<"INGRESE NUEVAMENTE: ";
        descripcion=cargarCadena();
    }
     servis.setDescripcion(descripcion);
 break;
 }
 case 3:{
     string proveedor;
     cout<<"PROVEEDOR ACTUAL: "<<servis.getProveedor()<<endl;
     cout<<"NUEVO PROVEDOR: ";
      proveedor=cargarCadena();
        while (proveedor == "") {
        cout<<"NO PUEDE ESTAR VACIO."<<endl;
        cout<<"INGRESE NUEVAMENTE: ";
        proveedor=cargarCadena();
    }
    servis.setProveedor(proveedor);
 break;
 }
 case 4:{
     float precio;
     cout<<"PRECIO ACTUAL: $"<<servis.getPrecio()<<endl;
     cout<<"NUEVO PRECIO: $";
      while (true) {
        if (!(cin>>precio)) {
            cout<<" Debe ingresar un numero valido. "<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"INTENTE NUEVAMENTE: $";
            continue;
        }
    if(precio<=0){
        cout<<"EL PRECIO DEBE SER MAYOR A 0 "<<endl;
        cout<<"INTENTE NUEVAMENTE: $";
        continue;
    }
    break;
     }
    cout<<fixed<<setprecision(2);
    servis.setPrecio(precio);
 break;
 }
 case 0:
    break;
 default:
     cout<<"Opcion Invalida, Intente Nuevamente "<<endl;
    break;
    }
system("pause");
}while (opcion!=0);

	if (_repo.guardar(pos, servis)) {
		cout << "SERVICIO MODIFICADO CORRECTAMENTE." << endl;
	} else {
		cout << "ERROR AL MODIFICAR EL SERVICIO." << endl;
	}
}

void ManagerServicios::ActivarServicios(){
  int id, pos;
  char activar;

  int cantidad=_repo.getCantidadRegistros();
  bool encontrado=false;
    for(int i=0;i<cantidad;i++){
    Servicios ser=_repo.leer(i);
    if(ser.getEliminado()){
        cout<<"SERVICIOS ELIMINADOS "<<endl;
        cout<<"~ID: #"<<ser.getIdServicio()<<" "<<ser.getNombreServicio()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    cout<<"NO HAY SERVICIOS ELIMINADOS "<<endl;
    return;
  }
  system("pause");
  system("cls");

  cout<<"~~~~ ACTIVAR SERVICIOS ~~~~"<<endl;
  cout<<"ID SERVICIO:# (0 para cancelar): ";
   while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    if(id==0){
        return;
    }
    break;
 }
  pos=_repo.buscarIdServicios(id);
  if(pos==-1){
    cout<<"EL SERVICIO NO EXISTE "<<endl;
    return;
  }

  Servicios servis;
  servis= _repo.leer(pos);

    if(!servis.getEliminado()){
    cout<<"EL SERVICIO NO ESTA ELIMINADO "<<endl;
    cout<<"No es necesario activar "<<endl;
    return;
  }

  cout<<"~~INFORMACION DEL SERVICIO ELIMINADO~~"<<endl;
  cout<<endl;
  mostrarServicios(servis);
  cout<<endl;

  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  cin>>activar;
   if(activar=='s' or activar=='S'){
    servis.setEliminado(false);
   }
   if(_repo.guardar(pos,servis)){
    cout<<"GUARDADO CORRECTAMENTE "<<endl;
   }
   else {
    cout<<"OCURRIO UN ERROR "<<endl;
   }
}

void ManagerServicios::buscar(){
   int opcion;
do {
   system("cls");
   cout<<"~~~~~~~~~~BUSCAR SERVICIOS~~~~~~~~~"<<endl;
   cout<<" 1. BUSCAR POR ID "<<endl;
   cout<<" 2. BUSCAR POR PROVEEDOR "<<endl;
   cout<<" 0. VOLVER AL MENU SERVICIOS "<<endl;
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   cout<<"OPCION: ";
   cin>>opcion;
       system("cls");

   switch(opcion){
case 1:
    buscarIdServicios();
    break;
case 2:
    serviciosXproveedor();
    break;
case 0:
   break;
default:
    cout<<"Opcion invalida, Intenta Nuevamente "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);

}

void ManagerServicios::menuServicios(){
int opcion;
do {
   system("cls");
   cout<<"~~~~~~~~~~~~~~SERVICIOS~~~~~~~~~~~~~"<<endl;
   cout<<" 1. CARGAR "<<endl;
   cout<<" 2. MOSTRAR "<<endl;
   cout<<" 3. MODIFICAR "<<endl;
   cout<<" 4. ELIMINAR "<<endl;
   cout<<" 5. ACTIVAR "<<endl;
   cout<<" 6. BUSCAR SERVICIOS "<<endl;
   cout<<" 0. VOLVER AL MENU EVENTO/SERVICIOS "<<endl;
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   cout<<"OPCION: ";
   cin>>opcion;
       system("cls");

   switch(opcion){
case 1:
    cargarServicios();
    break;
case 2:
    listarServicios();
    break;
case 3:
    modificarServicio();
    break;
case 4:
    eliminar();
    break;
case 5:
    ActivarServicios();
    break;
case 6:
    buscar();
    break;
case 0:
   break;
default:
    cout<<"Opcion invalida, Intenta Nuevamente "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);
}

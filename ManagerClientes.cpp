#include <iostream>
#include "ManagerClientes.h"
#include "Necesario.h"
using namespace std;
ManagerClientes::ManagerClientes()
{
    //ctor
}

void ManagerClientes::CargarCliente(){
 int idClientes;
 string nombre,apellido,dni,email,telefono;
 bool estado=false;
 bool eliminar=false;

  cout<<"A la hora de Cargar Nombre o Apellido, no ingrese numeros, por favor :)"<<endl;

  idClientes = _repo.getNuevoID();
  cout << "ID CLIENTE: #" << idClientes << endl;

  cout <<"NOMBRE: ";
  nombre=cargarCadena();
    while (nombre == "") {
        cout << "NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
        nombre=cargarCadena();
    }

  cout<<"APELLIDO: ";
  apellido=cargarCadena();
   while(apellido==""){
     cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
     apellido=cargarCadena();
   }

  cout<<"DNI: ";
  dni=cargarCadena();
    while(dni==""){
        cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
        dni=cargarCadena();
    }
  if (validadDNI(dni)){
    cout<<"ESTE DNI YA EXISTE "<<endl;
    return;
  }

  cout<<"EMAIL: ";
  email=cargarCadena();
    while(email==""){
        cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
        email=cargarCadena();
    }

  cout<<"TELEFONO / CELULAR: ";
  telefono=cargarCadena();
    while(telefono==""){
        cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
        telefono=cargarCadena();
    }
    system("pause");
    system ("cls");

    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"ID: #"<<idClientes<<endl;
    cout<<"NOMBRE: "<<nombre<<endl;
    cout<<"APELLIDO: "<<apellido<<endl;
    cout<<"DNI: "<<dni<<endl;
    cout<<"EMAIL: "<<email<<endl;
    cout<<"TELEFONO: "<<telefono<<endl;
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
  estado= (opcion==1);

  Cliente cliente(idClientes,nombre,apellido,dni,email,telefono,estado);
  cliente.setEliminado(eliminar);

  if(_repo.guardar(cliente)){
    cout<<"CLIENTE GUARDADO CORRECTAMENTE "<<endl;
  }
  else {
    cout<<"ERROR AL GUARDAR AL CLIENTE "<<endl;
  }
}

void ManagerClientes::mostrarClientes(Cliente cliente){
  cout<<"ID CLIENTE: #" <<cliente.getidCliente()<<endl;
  cout<<"NOMBRE: "<<cliente.getNombre()<<endl;
  cout<<"APELLIDO: "<<cliente.getApellido()<<endl;
  cout<<"DNI: "<<cliente.getDni()<<endl;
  cout<<"EMAIL: "<<cliente.getEmail()<<endl;
  cout<<"TELEFONO / CELULAR: "<<cliente.getTelefono()<<endl;
  cout<<"ESTADO: "<< (cliente.getEstado() ? "REGISTRADO ":"NO REGISTRADO ")<<endl;
  if(cliente.getEliminado()){
    cout<<" [ELIMINADO] "<<endl;
  }
}

void ManagerClientes::ListarClientes(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;
  for (int i = 0; i < cantidad; i++){
    Cliente cliente = _repo.leer(i);
    if(!cliente.getEliminado()){
      mostrarClientes(cliente);
      encontrado=true;
      cout << "--------------------------" << endl;
//    system("pause");
//    system("cls");
  }
}
  if(!encontrado){
    cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
  }
}

void ManagerClientes::buscarClientesID(){
    int id;
    cout<<"INGRESAR ID DE CLIENTE: ";
  while(true){
    if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<" 0 para volver al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"Vuele al menu anterior "<<endl;
        return;
    }
    break;
}
    cin.ignore();

    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        Cliente cliente = _repo.leer(i);
        if (cliente.getidCliente() == id) {
            cout<<"-----CLIENTE ENCONTRADO-----"<<endl;
            mostrarClientes(cliente);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "NO SE ENCONTRO AL CLIENTE." << endl;
    }
}

void ManagerClientes::buscarClientesDNI(){
    string dni;
    cout<<"INGRESAR DNI DEL CLIENTE A BUSCAR: ";
    dni=cargarCadena();
       while(dni==""){
       cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
       dni=cargarCadena();
    }

    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    for (int i=0;i<cantidad;i++){
        Cliente cliente=_repo.leer(i);
        if(cliente.getDni()== dni){
            cout<<"-----CLIENTE ENCONTRADO-----"<<endl;
            mostrarClientes(cliente);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
    }
    if(!encontrado){
        cout<<"NO SE ENCONTRO AL CLIENTE "<<endl;
    }
}

void ManagerClientes::buscarClientesApellido(){
   string apellido;
   cout<<"INGRESAR APELLIDO DEL CLIENTE: ";
   apellido=cargarCadena();
    while(apellido==""){
        cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
        apellido=cargarCadena();
    }
   int cantidad=_repo.getCantidadRegistros();
   bool encontrado=false;

   for(int i=0;i<cantidad;i++){
    Cliente cliente =_repo.leer(i);
    if(cliente.getApellido()==apellido){
        cout<<"-----CLIENTE ENCONTRADO-----"<<endl;
        mostrarClientes(cliente);
        cout<<"---------------------------" << endl;
        encontrado = true;
        }
    }
    if(!encontrado){
        cout<<"NO SE ENCONTRO AL CLIENTE "<<endl;
    }
}

void ManagerClientes::buscarClientes(){
    int opcion;
    do {
    system("cls");
    cout<<"~~~ BUSCAR CLIENTE ~~~"<<endl;
    cout<<"1. BUSCAR POR ID "<<endl;
    cout<<"2. BUSCAR POR DNI "<<endl;
    cout<<"3. BUSCAR POR APELLIDO"<<endl;
    cout<<"0. SALIR "<<endl;
    cout<<"OPCION: ";
    cin>>opcion;
    system("cls");
switch (opcion){
  case 1:
      buscarClientesID();
      break;
  case 2:
    buscarClientesDNI();
    break;
  case 3:
    buscarClientesApellido();
  case 0:
    break;
default:
    cout<<"Opcion invalida, intente nuevamente "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);
}

void ManagerClientes::eliminar(){
  int opcion;
  do{
    system("cls");
  cout<<"------------------------------"<<endl;
  cout<<"1. ELIMINAR CLIENTE "<<endl;
  cout<<"2. MOSTRAR CLIENTES ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"------------------------------"<<endl;
  cout<<"OPCION: ";
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      eliminarClientes();
      break;
  case 2:
    mostrarClientesEliminados();
    break;
  case 0:
    return;
default:
    cout<<"Opcion invalida, intente nuevamente "<<endl;
    break;
   }
   system("pause");
  }while(opcion!=0);
}

void ManagerClientes::eliminarClientes(){
  int id,pos;
   Cliente cliente;
   char eliminar;
   bool encontrado=false;
   int cantidad=_repo.getCantidadRegistros();
   cout<<"=====CLIENTES DISPONIBLES====="<<endl;
   for(int i=0;i<cantidad;i++){
    cliente=_repo.leer(i);
    if(!cliente.getEliminado()){
      cout<<"#"<<cliente.getidCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDni()<<")"<<endl;
      encontrado=true;
    }
   }
   if(!encontrado){
    cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
    return;
   }

   cout<<"---- ELIMINAR CLIENTE ----"<<endl;
   cout<<"INGRESE ID DE CLIENTE: ";

  while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<" 0 para volver al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
 system("pause");
 system("cls");

    pos=_repo.buscarIDcliente(id);
   if(pos==-1){
    cout<<"EL CLIENTE NO EXISTE! "<<endl;
    return ;
  }
  cliente= _repo.leer(pos);

  cout<<"INFORMACION DEL CLIENTE "<<endl;
  cout<<endl;
  mostrarClientes(cliente);

  cout<<endl;
  cout<<"QUIERE ELIMINAR? S/N ";
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){

  if(_repo.eliminar(pos)){
    cout<<"EL CLIENTE FUE ELIMINADO"<<endl;
  }
  else {
    cout<<"OCURRIO UN ERROR AL ELIMINAR AL CLIENTE "<<endl;
  }
  }
}

void ManagerClientes::mostrarClientesEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cantidad;i++){
        Cliente cliente=_repo.leer(i);
       if(cliente.getEliminado()){
        mostrarClientes(cliente);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        cout<<"NO HAY CLIENTES ELIMINADOS "<<endl;
        return;
    }
}

void ManagerClientes::ActivarCliente(){
  int id, pos;
  char eliminar;
  int cantC=_repo.getCantidadRegistros();
  bool encontrado=false;
    cout<<"~~~~ CLIENTES ELIMINADOS ~~~~"<<endl;
    for(int i=0;i<cantC;i++){
    Cliente cliente=_repo.leer(i);
    if(cliente.getEliminado()){
        cout<<"~ID: #"<<cliente.getidCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDni()<<") "<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    cout<<"NO HAY CLIENTES ELIMINADOS "<<endl;
    return;
  }
  system("pause");
  system("cls");

  cout<<"~~~~ ACTIVAR CLIENTE ~~~~"<<endl;
  cout<<"ID CLIENTE: ";
 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<" 0 para volver al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }

  pos=_repo.buscarIDcliente(id);
  if(pos==-1){
    cout<<"EL CLIENTE NO EXISTE "<<endl;
    return;
  }
  Cliente cliente =_repo.leer(pos);

  if(!cliente.getEliminado()){
    cout<<"ERROR: EL CLIENTE NO ESTA ELIMINADO "<<endl;
    cout<<"No es necesario activar "<<endl;
    return;
  }

  cout<<"INFORMACION DEL CLIENTE ELIMINADO "<<endl;
  cout<<endl;
  mostrarClientes(cliente);
  cout<<endl;
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  cin>>eliminar;
   if(eliminar=='s' or eliminar=='S'){
    cliente.setEliminado(false);
    cliente.setEstado(true);
   }

   if(_repo.guardar(pos,cliente)){
    cout<<" GUARDADO CORRECTAMENTE "<<endl;
   }
   else {
    cout<<"OCURRIO UN ERROR "<<endl;
   }
}

void ManagerClientes::ordanadosAlfabeticamente(){

  int cantidad = _repo.getCantidadRegistros();

  Cliente*cliente;

  cliente=new Cliente[cantidad];

  _repo.leerTodos(cliente,cantidad);

  for(int i=0;i<cantidad;i++){ ///metodo burbuja
        bool intercambio=false;
    for(int j=0;j<cantidad -1-i;j++){
       if(cliente[j].getApellido()>cliente[j+1].getApellido()){
        Cliente aux= cliente[j];
        cliente[j]=cliente[j+1];
        cliente[j+1]=aux;
        intercambio=true;
       }
    }
    if(!intercambio){
        break;
    }
  }
  for (int i = 0; i < cantidad; i++)
  {
    Cliente clientes=_repo.leer(i);
    if(!clientes.getEliminado()){
    mostrarClientes(cliente[i]);
    cout << "------------------------" << endl;
  }
  }
  delete[] cliente;

}

void ManagerClientes::modificarClientes() {
	int id;
	int cant=_repo.getCantidadRegistros();
	bool encontrado=false;
   cout<<"~~~~ CLIENTES PARA MODIFICAR ~~~~"<<endl;
	for(int i=0; i<cant; i++){
        Cliente cliente=_repo.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID: #"<<cliente.getidCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDni()<<") "<<endl;
            encontrado=true;
        }
	}
	if(!encontrado){
        cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
        return;
	}

	cout<<"INGRESE EL ID CLIENTE A MODIFICAR: ";
   while(true){
    if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<" 0 para volver al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
	system("pause");
	system("cls");

	int pos = _repo.buscarIDcliente(id);
	if (pos == -1) {
		cout<<"CLIENTE NO ENCONTRADO."<<endl;
		return;
	}

	Cliente cliente = _repo.leer(pos);

	if(!cliente.getEliminado()){
	mostrarClientes(cliente);
	}
	else{
        cout<<"Este registro esta Eliminado "<<endl;
        return;
	}

	system("pause");
	system("cls");

    int opcion;
do {
    system("cls");
    cout<<"QUE QUIERE MODIFICAR? "<<endl;
    cout<<endl;
    cout<<"1. NOMBRE: "<<endl;
    cout<<"2. APELLIDO: "<<endl;
    cout<<"3. DNI: "<<endl;
    cout<<"4. EMAIL: "<<endl;
    cout<<"5. TELEFONO / CELULAR: "<<endl;
    cout<<"0. SALIR Y GUARDAR "<<endl;
    cout<<"INGRESE LA OPCION DESEADA: ";
    while(!(cin>>opcion)){
    cin.clear();
    cin.ignore(9999,'\n');
    cout<<"Debe ingresar un numero: ";
}
	system("cls");

    switch (opcion) {
        case 1: {
            string nombre;
            cout<<"NOMBRE ACTUAL: "<<cliente.getNombre()<<endl;
            cout<<"INGRESE NUEVO NOMBRE: ";
            nombre=cargarCadena();
            while (nombre == "") {
                cout<<"EL NOMBRE NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
                nombre=cargarCadena();
            }
            cliente.setNombre(nombre);
            break;
        }
        case 2: {
            string apellido;
            cout<<"APELLIDO ACTUAL: "<<cliente.getApellido()<<endl;
            cout<<"INGRESE APELLIDO: ";
            apellido=cargarCadena();
            while (apellido==""){
                cout<<"EL APELLIDO NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
                apellido=cargarCadena();
            }
            cliente.setApellido(apellido);
            break;
        }
        case 3: {
            string dni;
            cout<<"DNI ACTUAL: "<<cliente.getDni()<<endl;
            cout<<"INGRESE DNI: ";
            dni=cargarCadena();
            while(dni==""){
                cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
                dni=cargarCadena();
            }
            cliente.setDni(dni);
            break;
        }
        case 4: {
            string email;
            cout<<"EMAIL ACTUAL: "<<cliente.getEmail()<<endl;
            cout<<"INGRESE EMAIL: ";
            email=cargarCadena();
            while(email==""){
                cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
                email=cargarCadena();
            }
            cliente.setEmail(email);
            break;
        }
        case 5: {
            string cel;
            cout<<"NRO DE CELULAR ACTUAL: "<<cliente.getTelefono()<<endl;
            cout<<"INGRESE NUMERO DE CELULAR: ";
            cel=cargarCadena();
            while(cel==""){
                cout<<"NO PUEDE ESTAR VACIO. INGRESE NUEVAMENTE: ";
                cel=cargarCadena();
            }
            cliente.setTelefono(cel);
            break;
        }
        case 0:
            break;
        default:
            cout<<"OPCION INVALIDA."<<endl;
            break;
    }
	system("pause");
} while(opcion!=0);

	if (_repo.guardar(pos, cliente)) {
		cout<< "CLIENTE MODIFICADO CORRECTAMENTE."<<endl;
	} else {
		cout<< "ERROR AL MODIFICAR EL CLIENTE."<<endl;
	}
}

///validar que no haya dos clientes con un mismo DNI
bool ManagerClientes::validadDNI(string dni){
  int cantidad=_repo.getCantidadRegistros();

  for(int i=0;i<cantidad;i++){
    Cliente cliente=_repo.leer(i);
    if(!cliente.getEliminado() && cliente.getDni()==dni){
        return true;
    }
  }
  return false;
}


#include <iostream>
#include <iomanip>
#include "ManagerEventos.h"
#include "Fecha.h"
#include "ArchivoCliente.h"
#include "Cliente.h"
#include "Necesario.h"
#include "ManagerEventoServicio.h"
using namespace std;
ManagerEventos::ManagerEventos()
{
    //ctor
}

void ManagerEventos::cargarEvento(){
    int idE, idC, cant;
    string nombre;
    Fecha fechaEvento, fechaPagoR;

    ArchivoCliente arcC;
    int cantClientes = arcC.getCantidadRegistros();

    cout << "--- CLIENTES DISPONIBLES ---" << endl;

    if (cantClientes == 0){
        cout << "NO HAY CLIENTES REGISTRADOS." << endl;
        return;
    }

    for(int i = 0; i < cantClientes; i++){
        Cliente cliente = arcC.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID CLIENTE: #"<<cliente.getidCliente()<<"  ";
            cout<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ";
            cout<<"( "<< cliente.getDni()<<" )"<<endl;
            cout<<"-------------------------"<< endl;
        }
    }
    idE = _repo.getNuevoIdEvento();
    cout << "ID EVENTO: #" << idE << endl;
//    cout<<"ID EVENTO: #";
//    cin>>idE;

    while (true) {
        cout << "ID CLIENTE (0 para cancelar) #: ";
        if (!(cin >> idC)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Debe ingresar un numero valido "<<endl;
            continue;
        }
        if (idC == 0) {
            cout << "OPERACION CANCELADA. "<<endl;
            return;
        }
        bool existe = false;

        for (int i = 0; i < cantClientes; i++){
            Cliente cli = arcC.leer(i);
            if (cli.getidCliente() == idC && !cli.getEliminado()){
                existe = true;
                break;
            }
        }
        if (!existe) {
            cout << "El ID CLIENTE no existe. "<<endl;
            cout<<"Intente Nuevamente: "<<endl;
            continue;
        }
        break;
    }
    cout<<endl;
    mostrarHistorial(idC);
    system("pause");
    system("cls");

    int tipoEvento;
    cout << " --- TIPO DE EVENTO --- "<<endl;
    cout << "1. Boda "<<endl;
    cout << "2. Cumpleanios "<<endl;
    cout << "3. Empresarial "<<endl;
    cout << "4. Bautismos, Comunion "<<endl;
    cout << "5. Graduacion "<<endl;

    while (true) {
        cout << "Seleccione tipo (1-5): ";
        if (!(cin >> tipoEvento)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Debe ingresar un numero valido"<<endl;
            continue;
        }
        if (tipoEvento < 1 || tipoEvento > 5) {
            cout << "Tipo invalido, Elija entre 1 y 5 "<<endl;
            continue;
        }
        break;
    }
    cin.ignore();
    while (true) {
        cout << "NOMBRE DEL EVENTO: ";
        nombre=cargarCadena();

        if (nombre == "") {
            cout << "El nombre no puede estar vacio "<<endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "CANTIDAD DE INVITADOS: ";
        if (!(cin >> cant)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Debe ingresar un numero valido "<<endl;
            continue;
        }
        if (cant <= 0) {
            cout << "La cantidad debe ser mayor a 0 "<<endl;
            continue;
        }
        break;
    }

    Eventos even;
    float precio = even.calcularPrecioInicial(cant);
    cout << "PRECIO DE LA RESERVA: $" << fixed << setprecision(2) << precio << endl;

    cout << "FECHA DEL EVENTO:" << endl;
    fechaEvento.cargarFecha();

     int opcion;
     bool pagoReserva=false;
     cout<<"QUIERE PAGAR LA RESERVA AHORA? 1.SI 0.NO: ";
     cin>>opcion;

    while (opcion!=0 && opcion!=1){
    cout<<"OPCION INVALIDA, INGRESE 1.SI 0.NO: ";
    cin>>opcion;
  }
     pagoReserva= (opcion==1);

    if (pagoReserva == 1){
        cout << "FECHA DE PAGO DE LA RESERVA:" << endl;
        fechaPagoR.cargarFecha();
    }

    Eventos evento(idE, idC, nombre, fechaEvento, fechaPagoR, cant, true);
    evento.setPrecioInicial(precio);
    evento.setTipoEvento(tipoEvento);///colocar en el constructor
    evento.setPagoReserva(pagoReserva);///colocar en el constructor
    evento.setEstado(false);
    evento.setEliminado(false);

    if(_repo.guardar(evento)){
        cout << "EVENTO GUARDADO CORRECTAMENTE." << endl;
    }
    else {
        cout << "ERROR AL GUARDAR EL EVENTO." << endl;
    }
}

void ManagerEventos::mostrarEvento(Eventos evento){
  cout<<"ID EVENTO: #"<<evento.getIdEvento()<<endl;
  cout<<"ID CLIENTE: #" <<evento.getidCliente()<<endl;
  cout<<"TIPO DE EVENTO: ";
    switch(evento.getTipoEvento()){
        case 1: cout<<"Boda"; break;
        case 2: cout<<"Cumpleanios"; break;
        case 3: cout<<"Empresarial"; break;
        case 4: cout<<"Bautismos, Comunion"; break;
        case 5: cout<<"Graduacion"; break;
        default:cout<<"Desconocido"; break;
    }
    cout<<endl;
  cout<<"NOMBRE DE EVENTO: "<<evento.getNombreEvento()<<endl;
  cout<<"CANTIDAD DE INVITADOS: "<<evento.getcantidadInvitados()<<endl;
  cout<<"PRECIO INICIAL: $"<<evento.getPrecioInicial()<<endl;
  cout<<"FECHA DEL EVENTO: ";
  evento.getFechaEvento().mostrarFecha();
  if(evento.getPagoReserva()){
  cout<<"FECHA DE PAGO RESERVA: ";
  evento.getFechaPago().mostrarFecha();
  }
  cout<<"ESTADO: "<< (evento.getConfirmado() ? " ACTIVO ":" CANCELADO: ")<<endl;
  if(evento.getEliminado()){
    cout<<"EVENTO ELIMINADO  "<<endl;
  }
}
///LISTAR TODOS LOS EVENTOS
void ManagerEventos::listarEvento(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;
  for (int i = 0; i < cantidad; i++){
    Eventos evento = _repo.leer(i);
    if(!evento.getEliminado()){
    mostrarEvento(evento);
    encontrado=true;
    cout << "--------------------------" << endl;
  }
}
  if(!encontrado){
    cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
  }
}
///BUSCAR ID EVENTO
void ManagerEventos::buscarIdEvento(){
    int id;
    cout<<"INGRESAR ID EVENTO: ";
 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<" 0 Para volver al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VULEVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
}
    cin.ignore();
    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        Eventos h = _repo.leer(i);
        if (!h.getEliminado() && h.getIdEvento() == id) {
            cout<<"-----EVENTO ENCONTRADO-----"<<endl;
            mostrarEvento(h);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "NO SE ENCONTRO EL EVENTO." << endl;
    }

}
void ManagerEventos::buscarEventoDeCliente(){
    ArchivoCliente arcC;

    int cantC = arcC.getCantidadRegistros();
    int cantE = _repo.getCantidadRegistros();

    if(cantC == 0){
        cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
        return;
    }

    cout<<"--- CLIENTES DISPONIBLES ---"<<endl;
    for(int i=0;i<cantC;i++){
        Cliente cliente = arcC.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID: #"<<cliente.getidCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDni()<<") "<<endl;
        }
    }
    cout<<endl;
    int idCliente;
    while(true){
        cout<<"INGRESE ID CLIENTE (0 para volver): ";
        if(!(cin>>idCliente)){
            cin.clear();
            cin.ignore(9999,'\n');
            cout<<"Debe ingresar un numero valido"<<endl;
            continue;
        }
        if(idCliente==0){
                return;
        }
        bool existe=false;
        for(int i=0;i<cantC;i++){
            Cliente cliente = arcC.leer(i);
            if(!cliente.getEliminado() && cliente.getidCliente()==idCliente){
                existe=true;
                break;
            }
        }
        if(!existe){
            cout<<"CLIENTE NO EXISTE"<<endl;
            continue;
        }
        break;
    }
    bool hayEventos=false;
    system("pause");
    system("cls");
    cout<<"--- EVENTOS REALIZADOS DEL CLIENTE #" << idCliente << " ---"<<endl;

    for(int i=0;i<cantE;i++){
        Eventos evento = _repo.leer(i);
        if(!evento.getEliminado() &&evento.getConfirmado() &&evento.getidCliente() == idCliente){
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<endl;
            cout<<"NOMBRE DEL EVENTO: "<<evento.getNombreEvento()<<endl;
            cout<<"INVITADOS: "<<evento.getcantidadInvitados()<<endl;
            cout<<"---------------------------"<<endl;
            hayEventos=true;
        }
    }

    if(!hayEventos){
        cout<<"EL CLIENTE NO TIENE EVENTOS REALIZADOS"<<endl;
    }
}


///ELIMINAR
void ManagerEventos::eliminarEvento(){
      int id,pos;

   char eliminar;
   cout<<"----EVENTOS DISPONIBLES----"<<endl;
   ArchivoEvento arcE;
   int cantE=arcE.getCantidadRegistros();
   bool encontrado=false;
   for(int i=0;i<cantE;i++){
    Eventos evento=arcE.leer(i);
    if(!evento.getEliminado()){
        cout<<"~ ID: #"<<evento.getIdEvento()<<" "<<evento.getNombreEvento()<<endl;
        encontrado=true;
    }
   }
   if(!encontrado){
    cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
    return;
   }

   cout<<"---- ELIMINAR EVENTO ----"<<endl;
   cout<<"INGRESE ID EVENTO: # (0 para cancelar):";
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
            cout<<"vuelve al menu anterior "<<endl;
        return;
    }
    break;
 }
    pos=_repo.buscarIDEvento(id);
   if(pos==-1){
    cout<<"EL EVENTO NO EXISTE! "<<endl;
    return ;
  }

   Eventos evento = _repo.leer(pos);
   ManagerEventoServicio manager;

   if (manager.eventoPagado(evento.getIdEvento())) {
     cout << "EL EVENTO YA ESTA PAGADO. NO SE PUEDE ELIMINAR." << endl;
     return;
}


  cout<<"INFORMACION DEL EVENTO "<<endl;
  cout<<endl;
  mostrarEvento(evento);

  cout<<endl;
  cout<<"QUIERE ELIMINAR? S/N ";
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){

  if(_repo.eliminar(pos)){
    cout<<"EL EVENTO FUE ELIMINADO"<<endl;
  }
  else {
    cout<<"OCURRIO UN ERROR AL ELIMINAR EL EVENTO "<<endl;
  }
  }
}
///ACTIVAR EL EVENTO ELIMINADO
void ManagerEventos::ActivarEvento(){
  int id, pos;
  char activar;
  ArchivoEvento arcE;
  int cantE=arcE.getCantidadRegistros();
  bool encontrado=false;
  cout<<"~~~~ EVENTOS ELIMINADOS ~~~~"<<endl;
  for(int i=0;i<cantE;i++){
    Eventos eve=arcE.leer(i);
    if(eve.getEliminado()){
        cout<<"~ID: #"<<eve.getIdEvento()<<" "<<eve.getNombreEvento()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    cout<<"NO HAY EVENTOS ELIMINADOS "<<endl;
    return;
  }

  system("pause");
  system("cls");

  cout<<"~~~~ ACTIVAR EVENTO ~~~~"<<endl;
  cout<<"ID EVENTO: # (0 para cancelar):";
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
            cout<<"vuelve al menu anterior "<<endl;
        return;
    }
    break;
 }
  pos=_repo.buscarIDEvento(id);
  if(pos==-1){
    cout<<"EL EVENTO NO EXISTE "<<endl;
    return;
  }
  Eventos evento;
  evento= _repo.leer(pos);
    if(!evento.getEliminado()){
    cout<<" EL EVENTO NO ESTA ELIMINADO "<<endl;
    cout<<" No es necesario activar "<<endl;
    return;
  }

  cout<<"INFORMACION DEL EVENTO ELIMINADO "<<endl;
  cout<<endl;
  mostrarEvento(evento);
  cout<<endl;
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  cin>>activar;
   if(activar=='s' or activar=='S'){
    evento.setEliminado(false);
    evento.setConfirmado(true);
   }
   if(_repo.guardar(pos,evento)){
    cout<<"GUARDADO CORRECTAMENTE "<<endl;
   }
   else {
    cout<<"OCURRIO UN ERROR "<<endl;
   }
}
///MOSTRAR ELIMINADOS
void ManagerEventos::mostrarEventosEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cantidad;i++){
        Eventos evento=_repo.leer(i);
       if(evento.getEliminado()){
        mostrarEvento(evento);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        cout<<"NO HAY EVENTOS ELIMINADOS "<<endl;
        return;
    }
}

///ordenado por mes/ anio
void ManagerEventos::ordanadosPorFecha(){

  int cantidad = _repo.getCantidadRegistros();

  Eventos*evento;

  evento=new Eventos[cantidad];

  _repo.leerTodos(evento,cantidad);

  for(int i=0;i<cantidad;i++){ ///metodo burbuja
        bool intercambio=false;
    for(int j=0;j<cantidad -1-i;j++){
        Fecha f1=evento[j].getFechaEvento();
        Fecha f2=evento[j+1].getFechaEvento();
        bool f1esMaayor=false;
      if (f1.getAnio() > f2.getAnio()) {
            f1esMaayor=true;
       } else if (f1.getAnio() == f2.getAnio()) {
      if (f1.getMes() > f2.getMes()) {
          f1esMaayor=true;
      } else if (f1.getMes() == f2.getMes()) {
        if (f1.getDia() > f2.getDia()) {
            f1esMaayor=true;
        }
    }
}
if(f1esMaayor){
        Eventos aux= evento[j];
        evento[j]=evento[j+1];
        evento[j+1]=aux;
        intercambio=true;
       }
    }
    if(!intercambio){
        break;
    }
}

  for (int i = 0; i < cantidad; i++)
  {
    mostrarEvento(evento[i]);
    cout << "------------------------" << endl;
  }
  delete[] evento;
}

///EDITAR EL EVENTO...

void ManagerEventos::modificarEvento() {
	int id;
	int cant=_repo.getCantidadRegistros();
	bool encontrado=false;
	cout<<"~~~~ EVENTOS DISPONIBLES ~~~~"<<endl;
	for(int i=0; i<cant; i++){
        Eventos evento=_repo.leer(i);
        if(!evento.getEliminado() && evento.getConfirmado() ){
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<" ID CLIENTE: #"<<evento.getidCliente()<<" |Nombre del Evento: "<<evento.getNombreEvento()<<endl;
            encontrado=true;
        }
	}
	if(!encontrado) {
        cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
        return;
	}
	cout << "INGRESE EL ID EVENTO A MODIFICAR: ";
 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<"0 vuelve al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
    int pos = _repo.buscarIDEvento(id);
	if (pos == -1) {
		cout << "EVENTO NO ENCONTRADO." << endl;
		return;
	}

	Eventos evento = _repo.leer(pos);
    ManagerEventoServicio manager;

   if(manager.eventoPagado(evento.getIdEvento())) {
      cout << "ESTE EVENTO YA ESTA PAGADO, NO SE PUEDE MODIFICAR " << endl;
      return;
}


	if(!evento.getEliminado()){
	mostrarEvento(evento);
	}
	else {
        cout<<"Esta Eliminado "<<endl;
        return;
	}
    system("pause");
	system("cls");

    int opcion;

    do{
      system("cls");
      cout<<"QUE QUIERE MODIFICAR? "<<endl;
      cout<<"1. CLIENTE "<<endl;
      cout<<"2. TIPO DE EVENTO "<<endl;
      cout<<"3. NOMBRE DEL EVENTO "<<endl;
      cout<<"4. CANTIDAD DE INVITADOS "<<endl;
      cout<<"5. FECHA EVENTO "<<endl;
      cout<<"6. FECHA PAGO RESERVA "<<endl;
      cout<<"0. SALIR Y GUARDAR "<<endl;
      cout<<"OPCION: ";
      cin>>opcion;

      system("cls");

      switch(opcion){

  case 1:{
      ArchivoCliente arcCli;
      int cantC=arcCli.getCantidadRegistros();
      cout<<"CLIENTES DISPONIBLES "<<endl;
      for(int i=0;i<cantC;i++){
        Cliente cliente=arcCli.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID CLIENTE: #"<<cliente.getidCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<endl;
        }
      }
      int nuevoIdCliente;
      cout<<"INGRESE NUEVO ID CLIENTE: ";
   while(true){
       if(!( cin>>nuevoIdCliente)){
         cin.clear();
         cin.ignore(9999,'\n');
         cout<<"Debe ingresar un numero: "<<endl;
         continue;
    }
    if(nuevoIdCliente<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<"0 vuelve al menu anterior "<<endl;
        continue;
    }
    if(nuevoIdCliente==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
      bool existe=false;
      for(int i=0;i<cantC;i++){
        Cliente cliente=arcCli.leer(i);
        if(cliente.getidCliente()==nuevoIdCliente && !cliente.getEliminado()){
            existe=true;
            break;
        }
      }
      if(!existe){
        cout<<"El cliente no existe "<<endl;
        break;
      }
      evento.setidCliente(nuevoIdCliente);
      cout<<"CLIENTE MODIFICADO "<<endl;
    break;
      }
      case 2:{
    int tipoEvento;
    cout << " --- TIPO DE EVENTO --- "<<endl;
    cout << "1. Boda "<<endl;
    cout << "2. Cumpleanios "<<endl;
    cout << "3. Empresarial "<<endl;
    cout << "4. Bautismos, Comunion "<<endl;
    cout << "5. Graduacion "<<endl;

    while (true) {
        cout << "Seleccione tipo de evento (1-5): ";
        if (!(cin >> tipoEvento)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Por favor, ingrese un numero valido"<<endl;
            continue;
        }
        if (tipoEvento < 1 || tipoEvento > 5) {
            cout << "Tipo de evento incorrecto, Elija entre 1 y 5 "<<endl;
            continue;
        }
        if(tipoEvento==0){
            cout<<"Vuelve al menu de modificar "<<endl;
            return;
        }
        break;
    }
    evento.setTipoEvento(tipoEvento);
      break;
      }
  case 3:{
      ///validar
      string nombre;
      cout<<"NOMBRE DEL EVENTO ACTUAL: "<<evento.getNombreEvento()<<endl;
      cout<<"INGRESE NOMBRE DEL EVENTO ";
      nombre=cargarCadena();
      evento.setNombreEvento(nombre);
      cout<<"NOMBRE DEL EVENTO MODIFICADO "<<endl;
    break;
      }
  case 4:{
      int cantIn;
      cout<<"CANTIDAD DE INVITADOS ACTUAL: "<<evento.getcantidadInvitados()<<endl;
      cout<<"CANTIDAD DE INVITADOS: ";
      cin>>cantIn;
       if(cantIn<=0){
        cout<<"ERROR: La cantidad debe ser mayor a 0: ";
        break;
       }

      float precio=evento.calcularPrecioInicial(cantIn);
      evento.setPrecioInicial(precio);
      cout<<"PRECIO DE LA RESERVA: $"<<evento.getPrecioInicial()<<endl;
      evento.setCantidad(cantIn);
    break;
  }
  case 5:{
      Fecha f;
      cout<<"FECHA DEL EVENTO ACTUAL: ";
      evento.getFechaEvento().mostrarFecha();
      cout<<"FECHA DEL EVENTO: "<<endl;
      f.cargarFecha();
      evento.setFechaEvento(f);
    break;
  }
  case 6:{
      Fecha fp;
      cout<<"FECHA DE PAGO DE RESERVA ACTUAL: ";
      evento.getFechaPago().mostrarFecha();
      cout<<"FECHA DE PAGO DE RESERVA: "<<endl;
      fp.cargarFecha();
      evento.setFechaPago(fp);
    break;
  }
  case 0:
   break;
  default:
      cout<<"Opcion Incorrecta, intente nuevamente "<<endl;
    break;

      }
system("pause");

}while(opcion!=0);

	if (_repo.guardar(pos, evento)) {
		cout << "EVENTO MODIFICADO CORRECTAMENTE." << endl;
	} else {
		cout << "ERROR AL MODIFICAR EL EVENTO." << endl;
	}
}
///MENU ELIMINAR LOGICA
void ManagerEventos::eliminar(){
  int opcion;
  do {
    system("cls");
  cout<<"------------------------------"<<endl;
  cout<<"1. ELIMINAR EVENTOS "<<endl;
  cout<<"2. MOSTRAR EVENTOS ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"OPCION: ";
  cin>>opcion;
  cout<<"------------------------------"<<endl;
  system("cls");
  switch(opcion){
  case 1:
      eliminarEvento();
      break;
  case 2:
      mostrarEventosEliminados();
      break;
  case 0:
    return;
default:
    cout<<"Opcion invalida "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);
}

///evento mas frecuentes
void ManagerEventos::eventosPorTipo() {
    ArchivoEvento arc;
    int cant = arc.getCantidadRegistros();

    if (cant == 0) {
        cout << "NO HAY EVENTOS REGISTRADOS." << endl;
        return;
    }
    int contador[6] = {};
        string nombresTipos[6] = {" ","Boda","Cumpleanios","Empresarial","Bautismo/ Comunion","Graduacion"};

    for (int i = 0; i < cant; i++) {
        Eventos e = arc.leer(i);

        if (!e.getEliminado()) {
            int tipo = e.getTipoEvento();
                contador[tipo]++;
            }
        }
    cout << "--- CANTIDAD DE EVENTOS POR TIPO ---" << endl;
    for (int i = 1; i <= 5; i++) {
        if(contador[i]>0){
        cout <<nombresTipos[i] << ":  " << contador[i] << " evento(s)" << endl;
        }
    }
    cout<<endl;
}
///historial del cliente
void ManagerEventos::mostrarHistorial(int idCliente){
     int cantidad=_repo.getCantidadRegistros();
     bool encontrado=false;
     cout<<"~~ HISTORIAL DE EVENTOS DEL ID CLIENTE: #"<<idCliente<<" ~~"<<endl;
     for(int i=0;i<cantidad;i++){
        Eventos evento=_repo.leer(i);
        if(!evento.getEliminado() && evento.getidCliente()==idCliente){
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<endl;
             cout<<"TIPO DE EVENTO ";
                   switch(evento.getTipoEvento()){
                      case 1: cout<<"Boda"; break;
                        case 2: cout<<"Cumpleanios"; break;
                         case 3: cout<<"Empresarial"; break;
                          case 4: cout<<"Bautismos, Comunion"; break;
                            case 5: cout<<"Graduacion"; break;
                              default:cout<<"Desconocido"; break;
                           }
                           cout<<endl;
            cout<<"FECHA DEL EVENTO: ";
            evento.getFechaEvento().mostrarFecha();
            cout<<"CANTIDAD DE INVITADOS: "<<evento.getcantidadInvitados()<<endl;
           encontrado=true;
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        }
     }
     if(!encontrado){
        cout<<"NO TIENE EVENTOS REGISTRADOS "<<endl;
     }
}
///cancelar evento
void ManagerEventos::cancelarEventos(){
    int id;
       cout<<"----EVENTOS DISPONIBLES----"<<endl;
   ArchivoEvento arcE;
   Eventos eventos;
   int cantE=arcE.getCantidadRegistros();
   bool encontrado=false;
   for(int i=0;i<cantE;i++){
    eventos=arcE.leer(i);
    if(!eventos.getEliminado()){
        cout<<"~ ID: #"<<eventos.getIdEvento()<<" "<<eventos.getNombreEvento()<<endl;
        encontrado=true;
    }
   }
   if(!encontrado){
    cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
    return;
   }
    cout<<"INGRESAR ID EVENTO: ";

  while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<"0 para volver al menu anterior "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
    int pos=_repo.buscarIDEvento(id);

    if(pos==-1){
        cout<<"NO SE ENCONTRO EL EVENTO "<<endl;
        return;
    }

     eventos=_repo.leer(pos);
     ManagerEventoServicio manager;

  if (manager.eventoPagado(eventos.getIdEvento())) {
    cout << "NO SE PUEDE CANCELAR: EL EVENTO YA ESTA PAGADO " << endl;
    return;
  }
    if(eventos.getEliminado()){
        cout<<"NO SE PUEDE CANCELAR: EL EVENTO ESTA ELIMINADO"<<endl;
        return;
    }

    if(!eventos.getConfirmado()){
        cout<<"EL EVENTO YA ESTA CANCELADO "<<endl;
        return;
    }

    cout<<"~~~~ INFORMACION DEL EVENTO ~~~~"<<endl;
    mostrarEvento(eventos);

    int opcion;
    cout<<"QUIERE CANCELAR EL EVENTO? (1.SI 0.NO): ";
    cin>>opcion;

    if(opcion!=1){
        cout<<"OPERACION CANCELADA "<<endl;
        return;
    }

    eventos.setConfirmado(false); /// CANCELADO (pero NO eliminado)

    if(_repo.guardar(pos,eventos)){
        cout<<"EVENTO CANCELADO "<<endl;
    }
    else{
        cout<<"ERROR: NO SE PUDO GUARDAR, intente nuevamente dentro de unos minutos "<<endl;
    }
    ManagerEventoServicio evs;
    evs.cancelarServiciosPorEvento(id);
    cout<<"TODO FUE GUARDADO "<<endl;
}

void ManagerEventos::activarEventoCancelado(){
    int id;
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    cout<<"~~~~~~ EVENTOS CANCELADOS ~~~~~~"<<endl;
    for(int i=0; i<cantidad; i++){
        Eventos evento=_repo.leer(i);
        if(!evento.getConfirmado()){
            cout<<"ID: #"<<evento.getIdEvento()<<" "<<evento.getNombreEvento()<<endl;
            encontrado=true;
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        }
    }
    if(!encontrado){
        cout<<"NO HAY EVENTOS CANCELADOS "<<endl;
        return;
    }

    cout<<"INGRESAR ID EVENTO: ";

 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        cout<<"0 PARA VOLVER AL MENU ANTERIOR "<<endl;
        continue;
    }
    if(id==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
    int pos=_repo.buscarIDEvento(id);
    if(pos==-1){
        cout<<"NO SE ENCONTRO EL EVENTO "<<endl;
        return;
    }
    Eventos eventos=_repo.leer(pos);

    if(eventos.getEliminado()){
        cout<<"NO SE PUEDE ACTIVAR: ESTA ELIMINADO "<<endl;
        return;
    }

    if(eventos.getConfirmado()){
        cout<<"EL EVENTO YA ESTA ACTIVO "<<endl;
        return;
    }

    cout<<"~~~~ INFORMACION DEL EVENTO CANCELADO ~~~~"<<endl;
    mostrarEvento(eventos);

    int opcion;
    cout<<"QUIERE ACTIVARLO? (1.SI / 0.NO): ";
    cin>>opcion;

    if(opcion!=1){
        cout<<"OPERACION CANCELADA"<<endl;
        return;
    }

    eventos.setConfirmado(true);

    if(_repo.guardar(pos,eventos)){
        cout<<"EVENTO ACTIVADO CORRECTAMENTE "<<endl;
    }
}

void ManagerEventos::submenuCancelarActivar(){
  int opcion;
  do {
    system("cls");
  cout<<"------------------------------"<<endl;
  cout<<"1. CANCELAR EVENTOS "<<endl;
  cout<<"2. ACTIVAR EVENTOS CANCELADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"OPCION: ";
  cin>>opcion;
  cout<<"------------------------------"<<endl;
  system("cls");
  switch(opcion){
  case 1:
      cancelarEventos();
      break;
  case 2:
      activarEventoCancelado();
      break;
  case 0:
    return;
default:
    cout<<"Opcion invalida "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);
}

void ManagerEventos::buscar(){
  int opcion;
  do {
    system("cls");
  cout<<"------------------------------"<<endl;
  cout<<"1. BUSCAR POR ID "<<endl;
  cout<<"2. BUSCAR POR ID CLIENTE "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"------------------------------"<<endl;
  cout<<"OPCION: ";
  cin>>opcion;
  system("cls");
  switch(opcion){
  case 1:
      buscarIdEvento();
      break;
  case 2:
      buscarEventoDeCliente();
      break;
  case 0:
    return;
default:
    cout<<"Opcion invalida "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);
}

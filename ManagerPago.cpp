#include <iostream>
#include <iomanip>
#include "Necesario.h"
#include "ManagerPago.h"
#include "Fecha.h"
#include "ArchivoEvento.h"
#include "Eventos.h"
#include "ArcEventoServicios.h"
#include "EventoServicios.h"
#include "ArchivoCliente.h"
#include "Cliente.h"
#include "ManagerDetallePago.h"
using namespace std;
ManagerPago::ManagerPago()
{
    //ctor
}
float ManagerPago::CalcularElTotal(int idevento){
      float totalServicios=0;
      ArcEventoServicios ArcEventoyServicios;
      int cantEventoServicios = ArcEventoyServicios.getCantidadRegistros();
      for(int i=0;i<cantEventoServicios;i++){
            EventoServicios evSer=ArcEventoyServicios.leer(i);
            if(evSer.getIdEvento()==idevento){
                totalServicios+=evSer.getPrecioUnitario()*evSer.getCantidadContratado();
            }
      }
      ArchivoEvento arce;
      int cant=arce.getCantidadRegistros();
      float precioI=0;
      for(int i = 0; i < cant; i++){
        Eventos evento = arce.leer(i);
        if(evento.getIdEvento() == idevento){
            precioI = evento.getPrecioInicial();
            if(!evento.getPagoReserva()){
                return precioI + totalServicios;
            }
            else {
                return totalServicios;
            }
        }
    }
    return 0;
}

void ManagerPago::cargarPagos(){
    ArchivoEvento ArcEvento;
    ArchivoCliente ArcCliente;

    ///que me muestre los eventos reservados y al cliente
    cout<<"~~~~~ EVENTOS CON PAGOS PENDIENTES ~~~~~"<<endl;

    int cantidad=ArcEvento.getCantidadRegistros();
    int cantClientes = ArcCliente.getCantidadRegistros();

     for(int i=0;i<cantidad;i++){
       Eventos evento = ArcEvento.leer(i);

        if (!evento.getEliminado() && !evento.getEstado()) {
            for (int j = 0; j < cantClientes; j++) {
               Cliente cliente = ArcCliente.leer(j);
                if (cliente.getidCliente() == evento.getidCliente()) {
                   cout << "EVENTO: #" << evento.getIdEvento() << " " << evento.getNombreEvento() << endl;
                   cout << "CLIENTE: #" << cliente.getidCliente() << " " << cliente.getNombre() << endl;
                   cout<<"--------------------------------"<<endl;
                   break;
            }
        }
    }
}
system("pause");
system("cls");

    cout<<"-----REGISTRAR PAGOS----- "<<endl;

    int idEvento;
    cout<<"ID EVENTO A PAGAR: #(0 CANCELAR): ";
 while(true){
   if(!( cin>>idEvento)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(idEvento<0){
        cout<<"EL ID NO PUEDE SER MENOR A 0 "<<endl;
        continue;
    }
    if(idEvento==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
    int posE=ArcEvento.buscarIDEvento(idEvento);
    if(posE==-1){
        cout<<"ERROR: el evento no existe "<<endl;
        return;
    }

    Eventos evento=ArcEvento.leer(posE);
    if(evento.getEstado()){
        cout<<"ESTE EVENTO YA ESTA PAGADO "<<endl;
        return;
    }

    int posC=ArcCliente.buscarIDcliente(evento.getidCliente());
    Cliente cliente=ArcCliente.leer(posC);
    cout<<"CLIENTE: "<<cliente.getNombre()<<endl;
    cout<<"EVENTO: "<<evento.getNombreEvento()<<endl;

    float total= CalcularElTotal(idEvento);
    cout<<fixed<<setprecision(2);
    cout<<"TOTAL A PAGAR: $"<<total<<endl;

    int idP=_repo.getNuevoIdPago();
//    cout<<"ID PAGO: #"<< idP <<endl;
    Fecha fechaPago;
    Fecha fechaEvento=evento.getFechaEvento();
    string metodo;

     int opcion;
     cout<<"ELIJA EL METODO DE PAGO "<<endl;
     cout<<"1. Efectivo "<<endl;
     cout<<"2. Tarjeta "<<endl;
     cout<<"3. Transferencia "<<endl;
     cout<<"Opcion: ";
     cin>>opcion;

      switch(opcion){
    case 1:
        metodo="Efectivo";
        break;
    case 2:
        metodo="Tarjeta";
        break;
    case 3:
        metodo="Transferencia";
        break;
    default:
        cout<<"OPCION INCORRECTA "<<endl;
        cout<<"SE ASIGNA 'Efectivo' "<<endl;
        metodo="Efectivo";
        break;
      }
    cout<<"FECHA DE PAGO: ";
    fechaPago.cargarFecha();

    bool atrasado=false;
    if(fechaPago > fechaEvento&& !evento.getEliminado()){
        atrasado=true;
        cout<<" PAGO ATRASADO "<<endl;
    }
     Pagos pagos(idP,cliente.getidCliente(),idEvento,fechaPago,total,metodo,true,atrasado);
     pagos.setEliminado(false);
  if(_repo.guardar(pagos)){
        evento.setEstado(true);
        ArcEvento.guardar(posE,evento);

        ManagerDetallePago MDPago;
        MDPago.cargarDetallePagos(idEvento,idP);
        cout<<"PAGO GUARDADO CORRECTAMENTE. "<<endl;
  }
  else{
    cout<<"ERROR AL GUARDAR PAGOS. "<<endl;
  }
}

void ManagerPago::mostrarPagos(Pagos pago){
    cout<<"ID PAGO: #"<<pago.getIdPago()<<endl;
    cout<<"ID CLIENTE: #"<<pago.getIdCliente()<<endl;
    cout<<"ID EVENTO: #"<<pago.getIdEvento()<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"TOTAL: $"<<pago.getMontoTotal()<<endl;
    cout<<"METODO DE PAGO: "<<pago.getMetodoPago()<<endl;
    cout<<"FECHA DE PAGO: ";
    pago.getFechaPago().mostrarFecha();
    cout << "ESTADO :" << (pago.getPagado() ? " PAGADO " : " PENDIENTE ") << endl;
    cout << "ELIMINADO: " << (pago.getEliminado() ? " Si " : " No ") << endl;
}

void ManagerPago::listarPagos(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;
  for (int i = 0; i < cantidad; i++){
    Pagos pago = _repo.leer(i);
  if(!pago.getEliminado()){
      mostrarPagos(pago);
      encontrado=true;
    cout << "--------------------------" << endl;
  }
}
  if(!encontrado){
    cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
  }
}

void ManagerPago::buscarIdPagos(){
    int id;
    cout<<"BUSCAR PAGOS POR ID "<<endl;
    cout<<"INGRESAR ID PAGO: ";
 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }

    if(id<=0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    break;
 }
    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;

    for (int i = 0; i < cantidad; i++) {
        Pagos p = _repo.leer(i);
        if ( p.getIdPago() == id) {
            cout<<"-----PAGOS ENCONTRADO-----"<<endl;
            mostrarPagos(p);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "NO SE ENCONTRO EL PAGO." << endl;
    }
}

void ManagerPago::buscarPorCliente(){
   int id;
   cout<<"BUSCAR POR ID CLIENTE "<<endl;
   cout<<"INGRESE ID CLIENTE: ";
    while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }

    if(id<=0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    break;
 }
   int cantidad=_repo.getCantidadRegistros();
   bool encontrado=false;
      for(int i=0;i<cantidad;i++){
        Pagos pago=_repo.leer(i);
        if(!pago.getEliminado() && pago.getPagado()){
            if(pago.getIdCliente()==id){
                cout<<"     PAGO ENCONTRADO   "<<endl;
                mostrarPagos(pago);
                cout<<"-----------------------"<<endl;
                encontrado=true;
            }
        }
      }
        if(!encontrado){
            cout<<"NO SE ENCONTRO "<<endl;
        }
}

void ManagerPago::buscarXfecha(){
  Fecha abuscar;
   cout<<"BUSCAR POR FECHA "<<endl;
   cout<<"INGRESE FECHA: ";
   abuscar.cargarFecha();
   int cantidad=_repo.getCantidadRegistros();
   bool encontrado=false;
   system("pause");
   system("cls");
   cout<<"LA FECHA A BUSCAR ES: ";
   abuscar.mostrarFecha();
   cout<<endl;

   for(int i=0;i<cantidad;i++){
    Pagos pago=_repo.leer(i);
        if(!pago.getEliminado() && pago.getPagado()){
            if(pago.getFechaPago()==abuscar){
                cout<<"     PAGO ENCONTRADO   "<<endl;
                mostrarPagos(pago);
                cout<<"-----------------------"<<endl;
                encontrado=true;
            }
        }
   }
        if(!encontrado){
            cout<<"NO HAY PAGOS EN LA FECHA INGRESADA "<<endl;
        }
}

void ManagerPago::eliminar(){
int opcion;
   do{
    system("cls");
    cout<<"~~~~ ELIMINAR PAGOS ~~~~~"<<endl;
    cout<<"1. ELIMINAR "<<endl;
    cout<<"2. MOSTRAR ELIMINADOS "<<endl;
    cout<<"0. VOLVER A MENU PAGOS "<<endl;
    cout<<"OPCION: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
    case 1:
        eliminarPago();
        break;
    case 2:
         mostrarEliminados();
        break;
    case 0:
        break;
    default:
        cout<<"OPCION INCORRECTA, INTENTE NUEVAMENTE "<<endl;
        break;
    }
    system("pause");
   }while(opcion!=0);
}

void ManagerPago::eliminarPago(){
    int id,pos;
   Pagos pago;
   char eliminar;

   cout<<" PAGOS DISPONIBLES "<<endl;
   bool encontrado=false;
   int cantidad=_repo.getCantidadRegistros();
   for(int i=0;i<cantidad;i++){
        pago=_repo.leer(i);
   if(!pago.getEliminado()){
    cout << fixed << setprecision(2);
    cout<<"ID: #"<<pago.getIdPago()<<" ($"<<pago.getMontoTotal()<<")"<<endl;
    encontrado=true;
   }
}
    if(!encontrado){
        cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
        return;
    }

   cout<<"---- ELIMINAR PAGO ----"<<endl;
   cout<<"INGRESE ID PAGO: ";
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
    pos=_repo.buscarIdPago(id);

   if(pos==-1){
    cout<<"EL PAGO NO EXISTE! "<<endl;
    return ;
  }

  pago= _repo.leer(pos);

  cout<<"INFORMACION DEL PAGO "<<endl;
  cout<<endl;
  mostrarPagos(pago);

  cout<<endl;
  cout<<"QUIERE ELIMINAR? S/N ";
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){

  if(_repo.eliminar(pos)){
    cout<<"EL PAGO FUE ELIMINADO"<<endl;
  }
  else {
    cout<<"OCURRIO UN ERROR AL ELIMINAR EL PAGO "<<endl;
  }
  }
}

void ManagerPago::mostrarEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cantidad;i++){
        Pagos pago=_repo.leer(i);
       if(pago.getEliminado()){
        mostrarPagos(pago);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        cout<<"NO HAY PAGOS ELIMINADOS "<<endl;
        return;
    }
}

void ManagerPago::modificarPago() {
    int id;
    cout<<"---- PAGOS REALIZADOS ----"<<endl;
    int cant=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cant;i++){
        Pagos pago=_repo.leer(i);
        if(!pago.getEliminado() && pago.getPagado()){
            cout << fixed << setprecision(2);
            cout<<"ID PAGO: #"<<pago.getIdPago()<<" | ID EVENTO: #"<<pago.getIdEvento()<<" ($"<<pago.getMontoTotal()<<")"<<endl;
            encontrado=true;
        }
    }
    if(!encontrado){
        cout<<"NO HAY PAGOS REALIZADOS "<<endl;
        return;
    }
    system("pause");
    system("cls");

    cout << "INGRESE EL ID PAGO A MODIFICAR: #";
  while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<=0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    break;
 }
    int pos = _repo.buscarIdPago(id);
    if (pos == -1) {
        cout << "PAGO NO ENCONTRADO " << endl;
        return;
    }

    Pagos pago = _repo.leer(pos);
    if(!pago.getEliminado()){
    mostrarPagos(pago);
    }
    else{
        cout<<"Este Pago esta Eliminado "<<endl;
        return;
    }

    system("pause");
    system("cls");

    int opcion;

    do {
        cout << "------ MODIFICAR PAGO ------" << endl;
        ///no se puede modificar los id ya que se generan automaticamente
        cout << "1. CAMBIAR METODO DE PAGO" << endl;
        cout << "2. CAMBIAR FECHA DE PAGO" << endl;
        cout << "3. CAMBIAR ESTADO (Pagado / Pendiente)" << endl;
        cout << "0. GUARDAR Y SALIR" << endl;
        cout << "OPCION: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {

        case 1: {
             int opcion;
             cout<<"~~~~~METODOS DISPONIBLES~~~~~"<<endl;
             cout<<" 1. EFECTIVO "<<endl;
             cout<<" 2. TARJETA "<<endl;
             cout<<" 3. TRANSFERENCIA O MERCADO PAGO "<<endl;
             cout<<" 0. Salir "<<endl;
             cout<<"OPCION: ";
             cin>>opcion;

              switch(opcion){
             case 1:
                 pago.setMetodoPago("Efectivo");
                break;
             case 2:
                pago.setMetodoPago("Tarjeta");
                break;
             case 3:
                pago.setMetodoPago("Transferencia");
                break;
             case 0:
                break;
              }
      break;
        }
        case 2: {
            Fecha nuevaFecha;
            cout << "NUEVA FECHA DE PAGO: " << endl;
            nuevaFecha.cargarFecha();
            pago.setFechaPago(nuevaFecha);
        break;
 }
        case 3: {
             int opcionE;
             cout<<"ESTADO DEL PAGO "<<endl;
             cout<<" 1. PAGADO "<<endl;
             cout<<" 2. PENDIENTE "<<endl;
             cout<<" 0. SALIR "<<endl;
             cout<<"OPCION: ";
             cin>>opcionE;

             if(opcionE==1)pago.setPagado(true);
             else if(opcionE==2)pago.setPagado(false);
             else{
                cout<<"OPCION INCORRECTA "<<endl;
             }
        break;
 }
        case 0:
            break;

        default:
            cout << "OPCION INVALIDA." << endl;
            break;
}
system("pause");
    } while (opcion != 0);

    if (_repo.guardar(pos, pago)) {
        cout << "PAGO MODIFICADO CORRECTAMENTE." << endl;
    } else {
        cout << "ERROR AL GUARDAR CAMBIOS." << endl;
    }
}

void ManagerPago::Activar(){
  int id, pos;
  char eliminar;
  int cantidad=_repo.getCantidadRegistros();
  bool encontrado=false;
    for(int i=0;i<cantidad;i++){
    Pagos pago=_repo.leer(i);
    if(pago.getEliminado()){
        cout<<"PAGOS ELIMINADOS "<<endl;
        cout<<"~ID: #"<<pago.getIdPago()<<" $"<<pago.getMontoTotal()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    cout<<"NO HAY EVENTO/SERVICIOS ELIMINADOS "<<endl;
    return;
  }

  cout<<"~~~~ ACTIVAR PAGO ~~~~"<<endl;
  cout<<"ID PAGO: ";
  cin>>id;
 while(true){
   if(!( cin>>id)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(id<=0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    break;
 }

  pos=_repo.buscarIdPago(id);
  if(pos==-1){
    cout<<"EL PAGO NO EXISTE "<<endl;
    return;
  }
  Pagos pago;
  pago= _repo.leer(pos);
    if(!pago.getEliminado()){
    cout<<"ERROR: EL PAGO NO ESTA ELIMINADO "<<endl;
    cout<<"No es necesario activar "<<endl;
    return;
  }

  cout<<"INFORMACION DEL PAGO ELIMINADO "<<endl;
  cout<<endl;
  mostrarPagos(pago);
  cout<<endl;
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  cin>>eliminar;
   if(eliminar=='s' or eliminar=='S'){
    pago.setEliminado(false);
   }
   if(_repo.guardar(pos,pago)){
    cout<<"GUARDADO CORRECTAMENTE "<<endl;
   }
   else {
    cout<<"OCURRIO UN ERROR "<<endl;
   }
}

void ManagerPago::calcularTotalAnual(){
    int anio,cantidad;
   cout<<"INGRESAR ANIO: ";
   while (true){
   if(!(cin >> anio)) {
    cin.clear();
    cin.ignore(9999,'\n');
    cout << "ANIO INVALIDO. INGRESE NUEVAMENTE: ";
    continue;
}
   if(anio<=0){
    cout<<"El anio no puede ser menor o igual a 0 "<<endl;
    continue;
   }
   break;
}
    float totalPago=0,totalEvento=0;
    cantidad=_repo.getCantidadRegistros();
    if(cantidad==0){
        cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
        return;
    }
    ArchivoEvento Arch;
    int cant=Arch.getCantidadRegistros();

   for(int i=0;i<cantidad;i++){
    Pagos pago=_repo.leer(i);
    if(!pago.getEliminado() && pago.getPagado()){
        Fecha fecha=pago.getFechaPago();
        if(fecha.getAnio()==anio){
            totalPago +=pago.getMontoTotal();
        }
    }
   }
    for(int x=0;x<cant;x++){
        Eventos even=Arch.leer(x);
        if(!even.getEliminado()){
            Fecha fech=even.getFechaPago();
            if(fech.getAnio()==anio && even.getPagoReserva()){
                totalEvento+=even.getPrecioInicial();
            }
        }
    }
 float totalAnual=totalPago + totalEvento;

   cout << fixed << setprecision(2);
   cout<<"EL TOTAL DEL ANIO "<<anio<<" ES "<<" $"<<totalAnual<<endl;
   cout<<"  ~Pagos Confirmados: $"<<totalPago<<endl;
   cout<<"  ~Reservas Iniciales: $"<<totalEvento<<endl;
}

void ManagerPago::mostrarRecaudacionxCliente(){
   ArchivoCliente arcCliente;
   ArchivoEvento arc;
   int cantClientes=arcCliente.getCantidadRegistros();
   int cantPagos=_repo.getCantidadRegistros();
   int cantEvento=arc.getCantidadRegistros();

   cout<<"------ RECAUDACION POR CLIENTE ------"<<endl;
   for(int i=0;i<cantClientes;i++){
    Cliente cliente= arcCliente.leer(i);
    float total=0;

      for(int x=0;x<cantPagos;x++){
        Pagos pago=_repo.leer(x);
        if(!pago.getEliminado() && pago.getPagado()&&pago.getIdCliente()==cliente.getidCliente()){
            total+=pago.getMontoTotal();
        }
      }
       for(int e=0;e<cantEvento;e++){
           Eventos evento=arc.leer(e);
         if(!evento.getEliminado()&&evento.getidCliente()==cliente.getidCliente()){
           if(evento.getPagoReserva()){
              total += evento.getPrecioInicial();
           }
       }
       }
        if(total>0){
            cout<<"~ CLIENTE: #"<<cliente.getidCliente()<<" ~ "<<cliente.getNombre()<<" "<<cliente.getApellido()<<endl;
            cout<<fixed<<setprecision(2);
            cout<<"  ~TOTAL: $"<<total<<endl;
        }
  }
}

///recaudacion por tipo de evento
void ManagerPago::recaudacionTipoEvento() {
    ArchivoEvento arcEventos;
    int cantEventos = arcEventos.getCantidadRegistros();
    int cantPagos   = _repo.getCantidadRegistros();

    if (cantEventos == 0 || cantPagos == 0) {
        cout << "NO HAY DATOS SUFICIENTES PARA GENERAR EL INFORME." << endl;
        return;
    }
    float totalPorTipo[6] = {};
    for (int i = 0; i < cantPagos; i++) {
        Pagos pago = _repo.leer(i);
        if (!pago.getEliminado() || !pago.getPagado()) {
            int posEvento = arcEventos.buscarIDEvento(pago.getIdEvento());
            if (posEvento != -1) {
                Eventos ev = arcEventos.leer(posEvento);
                int tipo = ev.getTipoEvento();
                if (tipo >= 0 && tipo <=5) {
                    totalPorTipo[tipo] += pago.getMontoTotal();
                    if(ev.getPagoReserva()){
                        totalPorTipo[tipo]+=ev.getPrecioInicial();
                    }
                }
            }
        }
    }
    cout << "--- RECAUDACION POR TIPO DE EVENTO ---" << endl;

    const char* nombres[6] = {"","BODA", "CUMPLEANIOS", "EMPRESARIAL", "BAUTISMO/COMUNION", "GRADUACION"};
    bool encontrado=false;
    for (int i = 1; i <= 5; i++) {
        if(totalPorTipo[i]>0){
                encontrado=true;
        cout << nombres[i] << ": $"<< fixed << setprecision(2) << totalPorTipo[i] << endl;
        }
    }
    if(!encontrado){
        cout<<"NO HAY RECAUDACION "<<endl;
    }
}

void ManagerPago::listarPendientes(){
    ArchivoEvento ArcEvento;
    ArchivoCliente ArcCliente;

    cout<<"~~~~~ EVENTOS CON PAGOS PENDIENTES ~~~~~"<<endl;

    int cantidad=ArcEvento.getCantidadRegistros();
    int cantClientes = ArcCliente.getCantidadRegistros();
    bool hay=false;
     for(int i=0;i<cantidad;i++){
       Eventos evento = ArcEvento.leer(i);

        if (!evento.getEliminado() && !evento.getEstado()) {
            for (int j = 0; j < cantClientes; j++) {
               Cliente cliente = ArcCliente.leer(j);
                if (cliente.getidCliente() == evento.getidCliente()) {
                   cout << "EVENTO: #" << evento.getIdEvento() << " " << evento.getNombreEvento() << endl;
                   cout << "CLIENTE: #" << cliente.getidCliente() << " " << cliente.getNombre() << endl;
                   cout<<"--------------------------------"<<endl;
                   hay=true;
                   break;
            }
        }
    }
}
       if(!hay){
        cout<<"NO HAY EVENTOS PENDIENTES "<<endl;
       }
}

///verificar si funciona
void ManagerPago::listarAtrasados(){
    ArchivoEvento arc;
   int cantidadP=_repo.getCantidadRegistros();

   if(cantidadP ==0){
    cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
    return;
   }
   cout<<"------PAGOS ATRASADOS------"<<endl;

   bool hay=false;
   for(int i=0;i<cantidadP;i++){
    Pagos pago=_repo.leer(i);
    if(!pago.getEliminado()){
        int posEvento=arc.buscarIDEvento(pago.getIdEvento());
        if(posEvento!=-1){
            Eventos evento=arc.leer(posEvento);
            Fecha FechaPago=pago.getFechaPago();
            Fecha FechaEvento=evento.getFechaEvento();
            if(FechaPago > FechaEvento){
                hay=true;
                cout<<"ID PAGO: #"<<pago.getIdPago()<<endl;
                cout<<" ~ EVENTO: "<<evento.getNombreEvento()<<endl;
                cout<<" ~ MONTO: $"<<pago.getMontoTotal()<<endl;
            }
        }
    }
   }
   if(!hay){
    cout<<" NO HAY PAGOS ATRASADOS "<<endl;
   }
}

void ManagerPago::submenuPago(){
 int opcion;
 do{
    system("cls");
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"1. TOTAL ANUAL "<<endl;
    cout<<"2. TOTAL POR CLIENTE "<<endl;
    cout<<"3. TOTAL POR TIPO DE EVENTO "<<endl;
    cout<<"0. volver al menu pagos"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"OPCION: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
    case 1:
        calcularTotalAnual();
        break;
    case 2:
        mostrarRecaudacionxCliente();
        break;
    case 3:
        recaudacionTipoEvento();
        break;
    case 0:
        break;
    default:
        cout<<"Opcion incorrecta, volve a intentar "<<endl;
        break;
    }
    system("pause");
 }while (opcion!=0);
}

void ManagerPago::buscar(){
     int opcion;
 do{
    system("cls");
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"1. BUSCAR POR ID "<<endl;
    cout<<"2. BUSCAR ID CLIENTE "<<endl;
    cout<<"3. BUSCAR POR FECHA "<<endl;
    cout<<"0. volver al menu anterior"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"OPCION: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
    case 1:
       buscarIdPagos();
        break;
    case 2:
        buscarPorCliente();
        break;
    case 3:
        buscarXfecha();
        break;

    case 0:
        break;
    default:
        cout<<"Opcion incorrecta, volve a intentar "<<endl;
        break;
    }
    system("pause");
 }while (opcion!=0);
}

void ManagerPago::mostrarPagosxEstados(){
   int opcion;
   do{
    system("cls");
   cout<<"1. LISTAR PAGADOS "<<endl;
   cout<<"2. LISTAR PENDIENTES "<<endl;
   cout<<"3. LISTAR ATRASADOS "<<endl;
   cout<<"0. SALIR "<<endl;
   cout<<"OPCION: ";
   cin>>opcion;
   system("cls");
   switch(opcion){
   case 1:
       listarPagos();
    break;
   case 2:
    listarPendientes();
    break;
   case 3:
   listarAtrasados();
    break;
   case 0:
    break;
   default:
       cout<<"Opcion incorrecta "<<endl;
    break;
   }

    system("pause");
   }while(opcion!=0);

}

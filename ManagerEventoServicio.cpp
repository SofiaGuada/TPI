# include<iostream>
#include <iomanip>
#include "ManagerEventoServicio.h"
#include "ArchivoEvento.h"
#include "Eventos.h"
#include "ArchivoServicios.h"
#include "Servicios.h"
#include "ArcPagos.h"

using namespace std;

ManagerEventoServicio::ManagerEventoServicio()
{
    //ctor
}

void ManagerEventoServicio::cargarEventosyServicios(){
    int idE,idS,cantidad;

    ArchivoEvento arcE;
    int cant = arcE.getCantidadRegistros();

      if (cant==0){
        cout<<"NO HAY EVENTOS REGISTRADOS. "<<endl;
        return;
      }

     cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
     bool encontrado=false;
      for(int i=0;i<cant;i++){
        Eventos evento=arcE.leer(i);
        if(!evento.getEliminado() && evento.getConfirmado()){
            encontrado=true;
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<"| ID CLIENTE: #"<<evento.getidCliente()<<"|"<<endl;
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
            cout<<"CANTIDAD DE INVITADOS: "<<evento.getcantidadInvitados()<<endl;
            cout<<"-------------------------------"<<endl;
        }
      }
      if(!encontrado){
        cout<<"NO HAY EVENTOS DISPONIBLES PARA AGREGAR SERVICIOS "<<endl;
        return;
      }
		system("pause");
		system("cls");

    while(true){
        cout<<"INGRESAR EL ID EVENTO (0 para volver): ";

		if(!(cin>>idE)){
            cin.clear();
            cin.ignore(9999,'\n');
            cout<<"Debe ingresar un numero valido "<<endl;
            continue;
		}
		if(idE<0){
            cout<<"NO PUEDE SER MENOR A 0 "<<endl;
            continue;
		}
		if(idE==0){
            return;
		}

		bool Eventoexistente=false;
		for(int i=0;i<cant;i++){
            Eventos evento=arcE.leer(i);
            if(evento.getIdEvento()==idE && !evento.getEliminado() && evento.getConfirmado()){
                Eventoexistente=true;
                break;
            }
		}
		if(!Eventoexistente){
            cout<<"EL EVENTO NO EXISTE "<<endl;
            continue;
		}
		break;
    }
		bool hayserviciosEv=false;
		int CantEvS=_repo.getCantidadRegistros();
        cout<<"---- SERVICIOS DEL EVENTO ----"<<endl;

		for(int i=0;i<CantEvS;i++){
            EventoServicios EvenSer=_repo.leer(i);
            if(EvenSer.getIdEvento()==idE && !EvenSer.getEliminado()){
                cout << fixed << setprecision(2);
                cout<<"ID SERVICIO:#"<<EvenSer.getIdServicio()<<" (CANTIDAD: "<<EvenSer.getCantidadContratado()<<") $"<<EvenSer.getPrecioUnitario()<<endl;
                hayserviciosEv=true;
            }
		}
		if(!hayserviciosEv){
            cout<<"ESTE EVENTO NO TIENE SERVICIOS ASOCIADOS "<<endl<<endl;
		}

		cout<<endl;
///---------------------
		char continuar;
        cout<<"QUIERE AGREGAR SERVICIOS AL EVENTO ? (s/n) ";
		cin>>continuar;


            if(continuar=='n'|| continuar=='N'){
                cout<<"NO SE AGREGAN SERVICIOS AL EVENTO "<<endl;
                return;
            }

         ArchivoServicios arcS;
		int Cant= arcS.getCantidadRegistros();

		if (Cant==0){
			cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
			return;
		}
		while (continuar=='s'||continuar=='S'){

		cout<<"--- SERVICIOS DISPONIBLES ---"<<endl;

		for(int i=0;i<Cant;i++){
			Servicios servis=arcS.leer(i);
			if(!servis.getEliminado()){
				cout<<"ID SERVICIO: #"<<servis.getIdServicio()<<endl;
				cout<<"NOMBRE: "<<servis.getNombreServicio()<<endl;
				cout<<"DESCRIPCION: "<<servis.getDescripcion()<<endl;
				cout<<"PROVEEDOR: "<<servis.getProveedor()<<endl;
                cout<<fixed<<setprecision(2);
				cout<<"PRECIO: $"<<servis.getPrecio()<<endl;
				cout<<"-------------------------------"<<endl;
			}
		}
        system("pause");
		system("cls");

		cout<<"~~~~ AGREGAR SERVICIOS AL EVENTO ~~~~"<<endl;
   while (true) {
      cout<<"ID SERVICIO: #";

      if (!(cin>>idS)){
        cin.clear();
        cin.ignore(9999, '\n');
        cout<<"ERROR: Debe ingresar un numero valido "<<endl;
        continue;
    }
    bool existe=false;
    for (int i=0; i<Cant; i++) {
        Servicios ser=arcS.leer(i);
        if (ser.getIdServicio()==idS && !ser.getEliminado()){
            existe=true;
            break;
        }
    }
    if (!existe) {
        cout<<"Intente nuevamente "<<endl;
        continue;
    }
    break;
}

    while(true){
        cout<<"CANTIDAD: ";
        if (!(cin >> cantidad)){
            cin.clear();
            cin.ignore(9999, '\n');
            cout<< "Debe ingresar un numero valido "<<endl;
            continue;
        }
        if(cantidad <=0){
            cout<<"La cantidad debe ser mayor a 0 "<<endl;
            continue;
        }
        break;
    }

    bool duplicado=false;
    int canti=_repo.getCantidadRegistros();
    for(int i=0; i<canti; i++) {
         EventoServicios ev = _repo.leer(i);
      if(!ev.getEliminado()&&ev.getIdEvento()==idE &&ev.getIdServicio()==idS){
         duplicado=true;
         break;
       }
    }
    if(duplicado){
       cout<<" ESTE SERVICIO YA ESTA ASOCIADO AL EVENTO "<<endl;
       cout<<" NO SE PUEDE DUPLICAR "<<endl;

       cout<<"Desea intentar con otro servicio? (s/n): ";
       cin>>continuar;

        if(continuar =='s' || continuar == 'S')
           continue;
    else{
        return;
        }
    }
        float precioUnitario=0;
		string nombreEvento,nombreServicio;

		for(int i=0;i<Cant;i++){
			Servicios servi =arcS.leer(i);
			if(servi.getIdServicio()==idS ){
                cout<<fixed<<setprecision(2);
				precioUnitario=servi.getPrecio();
				nombreServicio=servi.getNombreServicio();
			}
		}
		for(int i=0;i<cant;i++){
			Eventos eve =arcE.leer(i);
			if(eve.getIdEvento()==idE){
				nombreEvento=eve.getNombreEvento();
			}
		}
    EventoServicios eventoServis(idE,idS,cantidad,precioUnitario,nombreEvento,nombreServicio);
		if(_repo.guardar(eventoServis)){
			cout<<" GUARDADO CORRECTAMENTE "<<endl;
		}
		else {
			cout<<" HUBO UN ERROR AL GUARDAR "<<endl;
		}
		cout<<"QUIERE AGREGAR MAS SERVICIOS AL EVENTO ? (s/n) ";
		cin>>continuar;
}
}


void ManagerEventoServicio::mostrarEventoyServicios(EventoServicios Evenservis){
    float total= Evenservis.getCantidadContratado()*Evenservis.getPrecioUnitario();
      cout<<"ID EVENTO: #"<<Evenservis.getIdEvento()<<" "<<Evenservis.getNombreEvento()<<endl;
      cout<<"ID SERVICIO: #"<<Evenservis.getIdServicio()<<" "<<Evenservis.getNombreServicios()<<endl;
      cout<<"CANTIDAD: "<<Evenservis.getCantidadContratado()<<endl;
      cout<<"PRECIO: $"<<Evenservis.getPrecioUnitario()<<endl;
      cout<<fixed<<setprecision(2);
      cout<<"TOTAL DEL SERVICIOS: $"<<total<<endl;
      if(Evenservis.getEliminado()){
        cout<<"[ELIMINADO] "<<endl;
      }
}

void ManagerEventoServicio::mostrarEventoCompleto(int idEvento){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    cout<<"~~~~ EVENTO #"<<idEvento<<" ~~~~"<<endl;

    for (int i=0; i<cantidad; i++) {
        EventoServicios es=_repo.leer(i);
        if(es.getIdEvento()==idEvento && es.getEliminado()){
            if(!encontrado){
                cout<<"Servicios eliminados del evento:"<<endl;
                encontrado=true;
            }
            cout<<" - Servicio #"<<es.getIdServicio()<<" "<<es.getNombreServicios()<<" x "<< es.getCantidadContratado();
            cout<<" ($"<<es.getPrecioUnitario()*es.getCantidadContratado()<< ")"<<endl;
        }
    }
    if(!encontrado){
        cout<<"Este evento no tiene servicios eliminados "<<endl;
    }
}

void ManagerEventoServicio::listarEventoyServicios(){
    int cantidad=_repo.getCantidadRegistros();

    if(cantidad==0){
        cout<<"NO HAY SERVICIOS CARGADOS EN EVENTOS "<<endl;
        return;
    }
    int i = 0;
    int eventoActual=-1;
    float totalEvento=0;
    bool hayServicios=false;

    while(i<cantidad){
        EventoServicios es=_repo.leer(i);
        if(!es.getEliminado()){
            hayServicios=true;
            if(es.getIdEvento()!=eventoActual){
                if(eventoActual!=-1){
                    cout<<fixed << setprecision(2);
                    cout<<" TOTAL SERVICIOS DEL EVENTO: $"<<totalEvento<<endl;
                    cout<<"--------------------------"<<endl;
                }

                eventoActual=es.getIdEvento();
                totalEvento=0;
                cout<<"EVENTO #"<<es.getIdEvento()<<" - "<<es.getNombreEvento()<<endl;
            }

            cout<<" - SERVICIO: "<<es.getNombreServicios()<<endl;
            cout<<"    CANTIDAD: "<<es.getCantidadContratado()<<endl;
            cout<<fixed << setprecision(2);
            cout<<"    UNITARIO: $"<<es.getPrecioUnitario()<<endl;
            totalEvento+=es.getPrecioUnitario() * es.getCantidadContratado();
        }
        i++;
    }
    if(eventoActual!=-1) {
        cout<<fixed << setprecision(2);
        cout<<" TOTAL SERVICIOS DEL EVENTO: $"<<totalEvento<<endl;
        cout<<"--------------------------"<<endl;
    }
    if(!hayServicios) {
        cout<<"NO HAY SERVICIOS ACTIVOS EN LOS EVENTOS "<<endl;
    }
}

void ManagerEventoServicio::buscarIdEventoServicios(){
    ///primero encuentro el id del evento, asi solo muestra el encabezado
    ///despues busca sus servicios, y los lista tambien calcula el total
    int idE;
    cout << "BUSCAR EL EVENTO POR ID " << endl;
    cout << "INGRESAR ID EVENTO: # (0 para cancelar): ";

   while(true){
     if(!( cin>>idE)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(idE<0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    if(idE==0){
            return;
    }
    break;
}
    cin.ignore();
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    float totalEvento=0;
    for(int i=0; i<cantidad; i++) {
        EventoServicios Es=_repo.leer(i);
        if(!Es.getEliminado()&&Es.getIdEvento()==idE){
            cout<<"----- EVENTO #"<<idE<<" - "<<Es.getNombreEvento()<<" -----"<<endl;
            encontrado=true;
            break;
        }
    }
    if(!encontrado) {
        cout<<"NO SE ENCONTRO EL EVENTO "<<endl;
        return;
    }
    for(int i=0; i<cantidad; i++){
        EventoServicios Es=_repo.leer(i);
        if(!Es.getEliminado() && Es.getIdEvento()==idE){
            cout<<"~ Servicio: "<<Es.getNombreServicios()<<endl;
            cout<<"~ Cantidad: "<<Es.getCantidadContratado()<<endl;
            cout<<"~ Unitario: $"<<Es.getPrecioUnitario()<<endl;
            cout<<"---------------------------"<<endl;
            totalEvento += Es.getPrecioUnitario()*Es.getCantidadContratado();
        }
    }
    cout<<fixed<<setprecision(2);
    cout<<"TOTAL DE SERVICIOS CONTRATADOS: $"<<totalEvento<<endl<<endl;
}

float ManagerEventoServicio::calcularTotalEvento(int idEvento){
    float total= 0;
    int cantidad=_repo.getCantidadRegistros();

    for(int i=0; i<cantidad; i++){
        EventoServicios es=_repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            total+=es.getPrecioUnitario()* es.getCantidadContratado();
        }
    }
    return total;
}

void ManagerEventoServicio::eliminar(){
  int opcion;
  do {
        system("cls");
  cout<<"------------------------------"<<endl;
  cout<<"1. ELIMINAR  "<<endl;
  cout<<"2. ELIMINAR SERVICIO DEL EVENTO "<<endl;
  cout<<"3. MOSTRAR ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"------------------------------"<<endl;
  cout<<"OPCION: ";
  cin>>opcion;
  system("cls");
  switch(opcion){
  case 1:
      eliminarEventoServicio();
      break;
  case 2:
      eliminarServicioDelEvento();
    break;
  case 3:
    mostrarEliminados();
    break;
  case 0:
    return;
default:
    cout<<"Opcion invalida, volve a intentar "<<endl;
    break;
   }
   system("pause");
  }while(opcion!=0);
}

void ManagerEventoServicio::eliminarEventoServicio() {
    ArchivoEvento arcE;
    int cantE = arcE.getCantidadRegistros();

    if(cantE==0){
        cout<<"NO HAY EVENTOS REGISTRADOS"<<endl;
        return;
    }

    cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
    bool hay=false;

    for(int i=0;i<cantE;i++){
        Eventos ev = arcE.leer(i);
        if(!ev.getEliminado() && ev.getConfirmado()){
            cout<<"ID EVENTO: #"<<ev.getIdEvento()<<" "<<ev.getNombreEvento()<<endl;
            hay=true;
        }
    }

    if(!hay){
        cout<<"NO HAY EVENTOS DISPONIBLES"<<endl;
        return;
    }

    int idEvento;

    while(true){
        cout<<"INGRESE ID EVENTO (0 para cancelar): ";
        if(!(cin>>idEvento)){
            cin.clear();
            cin.ignore(9999,'\n');
            cout<<"Debe ingresar un numero valido"<<endl;
            continue;
        }
        if(idEvento==0) return;

        bool existe=false;
        Eventos evento;

        for(int i=0;i<cantE;i++){
            Eventos ev = arcE.leer(i);
            if(!ev.getEliminado() &&
               ev.getConfirmado() &&
               ev.getIdEvento()==idEvento){
                evento = ev;
                existe=true;
                break;
            }
        }

        if(!existe){
            cout<<"EL EVENTO NO EXISTE O ESTA CANCELADO"<<endl;
            continue;
        }

        if(eventoPagado(idEvento)){
            cout<<"NO SE PUEDE ELIMINAR: EVENTO PAGADO"<<endl;
            return;
        }

        break;
    }

    int totalES = _repo.getCantidadRegistros();
    bool tieneServicios=false;

    cout<<"--- SERVICIOS ASOCIADOS ---"<<endl;

    for(int i=0;i<totalES;i++){
        EventoServicios es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            cout<<"- "<<es.getNombreServicios()<<endl;
            tieneServicios=true;
        }
    }

    if(!tieneServicios){
        cout<<"EL EVENTO NO TIENE SERVICIOS ASOCIADOS"<<endl;
    }

    char eliminar;
    cout<<"CONFIRMA ELIMINAR EVENTO Y SUS SERVICIOS? (S/N): ";
    cin>>eliminar;

    if(eliminar!='S' && eliminar!='s'){
        cout<<"OPERACION CANCELADA"<<endl;
        return;
    }

    for(int i=0;i<totalES;i++){
        EventoServicios es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            es.setEliminado(true);
            _repo.guardar(i,es);
        }
    }

    for(int i=0;i<cantE;i++){
        Eventos ev = arcE.leer(i);
        if(ev.getIdEvento()==idEvento){
            ev.setEliminado(true);
            arcE.guardar(i,ev);
            break;
        }
    }

    cout<<"EVENTO Y SERVICIOS ELIMINADOS CORRECTAMENTE"<<endl;
}


void ManagerEventoServicio::eliminarServicioDelEvento() {
    ArchivoEvento arcE;
    int cantE = arcE.getCantidadRegistros();

    if(cantE == 0){
        cout<<"NO HAY EVENTOS REGISTRADOS"<<endl;
        return;
    }

    cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
    bool hayEventos=false;

    for(int i=0;i<cantE;i++){
        Eventos ev = arcE.leer(i);
        if(!ev.getEliminado() && ev.getConfirmado()){
            cout<<"ID EVENTO: #"<<ev.getIdEvento() <<" "<<ev.getNombreEvento()<<endl;
            hayEventos=true;
        }
    }

    if(!hayEventos){
        cout<<"NO HAY EVENTOS DISPONIBLES"<<endl;
        return;
    }

    int idEvento;

    while(true){
        cout<<"INGRESE EL ID EVENTO (0 para volver): ";
        if(!(cin>>idEvento)){
            cin.clear();
            cin.ignore(9999,'\n');
            cout<<"Debe ingresar un numero valido"<<endl;
            continue;
        }
        if(idEvento==0) return;

        bool existe=false;
        Eventos evento;

        for(int i=0;i<cantE;i++){
            Eventos ev = arcE.leer(i);
            if(!ev.getEliminado() &&ev.getConfirmado() &&ev.getIdEvento()==idEvento){
                evento = ev;
                existe=true;
                break;
            }
        }

        if(!existe){
            cout<<"EL EVENTO NO EXISTE O NO ESTA ACTIVO"<<endl;
            continue;
        }

        if(eventoPagado(idEvento)){
            cout<<"NO SE PUEDEN MODIFICAR SERVICIOS: EVENTO PAGADO"<<endl;
            return;
        }

        break;
    }

    int totalES = _repo.getCantidadRegistros();
    bool hayServicios=false;

    cout<<"--- SERVICIOS DEL EVENTO ---"<<endl;

    for(int i=0;i<totalES;i++){
        EventoServicios es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            cout<<"ID SERVICIO: #"<<es.getIdServicio()<<" | CANT: "<<es.getCantidadContratado()<<endl;
            hayServicios=true;
        }
    }

    if(!hayServicios){
        cout<<"EL EVENTO NO TIENE SERVICIOS ASOCIADOS"<<endl;
        return;
    }

    int idServicio;

    while(true){
        cout<<"INGRESE EL ID DEL SERVICIO A ELIMINAR: ";
        if(!(cin>>idServicio)){
            cin.clear();
            cin.ignore(9999,'\n');
            cout<<"Debe ingresar un numero valido"<<endl;
            continue;
        }
        bool encontrado=false;
        for(int i=0;i<totalES;i++){
            EventoServicios es = _repo.leer(i);
            if(!es.getEliminado() &&es.getIdEvento()==idEvento && es.getIdServicio()==idServicio){
                es.setEliminado(true);
                if(_repo.guardar(i,es)){
                    cout<<"SERVICIO ELIMINADO CORRECTAMENTE"<<endl;
                } else {
                    cout<<"ERROR AL ELIMINAR"<<endl;
                }
                encontrado=true;
                break;
            }
        }
        if(!encontrado){
            cout<<"ESE SERVICIO NO ESTA ASOCIADO AL EVENTO"<<endl;
            continue;
        }

        break;
    }
}

void ManagerEventoServicio::mostrarEliminados() {
    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;
    int eventoActual=-1;

    cout<<"--- EVENTOS/SERVICIOS ELIMINADOS ---"<<endl;

    for(int i=0; i<cantidad; i++) {
        EventoServicios Evservis = _repo.leer(i);
        if(Evservis.getEliminado()){
            encontrado = true;
            if(Evservis.getIdEvento()!=eventoActual){
                eventoActual=Evservis.getIdEvento();
                cout<<"---- EVENTO #"<<eventoActual<<" ----"<<endl;
            }
            cout<<"~ Servicio #"<<Evservis.getIdServicio()<<" "<<Evservis.getNombreServicios()<<endl;
            cout<<" Cantidad "<<Evservis.getCantidadContratado()<<" ($"<<Evservis.getPrecioUnitario()*Evservis.getCantidadContratado()<<") "<<endl;
        }
    }
    if(!encontrado){
        cout << "NO HAY EVENTOS/SERVICIOS ELIMINADOS" << endl;
    }
}

void ManagerEventoServicio::modificarEventoyServicio() {
    cout<<"=== EVENTOS Y SERVICIOS CARGADOS ==="<<endl;
    listarEventoyServicios();
    cout<<"===================================="<<endl;

    int idEvento;
    cout<<"INGRESE EL ID EVENTO: #";
  while(true){
   if(!( cin>>idEvento)){
        cin.clear();
        cin.ignore(9999,'\n');
        cout<<"Debe ingresar un numero: "<<endl;
        continue;
    }
    if(idEvento<=0){
        cout<<"EL ID NO PUEDE SER MENOR O IGUAL A 0 "<<endl;
        continue;
    }
    break;
 }
   if (eventoPagado(idEvento)) {
    cout << "EL EVENTO YA ESTA PAGADO. NO SE PUEDE MODIFICAR." << endl;
    system("pause");
    return;
}
    int cant = _repo.getCantidadRegistros();
    EventoServicios es;
    bool hayServicios = false;

    system("pause");
    system("cls");

    cout<<"--- SERVICIOS DEL EVENTO #"<<idEvento<<" ---"<<endl;
    for(int i = 0; i < cant; i++) {
        es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento() == idEvento) {
            cout<<"Servicio ID: #" << es.getIdServicio()<<" "<<es.getNombreServicios()<<",  Cantidad: "<<es.getCantidadContratado()<<endl;
            hayServicios = true;
        }
    }
    if(!hayServicios) {
        cout<<"EL EVENTO NO TIENE SERVICIOS ASOCIADOS." << endl;
        return;
    }
    int idServicioElegido;
    cout<<"INGRESE EL ID SERVICIO A MODIFICAR: #";
    cin>>idServicioElegido;

    int posReal = -1;

    for(int i=0; i<cant; i++) {
        es=_repo.leer(i);
        if(!es.getEliminado()&& es.getIdEvento() == idEvento&& es.getIdServicio() == idServicioElegido) {
            posReal=i;
            break;
        }
    }
    if(posReal==-1) {
        cout<<"SERVICIO NO ENCONTRADO PARA ESE EVENTO "<<endl;
        return;
    }
    EventoServicios eventoServi =_repo.leer(posReal);

    system("pause");
    system("cls");

    int opcion;
    do {
        system("cls");
        cout<<"MODIFICAR SERVICIO DEL EVENTO "<<endl;
        cout<<"1. CAMBIAR ID SERVICIO "<<endl;
        cout<<"2. CAMBIAR CANTIDAD "<<endl;
        cout<<"0. GUARDAR Y SALIR "<<endl;
        cin>>opcion;
        system("cls");

 switch(opcion){
   case 1:{
    ArchivoServicios arcS;
    int cantS = arcS.getCantidadRegistros();

    cout<<"SERVICIOS DISPONIBLES:"<<endl;
    for (int i = 0; i < cantS; i++) {
        Servicios s = arcS.leer(i);
        if (!s.getEliminado()) {
            cout<<"#"<<s.getIdServicio()<<" - "<<s.getNombreServicio()<<" $ "<<s.getPrecio()<<endl;
        }
    }
    cout<<endl;

    cout<<"ID actual: #"<<eventoServi.getIdServicio()<<endl;
    int nuevoId;
    cout<<"Nuevo ID: #";

    if (!(cin >> nuevoId)) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout<<"Por favor, ingrese un numero valido "<<endl;
        continue;
    }
    if (nuevoId == 0) {
        cout<<"Operación cancelada "<<endl;
        break;
    }
    bool existeNuevo = false;
    Servicios nuevo;
    for (int i = 0; i < cantS; i++) {
        Servicios ser = arcS.leer(i);
        if (ser.getIdServicio() == nuevoId && !ser.getEliminado()) {
            nuevo = ser;
            existeNuevo = true;
            break;
        }
    }
    if (!existeNuevo) {
        cout<<"El ID servicio no existe "<<endl;
        break;
    }
    for (int i = 0; i < cant; i++) {
        EventoServicios aux = _repo.leer(i);
        if (!aux.getEliminado() &&
            aux.getIdEvento() == idEvento &&
            aux.getIdServicio() == nuevoId &&
            i != posReal) { /// para evitar compararse con sí mismo
            cout<<"Ese servicio ya esta agregado a este evento. No se puede duplicar "<<endl;
            existeNuevo = false;
            break;
        }
    }
    if (!existeNuevo) {
        break;
    }
    eventoServi.setIdServicio(nuevoId);
    eventoServi.setNombreServicio(nuevo.getNombreServicio());
    eventoServi.setPrecioUnitario(nuevo.getPrecio());
    break;
}
   case 2:{
        cout<<"Cantidad actual: "<<eventoServi.getCantidadContratado()<<endl;
        int nuevaCant;
      while (true) {
         cout<<"Nueva cantidad: ";
         cin>>nuevaCant;

      if (!cin) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout<<"Por favor, ingrese un numero valido "<<endl;
        continue;
    }
    if (nuevaCant > 0) {
        eventoServi.setCantidadContratado(nuevaCant);
        break;
    }
    cout<<"...TIENE QUE SER MAYOR A 0, VUELVA A INTENTAR... "<<endl;
  }
 break;
}
    case 0:
        _repo.guardar(posReal, eventoServi);
        cout<<"CAMBIOS GUARDADOS "<<endl;
        break;
        }
    system("pause");
    } while(opcion != 0);
}

void ManagerEventoServicio::Activar(){
  int id, pos;
  char activar;
  int cantidad=_repo.getCantidadRegistros();
  bool encontrado=false;
    for(int i=0;i<cantidad;i++){
    EventoServicios eveSer=_repo.leer(i);
    if(eveSer.getEliminado()){
        cout<<"EVENTO/SERVICIOS ELIMINADOS "<<endl;
        cout<<"~ID: #"<<eveSer.getIdEvento()<<" "<<eveSer.getNombreEvento()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    cout<<"NO HAY EVENTO/SERVICIOS ELIMINADOS "<<endl;
    return;
  }
  system("pause");
  system("cls");

  cout<<"~~~~ ACTIVAR EVENTOS/SERVICIOS ~~~~"<<endl;
  cout<<"ID EVENTO: ";

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
  pos=_repo.buscarID(id);
  if(pos==-1){
    cout<<"EL EVENTOS/SERVICIO NO EXISTE "<<endl;
    return;
  }
  EventoServicios Evservis;
  Evservis= _repo.leer(pos);

    if(!Evservis.getEliminado()){
    cout<<"HAY UN ERROR: EL EVENTO/SERVICIO NO ESTA ELIMINADO "<<endl;
    cout<<"No es necesario activar "<<endl;
    return;
  }
  system("pause");
  system("cls");

  cout<<"INFORMACION DEL EVENTO/SERVICIO ELIMINADO "<<endl;
  cout<<endl;
  mostrarEventoCompleto(id);
  cout<<endl;
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  cin>>activar;
   if(activar=='s' or activar=='S'){
    Evservis.setEliminado(false);
   }
    int activarS=0;
    for(int i=0;i<cantidad;i++){
        EventoServicios evse=_repo.leer(i);
        if(evse.getIdEvento()==id && evse.getEliminado()){
            evse.setEliminado(false);
            _repo.guardar(i,evse);
            activarS++;
        }
    }
    cout<<"SE ACTIVARON "<<activarS<<" SERVICIOS DEL EVENTO: #"<<id<<endl;
}

void ManagerEventoServicio::serviciosMasContratados(){
    int cantidadES=_repo.getCantidadRegistros();
    if(cantidadES==0){
        cout<<"NO HAY SERVICIOS CONTRATADOS "<<endl;
        return;
    }
    ArchivoServicios arcServis;
    int cantServicios=arcServis.getCantidadRegistros();

    int *Id= new int[cantServicios];
    string *nombres= new string[cantServicios];
    int *cant= new int [cantServicios];

    int totalEncontrado=0;

    for(int i=0;i<cantServicios;i++){
        Servicios ser= arcServis.leer(i);
        int buscarId=ser.getIdServicio();
        int acumulador=0;

         for(int x=0; x<cantidadES;x++){
            EventoServicios eves=_repo.leer(x);
            if(eves.getEliminado()) continue;
            if(eves.getIdServicio()==buscarId){
                acumulador +=eves.getCantidadContratado();
            }
         }
         if(acumulador>0){
            Id[totalEncontrado]=buscarId;
            nombres[totalEncontrado]=ser.getNombreServicio();
            cant[totalEncontrado]=acumulador;
            totalEncontrado++;
         }
    }
    if(totalEncontrado==0){
        cout<<"NO HAY SERVICIOS CONTRATADOS "<<endl;
        delete[] Id;
        delete[] nombres;
        delete[] cant;
        return;
    }
     for(int i=0;i<totalEncontrado-1;i++){
        for(int x=0; x<totalEncontrado -i-1;x++){
            if(cant[x]<cant[x+1]){
                int AuxCant= cant[x];
                cant[x]=cant[x+1];
                cant[x+1]=AuxCant;
                int AuxId=Id[x];
                Id[x]=Id[x+1];
                Id[x+1]=AuxId;
                string AuxNom= nombres[x];
                nombres[x]=nombres[x+1];
                nombres[x+1]=AuxNom;
            }
        }
     }
     cout<<"~~~~~ SERVICIOS MAS CONTRATADOS ~~~~~"<<endl;
     for(int i=0;i<totalEncontrado;i++){
        cout<<"#"<<Id[i]<<" "<<nombres[i]<<" (CANTIDAD CONTRATADOS: "<<cant[i]<<") "<<endl;
     }
     cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

    delete[] Id;
    delete[] nombres;
    delete[] cant;
}

void ManagerEventoServicio::cancelarServiciosPorEvento(int idEvento) {
    int cant = _repo.getCantidadRegistros();
    for (int i=0; i<cant; i++) {
        EventoServicios es=_repo.leer(i);
        if(es.getIdEvento() ==idEvento && !es.getEliminado()){
            es.setActivo(false);     /// servicio cancelado
            _repo.guardar(i,es);
        }
    }
}

bool ManagerEventoServicio::eventoPagado(int idEvento){
    ArcPagos arc;
    int cant = arc.getCantidadRegistros();
    for(int i=0;i<cant;i++){
        Pagos pago = arc.leer(i);
        if(!pago.getEliminado() &&pago.getIdEvento()==idEvento &&pago.getPagado()){
            return true;
        }
    }
    return false;
}

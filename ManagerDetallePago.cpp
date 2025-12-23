# include<iostream>
#include <iomanip>
#include "ManagerDetallePago.h"
#include "ArcEventoServicios.h"
#include "EventoServicios.h"
#include "ArchivoServicios.h"
#include "Servicios.h"
#include "ArcPagos.h"
#include "Pagos.h"
using namespace std;

ManagerDetallePago::ManagerDetallePago()
{
    //ctor
}

void ManagerDetallePago::cargarDetallePagos(int idEvento,int idPago){
     ArcEventoServicios ArcEvS;
     ArchivoServicios ArcSer;

     int cantidad=ArcEvS.getCantidadRegistros();

     for(int i=0;i<cantidad;i++){
        EventoServicios eventos=ArcEvS.leer(i);
        if(!eventos.getEliminado() && eventos.getIdEvento()==idEvento){
        int cantServicios = ArcSer.getCantidadRegistros();
        for (int j = 0; j < cantServicios; j++) {
            Servicios servis = ArcSer.leer(j);

        if(!servis.getEliminado() && eventos.getIdServicio()==servis.getIdServicio()){
            DetallePago Dpago;
            Dpago.setIdPago(idPago);
            Dpago.setIdServicio(servis.getIdServicio());
            Dpago.setCantidad(eventos.getCantidadContratado());
            Dpago.setMonto(servis.getPrecio());
            _repo.guardar(Dpago);
        }
        }
     }
}
}

void ManagerDetallePago::mostrarDetallePagos(){
    int idPago;
    cout<<"INGRESE ID PAGO: #";
    cin>>idPago;
//    system("pause");
//    system("cls");
    ArcPagos arc;
    int pos=arc.buscarIdPago(idPago);
    if(pos==-1){
        cout<<"NO HAY PAGOS CON ESE ID "<<endl;
        return;
    }
    Pagos pago=arc.leer(pos);
    if(!pago.getPagado()){
        cout<<"ESTE ID NO TIENE REGISTRO DE HABER PAGADO. "<<endl;
        return;
    }

    int cantidad=_repo.getCantidadRegistros();
    float total=0;
    cout<<"-----DETALLE DE PAGO-----"<<endl;
    cout<<" ID PAGO: #"<<idPago<<endl;
    cout<<"| ID SERVICIO | CANTIDAD |   MONTO     | "<<endl;

    for(int i=0;i<cantidad; i++){
        DetallePago detalle=_repo.leer(i);
        if(detalle.getIdPago()==idPago){
cout<<"|     "<<detalle.getIdServicio()<<"       |   "<<detalle.getCantidad()<<"      |  $"<<fixed<<setprecision(2)<<detalle.getMonto()<<" |"<<endl;
        total +=detalle.getMonto()*detalle.getCantidad();
        }
    }
    cout<<fixed<<setprecision(2);
    cout<<"TOTAL $ "<<total<<endl;
}


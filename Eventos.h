#pragma once
#include <string>
#include "Fecha.h"
///hay un precio base dependiendo de la cantidad de invitados que tendra el evento

class Eventos
{
    public:
        Eventos(){}
        Eventos(int idEven,int idClien,std::string nombre,Fecha fechaEvento,Fecha fechaPago,int cant,bool confirmado);
        int getIdEvento();
        void setIdEvento(int idEvento);
        int getidCliente();
        void setidCliente(int id) ;

        std::string getNombreEvento();
        void setNombreEvento(std::string nombreEvento);
        Fecha getFechaEvento();
        void setFechaEvento(Fecha fechaEvento);
        Fecha getFechaPago();
        void setFechaPago(Fecha fechaPago);

        int getcantidadInvitados();
        void setCantidad(int cantidad);
        bool getConfirmado();
        void setConfirmado(bool confirmado);
        bool getEliminado();
        bool getEstado(){return _estado;}
        void setEstado(bool estado){_estado=estado;}
        void setEliminado(bool eliminado);
        void cargarEventos();
        bool getPagoReserva(){return _pagoReserva;}
        void setPagoReserva(bool pago){_pagoReserva=pago;}

        float getPrecioInicial(){return _precioInicial;}
        void setPrecioInicial(float precioInicial){
            _precioInicial=precioInicial;}

        float calcularPrecioInicial(int cantidadInvitados);
        int getTipoEvento(){return _idTipoEvento;}
        void setTipoEvento(int tipo){_idTipoEvento=tipo;}

    private:
        int _idEvento;
        int _idCliente;
        int _idTipoEvento;
        char _nombreEvento[300];
        Fecha _fechaEvento;
        Fecha _fechaPagoR;
        int _cantidadInvitados;
        float _precioInicial;
        bool _confirmado; ///se confirma la reserva
        bool _pagoReserva;///se confirma el pago de la reserva
        bool _estado; ///pendiente
        bool _eliminado;

};

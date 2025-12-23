#pragma once
#include "ArchivoEvento.h"
class ManagerEventos
{
    public:
        ManagerEventos();
        void cargarEvento();
        void mostrarEvento(Eventos evento);
        void listarEvento();
        void buscarIdEvento();
        void ordanadosPorFecha();
        void eventosPorTipo();
        void modificarEvento();
        void mostrarHistorial(int idCliente);
        void mostrarEventosEliminados();
        void cancelarEventos();
        void activarEventoCancelado();
        void submenuCancelarActivar();
        void buscarEventoDeCliente();
        void buscar();

        void eliminarEvento();
        void eliminar();
        void ActivarEvento();

    private:
        ArchivoEvento _repo;
};

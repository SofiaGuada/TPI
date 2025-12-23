#pragma once
#include "ManagerEventos.h"
#include "MenuEventoServicios.h"

class MenuEventos
{
    public:
        MenuEventos();
        void mostrar();
        void mostrarOpciones();
        int seleccionarOpcion();
        void ejecutarOpcion(int opcion);
        ManagerEventos _managerEventos;
        MenuEventoServicios _menuEventoServicios;


    private:
       int _cantidadOpciones;
};

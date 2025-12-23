#pragma once
#include "ManagerClientes.h"

class MenuClientes
{
    public:
        MenuClientes();
        void mostrar();

    protected:
        void mostrarOpciones();
        int seleccionarOpcion();
        void ejecutarOpcion(int opcion);
         ManagerClientes _managerCliente;

    private:
        int _cantidadOpciones;
};



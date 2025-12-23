#pragma once
#include "MenuClientes.h"
#include "MenuEventos.h"
#include "MenuPagos.h"

class App
{
    public:
        App();
    void run();

    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    MenuClientes _menuClientes;
    MenuEventos _menuEventos;
    MenuPagos _menuPagos;

    private:
        int _cantidadOpciones;
};


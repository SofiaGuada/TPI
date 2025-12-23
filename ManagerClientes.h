#pragma once
#include <string>
#include "ArchivoCliente.h"
class ManagerClientes
{
    public:
        ManagerClientes();
        void CargarCliente();
        void ListarClientes();
        void buscarClientes();
        void buscarClientesID();
        void buscarClientesDNI();
        void buscarClientesApellido();
        void eliminarClientes();
        void mostrarClientes(Cliente cliente);
        void eliminar();
        void ActivarCliente();
        void modificarClientes();
        void mostrarClientesEliminados();
        void ordanadosAlfabeticamente();
        bool validadDNI(std::string dni);

    private:
        ArchivoCliente _repo;
};

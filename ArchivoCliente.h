#pragma once
#include <string>
#include "Cliente.h"
class ArchivoCliente
{
    public:
        ArchivoCliente(std::string nombreArchivo ="Cliente.dat");
        bool guardar (Cliente registro);
        bool guardar (int pos, Cliente registro);
        int buscarIDcliente(int idcliente);
        int buscarDni(std::string dni);
        int getNuevoID();
        Cliente leer(int pos);
        int leerTodos(Cliente cliente[],int cantidad);
        int getCantidadRegistros();
        bool eliminar(int pos);

    protected:

    private:
        std::string _nombreArchivo;

};


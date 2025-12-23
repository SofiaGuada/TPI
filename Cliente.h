#pragma once
#include <string>

class Cliente
{
    public:
        Cliente();
        Cliente(int idCliente,std::string nombre,std::string apellido,std::string dni,std::string email,std::string telefono,bool estado);

        int getidCliente();
        void setidCliente(int id) ;

        std::string getNombre();
        void setNombre (std::string nombre);

        std::string getApellido();
        void setApellido (std::string apellido);

        std::string getDni();
        void setDni(std::string dni);

        std::string getEmail();
        void setEmail(std::string email);

        std::string getTelefono();
        void setTelefono (std::string telefono);
        bool getEstado();
        void setEstado(bool estado);
        bool getEliminado();
        void setEliminado(bool eliminado);

        void cargar();
        void mostrar();

        int getCantidadRegistros();

    private:
        int _idCliente;
        char _nombre[300];
        char _apellido[300];
        char _dni[20];
        char _email[300];
        char _telefono[15];
        bool _estado;
        bool _eliminado;
};


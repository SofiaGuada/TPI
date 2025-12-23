#include "ArchivoCliente.h"
using namespace std;

ArchivoCliente::ArchivoCliente(string nombreArchivo)
    :_nombreArchivo(nombreArchivo){
}

bool ArchivoCliente::guardar (Cliente registro){
  FILE *pFile;
  bool result;
 if(buscarDni(registro.getDni())!=-1){
    return false;
   }
   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(Cliente),1,pFile);

   fclose(pFile);
   return result;
}

bool ArchivoCliente::guardar (int pos, Cliente registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(Cliente) , SEEK_SET);

  result = fwrite(&registro, sizeof(Cliente), 1, pFile);

  fclose(pFile);

  return result;
}

int ArchivoCliente::buscarIDcliente(int idcliente){
FILE*pFile;
      Cliente cliente;
      int pos=-1;

     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }

     while (fread(&cliente,sizeof(Cliente),1,pFile)){
        if (cliente.getidCliente()== idcliente){
            pos=ftell(pFile)/sizeof (Cliente)-1;
            break;
        }
     }
     fclose(pFile); ///salgo
     return pos;

}

int ArchivoCliente::buscarDni(string dni){
FILE*pFile;
      Cliente cliente;
      int pos=-1;

     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }

     while (fread(&cliente,sizeof(Cliente),1,pFile)){
        if (cliente.getDni()== dni){
            pos=ftell(pFile)/sizeof (Cliente)-1;
            break;
        }
     }
     fclose(pFile); ///salgo
     return pos;
}

int ArchivoCliente::getNuevoID(){

 if(getCantidadRegistros() == 0){
  return 1;
 }

 return leer(getCantidadRegistros() - 1).getidCliente() + 1;
}

Cliente ArchivoCliente::leer(int pos){
 FILE*pFile;
    Cliente cliente;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return cliente;
    }
    fseek(pFile, pos * sizeof(Cliente),SEEK_SET);

  if(!fread(&cliente, sizeof(Cliente), 1, pFile)){
    cliente.setidCliente(-1);
  }

    fclose(pFile);
    return cliente;
}

int ArchivoCliente::leerTodos(Cliente cliente[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }

   result=fread(cliente,sizeof(Cliente),cantidad,pFile);
   fclose(pFile);
   return result;
}

int ArchivoCliente::getCantidadRegistros(){
   FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(Cliente);
   fclose(pFile);
   return cantidad;
}

bool ArchivoCliente::eliminar(int pos){
    Cliente cliente = leer(pos);

   if(cliente.getDni()!="-1"){
    cliente.setEliminado(true);
    return guardar(pos,cliente);
   }
   return false;
}

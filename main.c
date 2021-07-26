#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char marca[20];
    int tipo;
    float peso;

}eVehiculo;

//constructores
eVehiculo* newVehiculo();
eVehiculo* newVehiculoParam(int id, char* marca, int tipo, float peso);

//setters
int vehiculo_setId(eVehiculo* this, int id);
int vehiculo_setMarca(eVehiculo* this, char* marca);
int vehiculo_setTipo(eVehiculo* this, int tipo);
int vehiculo_setPeso(eVehiculo* this, float peso);

//getters
int vehiculo_getId(eVehiculo* this,int* id);
int vehiculo_getMarca(eVehiculo* this,char* marca);
int vehiculo_getTipo(eVehiculo* this,int* tipo);
int vehiculo_getPeso(eVehiculo* this,float* peso);

//archivos
int guardarTexto(char* path, eVehiculo* vehiculo);
int guardarBinario(char* path, eVehiculo* vehiculo);

int main()
{

    eVehiculo* vehiculo1 = newVehiculoParam(256, "Fiat", 206, 56.000);

    if(vehiculo1==NULL)
    {
        printf("Ocurrio un error al crear la variable. \n");
        exit(1);
    }

    guardarTexto("vehiculos.txt", vehiculo1);

    guardarBinario("vehiculos.bin", vehiculo1);

    printf("Vehiculo almacenado en texto y binario\n");
    return 0;
}

eVehiculo* newVehiculo()
{
    eVehiculo* nuevoVehiculo = (eVehiculo*) malloc(sizeof(eVehiculo));
    if(nuevoVehiculo!=NULL)
    {
        nuevoVehiculo->id=0;
        strcpy(nuevoVehiculo->marca, " ");
        nuevoVehiculo->tipo=0;
        nuevoVehiculo->peso=0;
    }

    return nuevoVehiculo;
}

eVehiculo* newVehiculoParam(int id, char* marca, int tipo, float peso)
{
    eVehiculo* nuevoVehiculo= newVehiculo();

    if(!(vehiculo_setId(nuevoVehiculo, id)
       && vehiculo_setMarca(nuevoVehiculo, marca)
       && vehiculo_setTipo(nuevoVehiculo, tipo)
       && vehiculo_setPeso(nuevoVehiculo, peso)))
    {
        free(nuevoVehiculo);
        nuevoVehiculo=NULL;
    }

    return nuevoVehiculo;
}

//setter
int vehiculo_setId(eVehiculo* this, int id)
{
    int todoOk=0;

    if(this!=NULL && id>0)
    {
        this->id=id;
        todoOk=1;
    }

    return todoOk;
}

int vehiculo_setMarca(eVehiculo* this, char* marca)
{
    int todoOk=0;

    if(this!=NULL && marca!=NULL && strlen(marca)<20 && strlen(marca)>0)
    {
        strcpy(this->marca, marca);
        todoOk=1;
    }

    return todoOk;
}

int vehiculo_setTipo(eVehiculo* this, int tipo)
{
    int todoOk=0;

    if(this!=NULL && tipo>0)
    {
        this->tipo=tipo;
        todoOk=1;
    }

    return todoOk;
}

int vehiculo_setPeso(eVehiculo* this, float peso)
{
    int todoOk=0;

    if(this!=NULL && peso>0)
    {
        this->peso=peso;
        todoOk=1;
    }

    return todoOk;
}

//getters
int vehiculo_getId(eVehiculo* this,int* id)
{
    int todoOk=0;
    if(id!=NULL && this!=NULL)
    {
        *id = this->id;
        todoOk=1;
    }
    return todoOk;
}

int vehiculo_getMarca(eVehiculo* this,char* marca)
{
    int todoOk=0;
    if(marca!=NULL && this!=NULL)
    {
        strcpy(marca, this->marca);
        todoOk=1;
    }
    return todoOk;
}


int vehiculo_getTipo(eVehiculo* this,int* tipo)
{
    int todoOk=0;
    if(tipo!=NULL && this!=NULL)
    {
        *tipo = this->tipo;
        todoOk=1;
    }
    return todoOk;
}

int vehiculo_getPeso(eVehiculo* this,float* peso)
{
    int todoOk=0;
    if(peso!=NULL && this!=NULL)
    {
        *peso = this->peso;
        todoOk=1;
    }
    return todoOk;
}

///ARCHIVOS

int guardarTexto(char* path, eVehiculo* vehiculo){

    int todoOk=0;
    int id;
    char marca[20];
    int tipo;
    float peso;

    FILE* f = fopen(path, "w");

    if(f!=NULL)
    {
        fprintf(f, "ID, Marca, Tipo, Peso\n");

        vehiculo_getId(vehiculo, &id);
        vehiculo_getMarca(vehiculo, marca);
        vehiculo_getTipo(vehiculo, &tipo);
        vehiculo_getPeso(vehiculo, &peso);

        fprintf(f, "%d, %s, %d, %f\n", id, marca, tipo, peso);

        todoOk=1;
    }

    fclose(f);
    return todoOk;
}

int guardarBinario(char* path, eVehiculo* vehiculo){

    int todoOk=0;
    FILE* f = fopen(path, "wb");
    if(f != NULL)
    {
        if(fwrite(vehiculo, sizeof(eVehiculo), 1, f)==1)
        {
            printf("Archivo guardado con exito\n");
        }
        todoOk=1;
    }

    fclose(f);
    return todoOk;
}

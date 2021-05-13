/*
 ============================================================================
 Name        : Pacial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "UTN.h"
#define S 4
#define T 4
#define F 4
#define OCUPADO 1
#define VACIO 0

typedef struct
{
	int dia;
	int mes;
	int anio;
	int isEmpty;

}eFecha;

typedef struct
{
	int idServicio;
	char descripcion[25];
	int precio;
	int isEmpty;

}eServicio;

typedef struct
{
	int idTrabajo;
	char marcaBicicleta[20];
	int rodadoBicicleta;
	int idServicio;
	eFecha fecha;
	int isEmpty;


}eTrabajo;

void MostrarServicios(eServicio[], int);
int CargarTrabajo(eTrabajo[], int, eServicio[], int);
void VaciarLista(eTrabajo[], int);
int BuscarLibre(eTrabajo [], int);
int ModificarTrabajo(eTrabajo[],int, eServicio[], int);
void MostrarUnTrabajo(eTrabajo, eFecha);
void ListadoTrabajos(eTrabajo[], int, eFecha[], int);
void BajaTrabajo(eTrabajo[], int, eFecha[], int);
int Total(eTrabajo[], int, eServicio[], int);
void OrdenarPorFecha(eFecha[], int, eTrabajo[], int);

int main(void)
{
	setbuf(stdout, NULL);
	eServicio listaServicio[S] = {{20000,"Limpieza",250,OCUPADO},{20001,"Parche",300,OCUPADO},{20002,"Centrado",400,OCUPADO},{20003,"Cadena",350,OCUPADO}};
	eTrabajo listaTrabajo[T];
	eFecha listaFecha[F];

	VaciarLista(listaTrabajo, T);

	char opcion;
	int retorno;
	int precioTotal;

	do
	{
		printf("A- Alta trabajo\n");
		printf("B- Modificar trabajo\n");
		printf("C- Baja trabajo\n");
		printf("D- Listar trabajos\n");
		printf("E- Listar servicios\n");
		printf("F- Total\n");
		printf("G- Salir\n");
		utn_getCaracter(&opcion, "Ingrese una opcion: ", "Error,ingrese una opcion valida\n", 'A','G', 2);

		switch(opcion)
		{
			case 'A':
				retorno = CargarTrabajo(listaTrabajo, T, listaServicio, S);
				if(retorno !=-1)
				{
					 printf("\nProducto cargado correctamente.\n");
				}
				else
				{
					 printf("No hay mas lugar en la lista.\n");
				}

			break;

			case 'B':
				ModificarTrabajo(listaTrabajo, T, listaServicio, S);
			break;

			case 'C':
				BajaTrabajo(listaTrabajo ,T, listaFecha, F);
			break;

			case 'D':
				//OrdenarPorFecha(listaFecha, F, listaTrabajo, T);
				ListadoTrabajos(listaTrabajo,T, listaFecha, F);
			break;

			case 'E':
				MostrarServicios(listaServicio, S);
			break;

			case 'F':
				precioTotal = Total(listaTrabajo, T, listaServicio, S);
				if(precioTotal != 0)
				{
					printf("El precio total es de: $%d\n", precioTotal);
				}
				else
				{
					printf("No hay trabajos.\n");
				}
			break;

			case 'G':
				printf("Ha salido con exito.");
			break;
		}

	}while(opcion != 'G');
	return EXIT_SUCCESS;
}

eTrabajo AltaTrabajo(eServicio listaServicio[], int tamServicio)
{
	setbuf(stdout, NULL);
	eTrabajo miTrabajo;
	eFecha miFecha;

	miTrabajo.idTrabajo = 0;

	printf("Ingrese la marca de la bicicleta: ");
	fflush(stdin);
	scanf("%[^\n]", miTrabajo.marcaBicicleta);

	utn_getNumero(&miTrabajo.rodadoBicicleta, "Ingrese el rodado de la bicicleta: ", "Error, ingrese un rodado valido\n", 10, 30, 1);

	MostrarServicios(listaServicio, tamServicio);
	utn_getNumero(&miTrabajo.idServicio, "Ingrese el servicio deseado: ", "Error, ingrese un servicio valido\n", 20000, 20003, 1);

	utn_getNumero(&miFecha.dia, "Ingrese el dia: ", "Error, ingrese un dia valido\n", 1, 31, 1);

	utn_getNumero(&miFecha.mes, "Ingrese el mes: ", "Error, ingrese un mes valido\n", 1, 12, 1);

	utn_getNumero(&miFecha.anio, "Ingrese el anio: ", "Error, ingrese un anio valido\n", 2021, 2030, 1);

	miFecha.isEmpty = OCUPADO;
	miTrabajo.isEmpty = OCUPADO;
	miTrabajo.idTrabajo ++;

	return miTrabajo;
}

void VaciarLista(eTrabajo listaTrabajo[], int tamTrabajo)
{
    int i;
    for(i=0; i<tamTrabajo; i++)
    {
        listaTrabajo[i].isEmpty = VACIO;
    }
}

int BuscarLibre(eTrabajo listaTrabajo[], int tamTrabajo)
{
    int i;
    int index = -1;
    for(i=0; i<tamTrabajo; i++)
    {
        if(listaTrabajo[i].isEmpty==VACIO)
        {
            index = i;
            break;
        }
    }
    return index;
}

int CargarTrabajo(eTrabajo listaTrabajo[], int tamTrabajo, eServicio listaServicio[], int tamServicio)
{
    int i;
    i = BuscarLibre(listaTrabajo, tamTrabajo);
    if(i!=-1)
    {
        listaTrabajo[i] = AltaTrabajo(listaServicio, tamServicio);
    }
    return i;
}

void MostrarServicios(eServicio listaServicio[], int tamServicio)
{
	int i;
	for(i=0 ; i<tamServicio; i++)
	{
		printf("%2d %15s $%5d\n", listaServicio[i].idServicio, listaServicio[i].descripcion, listaServicio[i].precio);
	}
}

int ModificarTrabajo(eTrabajo listaTrabajo[],int tamTrabajo, eServicio listaServicio[], int tamServicio)
{
	int idIngresado;
	int i;
	char opcion;

		printf("Ingrese el ID: ");
		scanf("%d", &idIngresado);

		for(i=0; i<tamTrabajo; i++)
		{
			if(idIngresado == listaTrabajo[i].idTrabajo)
			{
				do
				{
				 printf("\nA.Modificar marca de la bicicleta\n");
				 printf("B.Modificar el servicio\n");
				 printf("C.Salir\n");

				 utn_getCaracter(&opcion,"\n¿Que quiere modificar?: ", "Error, elija una opcion valida\n", 'A', 'C', 2);

				switch(opcion)
				{
					case 'A':
						 printf("Ingrese la nueva marca: ");
						 fflush(stdin);
						 scanf("%[^\n]", listaTrabajo[i].marcaBicicleta);
						 printf("Marca modificada con exito.\n");
					break;

					case 'B':
						MostrarServicios(listaServicio, tamServicio);
						utn_getNumero(&listaServicio[i].idServicio, "Ingrese el servicio deseado: ", "Error, ingrese un servicio valido\n", 20000, 20003, 2);
						printf("Servicio modificado con exito.\n");
					break;

					case 'C':
						printf("Ha salido de la modificacion con exito.\n");
					}
				}while(opcion != 'C');

			}
		}
		return i;
}

void BajaTrabajo(eTrabajo listaTrabajo[], int tamTrabajo, eFecha listaFecha[], int tamFecha)
{
	int idIngresado;
	int i;

	ListadoTrabajos(listaTrabajo, tamTrabajo, listaFecha, tamFecha);

	printf("Ingrese el ID: ");
	scanf("%d", &idIngresado);

	for(i=0; i<tamTrabajo; i++)
	{
		if(idIngresado == listaTrabajo[i].idTrabajo)
		{
			listaTrabajo[i].isEmpty = VACIO;
			printf("El trabajo ha sido dado de baja con exito.\n");
			break;
		}
		else
		{
			printf("No se han encontrado productos con el ID ingresado.");
			break;
		}
	}
}

void MostrarUnTrabajo(eTrabajo unTrabajo, eFecha unaFecha)
{
    printf("%d %20s %4d %4d %8d/%d/%d\n", unTrabajo.idTrabajo,
                                unTrabajo.marcaBicicleta,
                                unTrabajo.rodadoBicicleta,
                                unTrabajo.idServicio,
								unaFecha.dia,
								unaFecha.mes,
								unaFecha.anio
                                );
}

void ListadoTrabajos(eTrabajo listaTrabajo[], int tamTrabajo, eFecha listaFecha[], int tamFecha)
{
    int i;

    for(i=0; i<tamTrabajo; i++)
    {
        if(listaTrabajo[i].isEmpty == OCUPADO)
        {
            MostrarUnTrabajo(listaTrabajo[i], listaFecha[i]);
        }
    }
}

int Total(eTrabajo listaTrabajo[], int tamTrabajo, eServicio listaServicio[], int tamServicio)
{
	int i;
	int j;
	int acumuladorPrecio;

	acumuladorPrecio = 0;

	for(i=0; i<tamTrabajo; i++)
	{
		for(j=0; j< tamServicio; j++)
		{
			if(listaServicio[j].idServicio == listaTrabajo[i].idServicio)
			{
				acumuladorPrecio = acumuladorPrecio + listaServicio[j].precio;
			}
		}
	}

	return acumuladorPrecio;
}

void OrdenarPorFecha(eFecha listaFecha[], int tamFecha, eTrabajo listaTrabajo[], int tamTrabajo)
{
   int i;
   int j;
   eFecha auxFecha;

   for(i=0; i<tamFecha-1; i++)
   {
	   for(j=i+1; j<tamFecha; j++)
	   {
           if(listaFecha[i].mes < listaFecha[j].mes)
           {
               auxFecha = listaFecha[j];
               listaFecha[j] = listaFecha[i];
               listaFecha[i] = auxFecha;
           }
       }
   }
}

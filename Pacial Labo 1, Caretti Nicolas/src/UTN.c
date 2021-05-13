/*
 * UTN.c
 *
 *  Created on: 9 may. 2021
 *      Author: Seether
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int esNumerica(char* cadena);
static int getInt(int* pResultado);
static int myGets(char* cadena, int longitud);

/*
 *
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[128];


	if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer))
	{
		retorno = 0;
		*pResultado = atoi(buffer);
	}

	return retorno;
}

static int esNumerica(char* cadena)
{
	int retorno = 1;
	int i = 0;

	if(cadena[0] == '-')
	{
		i = 1;
	}

	for( ; cadena[i] != '\0'; i++)
	{
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
	}

	return retorno;

}

static int myGets(char* cadena, int longitud)
{
	int retorno=-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
	fflush(stdin);
	if(cadena[strlen(cadena)-1] == '\n')
	{
	cadena[strlen(cadena)-1] = '\0';
	}
	retorno=0;
	}
	return retorno;

}



int utn_getNumero (int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	setbuf(stdout, NULL);
	int retorno = -1;
	int bufferINT;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferINT) == 0 && bufferINT >= minimo && bufferINT <= maximo)
			{
				*pResultado = bufferINT;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

int utn_getNumeroFlotante (float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	setbuf(stdout, NULL);
	int retorno = -1;
	float bufferFLOAT;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			scanf("%f", &bufferFLOAT);

			if(bufferFLOAT >= minimo && bufferFLOAT <= maximo)
			{
				*pResultado = bufferFLOAT;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

int utn_getCaracter (char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
	setbuf(stdout, NULL);
	int retorno = -1;
	char bufferCHAR;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			fflush(stdin);
			scanf("%c", &bufferCHAR);

			if(bufferCHAR >= minimo && bufferCHAR <= maximo)
			{
				*pResultado = bufferCHAR;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

#include <iostream>
#include <string.h>
using namespace std;

struct Empleados
{
	unsigned legajo;
	int dni;
	char nombre[20];
	char apellido[20];
	char transporte[20];
	char patente[20];
	int zona;
};

struct Zonas
{
	int numZona;
	Empleados repMoto[20];
	Empleados repAuto[20];
	Empleados repCamioneta[20];  //FALTA UN TIPO DE VEHÍCULO (CAMIÓN Y CAMIONETA SON DISTINTOS)
	Empleados repCamion[20];
	int repartidores[4];
	int totalRep;
};

int menu();
void procesarOpc(int opc,Zonas z[]);
void ingresarRep(Zonas z[]);
void generarArchivos(Zonas z[]);
void mostrarDatos();
void verificarCarga(char[],int,Zonas[],char[],char[],int,char[]);
void inicializarZonas(Zonas z[]);


int main()
{
	Zonas z[14];//vector de las Zonas
	int opc;
	inicializarZonas(z);
	do{
	opc=menu();//se muestra el menu
	procesarOpc(opc,z);//se procesa la opcion seleccionada
	}while(opc<4 && opc>0);
	cout<<"Adios!"<<endl;
}


void generarArchivos(Zonas z[])
{
	FILE *arch1=fopen("repMoto.dat","wb");
	FILE *arch2=fopen("repAuto.dat","wb");
	FILE *arch3=fopen("repCamion.dat","wb");
	FILE *arch4=fopen("repCamioneta.dat","wb");
    if(arch1==NULL || arch2==NULL || arch3==NULL || arch4==NULL)
        cout<<"ERROR"<<endl;
    else
    {
        for(int i=0;i<14;i++)//zonas
        {
        	for(int j=0;j<20;j++)
			{
				if((strcmp(z[i].repMoto[i].transporte,"moto")==0) && z[i].repMoto[i].legajo!=0)
				{

					fwrite(&z[i].repMoto[j],sizeof(Empleados),1,arch1);
				}
				else if(strcmp(z[i].repAuto[i].transporte,"auto")==0 && z[i].repAuto[i].legajo!=0 )
				{

					fwrite(&z[i].repAuto[j],sizeof(Zonas),1,arch2);
				}else if((strcmp(z[i].repCamion[i].transporte,"camion")==0) && z[i].repCamion[i].legajo!=0 )
				{

					fwrite(&z[i].repCamion[j],sizeof(Zonas),1,arch3);
				}else if(strcmp(z[i].repCamioneta[i].transporte,"camioneta")==0 && z[i].repCamioneta[i].legajo!=0)
				{
					fwrite(&z[i].repCamioneta[j],sizeof(Zonas),1,arch4);
				}
    		}
			fclose(arch1);
			fclose(arch2);
			fclose(arch3);
			fclose(arch4);
    	}
    }
}

void inicializarZonas(Zonas z[])
{
	for(int i=0;i<14;i++)//zona
	{
		z[i].totalRep=0; //NO ES NECSARIO DENTRO DEL for DE j
		z[i].repartidores[0]=0; //NO ES NECSARIO DENTRO DEL for DE j
		z[i].repartidores[1]=0; //NO ES NECSARIO DENTRO DEL for DE j
		z[i].repartidores[2]=0; //NO ES NECSARIO DENTRO DEL for DE j
		z[i].numZona=i+1;
		
		for(int j=0;j<20;j++)//reparitidor
		{
			z[i].repMoto[j].legajo=0;
			z[i].repAuto[j].legajo=0;
			z[i].repCamioneta[j].legajo=0;
			z[i].repCamion[j].legajo=0;
		}

	}

}

void mostrarZonas(Zonas z[])
{
	bool flag=false;
	int acumMoto=0,acumAuto=0,acumCamioneta=0,acumCamion,zonaMax,max;
	for(int i=0;i<14;i++)
	{
		if(!flag || max<z[i].totalRep)//Zona con mas repartidores
		{
			flag=true;
			max=z[i].totalRep;
			zonaMax=i+1;
		}
		if(z[i].totalRep>0)//Datos de los repartidores por Zona y Transporte
		{
				cout<<"==========ZONA:"<<z[i].numZona<<" ========Repartidores:"<<z[i].totalRep<<endl;
				if(z[i].repartidores[0]>0)
				{
				cout<<"-->REPARTIDORES MOTO:"<<z[i].repartidores[0]<<endl;
				for(int j=0;j<20;j++)
				{
					if(z[i].repMoto[j].legajo!=0)
					{
						cout<<"*Legajo:"<<z[i].repMoto[j].legajo;
						cout<<" -Nombre:"<<z[i].repMoto[j].nombre<<endl;
					}
				}
				}else if(z[i].repartidores[0]==0)cout<<"No hay repartidores inscriptos"<<endl;

				if(z[i].repartidores[1]>0)
				{
					cout<<"---->REPARTIDORES AUTO:"<<z[i].repartidores[1]<<endl;
					for(int j=0;j<20;j++)
					{
						if(z[i].repAuto[j].legajo!=0)
						{
							cout<<"Legajo:"<<z[i].repAuto[j].legajo<<endl;
							cout<<" -Nombre:"<<z[i].repAuto[j].nombre<<endl;
						}
					}
				}else if(z[i].repartidores[1]==0)cout<<"No hay repartidores inscriptos"<<endl;

				if(z[i].repartidores[2]>0)
				{
				cout<<"------>REPARTIDORES CAMION:"<<z[i].repartidores[2]<<endl;
				for(int j=0;j<20;j++)
				{
					if(z[i].repCamion[j].legajo!=0)
					{
						cout<<"Legajo:"<<z[i].repCamion[j].legajo<<endl;
						cout<<" -Nombre:"<<z[i].repCamion[j].nombre<<endl;
					}
				}
				}else if(z[i].repartidores[2]==0)cout<<"No hay repartidores inscriptos"<<endl;
				
				if(z[i].repartidores[3]>0)
				{
				cout<<"-------->REPARTIDORES CAMIONETA:"<<z[i].repartidores[2]<<endl;
				for(int j=0;j<20;j++)
				{
					if(z[i].repCamioneta[j].legajo!=0)
					{
						cout<<"Legajo:"<<z[i].repCamioneta[j].legajo<<endl;
						cout<<" -Nombre:"<<z[i].repCamioneta[j].nombre<<endl;
					}
				}
				}else if(z[i].repartidores[3]==0)cout<<"No hay repartidores inscriptos"<<endl;
		}
		acumMoto+=z[i].repartidores[0];
		acumAuto+=z[i].repartidores[1];
		acumCamioneta+=z[i].repartidores[2];
		acumCamion+=z[i].repartidores[3];
	}
	if(acumMoto==0)
	{
		cout<<"No hay MOTOS disponibles, por no haber ningun inscripto"<<endl;
	}
	if(acumAuto==0)
	{
		cout<<"No hay AUTOS disponibles, por no haber ningun inscripto"<<endl;
	}
	if(acumCamion==0)
	{
		cout<<"No hay CAMIONES disponibles, por no haber ningun inscripto"<<endl;
	}
	if(acumCamioneta==0)
	{
		cout<<"No hay CAMIONETAS disponibles, por no haber ningun inscripto"<<endl;
	}
	cout<<"La zona:"<<zonaMax<<" tiene mas repartidores inscriptos("<<max<<")"<<endl;

}

void ingresarRep(Zonas z[])
{
	int rta=0;
	do{
		bool flag;
		int zona=0,dni=0;
		char nombre[20],apellido[20],transporte[20],patente[20];
		cout<<"*Ingrese el DNI del repartidor"<<endl;
		cin>>dni;
		cout<<"*Ingrese el nombre del repartidor"<<endl;
		cin>>nombre;
		cout<<"*Ingrese el apellido del repartidor"<<endl;
		cin>>apellido;
		cout<<"*Ingrese el transporte del repartidor(moto,auto,camion o camioneta)"<<endl;
		cin>>transporte;
		cout<<"*Ingrese la patente del vehiculo"<<endl;
		cin>>patente;
		cout<<"*Ingrese la zona de trabajo"<<endl;
		cin>>zona;
		verificarCarga(transporte,zona,z,nombre,apellido,dni,patente);//verifico si hay cupo
		cout<<"-¿Desea cargar otro repartidor?-(1=SI/2=NO)"<<endl;
		cin>>rta;
	}while(rta==1);
	system("cls");
}


void verificarCarga(char transporte[],int zona,Zonas z[],char nombre[],char apellido[],int dni,char patente[])
{
	bool flag=false;
	int i=0;
	zona=zona-1;//se le resta 1 porque en el array la posicion de la zona es uno menos
	while(!flag && i<20)
	{
		if((strcmp(transporte,"moto")==0) && z[zona].repMoto[i].legajo==0 && !flag)
		{
			flag=true;
			z[zona].repMoto[i].legajo=z[zona].totalRep+1;
			z[zona].repMoto[i].dni=dni;
			strcpy(z[zona].repMoto[i].nombre,nombre);
			strcpy(z[zona].repMoto[i].apellido,apellido);
			strcpy(z[zona].repMoto[i].transporte,transporte);
			strcpy(z[zona].repMoto[i].patente,patente);
			z[zona].repMoto[i].zona=zona;
			z[zona].repartidores[0]++;
			z[zona].totalRep++;
		}else if(strcmp(transporte,"auto")==0 && z[zona].repAuto[i].legajo==0 && !flag)
		{
			flag=true;
			z[zona].repAuto[i].legajo=z[zona].totalRep+1;
			z[zona].repAuto[i].dni=dni;
			strcpy(z[zona].repAuto[i].nombre,nombre);
			strcpy(z[zona].repAuto[i].apellido,apellido);
			strcpy(z[zona].repAuto[i].transporte,transporte);
			strcpy(z[zona].repAuto[i].patente,patente);
			z[zona].repAuto[i].zona=zona;
			z[zona].repartidores[1]++;
			z[zona].totalRep++;
		}else if(strcmp(transporte,"camion")==0 && z[zona].repCamion[i].legajo==0 && !flag)
		{
			flag=true;
			z[zona].repCamion[i].legajo=z[zona].totalRep+1;
			z[zona].repCamion[i].dni=dni;
			strcpy(z[zona].repCamion[i].nombre,nombre);
			strcpy(z[zona].repCamion[i].apellido,apellido);
			strcpy(z[zona].repCamion[i].transporte,transporte);
			strcpy(z[zona].repCamion[i].patente,patente);
			z[zona].repCamion[i].zona=zona;
			z[zona].repartidores[2]++;
			z[zona].totalRep++;
		}else if(strcmp(transporte,"camioneta")==0 && z[zona].repCamioneta[i].legajo==0 && !flag)
		{
			flag=true;
			z[zona].repCamioneta[i].legajo=z[zona].totalRep+1;
			z[zona].repCamioneta[i].dni=dni;
			strcpy(z[zona].repCamioneta[i].nombre,nombre);
			strcpy(z[zona].repCamioneta[i].apellido,apellido);
			strcpy(z[zona].repCamioneta[i].transporte,transporte);
			strcpy(z[zona].repCamioneta[i].patente,patente);
			z[zona].repCamioneta[i].zona=zona;
			z[zona].repartidores[2]++;
			z[zona].totalRep++;
		}
		
		i++;
		if(i==20 && !flag)//2? EL CUPO ES POR TIPO DE VEHÍCULO Y POR ZONA
		{
			flag=true;
			cout<<"¡No hay cupos disponibles! para la Zona:"<<zona<<" Transporte:"<<transporte<<endl;
		}
	}
}


void procesarOpc(int opc, Zonas z[])
{
	system("cls");
	switch(opc)
	{
		case 1:
			ingresarRep(z);
			break;
		case 2:
			generarArchivos(z);
			break;
		case 3:
			mostrarZonas(z);
			break;
	}
}

int menu()
{//POR QUÉ CON MENÚ?
	int opc;
	cout<<"_______________HOLA BIENVENIDO AL SISTEMA______________"<<endl;
	cout<<"1)Ingresar Repartidores"<<endl;
	cout<<"2)Generar Archivos"<<endl;
	cout<<"3)Mostrar Datos de las Zonas"<<endl;
	cout<<"4)Salir"<<endl;
	cout<<"_______________________________________________________"<<endl;
	cin>>opc;
	return opc;
}
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

int main()
{

    int coef[100][100],oft,dem,sol[100][100],ind[100][100],ubi,ubj,con,soft,sdem;
    int aux2[100][100],i,j,k,pen,z;
    system("color 1b");
    
    //Inicializando indicadores
    for(i=1; i<=100; i++)
    {
        for(j=1; j<=100; j++)
        {
            sol[i][j] = -1;
        }
    }
    
    
    gotoxy(40,3);cout<<"<<ARMADO DE TABLA ESQUINA NOROESTE>>";
    
    do{
    gotoxy(5,5);clreol();system("color 1b");gotoxy(5,5);cout<<"INGRESE NUMERO DE OFERTAS:"; cin>>oft;
    }while(oft < 0);
    
    do{
    gotoxy(5,6);clreol();system("color 1b");gotoxy(5,6);cout<<"INGRESE NUMERO DE DEMANDAS:"; cin>>dem;
    }while(dem < 0);
    

    // CREACION DE BORDES
    clrscr();system("color 1b");
    for(i=1; i<=oft+1; i++)
    {
        if(i < oft+1)
        {
            gotoxy(5,4+4*i);cout<<"OF"<<i;
        }

        for(j=1; j<=dem+1; j++)
        {
            gotoxy(9*j+1,2+4*i);cout<<"---------";
            for(k=0; k<=4; k++)
            {
                gotoxy(9*j+1,2+4*i+k);cout<<"|";
            }

        }

    }

    //Llenado de tabla
    for(i=1; i<=oft; i++)
    {
        for(j=1; j<=dem; j++)
        {
            gotoxy(5,3);clreol();system("color 1b");cout<<"INGRESE COSTO "<<i<<" - "<<j;
            do{
            gotoxy(6+9*j,3+4*i);clreol();system("color 1b");gotoxy(6+9*j,3+4*i);cin>>coef[i][j];
            }while(coef[i][j] < 0);
        }

        gotoxy(5,3);clreol();system("color 1b");cout<<"INGRESE OFERTA "<<i;
        do{
        gotoxy(3+9*j,4+4*i);clreol();system("color 1b");gotoxy(3+9*j,4+4*i);cin>>coef[i][dem+1];
        }while(coef[i][dem+1] < 0);
    }
    for(j=1; j<=dem; j++)
    {
        gotoxy(5,3);clreol();system("color 1b");cout<<"INGRESE DEMANDA "<<j;
        do{
        gotoxy(3+9*j,8+4*oft);clreol();system("color 1b");gotoxy(3+9*j,8+4*oft);cin>>coef[oft+1][j];
        }while(coef[oft+1][j] < 0);
    }
    

    //VERFICANDO BALANCE
    soft = 0;sdem = 0;
    for(i=1; i<=oft; i++)
    {
        soft = soft + coef[i][dem+1];
    }
    for(j=1; j<=dem; j++)
    {
        sdem = sdem + coef[oft+1][j];
    }
    
    
    if(soft == sdem)
    {
        gotoxy(5,25);cout<<"OFERTA Y DEMANDA BALANCEADAS!!!!  ";system("pause");
    }else
    {
        gotoxy(5,25);cout<<"OFERTA Y DEMANDA DESBALANCEADAS!!!!  ";system("pause");
        
		if(soft > sdem)
        {
            dem++;
            for(i=1; i<=oft; i++)
            {
                coef[i][dem+1] = coef[i][dem];
                coef[i][dem] = 0;
            }
            coef[oft+1][dem] = soft - sdem;
        }

        if(sdem > soft)
        {
            oft++;
            for(j=1; j<=dem; j++)
            {
                coef[oft+1][j] = coef[oft][j];
                coef[oft][dem+1] = 0;

            }
            coef[oft][dem+1] = sdem - soft;
        }
    }
    /* INICIALIZANDO AUXILIARES
    aux2:datos tachados
    */
    for(i=0; i<=100; i++)
    {
        for(j=1; j<=100; j++)
        {
            aux2[i][j] = 0;
        }
    }

    //INICIO DE PENALIZACIONES
    pen = 0;

    do{
    pen++;
    //BUSQUEDA DE LA ESQUINA
    con = 0;
    for(i=1; i<=oft; i++)
    {
        for(j=1; j<=dem; j++)
        {
            if(aux2[i][j] == 0 && con == 0)
            {
                con++;
                ubi = i;ubj = j;
            }
        }
    }


    //MAYOR DEMANDA
    if(coef[oft+1][ubj] >= coef[ubi][dem+1])
    {
        coef[oft+1][ubj] = coef[oft+1][ubj] - coef[ubi][dem+1];
        sol[ubi][ubj] = coef[ubi][dem+1];
        con = 0;
        for(i=1; i<=oft; i++)
        {
            if(aux2[i][ubj] == 0)
            {
                con++;
            }
        }
        coef[ubi][dem+1] = 0;
        for(j=1; j<=dem; j++)
        {
            aux2[ubi][j] = 1;
        }
        if(con == 2)
        {
            for(i=1; i<=oft; i++)
            {
                if(aux2[i][ubj] == 0)
                {
                    sol[i][ubj] = coef[oft+1][ubj];
                    coef[i][dem+1] = coef[i][dem+1] - coef[oft+1][ubj];
                    coef[oft+1][ubj] = 0;
                    aux2[i][ubj] = 1;
                }
            }
        }

    }

    //MAYOR OFERTA

    if(coef[oft+1][ubj] < coef[ubi][dem+1])
    {
        coef[ubi][dem+1] = coef[ubi][dem+1] - coef[oft+1][ubj];
        sol[ubi][ubj] = coef[oft+1][ubj];
        con = 0;
        for(j=1; j<=dem; j++)
        {
            if(aux2[ubi][j]==0)
            {
                con++;
            }
        }
        coef[oft+1][ubj]=0;
        for(i=1;i<=oft;i++)
        {
            aux2[i][ubj]=1;
        }
        if(con==2)
        {
            for(j=1;j<=dem;j++)
            {
                if(aux2[ubi][j]==0)
                {
                    sol[ubi][j]=coef[ubi][dem+1];
                    coef[oft+1][j]=coef[oft+1][j]-coef[ubi][dem+1];
                    coef[ubi][dem+1]=0;
                    aux2[ubi][j]=1;
                }
            }
        }

    }

    //IMPRESION DE TABLA

    clrscr();system("color 1b");
    for(i=1;i<=oft+1;i++)
    {
        if(i<oft+1)
        {
            gotoxy(5,4+4*i);cout<<"OF"<<i;
        }

        for(j=1;j<=dem+1;j++)
        {
            gotoxy(9*j+1,2+4*i);cout<<"---------";
            for(k=0;k<=4;k++)
            {
                gotoxy(9*j+1,2+4*i+k);cout<<"|";
            }

        }

    }

    //LLENADO DE DATOS
    con=0;
    for(i=1;i<=oft+1;i++)
    {
        if(i<oft+1)
        {
            gotoxy(5,4+4*i);cout<<"OF"<<i;
        }
        for(j=1;j<=dem+1;j++)
        {

            gotoxy(9*j+1,2+4*i);cout<<"---------";
            for(k=0;k<=4;k++)
            {

                gotoxy(9*j+1,2+4*i+k);cout<<"|";
            }

        }
    }
    gotoxy(5,3);cout<<"TABLA "<<pen<<" :";
     for(i=1;i<=oft;i++)
    {
        for(j=1;j<=dem;j++)
        {
            gotoxy(6+9*j,3+4*i);cout<<coef[i][j];
            if(sol[i][j]!=-1)//IMRPIMIR SOLUCIÓN
            {
                gotoxy(2+9*j,5+4*i);cout<<sol[i][j];
            }
        }
        gotoxy(3+9*(dem+1),4+4*i);cout<<coef[i][dem+1];



    }
    for(j=1;j<=dem;j++)
    {
        gotoxy(3+9*j,7+4*oft);cout<<coef[oft+1][j];

    }

    //COMPROBACIÓN DE BUCLE
    con=0;
    for(i=1;i<=oft;i++)
    {
        for(j=1;j<=dem;j++)
        {
            if(aux2[i][j]==0)
            {
                con++;
            }
        }
    }
    gotoxy(5,25);system("pause");

    }while(con!=0);

    //CALCULO DEL MAXIMO BENEFICIO
    z=0;
    gotoxy(5,23);cout<<"MAXIMO BENEFICIO = ";
    for(i=1;i<=oft;i++)
    {
        for(j=1;j<=dem;j++)
        {
            if(sol[i][j]!=-1)
            {
                    if(i!=oft||j!=dem)
                    {
                        cout<<coef[i][j]<<" x "<<sol[i][j]<<" + ";
                        z=z+sol[i][j]*coef[i][j];
                    }else
                    {
                        cout<<coef[i][j]<<" x "<<sol[i][j];
                        z=z+sol[i][j]*coef[i][j];
                    }



            }

        }
    }
    gotoxy(5,24);cout<<"EL MAXIMO BENEFICIO ES = "<<z;
    gotoxy(5,25);system("pause");







}

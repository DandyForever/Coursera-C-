#include <vcl.h>

#pragma hdrstop

#include "UBound.h"

#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

#pragma resource "*.dfm"

TForm1 *Form1;

int n=10;

int x1=1,x2=2;

double h=(x2-x1)/(double)n;

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)

        : TForm(Owner)

{

}

//---------------------------------------------------------------------------

double ex_sol(double x)

{

    return sin(sqrt(x))+cos(sqrt(x));

}

void __fastcall TForm1::Button_BashClick(TObject *Sender)

{

    Label_TypeMethod->Caption="Конечно-разностный";

    double x,s,p,q,par_1,par_n;

    int i,j,i1,j1;

    double A[100][100];

    double y[100];

    x=x1+h;

    par_1=(h/2.0*(-1.0/(2.0*(x)))+1)*ex_sol(1);

    par_n=(-h/2.0*(-1.0/(2.0*(2-2*h)))+1)*ex_sol(2);

    for(i=0;i<n-1;i++)

    {

        q=(-1.0/(4.0*x));

        p=(-1.0/(2.0*x));

        for(j=0;j<n-1;j++)

        {

            if(i==j)

            {

                A[i][j]=(2+h*h*q);

            }

            else

            {

                if(j==(i+1))

                {

                    A[i][j]=(h*p/2-1);

                }

                else

                {

                    if(i==j+1)

                        A[i][j]=(-h*p/2-1);

                    else

                        A[i][j]=0;

                }

            }

        }

        if(i==0)

        {

            A[i][j]=par_1;

        }

        else

        {

            if(i==n-2)

                A[i][j]=par_n;

            else

                A[i][j]=0;

        }

        x=x+h;

    }

    for(i=0;i<n-1;i++)

    {

        j=i;

        s=A[i][j];

        for(j=i;j<=n-1;j++)

        {

            A[i][j]=A[i][j]/s;

        }

        for(i1=i+1;i1<n-1;i1++)

        {

            s=A[i1][i];

            for(j1=i;j1<n;j1++)

                A[i1][j1]=A[i1][j1]-(A[i][j1]*s);

        }

    }

    y[n-2]=A[n-2][n-1]/A[n-2][n-2];

    for(i=n-3;i>=0;i--)

    {

        s=A[i][n-1];

        for(j=i+1;j<=n-2;j++)

        {

            s=s-A[i][j]*y[j];

        }

        y[i]=s/A[i][i];

    }

    x=x1+h;

    for (int m = 0; m < n-1; m++)

    {

        StringGrid1->Cells[0][m]=FloatToStr(x);

        StringGrid1->Cells[1][m]=FloatToStr(y[m]);

        StringGrid1->Cells[2][m]=FloatToStr(ex_sol(x));

        StringGrid1->Cells[3][m]=FloatToStr(fabs(y[m]-ex_sol(x)));

        x=x+h;

    }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button_ExitClick(TObject *Sender)

{

    Close();

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button_MolClick(TObject *Sender)

{

    Label_TypeMethod->Caption="Метод прогонки";

    double x;

    int i;

    i = 0;

    double alfa[100];

    double beta[100];

    double A,B,C,F;

    alfa[0] = 0;

    beta[0] = 1.38177;

    x=x1;

    for (i = 0; i < n - 1; i++)

    {

        x = x + h;

        A=-h/2.0*(-1.0/(2.0*x))-1.0;

        B=h/2.0*(-1.0/(2.0*x))-1.0;

        C=-2.0-h*h*(-1.0/(4.0*x));

        F=0;

        alfa[i+1]=B/(C-alfa[i]*A);

        beta[i+1]=(F+beta[i]*A)/(C-alfa[i]*A);

    }

    double y[100];

    y[0] = ex_sol(x2);

    x = x1+h;

    for (i = 1; i < n; i++)

    {

        y[i] = alfa[n - i] * y[i - 1] + beta[n - i];

    }

    for (i = 0; i <=n; i++)

    {

        StringGrid1->Cells[0][i]=FloatToStr(x);

        StringGrid1->Cells[1][i]=FloatToStr(y[n-i-1]);

        StringGrid1->Cells[2][i]=FloatToStr(ex_sol(x));

        StringGrid1->Cells[3][i]=FloatToStr(fabs(y[n-i-1]-ex_sol(x)));

        x=x+h;

    }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)

{

    Button_Bash->Visible=true;

    Button_Mol->Visible=false;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)

{

    Button_Bash->Visible=false;

    Button_Mol->Visible=true;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button_ExitClick(TObject *Sender)

{

    Close();

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button_MolClick(TObject *Sender)

{

    Label_TypeMethod->Caption="Метод прогонки";

    double x;

    int i;

    i = 0;

    double alfa[100];

    double beta[100];

    double A,B,C,F;

    alfa[0] = 0;

    beta[0] = 1.38177;

    x=x1;

    for (i = 0; i < n - 1; i++)

    {

        x = x + h;

        A=-h/2.0*(-1.0/(2.0*x))-1.0;

        B=h/2.0*(-1.0/(2.0*x))-1.0;

        C=-2.0-h*h*(-1.0/(4.0*x));

        F=0;

        alfa[i+1]=B/(C-alfa[i]*A);

        beta[i+1]=(F+beta[i]*A)/(C-alfa[i]*A);

    }

    double y[100];

    y[0] = ex_sol(x2);

    x = x1+h;

    for (i = 1; i < n; i++)

    {

        y[i] = alfa[n - i] * y[i - 1] + beta[n - i];

    }

    for (i = 0; i <=n; i++)

    {

        StringGrid1->Cells[0][i]=FloatToStr(x);

        StringGrid1->Cells[1][i]=FloatToStr(y[n-i-1]);

        StringGrid1->Cells[2][i]=FloatToStr(ex_sol(x));

        StringGrid1->Cells[3][i]=FloatToStr(fabs(y[n-i-1]-ex_sol(x)));

        x=x+h;

    }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)

{

    Button_Bash->Visible=true;

    Button_Mol->Visible=false;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)

{

    Button_Bash->Visible=false;

    Button_Mol->Visible=true;

}
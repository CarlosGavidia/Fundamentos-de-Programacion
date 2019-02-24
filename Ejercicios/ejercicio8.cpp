#include <iostream>
using namespace std;
int main ()
{
	double op1,op2,op3,op4,op5,op6, bruto, IRPF, retencion  ,  neto ;
	cout << "sueldo base :" << endl;
	cin >> op1;
	cout << "complemento de destino :" << endl;
	cin >> op2;
	cout >> "complemento de cargo academico:" << endl;
	cin >> op3;
	cout << "horas extra realizadas:" << endl;
	cin >> op4;
	cout << "hijos:" << endl;
	cin >> op5;
	cout << "mayores:" << endl;
	cin >> op6;
	cout << "calculo de la nomina" << endl;
	cout << "sueldo bruto"<< endl;
	bruto = op1 + op2+ op3 + (23* op4);
	cout <<  bruto << "€" << endl;
	cout << "porcentaje de IRPF:" << endl;
	IRPF = 24 - op6 - (2*op5);
	cout << IRPF << "%" << endl;
	cout << "retencion  : " << endl;
	retencion =  bruto *  IRPF / 100 ;
	cout << retencion << "€" << endl;
	cout << "sueldo neto:" << "€" <<  endl;
	 neto =  bruto - retencion  ;
	cout <<  neto << endl;
	}
	
	
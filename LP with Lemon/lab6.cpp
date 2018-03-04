/******************************************************
 Nome: Alan Ricardo Gomes 	RA: 145103
E-mail: alanrgo@gmail.com

Linear Programming assingment using lemon
*******************************************************/

#include <iostream>
#include <iomanip>
#include <lemon/lp.h>

using namespace lemon;
using namespace std;

int main(int argc, const char *argv[]){
	Lp lp;

	//read
	int n; //number of tests
	double h, c, rp, tp, tb;
	vector<double> d(13);
	vector<double> rb(13);
	vector<double> ra(13);
	cin >> n;

	cout << fixed;
	cout << setprecision(2);

	for ( int x = 0; x < n; x ++ ){
			//variables
		vector<Lp::Col> api(13);
		vector<Lp::Col> spi(13);
		vector<Lp::Col> abi(13);
		vector<Lp::Col> sbi(13);
		vector<Lp::Col> aai(13);
		vector<Lp::Col> sai(13);

		vector<Lp::Col> cc(13);
		vector<Lp::Col> pp(13);
		vector<Lp::Col> cdb(13);
		vector<Lp::Col> acoes(13);

		cin >> h >> c >> rp >> tp >> tb;
		for ( int k = 0; k < 12; k ++ )
			cin >> rb[k]; 
		for ( int k = 0; k < 12; k ++ )
			cin >> ra[k]; 
		for ( int k = 0; k < 12; k ++ )
			cin >> d[k]; 

		rb[12] = 0;
		ra[12] = 0;
		d[12] = 0;

		// Define variables to container
		lp.addColSet(api);
		lp.addColSet(spi);
		lp.addColSet(abi);
		lp.addColSet(sbi);
		lp.addColSet(sai);
		lp.addColSet(aai);
		lp.addColSet(cc);
		lp.addColSet(pp);
		lp.addColSet(cdb);
		lp.addColSet(acoes);

		// Define problem
		lp.max();
		lp.obj( cc[12] + pp[12] + cdb[12] + acoes[12] );

		// non-negative values 
		for (int i = 0 ; i < 13; i ++ ){
			lp.colLowerBound(cc[i], 0);
			lp.colLowerBound(pp[i], 0);
			lp.colLowerBound(cdb[i], 0);
			lp.colLowerBound(acoes[i], 0);
			lp.colLowerBound(api[i], 0);
			lp.colLowerBound(spi[i], 0);
			lp.colLowerBound(abi[i], 0);
			lp.colLowerBound(sbi[i], 0);
			lp.colLowerBound(sai[i], 0);
			lp.colLowerBound(aai[i], 0);
		}

		lp.addRow( cc[0] == h - d[0] - api[0] - abi[0] - aai[0] + spi[0] + sai[0] + sbi[0]); // first bound
		lp.addRow( pp[0] == 0 + api[0] ); // first bound
		lp.addRow( cdb[0] == 0 + abi[0] ); // first bound
		lp.addRow( acoes[0] == 0 + aai[0] ); // first bound

		// no withdraws from any investiments in the first month
		lp.addRow( spi[0] == 0 );
		lp.addRow( sbi[0] == 0 );
		lp.addRow( sai[0] == 0 );

		// no transactions in january/2019
		lp.addRow( api[12] == 0 );
		lp.addRow( abi[12] == 0 );
		lp.addRow( aai[12] == 0 );

		// Adding restrictions to the transactions' flow
		for (int i = 1; i < 13; i ++ ){
			lp.addRow( cc[i] == cc[i-1] - c - d[i] - api[i] - abi[i] - aai[i] + spi[i] + sai[i] + sbi[i] );
			lp.addRow( pp[i] == (pp[i-1] * (100 + rp) - spi[i] * ( 100 + tp ) + 100 * api[i])/100);
			lp.addRow( cdb[i] == ( cdb[i-1] * (100 + rb[i-1] ) - sbi[i]*( 100 + tb) + 100*abi[i])/100);
			lp.addRow( acoes[i] == (acoes[i-1]*(100 + ra[i-1] ) - 100 * sai[i] + 100 * aai[i])/100 );
		}
		
		lp.solve();
		cout << "Caso" << x+1 << endl;
		if (lp.primalType() == Lp::OPTIMAL) {
			for (int i = 0; i < 12; i++) {
		        cout << "Mes " << i+1 << "/2018:" << endl;
		        cout << "investir na poupanca " << lp.primal(api[i]) << " dinheiros" << endl; 
		        cout << "retirar da poupanca " << lp.primal(spi[i]) << " dinheiros" << endl; 
		        cout << "investir no CDB " << lp.primal(abi[i]) << " dinheiros" << endl; 
		        cout << "retirar do CDB " << lp.primal(sbi[i]) << " dinheiros" << endl; 
		        cout << "investir nas acoes " << lp.primal(aai[i]) << " dinheiros" << endl; 
		        cout << "retirar das acoes " << lp.primal(sai[i]) << " dinheiros" << endl; 
	    	}
	    	cout << "Mes " << 1 << "/2019:" << endl;
	        cout << "retirar da poupanca " << lp.primal(spi[12]) << " dinheiros" << endl; 
	        cout << "retirar do CDB " << lp.primal(sbi[12]) << " dinheiros" << endl; 
	        cout << "retirar das acoes " << lp.primal(sai[12]) << " dinheiros" << endl; 
	        cout << "saldo da heranca em 2019:  " << lp.primal() << " dinheiros" << endl; 
		} else {
			cout << "Solucao impossivel ou ilimitada" << endl;
		}

		lp.clear();
	}
}

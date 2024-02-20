//Stefan Sirkovic NRT-53/22
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
#define MAX 200

// Definisanje enuma za greske i poruka o greskama
enum Greska{GRESKA_MEMORIJA, GRESKA_CITANJA, GRESKA_UPISA};
char *poruke_o_greskama[] = {
	"\nGreska pri dodeli memorije.\n",
	"\nGreska pri otvaranju datoteke za citanje.\n",
	"\nGreska pri otvaranju datoteke za upis.\n"
};
// Struktura za cuvanje podataka o igracu
struct s{
	char ime[MAX+1];
	char prezime[MAX+1];
	int iznos;
};
// Globalna promenljiva za cuvanje sume
int suma=0;
// Deklaracije funkcija
void pravila();
void podaci(s *igrac);
void prvaIgra();
void drugaIgra(s *igrac);
void greska(Greska status);

// Glavna funkcija programa
int main(){

	s *igrac;
	int n=1;
	char opcija;
	
	igrac=new s[n];
	if(igrac==NULL)
		greska(GRESKA_MEMORIJA);

	pravila();

	// Petlja koja omogucava igracima da igraju vise puta
	do{
	podaci(igrac);
	prvaIgra();
	drugaIgra(igrac);
	cout << "Da li zelite novu igru (D/N)?: ";
	cin.ignore();
	cin >> opcija;
	if(opcija=='D' || opcija=='d'){
		n++;
		suma=0;
	}
	}while(opcija=='D' || opcija=='d');


	delete [] igrac;
	return 0;
}

/*
Funkcija pravila()
Opis:
    - Ispisuje pravila igre kviza.
Ulaz i izlaz:
    - Nema ulaznih parametara i nema povratnih vrednosti.
Poziva se u:
    - main()
Funkcije koje poziva:
    - Nema pozive drugih funkcija.
*/
void pravila(){

	// Izgled u konzoli
	cout.width(60);
	cout.fill('=');
	cout << " KVIZ POTERA ";
	cout.width(60);
	cout.setf(ios::left);
	cout << "=";
	cout.unsetf(ios::left);
	cout<<endl << endl;

	cout << "PRAVILA IGRE:" << endl << endl;
	cout << "1. Prva igra:" << endl << "-Odgovarate na deset postavljenih pitanja." 
	<< endl << "-Vasa pocetna suma je 0$, na svaki dat tacan odgovor na vasu sumu se dodaje 10000$."
	<< endl <<	"-Cilj je da odgovorite tacno na sto vise postavljenih pitanja,"
	<< endl << "a u slucaju da niste dali nijedan tacan odgovor, igra se zavrsava." << endl << endl;
	cout << "2. Druga igra:"
	<< endl << "-Borite se protiv 'tragaca' i zajedno sa njim odgovarate na postavljena pitanja."
	<< endl << "-Ponudjeni su Vam odgovori pod 'a','b' i 'c' i unosite ih u tom formatu."
	<< endl << "-Ulazite sa osvojenom sumom iz prve igre, a tragac ce Vam ponuditi donju i gornju sumu."
	<< endl << "-Cilj igre je da 'pobegnete' od tragaca, "
	<< "u slucaju da Vas tragac stigne, igra se zavrsava." << endl << endl;
	cout << "SRECNO!" << endl << endl;

}
/*
Funkcija podaci()
Opis:
    - Omogucava igracu unos imena i prezimena.
    - Koristi se za prikupljanje osnovnih podataka o igracu.
Ulaz:
    - Struktura s *igrac: Pokazivac na strukturu koja cuva podatke o igracu.
Izlaz:
    - Nema povratne vrednosti, ali unosi ime i prezime igraca u strukturu.
Poziva se u:
    - main()
Funkcije koje poziva:
    - Nema pozive drugih funkcija.
*/
void podaci(s *igrac){
	cout << "Unesite ime: ";
	cin	>> igrac->ime;
	cout << "Unesite prezime: ";
	cin	>> igrac->prezime;
}

/*
Funkcija prvaIgra()
Opis:
    - Prikazuje prvu igru kviza gde igrac odgovara na 10 pitanja.
    - Na osnovu tacnosti odgovora, igrac moze osvojiti odredjenu sumu koju brani u drugoj igri.
	- Ako nije dat bar jedan tacan odgovor, igra se prekida.
Ulaz:
    - Nema ulaznih parametara, ali koristi se ulaz iz tekstualnih datoteka s pitanjima.
Izlaz:
    - Nema povratne vrednosti, ali menja globalnu promenljivu 'suma'.
Poziva se u:
    - main()
Funkcije koje poziva:
    - greska() - u slucaju problema pri citanju datoteka.
*/
void prvaIgra(){

	ifstream fin;
	char mojOdg[MAX+1],pitanje[10][MAX+1],odgovor[10][MAX+1];
    int broj;
	
	//Random funkcija koja sluzi da nasumicno odabere jednu od datoteka sa pitanjima
	srand(time(0));
	broj=rand()%5+1;

	switch(broj){
	case 1: 
		fin.open("prvaIgraPitanja1.txt");
		break;
	case 2:
		fin.open("prvaIgraPitanja2.txt");
		break;
	case 3: 
		fin.open("prvaIgraPitanja3.txt");
		break;
	case 4: 
		fin.open("prvaIgraPitanja4.txt");
		break;
	case 5: 
		fin.open("prvaIgraPitanja5.txt");
		break;
	}

	if(!fin)
		greska(GRESKA_CITANJA);

	//Izgled u konzoli
	cout << endl;
	cout.width(60);
	cout.fill('=');
	cout << " PRVA IGRA ";
	cout.width(60);
	cout.setf(ios::left);
	cout << "=";
	cout.unsetf(ios::left);
	cout<<endl << endl;

	for(int i=0;i<10;i++){
		//Citanje pitanja i odgovora iz datoteke
		fin.getline(pitanje[i],MAX+1,':');     
		fin.getline(odgovor[i],MAX+1);
		cout << i + 1 << ". " << pitanje[i] << endl;
		cin >> mojOdg;
		//Provera tacnosti odgovora
		if (strcmp(mojOdg,odgovor[i]) == 0) {
            suma += 10000;
			cout << endl << "Vas odgovor je tacan!" 
			<< endl << "Trenutna suma: " << suma << "$" << endl << endl;
		}
		else
            cout << endl << "Greska, tacan odgovor je: " << odgovor[i] 
			<< endl << "Trenutna suma: " << suma << "$" << endl << endl;
	} 

	if(suma==0)
	{
		cout << "Nazalost, izgubili ste, niste tacno odgovorili ni na jedno pitanje" <<
		endl << "u prvoj igri i to nije dovoljno za pocetak druge igre." 
		<< endl << "Vise srece drugi put!" << endl << endl;
		exit(0);
	}

        fin.close();
    }

/*
Funkcija drugaIgra()
Opis:
    - Prikazuje drugu igru kviza gde igrac odgovara na pitanja izbegavajuci "tragaca".
    - Omogucava igracu da odabere nivo rizika i odgovara na pitanja za osvajanje odredjene sume.
Ulaz:
    - Struktura s *igrac: Pokazivac na strukturu koja cuva podatke o igracu.
Izlaz:
    - Nema povratne vrednosti, ali menja podatke o igracu sa osvojenom sumom.
Poziva se u:
    - main()
Funkcije koje poziva:
    - greska() - u slucaju problema pri citanju datoteka ili upisu rezultata.
*/
void drugaIgra(s *igrac){

	ifstream fin;
	ofstream fout;
	int donja,gornja,trenutna,igrac_brojac=0,tragac_brojac=8,i,broj,tragac_broj=0,tragac_iza=0;
	char opcija,mojOdg,pitanje[10][MAX+1],
	odgovorA[10][MAX+1],odgovorB[10][MAX+1],odgovorC[10][MAX+1],tacan,tragacOdgovor;

	//Odredjivanje ponuda sume
	trenutna=suma;
	donja=suma/9;
	gornja=suma*9;
	
	//Random funkcija koja sluzi da nasumicno odabere jednu od datoteka sa pitanjima
	srand(time(0));
	broj=rand()%3+1;
	
	switch(broj){
	case 1: 
		fin.open("drugaIgraPitanja1.txt");
		break;
	case 2:
		fin.open("drugaIgraPitanja2.txt");
		break;
	case 3: 
		fin.open("drugaIgraPitanja3.txt");
		break;
	}

	if(!fin)
		greska(GRESKA_CITANJA);

	//Izgled u konzoli
	cout << endl;
	cout.width(60);
	cout.fill('=');
	cout << " DRUGA IGRA ";
	cout.width(60);
	cout.setf(ios::left);
	cout << "=";
	cout.unsetf(ios::left);
	cout<<endl << endl;

	//Odabir tezine igre
	cout << "Cestitamo, u prvoj igri osvojili ste: " << trenutna << "$" << endl << endl;
	cout << "a) Gornja suma: " << gornja << "$"
	<< endl << "b) Trenutna suma: " << trenutna << "$" 
	<< endl << "c) Donja suma: " << donja << "$" << endl;
	do{
		cout << "Izaberite ponudu tragaca (a,b,c): ";
		cin.ignore();
		cin >> opcija;
		if(opcija!='a' && opcija!='b' && opcija!='c')
			cout << "Pogresno uneta opcija, unesite je u formatu sa jednim slovom (a,b,c)." 
			<< endl << endl;

	}while(opcija!='a' && opcija!='b' && opcija!='c');
	 
	//Switch case sa tri slucaja u zavisnosti od odabira tezine igre
	switch(opcija){
	case 'a':
		//Izgled u konzoli
		cout << endl << "Izabrali ste gornju sumu i branite: "
			<< gornja << "$"
			<< endl << "Morate tacno da odgovorite na 6 pitanja (a,b,c), a tragac je 2 koraka iza vas." 
			<< endl 
			<< "=========================================="
			<< "============================================" << endl << endl;
		//Broj potrebnih tacnih odgovora i udaljenost tragaca (tragac je udaljen 8 koraka od cilja uvek)
		igrac_brojac=6;
		tragac_iza=2;

		//Sve dok tragac nije stigao igraca
		while(igrac_brojac!=tragac_brojac){
			i=0;
			fin.getline(pitanje[i],MAX+1,':');
			fin.getline(odgovorA[i],MAX+1,':');
			fin.getline(odgovorB[i],MAX+1,':');
			fin.getline(odgovorC[i],MAX+1,':');
			fin.get(tacan);
			cout << pitanje[i] << endl << endl;
			cout << "a) " << odgovorA[i] << "   " << "b) " 
				<< odgovorB[i] << "   " << "c) " << odgovorC[i] << endl;
	
		//Unos odgovora
		do{
		cout << endl << "Unesite odgovor (a,b,c): ";
		cin.ignore();
		cin >> mojOdg;
		if(mojOdg!='a' && mojOdg!='b' && mojOdg!='c')
			cout << "Pogresno uneta opcija, unesite je u formatu sa jednim slovom (a,b,c)." 
			<< endl << endl;
		}while(mojOdg!='a' && mojOdg!='b' && mojOdg!='c');


		/*Provera tacnosti odgovora igraca, u slucaju da je tacan smanjuje se broj koraka do cilja
		i povecava se rastojanje od tragaca */
		if (mojOdg==tacan){ 
			cout << "=========================================="
				<< "============================================" 
				<< endl << "Tabela:" << endl << "\tVas odgovor je tacan!" << endl;
			igrac_brojac--;
			tragac_iza++;
		}
		else
            cout << "============================================="
			<< "=========================================" 
			<< endl << "\tGreska, tacan odgovor je pod: " << tacan << endl;
		
		//Nasumican odgovor tragaca koriscenjem funkcije rand()
		tragac_broj=rand()%3+1;
		switch(tragac_broj)
		{
		case 1: 
			tragacOdgovor='a';
			break;
		case 2: 
			tragacOdgovor='b';
			break;
		case 3: 
			tragacOdgovor='c';
			break;
		}

		/*Provera tacnosti odgovora tragaca, u slucaju da je tacan smanjuje mu se broj koraka do cilja
		i smanjuje mu se rastojanje od igraca */
		if (tragacOdgovor==tacan){ 
			cout << endl << "\tTragac je dao tacan odgovor!" << endl << endl;
			tragac_brojac--;
			tragac_iza--;
		}
		else
            cout << endl << "\tTragac nije dao tacan odgovor!" << endl << endl;
		

		cout << "\tOstalo vam je " 
		<< igrac_brojac << " koraka do cilja i tragac je " 
		<< tragac_iza << " korak/a iza vas." 
		<< endl << "======================================"
		<< "================================================" << endl << endl; 

		//Ako tragac stigne igraca igra je zavrsena
		if(igrac_brojac==tragac_brojac)
		{
			cout << "Nazalost tragac vas je stigao i igra je za vas zavrsena." << endl << endl;
			exit(0);
		}

		//Ako je igrac uspeo da stigne do cilja rezultati se upisuju u tekstualnu datoteku
		if(igrac_brojac==0){
			cout << endl << endl << "---CESTITAMO, USPELI STE DA OSVOJITE SUMU KOJA IZNOSI: " 
			<< gornja << "$" << endl << endl;
			igrac->iznos=gornja;
			fout.open("rezultat.txt",ios::app);
			if(!fout)
				greska(GRESKA_UPISA);
			fout << igrac->ime << " " << igrac->prezime << " " << igrac->iznos << "$" << endl;
			break;
		}
		i++;
		
		}
		break;
	
	
	case 'b':
		//U drugom slucaju razlikuje se samo udaljenost od cilja i od tragaca
		cout << endl << "Izabrali ste trenutnu sumu i branite: " 
		<< trenutna << "$" 
		<< endl << "Morate tacno da odgovorite na 5 pitanja (a,b,c), a tragac je 3 koraka iza vas." 
		<< endl << "===================================="
		<< "==================================================" << endl << endl;
		igrac_brojac=5;
		tragac_iza=3;
		while(igrac_brojac!=tragac_brojac){
			i=0;
			fin.getline(pitanje[i],MAX+1,':');
			fin.getline(odgovorA[i],MAX+1,':');
			fin.getline(odgovorB[i],MAX+1,':');
			fin.getline(odgovorC[i],MAX+1,':');
			fin.get(tacan);
			cout  << pitanje[i] << endl << endl;
			cout << "a) " << odgovorA[i] 
			<< "   " << "b) " << odgovorB[i] 
			<< "   " << "c) " << odgovorC[i] << endl;

		do{
		cout << endl << "Unesite odgovor (a,b,c): ";
		cin.ignore();
		cin >> mojOdg;
		if(mojOdg!='a' && mojOdg!='b' && mojOdg!='c')
			cout << "Pogresno uneta opcija " 
			<< "unesite je u formatu sa jednim slovom (a,b,c)." << endl << endl;
		}while(mojOdg!='a' && mojOdg!='b' && mojOdg!='c');

		if (mojOdg==tacan){ 
			cout << "======================================"
			<< "================================================" 
			<< endl << "Tabela:" << endl << "\tVas odgovor je tacan!" << endl;
			igrac_brojac--;
			tragac_iza++;
		}
		else
            cout << "========================================"
			<< "==============================================" 
			<< endl << "\tGreska, tacan odgovor je pod: " << tacan << endl;
		
		tragac_broj=rand()%3+1;
		switch(tragac_broj)
		{
		case 1: 
			tragacOdgovor='a';
			break;
		case 2: 
			tragacOdgovor='b';
			break;
		case 3: 
			tragacOdgovor='c';
			break;
		}

		if (tragacOdgovor==tacan){ 
			cout << endl << "\tTragac je dao tacan odgovor!" << endl << endl;
			tragac_brojac--;
			tragac_iza--;
		}
		else
            cout << endl << "\tTragac nije dao tacan odgovor!" << endl << endl;
		

		cout << "\tOstalo vam je " << igrac_brojac 
		<< " koraka do cilja i tragac je " 
		<< tragac_iza << " korak/a iza vas." 
		<< endl << "======================================"
		<< "================================================" << endl << endl; 

		if(igrac_brojac==tragac_brojac)
		{
			cout << "Nazalost tragac vas je stigao i igra je za vas zavrsena." << endl << endl;
			exit(0);
		}

		if(igrac_brojac==0){
			cout << endl << endl << "---CESTITAMO, USPELI STE DA OSVOJITE SUMU KOJA IZNOSI: " 
			<< trenutna << "$" << endl << endl;
			igrac->iznos=trenutna;
			fout.open("rezultat.txt",ios::app);
			if(!fout)
				greska(GRESKA_UPISA);
			fout << igrac->ime << " " << igrac->prezime << " " << igrac->iznos << "$" << endl;
			break;
		}
		i++;
		
		}
		
		break;

	case 'c':
		//U trecem slucaju razlikuje se samo udaljenost od cilja i od tragaca
		cout << endl << "Izabrali ste donju sumu i branite: " 
		<< donja << "$" << endl 
		<< "Morate tacno da odgovorite na 4 pitanja (a,b,c), a tragac je 4 koraka iza vas." 
		<< endl << "=========================================="
		<< "============================================" << endl << endl;
		igrac_brojac=4;
		tragac_iza=4;
		while(igrac_brojac!=tragac_brojac){
			i=0;
			fin.getline(pitanje[i],MAX+1,':');
			fin.getline(odgovorA[i],MAX+1,':');
			fin.getline(odgovorB[i],MAX+1,':');
			fin.getline(odgovorC[i],MAX+1,':');
			fin.get(tacan);
			cout  << pitanje[i] << endl << endl;
			cout << "a) " << odgovorA[i] << "   " 
			<< "b) " << odgovorB[i] << "   " 
			<< "c) " << odgovorC[i] << endl;

		do{
		cout << endl << "Unesite odgovor (a,b,c): ";
		cin.ignore();
		cin >> mojOdg;
		if(mojOdg!='a' && mojOdg!='b' && mojOdg!='c')
			cout << "Pogresno uneta opcija " 
			<< "unesite je u formatu sa jednim slovom (a,b,c)." << endl << endl;
		}while(mojOdg!='a' && mojOdg!='b' && mojOdg!='c');

		if (mojOdg==tacan){ 
			cout << "============================================"
			<< "==========================================" << endl 
			<< "Tabela:" << endl << "\tVas odgovor je tacan!" << endl;
			igrac_brojac--;
			tragac_iza++;
		}
		else
            cout << "====================================="
			<< "=================================================" 
			<< endl << "\tGreska, tacan odgovor je pod: " << tacan << endl;
		
		tragac_broj=rand()%3+1;
		switch(tragac_broj)
		{
		case 1: 
			tragacOdgovor='a';
			break;
		case 2: 
			tragacOdgovor='b';
			break;
		case 3: 
			tragacOdgovor='c';
			break;
		}

		if (tragacOdgovor==tacan){ 
			cout << endl << "\tTragac je dao tacan odgovor!" << endl << endl;
			tragac_brojac--;
			tragac_iza--;
		}
		else
            cout << endl << "\tTragac nije dao tacan odgovor!" << endl << endl;
		

		cout << "\tOstalo vam je " << igrac_brojac 
		<< " koraka do cilja i tragac je " 
		<< tragac_iza << " korak/a iza vas." 
		<< endl << "========================================"
		<< "==============================================" << endl << endl; 

		if(igrac_brojac==tragac_brojac)
		{
			cout << "Nazalost tragac vas je stigao i igra je za vas zavrsena." << endl << endl;
			exit(0);
		}

		if(igrac_brojac==0){
			cout << endl << endl << "---CESTITAMO, USPELI STE DA OSVOJITE SUMU KOJA IZNOSI: " 
			<< donja << "$" << endl << endl;
			igrac->iznos=donja;
			fout.open("rezultat.txt",ios::app);
			if(!fout)
				greska(GRESKA_UPISA);
			fout << igrac->ime << " " << igrac->prezime << " " << igrac->iznos << "$" << endl;
			break;
		}
		i++;
		
		}
		
		break;

	}

}

/*
Funkcija greska()
Opis:
    - Ispisuje odgovarajucu poruku o greskama na osnovu statusa.
Ulaz:
    - Greska status: status koji oznacava vrstu greske.
Izlaz:
    - Nema povratne vrednosti, ali ispisuje poruku o greskama.
Poziva se u:
    - skoro svim funkcijama.
Funkcije koje poziva:
    - exit() - za prekid izvrsavanja programa.
*/
void greska(Greska status){
	cerr << poruke_o_greskama[status];
	exit(1);
}

	



	
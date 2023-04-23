#include "funktsioonid.h"

#include <random>


//genereerib suvalise numbri antud vahemikus
int suvaline_number(int a, int b) {
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(a,b);
    return distribution(generator);
}

//olenevalt sisestatud numbrist tagastab värvi, mis sellele numbrile vastab, rouletti reeglite järgi
std::string värv(int a) {
    if (a == 0 || a == 37) { // kas 0 või 00
        return "roheline";
    }
    if (a < 11 || (a > 18 && a < 29)) {
        if (a % 2 == 0) {
            return "must";
        } else {
            return "punane";
        }
    } else {
        if (a % 2 == 1) {
            return "must";
        } else {
            return "punane";
        }
    }
}

// vastavalt sellele kas mängija võidab või kaotab (bool väärtus) tehakse teha kontole vastavad muudatused
void väline_tulemus(bool väärtus, int panuse_kogus, int kordaja, int* konto) {
    if (väärtus) {
        *konto += kordaja * panuse_kogus;
        std::cout << "võitiste: " << kordaja * panuse_kogus << "!\n";
    } else {
        *konto -=  panuse_kogus;
        std::cout << "kaotasite.\n";
    }
}

void käsurealt_info(int argc, char* argv[], std::vector<int>& kasutaja_sisend) { //loeb käsurealt saadud info ja paneb vektrorisse
    for (int i = 0; i < argc; ++i) { //töötleb käsurea sisendit
        kasutaja_sisend.push_back(std::atoi(argv[i])); //sisend muudetakse int tüübiks ja lisatakse vektorisse
    }
}

void failist_raha(std::string failiNimi, int& summa) { //loeb failist kontol oleva raha summa
    std::ifstream fail(failiNimi); //avab faili
    std::string rida;
    std::getline(fail, rida); //loeb ainult esimese rea, sest failis on ainult 1 rida konto summa jaoks
    summa = std::stoi(rida); //annab summale failist saadud väärtuse
    fail.close();
}

void raha_faili(std::string failiNimi, int& summa) { //paneb konto summa faili
    std::ofstream fail(failiNimi); //avab faili
    fail << summa; //lisab summa faili
    fail.close();
}

//pks rouletti round, kasutaja panuse kogusega ja panuse stiiliga, nt: 100€ panus punasele värvile
void round(int panuse_kogus, int panuse_stiil, int* konto) { //22 võidu viisi

    //genereeritakse suvaline number ja sellele vastav värv
    int number = suvaline_number(0, 37);
    std::string round_värv = värv(number);

    //väljastadakse, tulemus
    std::cout << "Pall maandus: " << round_värv << " " << number << "\n";     

    //sisemised panused

    //roulettis olevad välised panused (https://en.wikipedia.org/wiki/Roulette) 
    switch(panuse_stiil) {
        case 10: // 1 tulp
            väline_tulemus((number % 3 == 1 && number != 37), panuse_kogus, 2, konto);
        break;

        case 11: // 2 tulp
            väline_tulemus((number % 3 == 2), panuse_kogus, 2, konto);
        break;

        case 12: // 3 tulp
            väline_tulemus((number % 3 == 0 && number != 0), panuse_kogus, 2, konto);
        break;

        case 13: // 1 tosin
            väline_tulemus((0 < number && number < 13), panuse_kogus, 2, konto);
        break;

        case 14: // 2 tosin
            väline_tulemus((12 < number && number < 25), panuse_kogus, 2, konto);
        break;

        case 15: // 3 tosin
            väline_tulemus((24 < number && number < 37), panuse_kogus, 2, konto);
        break;

        case 16: // paaritu
            väline_tulemus((number % 2 == 1 && number != 37), panuse_kogus, 1, konto);
        break;

        case 17: // paaris
            väline_tulemus((number % 2 == 0 && number != 0), panuse_kogus, 1, konto);
        break;

        case 18: // punane
            väline_tulemus((round_värv == "punane"), panuse_kogus, 1, konto);
        break;

        case 19: // must
            väline_tulemus((round_värv == "must"), panuse_kogus, 1, konto);
        break;

        case 20: // 1-18 aka low
            väline_tulemus((number < 19 && number != 0), panuse_kogus, 1, konto);
        break;

        case 21: // 19-36 aka high
            väline_tulemus((number > 18), panuse_kogus, 1, konto);
        break;

        case 22: // snake
            väline_tulemus((number == 1 || number == 5 || number == 9 || number == 12 || number == 14 || 
            number == 16 || number == 19 || number == 23 || number == 27 || number == 39 || number == 32 || number == 34), panuse_kogus, 2, konto);
        break;
    }

}
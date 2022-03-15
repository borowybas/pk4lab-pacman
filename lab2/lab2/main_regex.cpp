#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>

/**
 * Wykonaj walidator adresu mejlowego z u�yciem biblioteki <regex>
 * najpierw wypisz wszystkie poprawne, a potem tylko te z domen� polsl
 */
void zad_1() {
    const std::string mailsToCheck[] = { "Jan.Kowalski@polsl.pl",
                                         "example.example.com",
                                         "rektor%polsl.pl",
                                         ".abc@gmail.com",
                                         "jankow-777@student.ads.polsl.pl",
                                         "test.@domian.com",
                                         "abx@wp.pl",
                                         "abc@pl",
                                         "Jan/Kowalski@polsl.pl" };

   
    std::regex mail("([a-z0-9-]+(\.[a-z]+)?)+@[a-z]+(\.[a-z]+)+", std::regex_constants::icase);

    for (const auto& plik : mailsToCheck) {
            std::cout << std::setw(16) << plik << " " <<
                std::regex_match(plik, mail) << std::endl;
    }
    std::cout << std::endl;
    

    std::regex mail2("([a-z]|[a-z]+\.[a-z])+@polsl\.pl", std::regex_constants::icase);
    
    std::cout << std::endl << "Maile polsl:" << std::endl;
    for (const auto& plik : mailsToCheck) {
        std::cout << std::setw(16) << plik << " " <<
            std::regex_match(plik, mail2) << std::endl;
    }
    std::cout << std::endl;
};

/**
 * Korzystaj�c z poznanej dzi� biblioteki policz ilo�� s��w w tek�cie
 * std::regex i std::regex_iterator b�d� tu niezb�dne, a pomocne b�dzie
 * std::distance
 */
void zad_2() {
    const std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

    std::regex word("([a-zA-Z])+");

    auto words_begin = std::sregex_iterator(text.begin(), text.end(), word);
    auto words_end = std::sregex_iterator();

    std::cout << "Zanleziono " << std::distance(words_begin, words_end) << " s��w." << std::endl<<std::endl;

};

/**
 * Popraw b��dy w tek�cie wed�ug podanych regu�
 * po p piszemy rz, a nie sz (wyj�tki: {pszczyna, pszenica, pszczo�a})
 * */
void zad_3() {
    std::string text = "pszyszedlem rzodkiewka pszenica zab pszczola pszebieralnia jelen";

    std::regex reg("\\b(psz)((?!enica)(?!czola)(?!czyna))");

    std::cout<<std::regex_replace(text, reg, "prz$3")<<std::endl<<std::endl;
};



/**
* Znajd� w tek�cie wczytanym z pliku wszystkie numery telefon�w,
* pami�taj o tym �e cyfry mog� by� rozdzielone spacj� lub my�lnikiem.
* Znalezione numery zapisz do jednej zmiennej typu string
* Nast�pnie wylistuj w konsoli wszystkie znalezione numery kierunkowe, bez plusa!
* wykorzystaj sregex_iterator oraz sregex_token_iterator
**/
void zad_4() {
    std::ifstream myFile("numery.txt");
    std::string line, file = "";

    if (myFile.is_open()) {
        while (std::getline(myFile, line))
        {
            file += line;
            file += "\n";
        }
        myFile.close();
    }

    std::regex reg1("\\+[0-9]{2,3}([ -][0-9]{2,4})+");

    std::sregex_iterator res(file.begin(), file.end(), reg1);
    std::sregex_iterator end;

    std::string numbers;

    while (res != end) {
        numbers += res->str();
        numbers += "\n";
        res++;
    }

    std::regex kierunkowy("\\+(\\d+)");

    std::sregex_token_iterator r(numbers.begin(), numbers.end(), kierunkowy, 1), end2;

    std::cout << "Poprawne numery:" << std::endl << numbers << std::endl;
    std::cout << "Poprawne numery kieunkowe: " << std::endl;

    std::copy(r, end2, std::ostream_iterator<std::string>(std::cout, "\n"));

    /*
    Poprawne numery to:
    +48 604 206 796
    +35 22 22 22 22
    +234 234 545 2332
    +63 242-34342-234
    +12 3442
    */
    /* Poprawne numery kierunkowe to:
    48
    35
    234
    63
    12
    */

};
/*-------------------------*/
/*        PREZENTACJA      */

/**
 * sprawdzamy, kt�re pliki maj� rozszerzenie TXT - klucz obejmuje ca�y string
 */
void test_regex_match() {
    //dane wej�ciowe
    const std::string pliki[] =
    { "planPutina.txt",
     "maszynaW.exe",
     "config.bat",
     "poezja.txt" };

    //                            search pattern       uwzgl�dnia wielkie litery
    const std::regex txt_fType("[a-z]+\\.txt", std::regex_constants::icase);

    //wyszukiwanie i wypisywanie
    for (const auto& plik : pliki) {
        std::cout << std::setw(16) << plik << " " <<
            std::regex_match(plik, txt_fType) << std::endl;
    }

};

/**
 * sprawdzamy, czy wyst�puje s�owo zgodne z kluczem
 */
void test_regex_search() {
    std::regex example("[a-z]+o[a-z]+a.*");
    std::string data[] = { "Ala ma kota.", "Ola ma szopa.", "Misia ma rysia." };
    for (const auto& item : data) {
        std::cout << std::setw(16) << item << " " << std::regex_search(item, example) << std::endl;
    }
};

/**
 * zamieniamy s�owa zaczynaj�ce si� na "pod" na zaczynaj�ce si� na "wy"
 * ignorujemy s�owo "pod"
 */
void test_regex_replace() {
    std::string s("wszyscy podci�gamy pod niekt�re podci�gi\n");
    //         pocz�tek s�owa  wy��czenie
    //                  "pod"  pustych po "pod"
    std::regex r("\\b(pod)([^ ])");
    //                                na co zamieniamy i ile znak�w zamieniamy (bez tego utnie)
    std::cout << std::regex_replace(s, r, "wy$2");
};

/**
 * iterujemy si� przez wyniki spe�niane przez u�ytego regex'a
 */
void test_regex_iterator() {
    //                             XX-XXX
    std::regex postal_code("\\d{2}-\\d{3}");
    std::string lot_of_codes = "43-200 202-50 12 41-706 512 21 88-37 45-302";
    //std::regex_iterator<std::string::const_iterator> <=> std::sregex_iterator
    std::sregex_iterator results(lot_of_codes.begin(), lot_of_codes.end(), postal_code);
    std::sregex_iterator end;
    while (results != end)
    {
        std::cout << results->str() << std::endl;
        ++results;
    }
};

/**
 * Wydobywa informacj� o po�o�eniu grup przechwytywania
 */
void test_match_results() {
    std::regex example("([a-z]+o[a-z]+a).*([a-z]+y[a-z]+a).*");
    std::regex example1("([a-z]+o[a-z]+a).*");
    std::string a = "Ala ma kota. ", b = "Ola ma szopa. ", c = "Misia ma rysia.";
    std::string  d = a + b + c;
    std::smatch m; // <- tu jest match_results jako instanizacja szablonu
    std::regex_search(d, m, example);
    if (m[0].matched) { // czy w og�le znalaz� cokolwiek
        for (int i = 0; i < m.size(); ++i) {
            std::cout << "[" << m[i].first - d.begin() << "]" << m[i].second - d.begin() << std::endl;
        }
    }
    std::cout << std::endl;
};


/*-------------------------*/
/*         ZADANIA         */

//PRZYDATNE LINKI:
//https://www.cplusplus.com/reference/regex/ECMAScript/ <- sk�adnia
//https://www.cplusplus.com/reference/regex/basic_regex/ <- flagi

//aby uruchomi� zadanie nale�y odkomentowa� wywo�ania poni�szych metod w main()

/**
 * Sprawd� czy w podanym zdaniu pada s�owo "MS" - je�li tak, to zamie� je na AEiI
 * u�yj std::regex_search i std::regex_replace
 */
void zad_0() {
    const std::string zdanie = "Wydzia� MS jest najlepszym wydzia�em spo�r�d polskich uczelni.";

    std::regex r("MS");

    std::cout << std::regex_replace(zdanie, r, "AEiI") << std::endl <<std::endl;

}


int main() {

    //ZADANIA S� PONI�EJ

    /*
    test_regex_match ();
    std::cout << std::endl;
    test_regex_search ();
    std::cout << std::endl;
    test_regex_replace ();
    std::cout << std::endl;
    test_regex_iterator ();
    std::cout << std::endl;
    test_match_results ();
    std::cout << std::endl;
    */

    std::cout << "********ZADANIE 0********" << std::endl;

    zad_0 ();

    std::cout << "********ZADANIE 1********" << std::endl;

    zad_1 ();

    std::cout << "********ZADANIE 2********" << std::endl;

    zad_2 ();

    std::cout << "********ZADANIE 3********" << std::endl;

    zad_3 ();

    std::cout << "********ZADANIE 4********" << std::endl;

    zad_4 ();
}
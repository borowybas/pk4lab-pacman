#include <iostream>
#include <filesystem>

//wyswietlanie sciezki i dekompozycja elementow
void zad1a() {
	std::cout << std::filesystem::current_path() << std::endl;

	std::cout << std::filesystem::current_path().root_name() << std::endl;
	std::cout << std::filesystem::current_path().root_path() << std::endl;
	std::cout << std::filesystem::current_path().root_directory() << std::endl;
	std::cout << std::filesystem::current_path().relative_path() << std::endl;
	std::cout << std::filesystem::current_path().parent_path() << std::endl;
	std::cout << std::filesystem::current_path().filename() << std::endl;
	std::cout << std::filesystem::current_path().stem() << std::endl;
	std::cout << std::filesystem::current_path().extension() << std::endl;
}
//dekompozycja za pomoca iteratora sciezek
void zad1b() {
	const std::filesystem::path p = "C:\\Users\\Admin\\Documents\\GitHub\\a87312ac-gr41-repo\\lab3";

	std::cout << "Iterators " << p << std::endl;

	for (auto it = p.begin(); it != p.end(); ++it) {
		std::cout << *it << " | ";
	}
	std::cout << '\n' << '\n';
}
//sciezka wskazuje na folder Laboratorium3, wyswietlanie sciezki: bezwzgledna, kanoniczna, wzgledna
void zad2() {
	std::filesystem::path path1 = "C:\\Users\\Admin\\Desktop\\Laboratorium3";

	std::cout << "Zadanie 2b" << '\n' << "Sciezka bezwzgledna: " << std::filesystem::absolute(path1) << '\n';
	std::cout << "Sciezka kanoniczna: " << std::filesystem::canonical(path1) << '\n';
	std::cout << "Sciezka wzgledna: " << std::filesystem::relative(path1) << '\n';
}
//sciezka path2 wskazuje na nieistniejacy element, dla polecen wywolujacych blad - wyswietlanie wyjatku na ekran
void zad2c() {

	std::filesystem::path path2 = "C:\\Users\\Admin\\Desktop\\Laboratorium4";

	std::cout << "Zadanie 2c" << '\n' << "Sciezka bezwzgledna: " << std::filesystem::absolute(path2) << '\n';
	try {
		std::cout << "Sciezka kanoniczna: " << std::filesystem::canonical(path2) << '\n';
	}
	catch (std::filesystem::filesystem_error const& ex) {
		std::cout << "what(): " << ex.what() << '\n';
	}
	std::cout << "Sciezka wzgledna: " << std::filesystem::relative(path2) << '\n';
}
//kopiuje z to_copy do Zadanie_3_1 cala zawartosc
void zad3a() {
	std::filesystem::path from = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\to_copy";
	std::filesystem::path to = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\Zadanie_3_1";

	auto const cop_opt = std::filesystem::copy_options::recursive;

	std::filesystem::copy(from, to, cop_opt);
}
//kopiuje z to_copy do Zadanie_3_2 pod warunkiem, ¿e kopiowany plik jest nowszy od istniej¹cego
void zad3b() {
	std::filesystem::path from = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\to_copy";
	std::filesystem::path to = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\Zadanie_3_2";

	auto const cop_opt = std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing;

	if (std::filesystem::last_write_time(from) < std::filesystem::last_write_time(to)) {
		std::filesystem::copy(from, to, cop_opt);
	}
}
//kopiuje z to_copy do Zadanie_3_2, tylko foldery i podfoldery (bez plików) 
void zad3c() {
	std::filesystem::path from = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\to_copy";
	std::filesystem::path to = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\Zadanie_3_3";

	auto const cop_opt = std::filesystem::copy_options::recursive | std::filesystem::copy_options::directories_only;

	std::filesystem::copy(from, to, cop_opt);
}

std::string printPermissions(std::filesystem::perms p)
{
	std::string permissions =
		((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? "r" : "-");
	permissions += ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? "w" : "-");
	permissions += ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? "x" : "-");
	permissions += ((p & std::filesystem::perms::group_read) != std::filesystem::perms::none ? "r" : "-");
	permissions += ((p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? "w" : "-");
	permissions += ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? "x" : "-");
	permissions += ((p & std::filesystem::perms::others_read) != std::filesystem::perms::none ? "r" : "-");
	permissions += ((p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? "w" : "-");
	permissions += ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? "x" : "-");
	return permissions;
}
/*Napisz (u¿ywaj¹c odpowiednich iteratorów) funkcjê, która z folderu Zadanie 4
wyœwietla:ˆ nazwy plików,ˆ rozszerzenia,ˆ uprawnienia,ˆ rozmiar (w KB), informacjê o tym, czy dany element jest folderem*/
void zad4a() {
	std::filesystem::path path4 = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\Zadanie_4";
	for (auto& p : std::filesystem::recursive_directory_iterator(path4)) {
		std::cout << "Nazwa pliku: " << p.path().stem() << std::endl;
		std::cout << "Rozszerzenie: " << p.path().extension()<< std::endl;
		std::cout << "Uprawnienia: " << printPermissions(std::filesystem::status(p.path()).permissions()) << std::endl;
		std::cout << "Rozmiar: " << p.file_size()/1024 << std::endl;
		std::cout << "Czy folder: " << p.is_directory() << std::endl;
		std::cout << std::endl;
	}
}
//wyswietla iloœæ wolnego miejsca na dysku (w GB), na którym znajduje siê folder
void zad4b() {
	std::filesystem::path path4 = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\Zadanie_4";
	std::error_code ec;
	const std::filesystem::space_info si = std::filesystem::space(path4, ec);
	std::cout << "Miejsce na dysku: " << si.available<<std::endl;
}
//napisz drug¹ funkcjê, która robi to samo co pierwsza, tylko zamiast wyœwietlaæ
//informacjê o ”byciu folderem”, wyœwietla jego zawartoœæ
void zad4c() {
	std::filesystem::path path4 = "C:\\Users\\Admin\\Desktop\\Laboratorium3\\Zadanie_4";
	for (auto& p : std::filesystem::recursive_directory_iterator(path4)) {
		std::cout << "Nazwa pliku: " << p.path().stem() << std::endl;
		std::cout << "Rozszerzenie: " << p.path().extension() << std::endl;
		std::cout << "Uprawnienia: " << printPermissions(std::filesystem::status(p.path()).permissions()) << std::endl;
		std::cout << "Rozmiar: " << p.file_size() / 1024 << std::endl;
		
		if (p.is_directory() == 1) {
			std::cout << "Zawartosc: " << std::endl;
			for (auto& p1 : std::filesystem::directory_iterator(p.path())) {
				std::cout << p1.path().filename() << std::endl;
			}
		} 
		else {
			std::cout << "Zawartosc: -" << std::endl;
		}
		std::cout << std::endl;
	}
}

int main() {

	//------------Zad 1a-----------
	//zad1a();
	//------------Zad 1b-----------
	//zad1b();
	//------------Zad 2a-------------------------------
	//zad2a();
	//------------Zad 2b-----------
	//zad2b();
	//sciezka kanoniczna i bezwzgledna sa takie same
	//------------Zad 2c-----------
	//zad2c();
	//zad2c();
	
	//------------Zad 3a-------------------------------
	
	zad3a();

	//------------Zad 3b-----------
	
	//zad3b();

	//------------Zad 3c-----------
	
	//zad3c();

		//------------Zad 4a----------------------------

	//zad4a();

	//------------Zad 4b-----------

	//zad4b();

	//------------Zad 4c-----------

	//zad4c();
}
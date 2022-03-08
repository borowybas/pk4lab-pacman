export module modul1;

import <vector>;
import <cstdlib>;
import <string>;
import <sstream>;

export std::vector<int> MyFun();
export std::string conv(std::vector<int> vec);

std::vector<int> MyFun() {
	std::vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(std::rand());
	}
	return vec;
}

std::string conv(std::vector<int> vec) {
	
	std::stringstream s;

	if (!vec.empty()) {
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(s, " "));

	}
	std::string res = s.str();
	return res;
}
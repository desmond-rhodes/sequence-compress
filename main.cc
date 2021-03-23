#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<unsigned long long> split(std::string const&, std::string const&);
std::string base36(unsigned long long);

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::vector<std::string> args {argv+1, argv+argc};

	if (args.size() != 3 || (args[0] != "encode" && args[0] != "decode")) {
		std::cerr
			<< "usage:\n"
			<< "\t(encode|decode) {size} {data}\n"
			<< "e.g.\n"
			<< "\tencode 12,31 1775,6,3\n"
			<< "\tdecode 12,31 e5mx\n";
		return -1;
	}

	std::vector<unsigned long long> size {split(args[1], ",")};

	if (args[0] == "encode") {
		std::vector<unsigned long long> data {split(args[2], ",")};

		if (size.size()+1 != data.size()) {
			std::cerr << "Amount of data and size don't match\n";
			return -1;
		}

		unsigned long long sum {data[0]};
		for (size_t i {0}; i < size.size(); ++i) {
			sum = sum * size[i] + data[i+1];
		}

		std::cout << base36(sum) << '\n';
	}

	if (args[0] == "decode") {
		std::reverse(size.begin(), size.end());
		std::vector<unsigned long long> data;

		unsigned long long sum {std::stoull(args[2], nullptr, 36)};

		for (size_t i {0}; i < size.size(); ++i) {
			data.push_back(sum % size[i]);
			sum /= size[i];
		}
		data.push_back(sum);

		std::reverse(data.begin(), data.end());
		for (size_t i {0}; i < data.size(); ++i)
			std::cout << data[i] << ' ';
		std::cout << '\n';
	}

	return 0;
}

std::vector<unsigned long long> split(std::string const& str, std::string const& del) {
	std::vector<unsigned long long> vec;
	for (size_t beg {0}; ;) {
		size_t end {str.find(del, beg)};
		vec.push_back(std::stoull(str.substr(beg, end-beg), nullptr, 0));
		if (end == std::string::npos)
			break;
		beg = end + del.size();
	}
	return vec;
}

char const* symbol {"0123456789abcdefghijklmnopqrstuvwxyz"};

std::string base36(unsigned long long num) {
	std::string str;
	while (num) {
		str += symbol[num % 36];
		num /= 36;
	}
	std::reverse(str.begin(), str.end());
	return str;
}

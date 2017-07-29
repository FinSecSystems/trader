#pragma once

namespace trader {

	template <typename type>
	inline bool equal(typename type left, typename type right)
	{
		return (left == right);
	}

	template<>
	inline bool equal<float>(float a, float b) {
		return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
	}

	template<>
	inline bool equal<double>(double a, double b) {
		return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
	}

	template<>
	inline bool equal<std::string>(std::string a, std::string b) {
		return (a.compare(b) == 0);
	}

	inline bool not_digit(char ch) {
		return ( '0' <= ch && ch <= '9' ) || ch == '.';
	}

	inline std::string remove_non_digits(const std::string& input) {
		std::string result;
		std::copy_if(input.begin(), input.end(),
			std::back_inserter(result),
			not_digit);
		return result;
	}

}

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

    class FormattedTime
    {
    public:
        FormattedTime(const char* _format)
            : format(_format)
            , time(std::numeric_limits<time_t>::max())
        {}

        void operator = (const std::string& str) {
            std::tm t = {};
            std::istringstream ss(str);
            ss >> std::get_time(&t, format.c_str());
            if (!ss.fail()) {
                time = mktime(&t);
            }
        }

        void operator = (const FormattedTime& ft) {
            time = ft.time;
            format = ft.format;
        }

        std::time_t time;
        std::string format;
    };

}

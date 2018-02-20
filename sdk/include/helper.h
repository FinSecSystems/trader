#pragma once

namespace trader {

	template <typename type>
	inline bool equal(type left, type right)
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
            : time(std::numeric_limits<time_t>::max())
            , format(_format)
        {}

        void operator = (const std::string& str) {
#if defined(POCO_OS_FAMILY_WINDOWS)
            std::tm t = {};
            std::istringstream ss(str);
            ss >> std::get_time(&t, format.c_str());
            if (!ss.fail()) {
                time = mktime(&t);
            }
#else
            struct tm tm;
            memset(&tm, 0, sizeof(struct tm));
            strptime(str.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
            time = mktime(&tm);
#endif
        }

        void operator = (const FormattedTime& ft) {
            time = ft.time;
            format = ft.format;
        }

        std::time_t time;
        std::string format;
    };


}

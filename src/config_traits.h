#include <type_traits>

template<typename T>
struct is_config_type: std::false_type{};

template<> struct is_config_type <bool>:               std::true_type{};

template<> struct is_config_type <int>:                std::true_type{};
template<> struct is_config_type <long>:               std::true_type{};
template<> struct is_config_type <long long>:          std::true_type{};

template<> struct is_config_type <unsigned int>:       std::true_type{};
template<> struct is_config_type <unsigned long>:      std::true_type{};
template<> struct is_config_type <unsigned long long>: std::true_type{};

template<> struct is_config_type <float>:              std::true_type{};
template<> struct is_config_type <double>:             std::true_type{};
template<> struct is_config_type <long double>:        std::true_type{};

template<> struct is_config_type <std::string>:        std::true_type{};


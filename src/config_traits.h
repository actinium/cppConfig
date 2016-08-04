#include <type_traits>

template<typename T>
struct is_config_type:std::integral_constant<bool,false>{};

template<> struct is_config_type <bool>:               std::integral_constant<bool,true>{};

template<> struct is_config_type <int>:                std::integral_constant<bool,true>{};
template<> struct is_config_type <long>:               std::integral_constant<bool,true>{};
template<> struct is_config_type <long long>:          std::integral_constant<bool,true>{};

template<> struct is_config_type <unsigned int>:       std::integral_constant<bool,true>{};
template<> struct is_config_type <unsigned long>:      std::integral_constant<bool,true>{};
template<> struct is_config_type <unsigned long long>: std::integral_constant<bool,true>{};

template<> struct is_config_type <float>:              std::integral_constant<bool,true>{};
template<> struct is_config_type <double>:             std::integral_constant<bool,true>{};
template<> struct is_config_type <long double>:        std::integral_constant<bool,true>{};

template<> struct is_config_type <std::string>:        std::integral_constant<bool,true>{};


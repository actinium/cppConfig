//===----------------------------------------------------------------------===//
//
//                              CppConfig
//
// A small utility for reading values from a config file.
//
//===----------------------------------------------------------------------===//
//
//===----------------------------------------------------------------------===//

#ifndef ACTINIUM_CONFIG_H
#define ACTINIUM_CONFIG_H

#include <string>
#include <map>
#include <type_traits>
#include <fstream>
#include <iostream>

namespace config{

class config final{
  friend config load(std::string);

  explicit config(std::string filename);

  static std::string    strip(const std::string & str);
  static std::string unescape(const std::string & str);
  static bool     stob(const std::string & str);
  static unsigned stou(const std::string & str); 

  class config_node final{
    friend config;

    explicit config_node(const std::string& value): value_(value) {}
    config_node(const config_node& cn): value_(cn.value_) {}

   public:
    operator std::string()        const;
    operator bool()               const;//      stob
    operator int()                const;// std::stoi
    operator long()               const;// std::stol
    operator long long()          const;// std::stoll
    operator unsigned()           const;//      stou
    operator unsigned long()      const;// std::stoul
    operator unsigned long long() const;// std::stoull
    operator float()              const;// std::stof
    operator double()             const;// std::stod
    operator long double()        const;// std::stold

   private:
    std::string value_;

  };

 public:
  config_node operator[](const std::string& variable_name) const;

  config_node get(const std::string& variable_name,
                  const char* default_value) const;
  config_node get(const std::string& variable_name,
                  const std::string & default_value) const;
  template<typename T>
  config_node get(const std::string& variable_name,
                  const T& default_value) const;

 private:
  std::map<std::string,std::string> nodes_;

};

//===----------------------------------------------------------------------===//
// Public functions
//===----------------------------------------------------------------------===//

// Loads the config values from the file called 'filename'.
config load(std::string filename) {
  return config(filename);
}

// Get the value of variable_name.
config::config_node config::operator[](const std::string& variable_name) const {
  return config_node("");
}

// Get the value of variable_name.
//
// If varible_name isn't present return default_value.
config::config_node config::get(const std::string& variable_name,
                                const std::string& default_value) const{
  return config_node("");
}
config::config_node config::get(const std::string& variable_name,
                                const char* default_value) const{
  return get(variable_name,std::string(default_value));
}
template<typename T>
config::config_node config::get(const std::string& variable_name,
                                const T& default_value) const{
  return get(variable_name,std::to_string(default_value));
}

// Convert config_node to a usefull type.
//
// Casts exception if convertion isn't possible( eg. from a non-numeric string
// to a numeric type).
config::config_node::operator std::string() const { return value_; }
config::config_node::operator int() const { return 0; }

//===----------------------------------------------------------------------===//
// Private functions
//===----------------------------------------------------------------------===//

// config ctor
config::config(std::string filename) : nodes_() {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)){
    if(line != ""){
      std::cout << line << std::endl;
    }
  }
}

// Strip string of whitespaces.
std::string config::strip(const std::string & str){
  return "";
}

// Unescape string
std::string config::unescape(const std::string & str){
  return "";
}

// String to unsigned
unsigned config::stou(const std::string & str){
  return 0;
}

// String to bool
bool config::stob(const std::string & str){
  return false;
}

}// end namespace config

#endif

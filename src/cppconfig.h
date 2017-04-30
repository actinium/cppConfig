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

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace config{

class config final{
  friend config load(std::string);

  explicit config(std::string filename);

  static std::vector<std::string> tokenize( const std::string & str);
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
  std::string s = nodes_.at(variable_name);
  return config_node( s );
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
    std::vector<std::string> tokens = tokenize(line);
    if( tokens.size() != 0 ){
      // Comment
      if( tokens[0][0] == '#' ){
        continue;
      }
      // 3 Tokens
      if( tokens.size() == 3 && tokens[2][0] != '\"' ){
        if( tokens[1] != "=" ){
          // ERROR!
        }
        nodes_[tokens[0]] = tokens[2];
        continue;
      }
      // String
      if( tokens.size() >= 3){
        if( tokens[1] == "=" && tokens[2][0] == '\"' ){
          std::string str = line.substr( line.find('=') + 1, line.length() );
          std::size_t start = str.find('\"') + 1;
          std::size_t end = str.find_last_of('\"');
          str = str.substr( start, end-start );
          str = unescape(str);
          nodes_[tokens[0]] = str;
          continue;
        }
      }
    }
  }
}

std::vector<std::string> config::tokenize( const std::string & str ){
  std::vector<std::string> tokens;
  std::string delim = " \t";
  std::size_t prev = 0;
  std::size_t pos = str.find_first_of( delim, prev );
  while( pos != std::string::npos ){
    if(pos > prev){
      tokens.push_back( str.substr(prev, pos-prev) );
    }
    prev = pos+1;
    pos = str.find_first_of( delim, prev );
  }
  if( prev < str.length() ){
    tokens.push_back( str.substr(prev, std::string::npos) );
  }
  return tokens;
}

std::string config::unescape(const std::string & str){
  std::string ret;
  std::string::const_iterator it = str.begin();
  while( it != str.end() ){
    char c = *it++;
    if( c == '\\' && it != str.end() ){
      switch(*it++){
        case '\\':
          ret += '\\';
          break;
        case '\'':
          ret += '\'';
          break;
        case '\"':
          ret += '\"';
          break;
        case 't':
          ret += '\t';
          break;
        case 'n':
          ret += '\n';
          break;
        default:
          continue;
      }
    }else{
      ret += c;
    }
  }
  return ret;
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

#cppconfig

##Usage

```
  auto conf = config::load("filename");
  
  std::string api_key = conf["api_key"];
  unsigned timeout = conf["timeout"];
```

##File format

One variable per line. The '#' is used for comments.

```
  # comment
  variable_name = value
  variable_name = "strings need quotation marks"
```

Variable names may contain `A-Z`, `a-z`, `0-9` and `_`.

__Valid types are:__

   - strings ( std::string )
   - integers ( int, long, long long )
   - unsigned integers ( unsigned, unsigned long, unsigned long long )
   - floating point numbers ( float, double, long double )


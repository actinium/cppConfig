#cppconfig

##Usage

```
  auto conf = config::load("filename");
  
  std::string api_key = conf["api_key"];
  unsigned timeout = conf["timeout"];
```

##File format

One variable per line. The `#` is used for comments.

```
  # comment
  variable_name = value
  variable_name = "strings need quotation marks"
```

Variable names may contain characters: `A-Z`, `a-z`, `0-9` and `_`.

###Valid types are:

__strings__ (std::string)

__integers__ (int, long, long long)

__unsigned integers__ (unsigned, unsigned long, unsigned long long)

__floating point numbers__ (float, double, long double)


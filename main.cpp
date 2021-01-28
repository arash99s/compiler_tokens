/*
c++ tokens:
  https://docs.microsoft.com/en-us/cpp/cpp/character-sets?view=msvc-160#:~:text=A%20token%20is%20the%20smallest,Numeric%2C%20Boolean%20and%20Pointer%20Literals
*/
#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

string read_file(string file_name);
static inline void ltrim(string &s);
static inline void rtrim(string &s);
static inline void trim(string &s);

int main ()
{
    smatch match_results;

    regex keywords_rejex ("((void)|(int)|(const)|(static)|(continue)|(long)|(struct)|(and)|(or)|\
      (co_await)|(mutable)|(switch)|(return)|(namespace)|(template)|(asm)|(co_yield)|(new)|(this)|(auto)|(decltype)|\
      (thread_local)|(bitand)|(bitor)|(bool)|(break)|(case)|(catch)|(char)|(char8_t)|(char16_t)|(char32_t)|(class)|\
      (comple)|(concept)|(const_cast)|(consteval)|(constexpr)|(default)|(delete)|(do)|(double)|(dynamic_cast)|(else)|(enum)|\
      (explicit)|(export)|(extern)|(false)|(float)|(for)|(friend)|(goto)|(if)|(inline)|(noexpect)|(not)|\
      (not_eq)|(nullptr)|(operator)|(or_eq)|(private)|(protected)|(public)|(requires)|(short)|(signed)|(sizeof)|(throw)|\
      (true)|(try)|(typedef)|(typeid)|(typename)|(union)|(unsigned)|(vitual)|(volatile)|(while)|(xor)|(xor_eq)|\
      (regex)|(smatch)|(string)|(std))[^a-zA-Z0-9_]");

    string operators = "(::)|(:)|(\\[)|(\\])|(\\()|(\\))|(\\+\\+)|(\\-\\-)|(\\+)|(\\-)|(\\~)|(\\!)|(\\&\\&)|(\\*)|\
      (\\/)|(\\%)|(\\<\\<)|(\\>\\>)|(\\<)|(\\>)|(\\<\\=)|(\\>\\=)|(\\<<)|(\\=\\=)|(\\^)|(\\|)|(\\&)|(\\|\\|)|(\\?)|\
      (\\*\\=)|(\\/\\=)|(\\%\\=)|(\\+\\=)|(\\-\\=)|(\\&\\=)|(\\|\\=)|(\\^\\=)|(\\,)|(\\=)";
    regex operators_rejex (operators);

    string punctuators = "(\\;)|(\\!)|(\\%)|(\\^)|(\\&)|(\\()|(\\))|(\\-)|(\\+)|(\\=)|(\\{)|(\\})|(\\|)|(\\~)|\
      (\\[)|(\\])|(\\<)|(\\>)|(\\?)|(\\,)|(\\.)|(\\/)|(\\#)";
    regex punctuators_rejex (punctuators);

    regex string_character_literals_regex ("(\".*\")|(\'.*\')");


    regex numeric_boolean_literals_regex ("(\\d+\\.\\d+)|(\\d+)|true|false");

    regex identifier_regex ("[a-zA-Z_][a-zA-Z0-9_]*");


    string src_text = read_file("src.txt");
    
    while (src_text != "")
    {
      if(regex_search (src_text,match_results,keywords_rejex) && match_results.position()==0){ // keylword
        cout << match_results[1] << " is keyword" << endl;
      }else if(regex_search (src_text,match_results,identifier_regex) && match_results.position()==0){ // identifier
        cout << match_results[0] << " is identifier" << endl;
      }else if(regex_search (src_text,match_results,operators_rejex) && match_results.position()==0){ // operator
        cout << match_results[0] << " is operator" << endl;
      }else if(regex_search (src_text,match_results,punctuators_rejex) && match_results.position()==0){ // punctuator
        cout << match_results[0] << " is punctuator" << endl;
      }else if(regex_search (src_text,match_results,string_character_literals_regex) && match_results.position()==0){ // string_character_literals
        cout << match_results[0] << " is string_character_literals" << endl;
      }else if(regex_search (src_text,match_results,numeric_boolean_literals_regex) && match_results.position()==0){ // numeric_boolean_literals
        cout << match_results[0] << " is numeric_boolean_literals" << endl;
      }
      src_text = match_results.suffix().str();
      //boost::trim(src_text);
      trim(src_text);
    }
    

  return 0;
}



string read_file(string file_name){
  string src_text = "";
  string line;
  ifstream file(file_name);
  while(getline(file , line)){
    src_text += "\n" + line;
  }
  file.close();
  //boost::trim_left(src_text);
  ltrim(src_text);
  return src_text;
}

// trim from start (in place)
static inline void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}

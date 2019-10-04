
#include <iostream>
#include <fstream>

#include <any>
#include "../include/json.h"

int main()
{
    std::ifstream file("../example_files/test.txt");
    std::string prom;
    //std::string prom2 = "{\"key\":\"string\"}";
    //std::string prom ="{""lastname"" : ""Ivanov"",""firstname"" : ""Ivan"",""age"" : 25,""islegal"" : false,""marks"" : [4, 5, 5, 5, 2, 3],""address"" : {""city"" : ""Moscow"",""street"" : ""Vozdvijenka""}}";
    //std::string prom = "{"lastname" : "Ivanov","firstname" : "Ivan","age" : 25,"islegal" : false,"marks" : [4,5,5,5,2,3],"address" : {"city" : "Moscow","street" : "Vozdvijenka"}}";


    std::any test1='[';

    if (std::any_cast<char>(test1)=='[')
        std::cout<<test1.type().name()<<std::endl;//marker
    //getline(file, prom);
    file.close();
    prom= R"({"lastname" : "Ivanov","firstname" : "Ivan","age" : 25,"islegal" : false,"marks" : [4,5,5,5,2,3],"address" : {"city" : "Moscow","street" : "Vozdvijenka"}})";
    std::any test = 123;

    std::cout << test.type().name() << std::endl;

    std::string prom2 = "{\"key\": 134}";
    std::cout<<"here: prom "<<prom<<std::endl;//marker
    Json object(prom);

    std::cout << std::endl << "Tests:" << std::endl;
    std::any_cast<std::string>(object["lastname"]);
    std::cout << std::any_cast<bool>(object["islegal"]) << std::endl;
    std::cout << std::any_cast<int>(object["age"]) << std::endl;

    auto marks = std::any_cast<Json>(object["marks"]);
    std::cout << std::any_cast<int>(marks[0]) << std::endl;
    std::cout << std::any_cast<int>(marks[1]) << std::endl;

    auto address = std::any_cast<Json>(object["address"]);
    std::cout << std::any_cast<std::string>(address["city"]) << std::endl;
    std::cout << std::any_cast<std::string>(address["street"]) << std::endl;

    return 0;
}
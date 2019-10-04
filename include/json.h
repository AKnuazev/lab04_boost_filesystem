#pragma once

#include <string>
#include <any>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Json {
    /*bool object_flag;

    std::unordered_multimap <std::string, std::any> object_data; // key&object

    std::vector<std::any> mas_data;*/

    std::any data;


public:

    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string &s);
    
    // Конструктор из строки, содержащей вектор токенов
    Json(const std::vector<std::any>& tokens);



    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.

    bool is_array() const;

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.

    bool is_object() const;



    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.

    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.

    // Если экземпляр является JSON-массивом, генерируется исключение.

    std::any operator[](const std::string &key);



    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.

    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.

    // Если экземпляр является JSON-объектом, генерируется исключение.

    std::any operator[](int index);



    // Метод возвращает объект класса Json из строки, содержащей Json-данные.

    static Json parse(const std::string &s);



    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.

    static Json parseFile(const std::string &path_to_file);

};

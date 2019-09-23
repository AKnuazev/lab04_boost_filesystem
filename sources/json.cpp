#include "json.h"
#include <fstream>
#include <exception>
#include <cmath>

#define TypeError "Error: type mismatch"
#define SyntaxError "Error: wrond syntax"


class Error : std::exception {
    std::string info;
public:
    Error() {
        info = "";
    }

    Error(std::string message) {
        info = message;
    }

    std::string GetInfo() {
        return info;
    }

};

int CharToInt(char c)
{
    //return (int)c - 87;
    switch (c)
    {
        case '0': {return 0; }
        case '1': {return 1; }
        case '2': {return 2; }
        case '3': {return 3; }
        case '4': {return 4; }
        case '5': {return 5; }
        case '6': {return 6; }
        case '7': {return 7; }
        case '8': {return 8; }
        case '9': {return 9; }
        default: {throw Error(); }
    }
}

std::string GetKey(int& i, const std::string& s)
{
    std::string key = "";
    try
    {
        for (; s[i] != '"'; i++);  // Доходим до начала строки
        // Считываем ключ
        i++;
        for (; s[i] != '"'; i++)
            key += s[i];
        i++;

        for (; s[i] == ' '; i++);  // Доходим до двоеточия
        if (s[i] == ':')           // и проверяем его наличие
        {
            i++;// Проходим его
            //throw Error();
        }

    }
    catch (const Error&)
    {
        throw Error(SyntaxError);
    }

    //std::cout << "Got key: " << key << std::endl; //marker
    return key;
}

std::any GetObject(int& i, const std::string& s)
{
    std::any object;
    try
    {
        for (; s[i] == ' '; i++);  // Доходим до объекта

        // Определяем его тип
        if (isdigit(s[i])||s[i]=='-')   // Обрабатываем число
        {
            int k = i;
            int f = 0;//fraction_counter

            bool type_flag = 0; //по умолчанию int
            bool negative_flag = 0;

            if (s[i] == '-')
            {
                i++;
                negative_flag = 1;
            }

            for (; isdigit(s[i]); i++);  // Доходим до конца числа
            if (s[i+1]=='.')
            {
                type_flag = 1;//double
                int dot_position = i + 1;

                if (isdigit(s[dot_position + 1]))
                    for (f=1; isdigit(s[dot_position + f]); f++);
                else
                    throw Error(SyntaxError);
            }

            object = 0;
            for (; i - k > 0; k++)
            {
                object = std::any_cast<int>(object) + CharToInt(s[k]) * (int)pow(10, i - k - 1);
            }
            if (type_flag)
            {
                i += 2;
                for ( k = 0; k < f; k++, i++)
                {
                    object = std::any_cast<int>(object) + CharToInt(s[i]) * (int)pow(10, -1-k);
                }
                i+=f;
            }

            if (negative_flag)
            {
                if (type_flag)
                    object=-1*std::any_cast<double>(object);
                else
                    object=-1*std::any_cast<int>(object);
            }
        }
        else if (s[i] == '[')    // Обрабатываем массив
        {
            try
            {
                int flag=0;

                int begin_of_json = i;
                i++;
                for (; flag != 1; i++)
                {
                    if (s[i] == ']')
                        flag++;
                    if (s[i] == '[')
                        flag--;
                }
                Json NewJson(s.substr(begin_of_json, i-begin_of_json));
                object = NewJson;
            }
            catch (const Error&)
            {
                throw Error(SyntaxError);
            }
        }
        else if (s[i] == '{')    // Обрабатываем объект
        {
            int flag = 0;

            int begin_of_json = i;
            i++;
            for (; flag != 1; i++)
            {
                if (s[i] == '}')
                    flag++;
                if (s[i] == '{')
                    flag--;
            }
            Json NewJson(s.substr(begin_of_json, i-begin_of_json));
            object = NewJson;
        }
        else if (s[i] == 'f' || s[i] == 't' || s[i] == 'n') // Обрабатываем литерал
        {
            if (s.substr(i, 5) == "false")
            {
                object = (bool)0;
                i += 5;
            }
            if (s.substr(i, 4) == "true")
            {
                i += 4;
                object = (bool)1;
            }
            if (s.substr(i, 4) == "null")
            {
                i += 4;
                object = NULL;
            }

        }
        else if (s[i] == '"') // Обрабатываем строку
        {
            object = GetKey(i, s);
        }
        else
        {
            throw Error();
        }

        for (; s[i] == ' '; i++); // Доходим до следующей запятой и проходим ее
        //i++;                    // или до конца объекта/массива

        if (s[i] != ',' && s[i] != ']' && s[i] != '}')
        {
            throw Error();
        }

        if (s[i] == ',') // Проходим запятую
            i++;
    }
    catch (const Error&)
    {
        throw Error(SyntaxError);
    }


    return object;
}

Json::Json(const std::string& s)
{
    if (s[0] == '{')
    {
        std::string key;
        std::unordered_multimap <std::string, std::any> object_data;
        try
        {
            for (int i = 1; s[i] != '}';)
            {
                key = GetKey(i, s);
                object_data.insert({ key, GetObject(i, s) });

                //std::cout << typeid(object_data.find(key)->second).name() << std::endl;//marker
                //CheckType(object_data.find(key)->second);//marker

            }
        }
        catch (const Error&)
        {
            throw Error(SyntaxError);
        }
        data = object_data;
    }
    else if (s[0] == '[')
    {
        std::vector<std::any> mas_data;
        try
        {
            for (int i = 1; s[i] != ']';)
            {
                mas_data.push_back(GetObject(i, s));
            }
        }
        catch (const Error&)
        {
            throw Error(SyntaxError);
        }

        data = mas_data;
    }
    else
    {
        throw Error(SyntaxError);
    }
}

// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
bool Json::is_array() const
{
    try
    {
        auto object_data = std::any_cast<std::vector<std::any>>(data);
    }
    catch (const std::bad_any_cast&)
    {
        return 0;
    }
    return 1;
}
// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
bool Json::is_object() const
{


    try
    {
        auto mas_data = std::any_cast<std::unordered_multimap<std::string, std::any>>(data);
    }
    catch (const std::bad_any_cast&)
    {
        return 0;
    }
    return 1;
}

// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
// Если экземпляр является JSON-массивом, генерируется исключение.
std::any Json::operator[](const std::string& key)
{
    if (this->is_object())
    {
        auto object_data = std::any_cast<std::unordered_multimap<std::string, std::any>>(data);
        std::any prom = object_data.find(key)->second;

        return prom;
    }
    else
    {
        throw Error(TypeError);
    }
}

// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
// Если экземпляр является JSON-объектом, генерируется исключение.
std::any Json::operator[](int index)
{
    if (this->is_array())
    {
        auto mas_data = std::any_cast<std::vector<std::any>>(data);
        return mas_data[index];
    }
    else
    {
        throw Error(TypeError);
    }
}

// Метод возвращает объект класса Json из строки, содержащей Json-данные.
Json Json::parse(const std::string& s)
{
    return Json(s);
}

// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
Json Json::parseFile(const std::string& path_to_file)
{
    std::string prom, s="";
    std::ifstream file(path_to_file);

    if (file.is_open())
        while (getline(file, prom))
            s += prom;
    else
    {
        throw Error("opening file failed");
    }

    return Json(s);
}
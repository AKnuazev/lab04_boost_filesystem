#include "../include/json.h"
#include <iostream> //marker
#include <fstream>
#include <exception>

const std::string TypeError = "Error: type mismatch";
const std::string SyntaxError = "Error: wrond syntax";
const std::string CharName = "c";
const std::string NullName = "n";

std::ostream& operator<< (std::ostream &stream, const std::any &object)
{
    try
    {
        stream << std::any_cast<int>(object);
        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        stream << std::any_cast<float>(object);
        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        stream << std::any_cast<double>(object);
        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        stream << std::any_cast<bool>(object);
        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        std::any_cast<std::vector<std::any>>(object);
        stream << "vector";

        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        stream << std::any_cast<std::string>(object);
        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        stream << std::any_cast<char>(object);
        return stream;
    }
    catch (const std::exception&) {}
    try
    {
        std::any_cast<Json>(object);
        stream << "Json";

        return stream;
    }
    catch (const std::exception&) {}

    return stream;
}

// Вспомогательные функции
bool IntNotDouble(const std::string text_number)
{
    auto iter = text_number.begin();

    if (isdigit(*iter))
        while (iter != text_number.begin() && isdigit(*iter))
            iter++;
    else
        throw std::exception();

    if (*iter == '.')
        return 0; // Int
    else
        return 1; // Double
}
std::string GetTextNumber(std::string& str)
{
    std::string text_number = "";
    auto iter = str.begin();

    if (*iter == '-')
    {
        text_number += "-";
        iter++;
    }

    if (isdigit(*iter))
        while (iter != str.end() && isdigit(*iter))
        {
            text_number += *iter;
            iter++;
        }
    else
        throw std::exception();

    if (*iter == '.')
    {
        text_number += '.';
        iter++;
        if (isdigit(*iter))
            while (iter != str.end() && isdigit(*iter))
            {
                text_number += *iter;
                iter++;
            }
        else
            throw std::exception();
    }
    return text_number;
}

// Функции для обработки токенов различных типов
std::string GetString(std::string& str)
{
    std::string res_str = "";
    if (str[0] == '"')
    {
        auto iter = str.begin() + 1;

        while (iter != str.end() && *iter != '"')
        {
            res_str += *iter;
            iter++;
        }

        if (iter == str.end())
            throw std::exception();

        str = str.substr(res_str.size() + 2, str.size() - res_str.size() - 2);
        return res_str;
    }
    else
        throw std::exception();
}
int GetInt(std::string& str)
{
    std::string text_number = GetTextNumber(str);
    if (IntNotDouble(text_number))
    {
        str = str.substr(text_number.size(), str.size() - text_number.size());
        return std::stoi(text_number);
    }
    else
        throw std::exception();
}
double GetDouble(std::string& str)
{
    std::string text_number = GetTextNumber(str);
    if (!IntNotDouble(text_number))
    {
        str = str.substr(text_number.size(), str.size() - text_number.size());
        return std::stof(GetTextNumber(str));
    }
    else
        throw std::exception();
}
bool GetBool(std::string& str)
{
    if (str.substr(0, 4) == "true")
    {
        str = str.substr(4, str.size() - 4);
        return 1;
    }

    else if (str.substr(0, 5) == "false")
    {
        str = str.substr(5, str.size() - 5);
        return 0;
    }
    else
        throw std::exception();
}
auto GetNull(std::string& str)
{
    if (str.substr(0, 7) == NullName)
    {
        str = str.substr(4, str.size() - 4);
        return nullptr;
    }
    else
        throw std::exception();

}
char GetSymbol(std::string& str)
{
    if (str[0] == '{' || str[0] == '}' || str[0] == ':' || str[0] == ',' || str[0] == '[' || str[0] == ']')
    {
        char res = str[0];
        str = str.substr(1, str.size() - 1);

        return res;
    }
    else
        throw std::exception();
}

std::any GetObject(std::vector<std::any>& tokens)
{
    std::string type_name = tokens[0].type().name();
    int brack_counter = 0;


    if (type_name == CharName)
    {
        if (std::any_cast<char>(tokens[0]) == '{')
        {
            brack_counter = 1;
            auto iter = tokens.begin() + 1;

            while (iter != tokens.end() && brack_counter > 0)
            {
                std::string prom = iter->type().name();

                if (prom == CharName) {
                    if (std::any_cast<char>(*iter) == '}')
                        brack_counter--;
                    else if (std::any_cast<char>(*iter) == '{')
                        brack_counter++;
                }
                iter++;
            }

            if (iter != tokens.end())
            {
                std::vector<std::any> including_tokens;
                including_tokens.resize(iter - tokens.begin());

                std::copy(tokens.begin(), iter, including_tokens.begin());
                tokens.erase(tokens.begin(), iter);
                return Json(including_tokens);
            }
            else
                throw std::exception();
        }
        else if (std::any_cast<char>(tokens[0]) == '[')
        {
            brack_counter = 1;
            auto iter = tokens.begin() + 1;

            while(iter != tokens.end() && brack_counter > 0)
            {
                std::string prom = iter->type().name();

                if (prom == CharName) {
                    if (std::any_cast<char>(*iter) == ']')
                        brack_counter--;
                    else if (std::any_cast<char>(*iter) == '[')
                        brack_counter++;
                }
                iter++;
            }

            if (iter != tokens.end())
            {
                std::vector<std::any> including_tokens;
                including_tokens.resize(iter - tokens.begin());

                std::copy(tokens.begin(), iter, including_tokens.begin());
                tokens.erase(tokens.begin(), iter);
                return Json(including_tokens);
            }
            else
                throw std::exception();
        }
    }
    else
    {
        std::any result = tokens[0];
        tokens.erase(tokens.begin());
        std::cout << "Got element: " << result << std::endl;
        return result;
    }
    return nullptr;
}
void ParceTokens(std::vector<std::any> tokens, std::any& data)
{
    if (std::any_cast<char>(tokens[0]) == '{')
    {
              std::string key;
        std::unordered_multimap <std::string, std::any> object_data;
        try
        {
            tokens.erase(tokens.begin());
            while (tokens.size() > 0)
            {
                key = std::any_cast<std::string>(tokens[0]);
                std::cout << "Got key:     " << key << std::endl; //marker
                tokens.erase(tokens.begin());
                std::cout<<"here 1"<<std::endl;

                if (std::any_cast<char>(tokens[0]) == ':')
                    tokens.erase(tokens.begin());
                else
                    throw std::exception();
                std::cout<<"here 2"<<std::endl;

                object_data.insert({ key, GetObject(tokens) });
                std::cout<<"here 3"<<std::endl;

                if (std::any_cast<char>(tokens[0]) == ',')
                    tokens.erase(tokens.begin());
                else if (std::any_cast<char>(tokens[0]) == '}')
                {
                    tokens.erase(tokens.begin());
                    continue;
                }
                else
                    throw std::exception();
                std::cout<<"here 4"<<std::endl;
                std::cout << "_________________________" << std::endl;
            }
        }
        catch (const std::exception&)
        {
            throw std::exception();
        }
        data = object_data;
    }
    else if (std::any_cast<char>(tokens[0]) == '[')
    {
        std::vector<std::any> mas_data;
        try
        {
            tokens.erase(tokens.begin());
            while (tokens.size() > 1)
            {
                mas_data.push_back(GetObject(tokens));

                if (std::any_cast<char>(tokens[0]) == ',')
                    tokens.erase(tokens.begin());
                else if (std::any_cast<char>(tokens[0]) == ']')
                {
                    tokens.erase(tokens.begin());
                    continue;
                }
                else
                    throw std::exception();
            }
        }
        catch (const std::exception&)
        {
            throw std::exception();
        }

        data = mas_data;
    }
    else
    {
        throw std::exception();
    }
}

// Функция, преобразующая строку в вектор токенов
std::vector<std::any> TakeTokens(std::string str)
{
    std::vector<std::any> tokens;

    while (str.size() > 0) {
        try {
            tokens.push_back(GetString(str));
            continue;
        }
        catch (const std::exception &) {}
        try {
            tokens.push_back(GetInt(str));
            continue;
        }
        catch (const std::exception &) {}
        try {
            tokens.push_back(GetDouble(str));
            continue;
        }
        catch (const std::exception &) {}
        try {
            tokens.push_back(GetBool(str));
            continue;
        }
        catch (const std::exception &) {}
        try {
            tokens.push_back(GetNull(str));
            continue;
        }
        catch (const std::exception &) {}
        try {
            tokens.push_back(GetSymbol(str));
            continue;
        }
        catch (const std::exception &) {}
        try {
            if (str[0] == ' ' || str[0] == '\n') {
                str = str.substr(1, str.size() - 1);
                continue;
            }
        }
        catch (const std::exception &) {}
        throw std::exception();
    }

    std::cout << "Tokens: ";
    for (auto it = tokens.begin(); it != tokens.end(); it++)
        std::cout << "'" << *it << "', ";

    std::cout << std::endl;

    return tokens;
}

// Конструктор из строки, содержащей Json-данные.
Json::Json(const std::string& s)
{
    ParceTokens(TakeTokens(s), data);
}


// Конструктор из набора токенов, содержащего Json-данные.
Json::Json(const std::vector<std::any>& tokens)
{
    ParceTokens(tokens, data);
}

// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
bool Json::is_array() const
{
    try
    {
        std::vector<std::any> object_data = std::any_cast<std::vector<std::any>>(data);
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
        std::unordered_multimap <std::string, std::any>mas_data = std::any_cast<std::unordered_multimap<std::string, std::any>>(data);
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
        throw std::exception();
    }
}

// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
// Если экземпляр является JSON-объектом, генерируется исключение.
std::any Json::operator[](int index)
{
    if (this->is_array())
    {
        std::vector<std::any> mas_data = std::any_cast<std::vector<std::any>>(data);
        return mas_data[index];
    }
    else
    {
        throw std::exception();
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
    std::string prom, s = "";
    std::ifstream file(path_to_file);

    if (file.is_open())
        while (getline(file, prom))
            s += prom;
    else
    {
        //throw exception
    }

    return Json(s);
}
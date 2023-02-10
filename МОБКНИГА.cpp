#include <iostream>
#include <windows.h> 
using namespace std;

class PhoneBook
{
    char* FullName;
    long int HomePhone;
    long int WorkPhone;
    long int MobilePhone;
public:
    PhoneBook()
    {
        FullName = nullptr;
        HomePhone = 0;
        WorkPhone = 0;
        MobilePhone = 0;
    }

    PhoneBook(char* fullName, long int homePhone, long int workPhone, long int mobilePhone)
    {
        FullName = new char[strlen(fullName) + 1];
        strcpy_s(FullName, strlen(fullName) + 1, fullName);

        FullName = fullName;
        HomePhone = homePhone;
        WorkPhone = workPhone;
        MobilePhone = mobilePhone;
    }

    ~PhoneBook()
    {
        delete[] FullName;
    }

    void Init()
    {
        char buf[40];
        cout << "Ваш фулл наме:";
        cin.getline(buf, 40);

        if (FullName != nullptr)
        {
            delete[] FullName;
        }
        FullName = new char[strlen(buf) + 1];
        strcpy_s(FullName, strlen(buf) + 1, buf);

        cout << "Ваш хоме фоне намбер: ";
        cin >> HomePhone;
        cout << "Ваш ворк фоне намбер: ";
        cin >> WorkPhone;
        cout << "Ваш мобиле фоне намбер: ";
        cin >> MobilePhone;
    }

    void Print()
    {
        cout << "Фулл наме: " << FullName << "\n";
        cout << "Хоме фоне: " << HomePhone << "\n";
        cout << "Ворк фоне: " << WorkPhone << "\n";
        cout << "Мобиле фоне: " << MobilePhone << "\n";
    }

    void Add()
    {
        char* info;
        char buf[40];
        cout << "Фулл имени: ";
        cin.getline(buf, 40);
        info = new char[strlen(buf) + 2];
        strcpy_s(info, strlen(buf) + 2, buf);
        info += '`';

        FILE* f;
        fopen_s(&f, "D:/ДЭЗЭ", "a+");
        string Info = info;
        fputs(Info.c_str(), f);
        fclose(f);
    }

    void Delete()
    {
        FILE* f;
        fopen_s(&f, "D:/ДЭЗЭ", "r");
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        char* str = new char[size + 1];
        rewind(f);
        int symbols = fread(str, sizeof(char), size, f);
        fclose(f);
        str[symbols] = '\0';
        AnsiToOem(str, str);

        char* info;
        char* temp;
        char buf[40];
        cout << "Полное имя для уничтожения: ";
        cin.getline(buf, 40);
        info = new char[strlen(buf) + 1];
        temp = new char[strlen(buf) + 1];
        strcpy_s(info, strlen(buf) + 1, buf);

        for (int i = 0; i < symbols; i++)
        {
            if (info == temp)
            {
                fopen_s(&f, "D:/ДЭЗЭ", "a");
                for (int j = strlen(buf) + 1; j != 0; j--)
                {
                    str[i--] = '`';
                }
                string Str = str;
                fputs(Str.c_str(), f);
                fclose(f);
                cout << "ЧЕЛ БЫЛ УДАЛЁН\n" << temp;
                break;
            }
            else if (i == symbols - 1)
                cout << "ЧЕЛ НЕ БЫЛ НАЙДЕН\n";
            else if (str[i] == '`')
            {
                delete[] temp;
                i++;
            }
            temp += str[i];
        }
    }

    void Search()
    {
        char* info;
        char* temp;
        char buf[40];
        cout << "Слыш, чё надо? \n ";
        cin.getline(buf, 40);
        info = new char[strlen(buf) + 1];
        temp = new char[strlen(buf) + 1];
        strcpy_s(info, strlen(buf) + 1, buf);

        FILE* f;
        fopen_s(&f, "D:/ДЭЗЭ", "r");
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        char* str = new char[size + 1];
        rewind(f);
        int symbols = fread(str, sizeof(char), size, f);
        fclose(f);
        str[symbols] = '\0';
        AnsiToOem(str, str);

        for (int i = 0; i < symbols; i++)
        {
            if (info == temp)
            {
                cout << "ЧЕЛ НАЙДЕН\n" << temp;
                break;
            }
            else if (i == symbols - 1)
                cout << "ЧЕЛ НЕ НАЙДЕН\n";
            else if (str[i])
            {
                delete[] temp;
                i++;
            }
            temp += str[i];
        }
    }

    void Show()
    {
        FILE* f;
        fopen_s(&f, "D:/ДЭЗЭ", "r");
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        char* str = new char[size + 1];
        rewind(f);
        int symbols = fread(str, sizeof(char), size, f);
        fclose(f);
        str[symbols] = '\0';
        AnsiToOem(str, str);

        for (int i = 0; i < symbols; i++)
        {
            if (str[i] == '`') cout << "\n";
            else cout << str[i];
        }
    }
};

int main()
{
    setlocale(0, "");
    PhoneBook obj1;
    obj1.Init();
    obj1.Print();
    obj1.Add();
    obj1.Search();
    obj1.Show();
}

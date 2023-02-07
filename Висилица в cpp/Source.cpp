//Задание
//Создайте консольную версию игры «Виселица».
//Важно :
//■ Соперник пишет слова в файл.
//■ Слово находится в файле.
//■ По завершенииигрына экран выводится статистика игры :
//• количество времени;
//• количество попыток;
//• искомое слово;
//• буквы игрока.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <map>
#include <Windows.h>
#include <time.h>
# include<Mmsystem.h> //для воиспровидения аудиофайлов
#pragma comment(lib, "Winmm.lib")
using namespace std;


class Gallows
{
    ifstream m_input;
    const string m_word;
    map<char, vector<size_t>> m_posMap;//поиска буквы в слове
    string m_searchWord;

    static const vector<string> m_images;
    //определяем перечисление
    enum steps : size_t
    {
        BEGIN,
        ONE, TWO, THREE, FOR, FIVE, SIX, SEVEN,
        END
    }
    m_step = BEGIN;
    //определяем перечисление
    enum result : size_t
    {
        LOSE, WIN
    }
    m_res = LOSE;

    void FillMap()
    {
        size_t pos{};
        for (char ch : m_word)
            m_posMap[ch].emplace_back(pos++);
    }

    char getChar()
    {
        cout << "Введите одну букву: ";
        char ch{}; cin >> ch;

        return m_posMap.find(ch) != m_posMap.cend() ? ch : '\0';
    }
    //оператор ++
    friend steps& operator++(steps&);
public:
    //коструктор с параметрами для выимки из файла слова
    Gallows(const string& filename = "word.txt") :
        m_input(filename),
        m_word(
            istream_iterator<char>(m_input),
            istream_iterator<char>()
        ),
        m_searchWord(m_word.size(), '*')
    {
        FillMap();
    };

    void Play()
    {
        clock_t start, end;

        start = clock();
        while (m_step != END)
        {
            system("cls");
            cout << "Загаданное слово: " << m_searchWord << '\n' << endl;
            cout << m_images[m_step] << endl;

            if (char ch{ getChar() })
            {
                const vector<size_t>& vec{ m_posMap[ch] };
                for (size_t i{}, end{ vec.size() }; i < end; ++i)
                    m_searchWord[vec[i]] = ch;

                m_posMap.erase(ch);
                if (m_searchWord.find('*') == string::npos)
                {
                    m_step = END, m_res = WIN;    
                }
                PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            else
                ++m_step;   
        }
        system("cls");
        cout << "\nЗагаданное слово: " << m_word << endl;
        cout << "Ты " << (m_res == WIN ? "***ПОБЕДИЛ***\n": "***ПРОИГРАЛ***\n")<< endl;
        if (m_res == WIN)
        {
            PlaySound(TEXT("Prize.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "   *   *   *   *   *   *   *   *   *   *   *\n"
                "    *   *   *   *   *  *  *   *   *   *   *\n"
                "     *   *   *   *   * * *   *   *   *   *\n"
                "      *   *   *   *   ***   *   *   *   *\n"
                "       *   *   *   *  ***  *   *   *   *\n"
                "        *   *   *   * *** *   *   *   *\n"
                "         *   *   *   *****   *   *   *\n"
                "          *   *   *  *****  *   *   *\n"
                "           *   *   * ***** *   *   *\n"
                "            *   *   *******   *   *\n"
                "             *   *  *******  *   *\n"
                "              *   * ******* *   *\n"
                "               *   *********   *\n"
                "                *  *********  *\n"
                "                 * ********* *\n"
                "                  ***********\n" << endl;
        }
        else
        {
            PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout <<
                "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "      / | \\           $\n"
                "        |             $\n"
                "       / \\            $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n"
                << endl;
        }
       
        end = clock();
        cout << "***ТВОЕ ВРЕМЯ***:  " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << endl;
        system("pause");
    }
};

Gallows::steps& operator++(Gallows::steps&);

bool win(string str)// ищет "*" в маске
{
    bool a = 1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '*')
        {
            a = 0;
            break;
        }
    }
    return a;
}

void game(string str)
{
    clock_t start, end;
    start = clock();
    int counter_try = 0;// для подсчета количества попыток
    string mask;// маска заполнена "*", которые меняются на буквы в ходе игры
    vector<char> player_letter;// хранит буквы введенные игроком
    system("cls");
    for (int i = 0; i < str.length(); i++)
    {
        mask.push_back('*');
    }
    while (counter_try < 8)
    {
        cout << "ВАШЕ СЛОВО:" << endl;
        cout << mask << endl;
        cout << "ВВЕДИТЕ БУКВУ" << endl;
        cout << "ПОПЫТОК: " << 8 - counter_try << endl;
        char letter;// буква вводимая игроком
        cin >> letter;
        player_letter.push_back(letter);
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == letter)
            { 
                mask[i] = str[i];  
                PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }    
        }
        counter_try++;
        system("cls");
        if (win(mask))
        {
            end = clock();
            cout << "   *   *   *   *   *   *   *   *   *   *   *\n"
                "    *   *   *   *   *  *  *   *   *   *   *\n"
                "     *   *   *   *   * * *   *   *   *   *\n"
                "      *   *   *   *   ***   *   *   *   *\n"
                "       *   *   *   *  ***  *   *   *   *\n"
                "        *   *   *   * *** *   *   *   *\n"
                "         *   *   *   *****   *   *   *\n"
                "          *   *   *  *****  *   *   *\n"
                "           *   *   * ***** *   *   *\n"
                "            *   *   *******   *   *\n"
                "             *   *  *******  *   *\n"
                "              *   * ******* *   *\n"
                "               *   *********   *\n"
                "                *  *********  *\n"
                "                 * ********* *\n"
                "                  ***********\n" << endl;
            cout << "ВЫ ВЫЙГРАЛИ!" << endl;
            PlaySound(TEXT("Prize.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "Слово: " << str << endl;
            cout << "Попыток: " << counter_try << endl;
            cout << "Ваше время: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << " секунд" << endl;
            cout << "Буквы игрока: " << endl;
            for (char a : player_letter)
            {
                cout << a << " ";
            }
            cout << endl;
            system("pause");
            break;
        }
        if (counter_try == 8 && !(win(mask)))
        {
            end = clock();
            cout <<
                "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "      / | \\           $\n"
                "        |             $\n"
                "       / \\            $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n"
                << endl;
            cout << "ВАС ПОВЕСИЛИ!" << endl;
            PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "Слово: " << str << endl;
            cout << "Попыток: " << counter_try << endl;
            cout << "Ваше время: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << " секунд" << endl;
            cout << "Буквы игрока: " << endl;
            for (char a : player_letter)
            {
                cout << a << " ";
            }
            cout << endl;
            system("pause");
        }
    }
}

int main()
{
    system("chcp 1251");
    system("cls");
    srand(time(0));
    string Vvod;
    int Vvod1;
    bool retry = 1;// для выбора продолжать игру или нет
    ofstream m_input1;
    while (retry)
    {
        m_input1.open("word.txt");
        if (!m_input1.is_open())
        {
            cout << "Файл пуст" << endl;
        }
        else
        {
            PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
         
            cout << "**********ИГРА ВИСЕЛИЦА**********" << endl;
            cout << "Необходимо отгадать загаданное слово соперником, допускается 8 неправельных ответов." << endl;
            cout << "Если вы не отгадаете вас ждет" << endl;
            cout <<
                "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "      / | \\           $\n"
                "        |             $\n"
                "       / \\            $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n"
                << endl;
            cout << "*************************УДАЧИ*************************" << endl << endl << endl;
            cout << "Выбереите с кем вы хотитет играть с компьютером или с соперником???" << endl;
            cout << "Если с компьютером то введите <1>, если с игроком то <2>" << endl;
            cin >> Vvod1;
           
            if (Vvod1 == 1)
            {
                cout << fixed;
                cout.precision(1);
                ifstream myFile("gallows1.txt");
                string str;// буферная строка: через нее считываю слова, в нее же записываю случайное слово из вектора, игра идет тоже с ней  
                vector<string> words7;// векторы для хранения слов из 7 букв и т.д.
                vector<string> words6;
                vector<string> words5;
                vector<string> words4;
                vector<string> words3;
                int index = 0;// для случайного выбора слова из вектора

                int number_of_letters;// для ввода длины слова игроком
                cout << "******Вы играете с компьютером******" << endl;
                while (!myFile.eof())
                {
                    str = " ";
                    getline(myFile, str);
                    if (str.length() == 7) words7.push_back(str);
                    else if (str.length() == 6) words6.push_back(str);
                    else if (str.length() == 5) words5.push_back(str);
                    else if (str.length() == 4) words4.push_back(str);
                    else if (str.length() == 3) words3.push_back(str);
                }
                while (retry)
                {
                    cout << "Введите количество букв от 3 до 7 ";
                    cin >> number_of_letters;
                    PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    switch (number_of_letters)
                    {
                    case 7:
                    {
                        index = rand() % words7.size();
                        str = words7[index];
                        game(str);
                        break;
                    }
                    case 6:
                    {
                        index = rand() % words6.size();
                        cout << str << endl;
                        game(str);
                        break;
                    }
                    case 5:
                    {
                        index = rand() % words5.size();
                        str = words5[index];
                        game(str);
                        break;
                    }
                    case 4:
                    {
                        index = rand() % words4.size();
                        str = words4[index];
                        game(str);
                        break;
                    }
                    case 3:
                    {
                        index = rand() % words3.size();
                        str = words3[index];
                        game(str);
                        break;
                    }
                    }
                    system("cls");
                    cout << "Для продолжения нажмите 1, для выхода 0" << endl;
                    cin >> retry;
                }
                myFile.close();
                return 0;
            }
            cout << "*********************вы играете с другим игроком*************************" << endl;
            cout << "*******************************************************" << endl << endl << endl;
            cout << "  Теперь отвернитесь и дайте сопернику загадать слово." << endl;
            cout << "  Когда он его введет и нажмет ввод игра начнется." << endl;
            cout << "  Количество звездочек это количествл букв в слове" << endl;
            system("pause");
            cout << "Введите слова для соперника и нажмите ввод:" << endl;
            cin >> Vvod;
            m_input1 << Vvod << endl;
        }
        m_input1.close();
        PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Gallows game;
        game.Play();
        system("cls");
        cout << "Для продолжения нажмите 1, для выхода 0" << endl;
        cin >> retry;
    }
    return 0;
}

Gallows::steps& operator++(Gallows::steps& st)
{
    size_t tmp = st;
    return st = static_cast<Gallows::steps>(++tmp);
}

const vector<string> Gallows::m_images
{
    {   },
    {
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "      /   \\           $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "      / | \\           $\n"
        "        |             $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "      / | \\           $\n"
        "        |             $\n"
        "       / \\            $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    }
};

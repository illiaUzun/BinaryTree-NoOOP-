//ДОБРО ПОЖАЛОВАТЬ В КОД КУРСОВОЙ РАБОТЫ №1. ВЫПОЛНИЛ: Илья Узун. АИ-174. ВАРИАНТ №21.

#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <string>
using namespace std;
using std::ofstream;

const int col = 179;                            // ширина окна консоли
const int row = 84;                             // высота консоли
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);     // дескриптор устройства стандартного вывода
const int N=256;                                // константный размер строки
///основные переменные

int x = 0, x2 = 0, i = 0, j=0;             // переменные счетчики // x - переход по кейсам
int number = 0;                            // счетчик общего количества
int number3 = 0;                           // счетчик для treeprint
int COUNTER = 0;                           // для функций
///счетчики

int changing_number;
int del_number;
int year_search;
char company_search[30];
int mileage_search;
///переменные для задания входных значений для работы с функциями определенного вывода


int flagg = 0;                              //флаг
int kolvo = 0;                              //для функций вывода определенных значений
char answer = '\0';                         //для yes_no();
///вспомагательные переменные для функций


int menu ();                                                                            //меню
struct CBinaryNode * addnode (struct CBinaryNode *ptr, struct CBinaryNode *tree);       //добавление элемента в дерево
int treeprint (struct CBinaryNode *tree);                                               //вывод всего дерева
struct CBinaryNode *del_elem (struct CBinaryNode *tree, struct CBinaryNode *del_elem ); //удаление элемента из дерева
struct CBinaryNode *root_del (struct CBinaryNode *del_elem);                            //удаление корня из дерева
struct CBinaryNode *correct (struct CBinaryNode *tree);                                //изменение данных об элементе
void sort_price ( struct database *tree );                                              //ф-я сортировки массива по цене
void sort_capacity ( struct database *tree );                                           //ф-я сортировки массива по пробегу
int year_output ( struct CBinaryNode *tree);                                             //вывод авто одного года выпуска
int company_output( struct CBinaryNode *tree);                                           //вывод авто одной фирмы производителя
int mileage_output ( struct CBinaryNode *tree);                                          //вывод авто одной фирмы производителя
void save(struct CBinaryNode *tree);                                                    //сохранение в файл
void deltree_mem (struct CBinaryNode *tree);                                            //освобождение памяти дерева
///основные функции

int one_el_print( struct CBinaryNode *tree, int num);                                   //печать одного эллемента
struct CBinaryNode *input ( struct CBinaryNode *tree );                                 //ввод
struct database *sort_mas ( struct CBinaryNode *tree  );                                  //для сортировки
struct CBinaryNode *TREE_scrl ( struct CBinaryNode *tree, int del_number);              //пробег по дереву
///вспомогательные функции

int yes_no();
void errors (int err_x);
void finish (int succ_x);
void header();
void privet ();
void SetColor (int text, int Fon);
void TITUL ();
///косметические функции

struct CBinaryNode *empty_check ( struct CBinaryNode *tree );
int num_check (int razmer);
float  float_num_check (int razmer2);
char *str_check (int razmer3, int if_integer);
///функции проверки

struct database                      //база данных
    {
            char car_model[20];     //модель
            float mileage;          //пробег в км
            char company[20];       //компания производитель
            int year;               //год
            int engine_capacity;    //объем двигателя
            float price;            //цена
    }no_sort[N];

struct CBinaryNode                  //структура бинарного дерева поиска
    {
        database CAR;               //база данных
        struct CBinaryNode *left;   //левый потомок
        struct CBinaryNode *right;  //правый потомок
        struct CBinaryNode *parent; //родитель
    }NODES;

struct CBinaryNode *root = NULL;     // Объявляем структуру дерева
struct CBinaryNode *ptr = &NODES;    //структура узла
struct CBinaryNode *current = NULL;  //родительская переменная, указывающая на предыдущий узел
struct CBinaryNode *PTR;             //вспомогательная для прохода по дереву

FILE *D_INP;
FILE *T_INP;                         //файлы вывода

int main ( )
    {
        system ("color F0");                                 //меняем цвет
      //setlocale(LC_ALL,"Russian");                         //меняем язык
        SetConsoleTitle("Database of the auto dealership. UZUN (c)");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        system("mode con cols=125 lines=85");                //подстраиваем консоль под свои нужды
        TITUL();
        privet();                                            //вывод текста из файлов
        if (yes_no()==1)                                     //читаем из файла
            {
                FILE *D_INP=fopen("data.txt", "r");
                while (( fscanf ( D_INP, "%s %f %s %d %d %f\n", &ptr -> CAR.car_model, &ptr -> CAR.mileage, &ptr -> CAR.company, &ptr -> CAR.year, &ptr -> CAR.engine_capacity, &ptr -> CAR.price)) != EOF)
                    root = addnode ( ptr, root);
                fclose(D_INP);
                if ( root == NULL )                         //проверка файла на пустоту
                    {
                    errors(5);
                    if (yes_no()==1)
                        goto MENU;
                    else
                        exit (0);
                    }
            }
        else                                                //очистка файла
            {
                ofstream D_INP("data.txt", ios_base::trunc);
                ofstream T_INP("Table.txt", ios_base::trunc);
                D_INP.close();
                T_INP.close();
            }

        MENU:
        finish(1);
        do                                                  //меню
            {
                menu();
                switch ( x )
                    {
                        case 1:///Вывод дерева
                            {
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            header();
                            number3=0;
                            treeprint(root);
                            finish(1);
                            break;
                            }
                        case 2:///Добавление элемента
                            {
                            root = addnode ( input(ptr), root); // размещаем введенный узел на дереве
                            finish(2);
                            break;
                            }
                        case 3:///Удаление елемента
                            {
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            header();
                            number3=0;
                            treeprint(root);
                            LL2:
                            del_number=0;
                            cout<<"Введите номер удаляемого элемента:"<<endl;
                            del_number = num_check(N);
                            if ( del_number > number || del_number <= 0)
                                {
                                errors(2);
                                cout<<"Хотите выбрать другой элемент [Y/N] ?"<<endl;
                                 if (yes_no() == 1)
                                    goto LL1;
                                 else
                                    break;
                                }
                            COUNTER = 1;
                            TREE_scrl(root, del_number);    //ишем адрес удаляемого элемента
                            cout<<"Вы уверены, что хотите удалить данные об этом авто [Y/N] ?"<<endl;
                            header();
                            one_el_print(PTR, del_number);
                            if (yes_no() == 1 )
                                {
                                if ( del_number == 1 )
                                    root = root_del(root);  //удаляем корень
                                else
                                    del_elem (root, PTR);   //удаляем елементы
                                }
                            else
                                {
                                cout<<"Хотите выбрать другой элемент [Y/N] ?"<<endl;
                                if (yes_no() == 1)
                                    goto LL2;
                                else
                                    break;
                                }
                            finish(3);
                            break;
                            }
                       case 4:///Изменение данных
                           {
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            header();
                            number3=0;
                            treeprint(root);
                            LL1:
                            changing_number=0;
                            cout<<"Введите номер удаляемого элемента:"<<endl;
                            changing_number = num_check(N);
                            if ( changing_number > number || changing_number <= 0)
                                {
                                errors(2);
                                cout<<"Хотите выбрать другой элемент [Y/N] ?"<<endl;
                                 if (yes_no() == 1)
                                    goto LL1;
                                 else
                                    break;
                                }
                            COUNTER = 1;
                            TREE_scrl(root, changing_number);    //адрес изменяемого элемента
                            cout<<"Вы уверены, что хотите внести изменения в данные этого авто [Y/N] ?"<<endl;
                            header();
                            one_el_print(PTR, changing_number);
                            if (yes_no() == 1)
                                correct ( PTR );
                            else
                                {
                                 cout<<"Хотите выбрать другой элемент [Y/N] ?"<<endl;
                                 if (yes_no() == 1)
                                    goto LL1;
                                 else
                                    break;
                                }
                            finish(4);
                            break;
                            }
                        case 5:///Вывод авто старше заданного года выпуска
                            {
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            cout<<"\nВведите год выпуска:\n";
                            year_search=num_check(10);
                            fflush(stdin);
                            number3 = 1;
                            flagg=0;
                            int z = year_output (root);
                            if ( z == 0 )
                                cout<<"Таких автомобилей нет.\n";
                            finish(1);
                            break;
                            }
                        case 6:///Вывод данных об автомобилей заданной фирмы производителя.
                            {
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            cout<<"\nВведите фирму производителя:\n";
                            strcpy(company_search, str_check(23, 0));
                            fflush(stdin);
                            number3 = 1;
                            flagg=0;
                            int z2 = company_output (root);
                            if ( z2 == 0 )
                                cout<<"Таких автомобилей нет.\n";
                            finish(1);
                            break;
                            }
                        case 7:///Вывод данных об автомобилей чей пробег превышает заданную величину.
                            {
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            cout<<"\nВведите пробег:\n";
                            mileage_search = float_num_check(14);
                            fflush(stdin);
                            number3 = 1;
                            flagg=0;
                            int z3 = mileage_output(root);
                            if ( z3 == 0 )
                                cout<<"Таких автомобилей нет.\n";
                            finish(1);
                            break;
                            }
                        case 8:///Вывод отсортированного по объему двигателя списка
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            COUNTER = 0;
                            sort_mas(root);
                            number3 = 1;
                            flagg=0;
                            cout<<"\nПроизведем сортировку по объему двигателя...\n";
                            header();
                            sort_capacity (no_sort);
                            break;
                        case 9:///Вывод отсортированного по цене списка
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            COUNTER = 0;
                            sort_mas( root );
                            number3 = 1;
                            flagg=0;
                            cout<<"\nПроизведем сортировку по цене...\n";
                            header();
                            sort_price (no_sort);
                            break;
                        case 10:///Сохранение
                            if ( empty_check( root ) == NULL)   //проверка на пустоту
                                break;
                            header();
                            number3=0;
                            treeprint(root);                    // выводим элементы дерева
                            cout<<"\nСохранить данные программы на этом этапе в файл [Y/N]?"<<endl;
                            if (yes_no()==1)
                                {
                                ofstream D_INP("data.txt", ios_base::trunc);        //чистим файл и заносим данные
                                ofstream T_INP("Table.txt", ios_base::trunc);
                                flagg=0;
                                D_INP.close();
                                T_INP.close();
                                number3=0;
                                flagg=0;
                                save(root);
                                finish(5);
                                break;
                                }
                            else
                            {
                                finish(5);
                                break;
                            }
                        case 0:
                            {
                            cout<<"\nВы уверены что хотите завершить работу программы [Y/N]?"<<endl;
                            if (yes_no()==1)
                                {
                                cout<<"\nСохранить результат программы в файл [Y/N]?"<<endl;
                                if (yes_no()==1)
                                    {
                                    ofstream D_INP("data.txt", ios_base::trunc);    //чистим файл и заносим данные
                                    ofstream T_INP("Table.txt", ios_base::trunc);
                                    D_INP.close();
                                    T_INP.close();
                                    number3=0;
                                    flagg=0;
                                    save(root);
                                    finish(0);
                                    }
                                else
                                    {
                                    finish(0);
                                    }
                                }
                            else
                                {
                                finish(1);
                                goto MENU;
                                }
                            }
                        default:
                            errors (3);
                    }
            } while ( x!=0 );
        deltree_mem(root);
        return 0;
    }

///Печать одного эллемента
int one_el_print( struct CBinaryNode *tree, int num)
    {
                cout    <<"|"<<setw( 4 )  << num
                        <<"|"<<setw( 20 ) << left << tree -> CAR.car_model
                        <<"|"<<setw( 14 ) << tree -> CAR.mileage
                        <<"|"<<setw( 21 ) << tree -> CAR.company
                        <<"|"<<setw( 10 ) << tree -> CAR.year
                        <<"|"<<setw( 20 ) << tree -> CAR.engine_capacity
                        <<"|"<<setw( 27 ) << tree -> CAR.price
                        <<"|\n"<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
    }

/// Вывод узлов дерева (обход в инфиксной форме)
int treeprint( struct CBinaryNode *tree )
    {
        if ( tree != NULL )                                     //Пока не встретится пустой узел
            {
                number3++;
                one_el_print( tree, number3 );
                treeprint ( tree -> left );                     //Рекурсивная функция вывода левого поддерева
                treeprint ( tree -> right );                    //Рекурсивная функция вывода правого поддерева
            }
        return ( number3 );
    }

/// Добавление узлов в дерево
struct CBinaryNode *addnode(struct CBinaryNode *ptr, struct CBinaryNode *tree)                                               //ГОТОВО
    {
        if (tree == NULL)                                           // Если дерева нет, то формируем корень
            {
                tree = new CBinaryNode;

                strcpy(tree -> CAR.car_model, ptr -> CAR.car_model);//заносим данные
                tree -> CAR.mileage = ptr -> CAR.mileage;
                strcpy(tree -> CAR.company, ptr -> CAR.company);
                tree -> CAR.year = ptr -> CAR.year;
                tree -> CAR.engine_capacity = ptr -> CAR.engine_capacity;
                tree -> CAR.price = ptr -> CAR.price;
                            number++;
                tree->left = NULL;
                tree->right = NULL;                                 //ветви инициализируем пустотой
                tree->parent = current;                             //передаем указатель на родителя
            }

        else
        {
            if ( ptr -> CAR.price < tree -> CAR.price )             //Если цена меньше корневого, уходим влево
            {
                    current = tree;
                    tree -> left = addnode ( ptr, tree->left );     //Рекурсивно добавляем элемент
            }
            else if ( ptr -> CAR.price > tree -> CAR.price )        //иначе уходим вправо
                {
                    current = tree;
                    tree -> right = addnode ( ptr, tree->right );   //Рекурсивно добавляем элемент
                }
            else                                                    //( ptr -> CAR.price = tree -> CAR.price ) усли равны - приходится уходить вправо
                {
                    current = tree;
                    tree -> right = addnode ( ptr, tree->right );   //Рекурсивно добавляем элемент
                }
        };
            return(tree);
    }

///Удаление
struct CBinaryNode *del_elem (struct CBinaryNode *tree, struct CBinaryNode *del_elem )
{
        struct CBinaryNode *p = del_elem->parent;                           //ук-ль на родителя удаляемого элемента
        if ( (del_elem->left == NULL) && (del_elem->right == NULL) )        // первый случай: удаляем лист
            {
            if ( p->left == del_elem )
                {
                delete (del_elem);
                p->left = NULL;
                }
            else
                {
                delete(del_elem);
                p->right = NULL;
                }
            }
        else if ( del_elem->left == NULL || del_elem->right == NULL )    // второй случай: удаляемый элемент имеет одного потомка
            {
            if ( del_elem->left == NULL )
                {
                if ( p->left == del_elem )
                    {
                    p->left = del_elem->right;
                    del_elem->right->parent = p;
                    delete (del_elem);
                    }
                else
                    {
                    p->right = del_elem->right;
                    del_elem->right->parent = p;
                    delete (del_elem);
                    }
                }
            else
                {
                if ( p->left == del_elem )
                    {
                    p->left = del_elem->left;
                    del_elem->left->parent = p;
                    delete (del_elem);
                    }
                else
                    {
                    p->right = del_elem->left;
                    del_elem->left->parent = p;
                    delete (del_elem);
                    }
                }
            }
        else                                                            //третий случай: удаление, где 2 сына
            {
            struct CBinaryNode *first_right = del_elem->right;          //укакзатель на правый элемент от удаляемого
            struct CBinaryNode *change = NULL;                          //для левого крайнего узла правого узла удаляемого элемента
            if ( del_elem->right->left == NULL )
                {
                if ( p->left == del_elem )
                    {
                    del_elem->left->parent = del_elem->right;
                    p->left = del_elem->right;
                    del_elem->right->left = del_elem->left;
                    del_elem->right->parent = p;
                    delete (del_elem);
                    }
                else
                    {
                    p->right = del_elem->right;
                    del_elem->right->parent = p;
                    del_elem->left->parent = del_elem->right;
                    del_elem->right->left = del_elem->left;
                    delete (del_elem);
                    }
                }
            else
                {
                while ( first_right -> left != NULL )
                    {
                    first_right = first_right->left;
                    change = first_right;
                    }
                change -> parent ->left = NULL;
                if ( p->left == del_elem )
                    {
                    p->left = change;

                    change->parent->left = NULL;

                    change->parent = p;
                    change->left = del_elem->left;
                    change->right = del_elem->right;

                    change->left->parent = change;
                    change->right->parent = change;

                    delete (del_elem);
                    }
                else
                    {
                    p->right = change;

                    change->parent->left = NULL;
                    change->parent = p;

                    change->left = del_elem->left;
                    change->right = del_elem->right;

                    change->left->parent = change;
                    change->right->parent = change;

                    delete (del_elem);
                    }
                    }
            number--;
            }
        return (tree);
    }

///Удаление корня
struct CBinaryNode *root_del (struct CBinaryNode *del_elem)
    {
        number--;
        struct CBinaryNode *zamena = NULL;                                  //для левого крайнего узла правого узла удаляемого элемента
        if ((del_elem->right == NULL) && (del_elem->left==NULL))
            {
            delete (del_elem);
            return ( zamena );
            }
        else if ( del_elem->left == NULL || del_elem->right == NULL )
            {
            if ( del_elem->left == NULL )
                {
                if ( del_elem->right->left == NULL )
                    {
                    zamena = del_elem->right;                               //указатель на правый элемент от удаляемого
                    zamena->parent = NULL;
                    delete (del_elem);
                    return ( zamena );
                    }
                else
                    {
                    struct CBinaryNode *zamena = del_elem -> right;
                    while ( zamena -> left != NULL )
                        zamena = zamena -> left;
                    if ( zamena -> right != NULL )
                        {
                        zamena -> parent -> left = zamena -> right;
                        zamena -> right -> parent = zamena -> parent;
                        }
                    else
                        zamena -> parent -> left = NULL;

                    zamena -> parent -> left = NULL;
                    zamena->right = del_elem->right;
                    zamena->parent = NULL;
                    zamena -> parent -> left = zamena -> right;

                    del_elem->right->parent = zamena;
                    delete (del_elem);
                    return ( zamena );
                    }
                }
            else
            {
                if ( del_elem->left->right == NULL )
                    {
                    zamena = del_elem->left;
                    zamena->parent = NULL;
                    delete (del_elem);
                    return ( zamena );
                    }
                else
                    {
                    struct CBinaryNode *zamena = del_elem -> left;
                    while ( zamena -> right != NULL )
                            zamena = zamena -> right;
                    if ( zamena -> left != NULL )
                        {
                        zamena -> parent -> right = zamena -> left;
                        zamena -> left -> parent = zamena -> parent;
                        }
                    else
                        zamena -> parent -> right = NULL;

                    zamena -> parent -> right = zamena -> left;
                    zamena->left = del_elem->left;
                    zamena->parent= NULL;

                    del_elem->left->parent = zamena;
                    delete (del_elem);
                    return ( zamena );
                    }
            }
        }
        else                                                //случай если два 2 сына
            {
            if ( del_elem->right->left == NULL )
                {
                zamena = del_elem->right;                   //ук-ль на правый элемент от удаляемого
                zamena->parent = NULL;
                zamena->left = del_elem->left;
                del_elem->left->parent = zamena;
                delete (del_elem);
                return ( zamena );
                }
            else
                {
                struct CBinaryNode *zamena = del_elem -> right;

                while ( zamena -> left != NULL )
                    zamena = zamena -> left;

                if ( zamena -> right != NULL )
                    {
                    zamena -> parent -> left = zamena -> right;
                    zamena -> right -> parent = zamena -> parent;
                    }
                else
                    zamena -> parent -> left = NULL;

                zamena->right = del_elem->right;
                zamena->left = del_elem->left;
                zamena->parent = NULL;

                del_elem->left->parent = zamena;
                del_elem->right->parent = zamena;
                delete (del_elem);
                return ( zamena );
                }
            }
    }

///Корректировка данных
struct CBinaryNode *correct (struct CBinaryNode *tree)
    {
          do
          {
            cout<<"Введите эллемент таблицы которых хотели бы исправить\n"
               <<"|1| Модель\n"
               <<"|2| Пробег\n"
               <<"|3| Фирма\n"
               <<"|4| Год\n"
               <<"|5| Объем двигателя\n"
               <<"|6| Цену\n"
               <<"|7| Все\n"
               <<"|0| Закончить корректировку данного элемента"<<endl;
            x2=num_check(N);
            switch (x2)
            {
                case 1:
                    {
                    cout<<"Введите новую модель: "<<endl;
                    strcpy(tree -> CAR.car_model, str_check(20, 1));
                    fflush(stdin);  //чистка потока
                    break;
                    }
                case 2:
                    {
                    cout<<"Введите новый пробег (в км):"<<endl;
                    tree -> CAR.mileage = float_num_check(14);
                    fflush(stdin);
                    break;
                    }
                case 3:
                    {
                    cout<<"Введите новую фирму производителя:"<<endl;
                    strcpy(tree -> CAR.company, str_check(23, 0));
                    fflush(stdin);
                    break;
                    }
                case 4:
                    {
                    cout<<"Введите новый год выпуска:"<<endl;
                    tree -> CAR.year = num_check(10);
                    fflush(stdin);
                    break;
                    }
                case 5:
                    {
                    cout<<"Введите новый объем двигателя (см квадратных) :"<<endl;
                    tree -> CAR.engine_capacity = num_check(20);
                    fflush(stdin);
                    break;
                    }
                case 6:
                    {
                    cout<<"Введите новую цену ($):"<<endl;
                    tree -> CAR.price = float_num_check(27);
                    fflush(stdin);
                    break;
                    }
                case 7:
                    {
                    tree = input ( tree );
                    break;
                    }
                case 0:
                    return (tree);
                default:
                    errors (3);
            }
        }while (x2!=0);
    }

///Сохранение
void save(struct CBinaryNode *tree)
{
    ofstream D_INP("data.txt", ios_base::app);              //заносим данные в конец
    ofstream T_INP("Table.txt", ios_base::app);
    if (flagg==0)                                           //первый раз - заносим заголовок
        {
        T_INP<<setw( 80 ) << right << "Список Автомобилей:\n"
        <<"============================================================================================================================\n"
        <<"|"<<setw( 4 )  << left <<"№"
        <<"|"<<setw( 20 ) << left << "Модель"
        <<"|"<<setw( 14 ) << "Пробег (км)"
        <<"|"<<setw( 21 ) << "Фирма"
        <<"|"<<setw( 10 ) << "Год"
        <<"|"<<setw( 20 ) << "Объем двигателя (см)"
        <<"|"<<setw( 27 ) << "Цена ($)"
        <<"|\n"<<"============================================================================================================================"<<endl;
        }
    if ( tree != NULL )   //Пока не встретится пустой узел
        {
        number3++;
        T_INP<<"|"<<setw( 4 )  << number3
             <<"|"<<setw( 20 ) << left << tree -> CAR.car_model
             <<"|"<<setw( 14 ) << tree -> CAR.mileage
             <<"|"<<setw( 21 ) << tree -> CAR.company
             <<"|"<<setw( 10 ) << tree -> CAR.year
             <<"|"<<setw( 20 ) << tree -> CAR.engine_capacity
             <<"|"<<setw( 27 ) << tree -> CAR.price
             <<"|\n"<<"----------------------------------------------------------------------------------------------------------------------------\n";

        D_INP<< left << tree -> CAR.car_model<<"\n"
             << tree -> CAR.mileage<<"\n"
             << tree -> CAR.company<<"\n"
             << tree -> CAR.year<<"\n"
             << tree -> CAR.engine_capacity<<"\n"
             << tree -> CAR.price<<"\n\n";
        flagg=1;
        D_INP.close();
        T_INP.close();
        save ( tree -> left );  //Рекурсивная функция вывода левого поддерева
        save ( tree -> right ); //Рекурсивная функция вывода правого поддерева
        }
}

///Функция создания массива для сортировки sorted
struct database *sort_mas( struct CBinaryNode *tree)
    {
        if ( tree != NULL )                                                  // если дерево не пустое
            {
                no_sort[COUNTER].mileage = tree->CAR.mileage;
                no_sort[COUNTER].year = tree->CAR.year;
                no_sort[COUNTER].engine_capacity = tree->CAR.engine_capacity;
                no_sort[COUNTER].price = tree->CAR.price;
                strcpy (no_sort[COUNTER].car_model, tree->CAR.car_model);
                strcpy (no_sort[COUNTER].company, tree->CAR.company);
                COUNTER++;
                sort_mas (tree->left);                                      // рекурсивно копируем левую ветку
                sort_mas (tree->right);                                     // рекурсивно копируем правую ветку
            }
        return (no_sort);
    }

///Сортировка по цене sorting
void sort_price ( struct database *tree )             //сортировка по цене
    {
        for( i = 0 ; i < COUNTER ; i++ )
            for( j = 0 ; j < COUNTER ; j++ )
                if (  no_sort[i].price < no_sort[j].price)
                    {                                           //заносим остортированные данные в массив
                        char tmp1[20];
                        strcpy (tmp1, no_sort[i].car_model);
                        strcpy (no_sort[i].car_model, no_sort[j].car_model);
                        strcpy(no_sort[j].car_model, tmp1);

                        char tmp6[20];
                        strcpy (tmp6, no_sort[i].company);
                        strcpy (no_sort[i].company, no_sort[j].company);
                        strcpy(no_sort[j].company, tmp6);

                        float  tmp2 = no_sort[i].price;
                        no_sort[i].price = no_sort[j].price;
                        no_sort[j].price = tmp2;

                        float  tmp3 = no_sort[i].mileage;
                        no_sort[i].mileage = no_sort[j].mileage;
                        no_sort[j].mileage = tmp3;

                        int tmp4 = no_sort[i].year;
                        no_sort[i].year = no_sort[j].year;
                        no_sort[j].year = tmp4;

                        int tmp5 = no_sort[i].engine_capacity;
                        no_sort[i].engine_capacity = no_sort[j].engine_capacity;
                        no_sort[j].engine_capacity = tmp5;
                    }
        number3=1;
        for ( i = 0; i < COUNTER; i++, number3++ )
                                {
                                     cout   <<"|"<<setw( 4 )  << number3
                                            <<"|"<<setw( 20 ) << left << no_sort[i].car_model
                                            <<"|"<<setw( 14 ) << no_sort[i].mileage
                                            <<"|"<<setw( 21 ) << no_sort[i].company
                                            <<"|"<<setw( 10 ) << no_sort[i].year
                                            <<"|"<<setw( 20 ) << no_sort[i].engine_capacity
                                            <<"|"<<setw( 27 ) << no_sort[i].price
                                            <<"|\n"<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                                }
        number3=1;
        cout<<"Сохранить отсортированные данные в файл [Y/N]"<<endl;
            if(yes_no()==1)
                {
                ofstream price_sort("saves/price_sort.txt", ios_base::trunc);
                for ( i = 0; i < COUNTER; i++, number3++ )
                                    {
                                        if (i==0)
                                        {
                                         price_sort<<setw( 80 ) << right << "Список Автомобилей:\n"
                                                                 <<"============================================================================================================================\n"
                                                                 <<"|"<<setw( 4 )  << left <<"№"
                                                                 <<"|"<<setw( 20 ) << left << "Модель"
                                                                 <<"|"<<setw( 14 ) << "Пробег (км)"
                                                                 <<"|"<<setw( 21 ) << "Фирма"
                                                                 <<"|"<<setw( 10 ) << "Год"
                                                                 <<"|"<<setw( 20 ) << "Объем двигателя (см)"
                                                                 <<"|"<<setw( 27 ) << "Цена ($)"
                                                                 <<"|\n"<<"============================================================================================================================"<<endl;
                                        }
                                         price_sort<<"|"<<setw( 4 )  << number3
                                                   <<"|"<<setw( 20 ) << left << no_sort[i].car_model
                                                   <<"|"<<setw( 14 ) << no_sort[i].mileage
                                                   <<"|"<<setw( 21 ) << no_sort[i].company
                                                   <<"|"<<setw( 10 ) << no_sort[i].year
                                                   <<"|"<<setw( 20 ) << no_sort[i].engine_capacity
                                                   <<"|"<<setw( 27 ) << no_sort[i].price
                                                   <<"|\n"<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                                    }
                price_sort.close();
                finish(5);
            }
            else
                finish(1);
    }

///Сортировка по обьему двигателя
void sort_capacity ( struct database *tree )
    {
        for( i = 0 ; i < COUNTER ; i++ )
            for( j = 0 ; j < COUNTER ; j++ )
                if (  no_sort[i].engine_capacity < no_sort[j].engine_capacity)
                    {                                           //заносим остортированные данные в массив
                        char tmp1[20];
                        strcpy (tmp1, no_sort[i].car_model);
                        strcpy (no_sort[i].car_model, no_sort[j].car_model);
                        strcpy(no_sort[j].car_model, tmp1);

                        char tmp6[20];
                        strcpy (tmp6, no_sort[i].company);
                        strcpy (no_sort[i].company, no_sort[j].company);
                        strcpy(no_sort[j].company, tmp6);

                        float  tmp2 = no_sort[i].price;
                        no_sort[i].price = no_sort[j].price;
                        no_sort[j].price = tmp2;

                        float  tmp3 = no_sort[i].mileage;
                        no_sort[i].mileage = no_sort[j].mileage;
                        no_sort[j].mileage = tmp3;

                        int tmp4 = no_sort[i].year;
                        no_sort[i].year = no_sort[j].year;
                        no_sort[j].year = tmp4;

                        int tmp5 = no_sort[i].engine_capacity;
                        no_sort[i].engine_capacity = no_sort[j].engine_capacity;
                        no_sort[j].engine_capacity = tmp5;

                    }
        number3=1;
        for ( i = 0; i < COUNTER; i++, number3++ )
                                {
                                    cout    <<"|"<<setw( 4 )  << number3
                                            <<"|"<<setw( 20 ) << left << no_sort[i].car_model
                                            <<"|"<<setw( 14 ) << no_sort[i].mileage
                                            <<"|"<<setw( 21 ) << no_sort[i].company
                                            <<"|"<<setw( 10 ) << no_sort[i].year
                                            <<"|"<<setw( 20 ) << no_sort[i].engine_capacity
                                            <<"|"<<setw( 27 ) << no_sort[i].price
                                            <<"|\n"<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                                }
         number3=1;
         cout<<"Сохранить отсортированные данные в файл [Y/N]"<<endl;
            if(yes_no()==1)
            {
                ofstream capacity_sort("saves/capacity_sort.txt", ios_base::trunc);
                for ( i = 0; i < COUNTER; i++, number3++ )
                                    {
                                        if (i==0)
                                        {
                                          capacity_sort<<setw( 80 ) << right << "Список Автомобилей:\n"
                                                                 <<"============================================================================================================================\n"
                                                                 <<"|"<<setw( 4 )  << left <<"№"
                                                                 <<"|"<<setw( 20 ) << left << "Модель"
                                                                 <<"|"<<setw( 14 ) << "Пробег (км)"
                                                                 <<"|"<<setw( 21 ) << "Фирма"
                                                                 <<"|"<<setw( 10 ) << "Год"
                                                                 <<"|"<<setw( 20 ) << "Объем двигателя (см)"
                                                                 <<"|"<<setw( 27 ) << "Цена ($)"
                                                                 <<"|\n"<<"============================================================================================================================"<<endl;
                                        }
                                          capacity_sort<<"|"<<setw( 4 )  << number3
                                                   <<"|"<<setw( 20 ) << left << no_sort[i].car_model
                                                   <<"|"<<setw( 14 ) << no_sort[i].mileage
                                                   <<"|"<<setw( 21 ) << no_sort[i].company
                                                   <<"|"<<setw( 10 ) << no_sort[i].year
                                                   <<"|"<<setw( 20 ) << no_sort[i].engine_capacity
                                                   <<"|"<<setw( 27 ) << no_sort[i].price
                                                   <<"|\n"<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                                    }
                capacity_sort.close();
                finish(5);
            }
            else
                finish(1);
    }

///Вывод данных об автомобиле старше заданного года выпуска.
int year_output( struct CBinaryNode *tree)
    {
    if ( tree != NULL )    // пока дерево не пустое
        {
        if ( year_search < tree -> CAR.year )
            {
            if ( flagg == 0 )
                {
                header();
                flagg=1;
                }
            one_el_print( tree, number3 );
            number3++;
            kolvo++;
            }
        year_output ( tree -> left );  //Рекурсивная функция вывода левого поддерева
        year_output ( tree -> right ); //Рекурсивная функция вывода правого поддерева
        }
    return ( kolvo );
    }

///Вывод данных об автомобилей заданной фирмы производителя.
int company_output( struct CBinaryNode *tree)
    {
    if ( tree != NULL )    // пока дерево не пустое
        {
        if ( !stricmp ( company_search, tree -> CAR.company ) )
            {
            if ( flagg == 0 )
                {
                header();
                flagg=1;
                }
            one_el_print( tree, number3 );
            kolvo++;
            number3++;
            }
        company_output ( tree -> left );  //Рекурсивная функция вывода левого поддерева
        company_output ( tree -> right ); //Рекурсивная функция вывода правого поддерева
        }
    return ( kolvo );
    }

///Вывод данных об автомобилей чей пробег превышает заданную величину.
int mileage_output( struct CBinaryNode *tree)
    {
    if ( tree != NULL )    // пока дерево не пустое
        {
        if ( mileage_search < tree -> CAR.mileage )
            {
            if ( flagg == 0 )
                {
                header();
                flagg=1;
                }
            one_el_print( tree, number3 );
            kolvo++;
            number3++;
            flagg++;
            }
        mileage_output ( tree -> left );  //Рекурсивная функция вывода левого поддерева
        mileage_output ( tree -> right ); //Рекурсивная функция вывода правого поддерева
        }
    return ( kolvo );
    }

///Да/Нет
int yes_no ()
    {
    answer = '\0';
    cin>>answer;
    fflush(stdin);
        if (  answer == 'Y' || answer == 'y'  )
            return 1;
        else if ( answer == 'N' || answer == 'n' )
            return 2;
        else
            {
            errors (6);
            yes_no();
            }
    }

///Функция для цветов
void SetColor (int Text, int Fon)
     {
        SetConsoleTextAttribute(h, (Fon << 4) + Text);
     }

///Начало работы
void privet()
    {
    char S[N]={""}; //В S будут считываться строки
    ifstream f("input/privet.txt"); //Открыли файл для чтения
    while (!f.eof()) //Будем читать информацию пока не дойдем до конца файла
        {
        f.getline(S,N); //Построчное считывание информации в S
        cout<<S<<endl; //Вывод очередной строки на экран
        }
    f.close();  //Закрыли открытый файл
}

///Титульный лист
void TITUL()
    {
    char S[N]={""}; //В S будут считываться строки
    ifstream f("input/titul.txt"); //Открыли файл для чтения
    while (!f.eof()) //Будем читать информацию пока не дойдем до конца файла
        {
        f.getline(S,N); //Построчное считывание информации в S
        cout<<S<<endl; //Вывод очередной строки на экран
        }
    f.close();  //Закрыли открытый файл
    getch();
    system("cls");      //clearscreen

}

///Меню
int menu ()
    {
    char S[N]={""}; //В S будут считываться строки
    ifstream f("input/menu.txt"); //Открыли файл для чтения
    while (!f.eof()) //Будем читать информацию пока не дойдем до конца файла
        {
        f.getline(S,N); //Построчное считывание информации в S
        cout<<S<<endl; //Вывод очередной строки на экран
        }
    f.close();  //Закрыли открытый файл
    cout<<"Ввод: "<<endl;
    x=num_check(N);
    return (x);
    }

///Вывод ошибок
void errors (int err_x)
    {
        SetColor(12, 15);
        switch (err_x)
         {
         case 1:
                cout<<"\n\tОшибка! Ввод числовых значений недопустим. Повторите попытку..."<<endl;
                SetColor(0, 15);
                break;
         case 2:
                cout<<"\n\tОшибка! Такого элемента не существует. Попробуйте еще раз..."<<endl;
                SetColor(0, 15);
                break;
         case 3:
                cout<<"\n\tОшибка! Вы ввели недопустимое значение. Выберите номер из предложенных.."<<endl;
                SetColor(0, 15);
                break;
         case 4:
                cout<<"\n\tОшибка! Ввод символов кроме, числовых недопустим. Повторите попытку..."<<endl;
                SetColor(0, 15);
                break;
         case 5:
                cout<<"\n\tОшибка! Файл с данными пуст... Продолжить работу [Y/N]?"<<endl;
                SetColor(0, 15);
                break;
         case 6:
                cout<<"\n\tВведите 'Y' - для подтверждения действия или 'N' - для отмены. "<<endl;
                SetColor(0, 15);
                break;
         case 7:
                cout<<"\n\tОшибка! Невозможно открыть файл."<<endl;
                SetColor(0, 15);
                break;
         case 8:
                cout<<"\n\tОшибка! Вы ввели слишком большое значение."<<endl;
                SetColor(0, 15);
                break;
         case 9:
                cout<<"Пока-что вами не был введен ни один элемент"<<endl;
                SetColor(0, 15);
                break;
         }
    }

///Заголовок
void header()
    {
                     cout<<setw( 80 ) << right << "Список Автомобилей:\n"
                         <<"============================================================================================================================\n"
                         <<"|"<<setw( 4 )  << left <<"№"
                         <<"|"<<setw( 20 ) << left << "Модель"
                         <<"|"<<setw( 14 ) << "Пробег (км)"
                         <<"|"<<setw( 21 ) << "Фирма"
                         <<"|"<<setw( 10 ) << "Год"
                         <<"|"<<setw( 20 ) << "Объем двигателя (см)"
                         <<"|"<<setw( 27 ) << "Цена ($)"
                         <<"|\n"<<"============================================================================================================================"<<endl;
    }

///Функция завершения каждого кейса
void finish (int succ_x)
    {
        SetColor(10, 15);
        switch (succ_x)
          {
         case 1:
                SetColor(0, 15);
                break;
         case 2:
                cout<<"\n\tЭлемент успешно добавлен..."<<endl;
                SetColor(0, 15);
                break;
         case 3:
                cout<<"\n\tДанные об авто успешно удалены.."<<endl;
                SetColor(0, 15);
                break;
         case 4:
                cout<<"\n\tДанные об авто успешно изменены.."<<endl;
                SetColor(0, 15);
                break;
         case 5:
                cout<<"\n\tДанные успешно сохранены.."<<endl;
                SetColor(0, 15);
                break;
         case 0:
                cout<<"\n\tСпасибо за использование программы! До Свидания!"<<endl;
                SetColor(0, 15);
                exit(0);
          }
        cout<<"Нажмите любую клавишу для продолжения..."<<endl;
        getch();
        system ("cls");
    }

///Для проверки наличия в дереве элементов
struct CBinaryNode *empty_check ( struct CBinaryNode *tree )
    {
        if ( tree == NULL )
            {
            errors(9);
            finish(1);
            return NULL;
            }
    }

/*МОЖНО СДЕЛАТЬ СОРТИРОВКУ ПО ЛЮБОМУ СТОЛБЦУ ТАБЛИЦЫ - ЗАМЕНИМ ДВЕ ФУНКЦИИ СОРТИРОВКУ НА ОДНУ - С ПЕРЕДАЧЕЙ ЗНАЧЕНИЯ НУЖНОГО СТОЛБЦЫ ТЕМ САМЫМ СОКРАТИВ КОД И ДОБАВИВ ВОЗМОЖНОСТЕЙ (ТОЖЕ САМОЕ КАСАЕТСЯ ФУНКЦИЙ УДАЛЕНИЯ, КОРРЕКТИРОВКИ И ВЫВОДА*/ ///НА БУДУюЩЕЕ

///Проход по дереву
struct CBinaryNode *TREE_scrl ( struct CBinaryNode *tree, int del_number )
    {
        if ( tree != NULL  )                                                //Пока не встретится пустой узел
            {
                if ( del_number == COUNTER )
                    PTR = tree;
                COUNTER++;
                TREE_scrl ( tree -> left, del_number );                     //Рекурсивная функция вывода левого поддерева
                TREE_scrl ( tree -> right, del_number );                    //Рекурсивная функция вывода правого поддерева
        }
        return ( PTR );
    }


///Проверка - int
int num_check (int razmer)
    {
    int bk;  //переменная возврата
    char znach[N];
    int err=0;
    do
        {
        memset(znach,'\0', sizeof (znach)); //заполнения всей строки нулями
        err=0;
        cin.getline(znach, 256);
        fflush(stdin);                      //чистка потока ввода
        if ((strlen(znach)) > razmer)       //проверка длины
            {
            errors(8);
            err = 1;
            }
        if (err==0)                         //проверка на цифры
            {
            for ( i = 0 ; i < strlen ( znach ) ; i++ )
                if ( ( isdigit ( ( unsigned char ) znach [i] ) ) == 0 )
                    err=2;
                if (err==2)
                    errors(4);
            }
        if (err==0)
            bk = atoi ( znach );
        } while (err != 0);
    return bk;
    }

///Проверка - float
float  float_num_check (int razmer2)
    {
    cout.setf(ios_base::fixed);
    cout.precision(2);
    int err = 0;
    string znach;
    int j = 0;
    int ser=0;
    do
        {
        //memset(znach,'\0', sizeof (znach));
        ser = 0;
        err = 0;
        getline(cin, znach);
        fflush(stdin);                  //чистка потока
        if ((znach.length() > razmer2)) //проверка длины
            {
            errors(8);
            err = 1;
            }
        if (err==0)                     //поиск запятой
            {
            for ( i = 0 ; i < znach.length() ; i++ )
                if  ( (znach [i] == ',') || (znach [i] == '.') )
                    {
                    znach [i] = ',';
                    ser = i;
                    }
            if ( ser != 0 )             //проверка на цифры
                {
                for ( i = 0; i < ser; i++)
                    if  ( isdigit ( znach [i] ) == 0 )
                        err=1;
                for ( j = ser+1; j < znach.length() ; j++ )
                    if  ( isdigit ( znach [j] ) == 0 )
                        err=1;
                }
            else
                for ( i = 0 ; i < znach.length() ; i++ )
                    if ( ( isdigit ( ( unsigned char ) znach [i] ) ) == 0)
                        err=1;
            if (err==1)
                errors(4);
            }
        } while (err != 0);
        float bk = atof (znach.c_str());
        return bk;
        }


///Проверка - строка
char *str_check (int razmer3, int if_integer)
{
    char str[N];
    char *PTR = str;
    int err=0;
    if (if_integer==0)
    {
        do
        {
        memset(str,'\0', sizeof (str)); //заполнения всей строки нулями
        cin.getline(str, N);
        fflush(stdin);                  //чистка потока
            for ( i = 0 ; str[i] ; i++ )
                if ( (str[i] >= '0') && (str[i] <= '9'))
                    break;
                if ( str[i] )
                    errors (1);
        }while (str[i]);
        if ((strlen(str)) > razmer3)
            {
            errors(8);
            str_check(razmer3, if_integer);
            }
        else
            return PTR;
    }
    if (if_integer == 1)
        {
        do
            {
            err=0;
            memset(str,'\0', sizeof (str));
            cin.getline(str, N);
            fflush(stdin);
            if (strlen(str)>razmer3)
                {
                    err=1;
                    errors(8);
                }
            }while (err != 0);
        return PTR;
    }
}

///Ввод данных
struct CBinaryNode *input ( struct CBinaryNode *tree )
    {

                            cout<<"Введите модель: "<<endl;
                            strcpy(tree -> CAR.car_model, str_check(20, 1));
                            fflush(stdin);  //чистка потока
                            cout<<"Введите пробег (в км):"<<endl;
                            tree -> CAR.mileage = float_num_check(14);
                            fflush(stdin);
                            cout<<"Введите фирму производителя:"<<endl;
                            strcpy(tree -> CAR.company, str_check(23, 0));
                            fflush(stdin);
                            cout<<"Введите год выпуска:"<<endl;
                            tree -> CAR.year = num_check(10);
                            fflush(stdin);
                            cout<<"Введите объем двигателя (см квадратных) :"<<endl;
                            tree -> CAR.engine_capacity = num_check(20);
                            fflush(stdin);
                            cout<<"Введите цену ($):"<<endl;
                            tree -> CAR.price = float_num_check(27);
                            fflush(stdin);
        return tree;
    }

///Освобождение памяти дерева
void deltree_mem( struct CBinaryNode *tree)
    {
        if ( tree != NULL )                     // если дерево не пустое
            {
            deltree_mem(tree->left);            // рекурсивно удаляем левую ветку
            deltree_mem(tree->right);           // рекурсивно удаляем правую ветку
            delete (tree);                      // удаляем корень
            }
    }



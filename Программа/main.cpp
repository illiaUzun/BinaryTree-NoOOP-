//����� ���������� � ��� �������� ������ �1. ��������: ���� ����. ��-174. ������� �21.

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

const int col = 179;                            // ������ ���� �������
const int row = 84;                             // ������ �������
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);     // ���������� ���������� ������������ ������
const int N=256;                                // ����������� ������ ������
///�������� ����������

int x = 0, x2 = 0, i = 0, j=0;             // ���������� �������� // x - ������� �� ������
int number = 0;                            // ������� ������ ����������
int number3 = 0;                           // ������� ��� treeprint
int COUNTER = 0;                           // ��� �������
///��������

int changing_number;
int del_number;
int year_search;
char company_search[30];
int mileage_search;
///���������� ��� ������� ������� �������� ��� ������ � ��������� ������������� ������


int flagg = 0;                              //����
int kolvo = 0;                              //��� ������� ������ ������������ ��������
char answer = '\0';                         //��� yes_no();
///��������������� ���������� ��� �������


int menu ();                                                                            //����
struct CBinaryNode * addnode (struct CBinaryNode *ptr, struct CBinaryNode *tree);       //���������� �������� � ������
int treeprint (struct CBinaryNode *tree);                                               //����� ����� ������
struct CBinaryNode *del_elem (struct CBinaryNode *tree, struct CBinaryNode *del_elem ); //�������� �������� �� ������
struct CBinaryNode *root_del (struct CBinaryNode *del_elem);                            //�������� ����� �� ������
struct CBinaryNode *correct (struct CBinaryNode *tree);                                //��������� ������ �� ��������
void sort_price ( struct database *tree );                                              //�-� ���������� ������� �� ����
void sort_capacity ( struct database *tree );                                           //�-� ���������� ������� �� �������
int year_output ( struct CBinaryNode *tree);                                             //����� ���� ������ ���� �������
int company_output( struct CBinaryNode *tree);                                           //����� ���� ����� ����� �������������
int mileage_output ( struct CBinaryNode *tree);                                          //����� ���� ����� ����� �������������
void save(struct CBinaryNode *tree);                                                    //���������� � ����
void deltree_mem (struct CBinaryNode *tree);                                            //������������ ������ ������
///�������� �������

int one_el_print( struct CBinaryNode *tree, int num);                                   //������ ������ ���������
struct CBinaryNode *input ( struct CBinaryNode *tree );                                 //����
struct database *sort_mas ( struct CBinaryNode *tree  );                                  //��� ����������
struct CBinaryNode *TREE_scrl ( struct CBinaryNode *tree, int del_number);              //������ �� ������
///��������������� �������

int yes_no();
void errors (int err_x);
void finish (int succ_x);
void header();
void privet ();
void SetColor (int text, int Fon);
void TITUL ();
///������������� �������

struct CBinaryNode *empty_check ( struct CBinaryNode *tree );
int num_check (int razmer);
float  float_num_check (int razmer2);
char *str_check (int razmer3, int if_integer);
///������� ��������

struct database                      //���� ������
    {
            char car_model[20];     //������
            float mileage;          //������ � ��
            char company[20];       //�������� �������������
            int year;               //���
            int engine_capacity;    //����� ���������
            float price;            //����
    }no_sort[N];

struct CBinaryNode                  //��������� ��������� ������ ������
    {
        database CAR;               //���� ������
        struct CBinaryNode *left;   //����� �������
        struct CBinaryNode *right;  //������ �������
        struct CBinaryNode *parent; //��������
    }NODES;

struct CBinaryNode *root = NULL;     // ��������� ��������� ������
struct CBinaryNode *ptr = &NODES;    //��������� ����
struct CBinaryNode *current = NULL;  //������������ ����������, ����������� �� ���������� ����
struct CBinaryNode *PTR;             //��������������� ��� ������� �� ������

FILE *D_INP;
FILE *T_INP;                         //����� ������

int main ( )
    {
        system ("color F0");                                 //������ ����
      //setlocale(LC_ALL,"Russian");                         //������ ����
        SetConsoleTitle("Database of the auto dealership. UZUN (c)");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        system("mode con cols=125 lines=85");                //������������ ������� ��� ���� �����
        TITUL();
        privet();                                            //����� ������ �� ������
        if (yes_no()==1)                                     //������ �� �����
            {
                FILE *D_INP=fopen("data.txt", "r");
                while (( fscanf ( D_INP, "%s %f %s %d %d %f\n", &ptr -> CAR.car_model, &ptr -> CAR.mileage, &ptr -> CAR.company, &ptr -> CAR.year, &ptr -> CAR.engine_capacity, &ptr -> CAR.price)) != EOF)
                    root = addnode ( ptr, root);
                fclose(D_INP);
                if ( root == NULL )                         //�������� ����� �� �������
                    {
                    errors(5);
                    if (yes_no()==1)
                        goto MENU;
                    else
                        exit (0);
                    }
            }
        else                                                //������� �����
            {
                ofstream D_INP("data.txt", ios_base::trunc);
                ofstream T_INP("Table.txt", ios_base::trunc);
                D_INP.close();
                T_INP.close();
            }

        MENU:
        finish(1);
        do                                                  //����
            {
                menu();
                switch ( x )
                    {
                        case 1:///����� ������
                            {
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            header();
                            number3=0;
                            treeprint(root);
                            finish(1);
                            break;
                            }
                        case 2:///���������� ��������
                            {
                            root = addnode ( input(ptr), root); // ��������� ��������� ���� �� ������
                            finish(2);
                            break;
                            }
                        case 3:///�������� ��������
                            {
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            header();
                            number3=0;
                            treeprint(root);
                            LL2:
                            del_number=0;
                            cout<<"������� ����� ���������� ��������:"<<endl;
                            del_number = num_check(N);
                            if ( del_number > number || del_number <= 0)
                                {
                                errors(2);
                                cout<<"������ ������� ������ ������� [Y/N] ?"<<endl;
                                 if (yes_no() == 1)
                                    goto LL1;
                                 else
                                    break;
                                }
                            COUNTER = 1;
                            TREE_scrl(root, del_number);    //���� ����� ���������� ��������
                            cout<<"�� �������, ��� ������ ������� ������ �� ���� ���� [Y/N] ?"<<endl;
                            header();
                            one_el_print(PTR, del_number);
                            if (yes_no() == 1 )
                                {
                                if ( del_number == 1 )
                                    root = root_del(root);  //������� ������
                                else
                                    del_elem (root, PTR);   //������� ��������
                                }
                            else
                                {
                                cout<<"������ ������� ������ ������� [Y/N] ?"<<endl;
                                if (yes_no() == 1)
                                    goto LL2;
                                else
                                    break;
                                }
                            finish(3);
                            break;
                            }
                       case 4:///��������� ������
                           {
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            header();
                            number3=0;
                            treeprint(root);
                            LL1:
                            changing_number=0;
                            cout<<"������� ����� ���������� ��������:"<<endl;
                            changing_number = num_check(N);
                            if ( changing_number > number || changing_number <= 0)
                                {
                                errors(2);
                                cout<<"������ ������� ������ ������� [Y/N] ?"<<endl;
                                 if (yes_no() == 1)
                                    goto LL1;
                                 else
                                    break;
                                }
                            COUNTER = 1;
                            TREE_scrl(root, changing_number);    //����� ����������� ��������
                            cout<<"�� �������, ��� ������ ������ ��������� � ������ ����� ���� [Y/N] ?"<<endl;
                            header();
                            one_el_print(PTR, changing_number);
                            if (yes_no() == 1)
                                correct ( PTR );
                            else
                                {
                                 cout<<"������ ������� ������ ������� [Y/N] ?"<<endl;
                                 if (yes_no() == 1)
                                    goto LL1;
                                 else
                                    break;
                                }
                            finish(4);
                            break;
                            }
                        case 5:///����� ���� ������ ��������� ���� �������
                            {
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            cout<<"\n������� ��� �������:\n";
                            year_search=num_check(10);
                            fflush(stdin);
                            number3 = 1;
                            flagg=0;
                            int z = year_output (root);
                            if ( z == 0 )
                                cout<<"����� ����������� ���.\n";
                            finish(1);
                            break;
                            }
                        case 6:///����� ������ �� ����������� �������� ����� �������������.
                            {
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            cout<<"\n������� ����� �������������:\n";
                            strcpy(company_search, str_check(23, 0));
                            fflush(stdin);
                            number3 = 1;
                            flagg=0;
                            int z2 = company_output (root);
                            if ( z2 == 0 )
                                cout<<"����� ����������� ���.\n";
                            finish(1);
                            break;
                            }
                        case 7:///����� ������ �� ����������� ��� ������ ��������� �������� ��������.
                            {
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            cout<<"\n������� ������:\n";
                            mileage_search = float_num_check(14);
                            fflush(stdin);
                            number3 = 1;
                            flagg=0;
                            int z3 = mileage_output(root);
                            if ( z3 == 0 )
                                cout<<"����� ����������� ���.\n";
                            finish(1);
                            break;
                            }
                        case 8:///����� ���������������� �� ������ ��������� ������
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            COUNTER = 0;
                            sort_mas(root);
                            number3 = 1;
                            flagg=0;
                            cout<<"\n���������� ���������� �� ������ ���������...\n";
                            header();
                            sort_capacity (no_sort);
                            break;
                        case 9:///����� ���������������� �� ���� ������
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            COUNTER = 0;
                            sort_mas( root );
                            number3 = 1;
                            flagg=0;
                            cout<<"\n���������� ���������� �� ����...\n";
                            header();
                            sort_price (no_sort);
                            break;
                        case 10:///����������
                            if ( empty_check( root ) == NULL)   //�������� �� �������
                                break;
                            header();
                            number3=0;
                            treeprint(root);                    // ������� �������� ������
                            cout<<"\n��������� ������ ��������� �� ���� ����� � ���� [Y/N]?"<<endl;
                            if (yes_no()==1)
                                {
                                ofstream D_INP("data.txt", ios_base::trunc);        //������ ���� � ������� ������
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
                            cout<<"\n�� ������� ��� ������ ��������� ������ ��������� [Y/N]?"<<endl;
                            if (yes_no()==1)
                                {
                                cout<<"\n��������� ��������� ��������� � ���� [Y/N]?"<<endl;
                                if (yes_no()==1)
                                    {
                                    ofstream D_INP("data.txt", ios_base::trunc);    //������ ���� � ������� ������
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

///������ ������ ���������
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

/// ����� ����� ������ (����� � ��������� �����)
int treeprint( struct CBinaryNode *tree )
    {
        if ( tree != NULL )                                     //���� �� ���������� ������ ����
            {
                number3++;
                one_el_print( tree, number3 );
                treeprint ( tree -> left );                     //����������� ������� ������ ������ ���������
                treeprint ( tree -> right );                    //����������� ������� ������ ������� ���������
            }
        return ( number3 );
    }

/// ���������� ����� � ������
struct CBinaryNode *addnode(struct CBinaryNode *ptr, struct CBinaryNode *tree)                                               //������
    {
        if (tree == NULL)                                           // ���� ������ ���, �� ��������� ������
            {
                tree = new CBinaryNode;

                strcpy(tree -> CAR.car_model, ptr -> CAR.car_model);//������� ������
                tree -> CAR.mileage = ptr -> CAR.mileage;
                strcpy(tree -> CAR.company, ptr -> CAR.company);
                tree -> CAR.year = ptr -> CAR.year;
                tree -> CAR.engine_capacity = ptr -> CAR.engine_capacity;
                tree -> CAR.price = ptr -> CAR.price;
                            number++;
                tree->left = NULL;
                tree->right = NULL;                                 //����� �������������� ��������
                tree->parent = current;                             //�������� ��������� �� ��������
            }

        else
        {
            if ( ptr -> CAR.price < tree -> CAR.price )             //���� ���� ������ ���������, ������ �����
            {
                    current = tree;
                    tree -> left = addnode ( ptr, tree->left );     //���������� ��������� �������
            }
            else if ( ptr -> CAR.price > tree -> CAR.price )        //����� ������ ������
                {
                    current = tree;
                    tree -> right = addnode ( ptr, tree->right );   //���������� ��������� �������
                }
            else                                                    //( ptr -> CAR.price = tree -> CAR.price ) ���� ����� - ���������� ������� ������
                {
                    current = tree;
                    tree -> right = addnode ( ptr, tree->right );   //���������� ��������� �������
                }
        };
            return(tree);
    }

///��������
struct CBinaryNode *del_elem (struct CBinaryNode *tree, struct CBinaryNode *del_elem )
{
        struct CBinaryNode *p = del_elem->parent;                           //��-�� �� �������� ���������� ��������
        if ( (del_elem->left == NULL) && (del_elem->right == NULL) )        // ������ ������: ������� ����
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
        else if ( del_elem->left == NULL || del_elem->right == NULL )    // ������ ������: ��������� ������� ����� ������ �������
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
        else                                                            //������ ������: ��������, ��� 2 ����
            {
            struct CBinaryNode *first_right = del_elem->right;          //���������� �� ������ ������� �� ����������
            struct CBinaryNode *change = NULL;                          //��� ������ �������� ���� ������� ���� ���������� ��������
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

///�������� �����
struct CBinaryNode *root_del (struct CBinaryNode *del_elem)
    {
        number--;
        struct CBinaryNode *zamena = NULL;                                  //��� ������ �������� ���� ������� ���� ���������� ��������
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
                    zamena = del_elem->right;                               //��������� �� ������ ������� �� ����������
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
        else                                                //������ ���� ��� 2 ����
            {
            if ( del_elem->right->left == NULL )
                {
                zamena = del_elem->right;                   //��-�� �� ������ ������� �� ����������
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

///������������� ������
struct CBinaryNode *correct (struct CBinaryNode *tree)
    {
          do
          {
            cout<<"������� �������� ������� ������� ������ �� ���������\n"
               <<"|1| ������\n"
               <<"|2| ������\n"
               <<"|3| �����\n"
               <<"|4| ���\n"
               <<"|5| ����� ���������\n"
               <<"|6| ����\n"
               <<"|7| ���\n"
               <<"|0| ��������� ������������� ������� ��������"<<endl;
            x2=num_check(N);
            switch (x2)
            {
                case 1:
                    {
                    cout<<"������� ����� ������: "<<endl;
                    strcpy(tree -> CAR.car_model, str_check(20, 1));
                    fflush(stdin);  //������ ������
                    break;
                    }
                case 2:
                    {
                    cout<<"������� ����� ������ (� ��):"<<endl;
                    tree -> CAR.mileage = float_num_check(14);
                    fflush(stdin);
                    break;
                    }
                case 3:
                    {
                    cout<<"������� ����� ����� �������������:"<<endl;
                    strcpy(tree -> CAR.company, str_check(23, 0));
                    fflush(stdin);
                    break;
                    }
                case 4:
                    {
                    cout<<"������� ����� ��� �������:"<<endl;
                    tree -> CAR.year = num_check(10);
                    fflush(stdin);
                    break;
                    }
                case 5:
                    {
                    cout<<"������� ����� ����� ��������� (�� ����������) :"<<endl;
                    tree -> CAR.engine_capacity = num_check(20);
                    fflush(stdin);
                    break;
                    }
                case 6:
                    {
                    cout<<"������� ����� ���� ($):"<<endl;
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

///����������
void save(struct CBinaryNode *tree)
{
    ofstream D_INP("data.txt", ios_base::app);              //������� ������ � �����
    ofstream T_INP("Table.txt", ios_base::app);
    if (flagg==0)                                           //������ ��� - ������� ���������
        {
        T_INP<<setw( 80 ) << right << "������ �����������:\n"
        <<"============================================================================================================================\n"
        <<"|"<<setw( 4 )  << left <<"�"
        <<"|"<<setw( 20 ) << left << "������"
        <<"|"<<setw( 14 ) << "������ (��)"
        <<"|"<<setw( 21 ) << "�����"
        <<"|"<<setw( 10 ) << "���"
        <<"|"<<setw( 20 ) << "����� ��������� (��)"
        <<"|"<<setw( 27 ) << "���� ($)"
        <<"|\n"<<"============================================================================================================================"<<endl;
        }
    if ( tree != NULL )   //���� �� ���������� ������ ����
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
        save ( tree -> left );  //����������� ������� ������ ������ ���������
        save ( tree -> right ); //����������� ������� ������ ������� ���������
        }
}

///������� �������� ������� ��� ���������� sorted
struct database *sort_mas( struct CBinaryNode *tree)
    {
        if ( tree != NULL )                                                  // ���� ������ �� ������
            {
                no_sort[COUNTER].mileage = tree->CAR.mileage;
                no_sort[COUNTER].year = tree->CAR.year;
                no_sort[COUNTER].engine_capacity = tree->CAR.engine_capacity;
                no_sort[COUNTER].price = tree->CAR.price;
                strcpy (no_sort[COUNTER].car_model, tree->CAR.car_model);
                strcpy (no_sort[COUNTER].company, tree->CAR.company);
                COUNTER++;
                sort_mas (tree->left);                                      // ���������� �������� ����� �����
                sort_mas (tree->right);                                     // ���������� �������� ������ �����
            }
        return (no_sort);
    }

///���������� �� ���� sorting
void sort_price ( struct database *tree )             //���������� �� ����
    {
        for( i = 0 ; i < COUNTER ; i++ )
            for( j = 0 ; j < COUNTER ; j++ )
                if (  no_sort[i].price < no_sort[j].price)
                    {                                           //������� ��������������� ������ � ������
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
        cout<<"��������� ��������������� ������ � ���� [Y/N]"<<endl;
            if(yes_no()==1)
                {
                ofstream price_sort("saves/price_sort.txt", ios_base::trunc);
                for ( i = 0; i < COUNTER; i++, number3++ )
                                    {
                                        if (i==0)
                                        {
                                         price_sort<<setw( 80 ) << right << "������ �����������:\n"
                                                                 <<"============================================================================================================================\n"
                                                                 <<"|"<<setw( 4 )  << left <<"�"
                                                                 <<"|"<<setw( 20 ) << left << "������"
                                                                 <<"|"<<setw( 14 ) << "������ (��)"
                                                                 <<"|"<<setw( 21 ) << "�����"
                                                                 <<"|"<<setw( 10 ) << "���"
                                                                 <<"|"<<setw( 20 ) << "����� ��������� (��)"
                                                                 <<"|"<<setw( 27 ) << "���� ($)"
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

///���������� �� ������ ���������
void sort_capacity ( struct database *tree )
    {
        for( i = 0 ; i < COUNTER ; i++ )
            for( j = 0 ; j < COUNTER ; j++ )
                if (  no_sort[i].engine_capacity < no_sort[j].engine_capacity)
                    {                                           //������� ��������������� ������ � ������
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
         cout<<"��������� ��������������� ������ � ���� [Y/N]"<<endl;
            if(yes_no()==1)
            {
                ofstream capacity_sort("saves/capacity_sort.txt", ios_base::trunc);
                for ( i = 0; i < COUNTER; i++, number3++ )
                                    {
                                        if (i==0)
                                        {
                                          capacity_sort<<setw( 80 ) << right << "������ �����������:\n"
                                                                 <<"============================================================================================================================\n"
                                                                 <<"|"<<setw( 4 )  << left <<"�"
                                                                 <<"|"<<setw( 20 ) << left << "������"
                                                                 <<"|"<<setw( 14 ) << "������ (��)"
                                                                 <<"|"<<setw( 21 ) << "�����"
                                                                 <<"|"<<setw( 10 ) << "���"
                                                                 <<"|"<<setw( 20 ) << "����� ��������� (��)"
                                                                 <<"|"<<setw( 27 ) << "���� ($)"
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

///����� ������ �� ���������� ������ ��������� ���� �������.
int year_output( struct CBinaryNode *tree)
    {
    if ( tree != NULL )    // ���� ������ �� ������
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
        year_output ( tree -> left );  //����������� ������� ������ ������ ���������
        year_output ( tree -> right ); //����������� ������� ������ ������� ���������
        }
    return ( kolvo );
    }

///����� ������ �� ����������� �������� ����� �������������.
int company_output( struct CBinaryNode *tree)
    {
    if ( tree != NULL )    // ���� ������ �� ������
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
        company_output ( tree -> left );  //����������� ������� ������ ������ ���������
        company_output ( tree -> right ); //����������� ������� ������ ������� ���������
        }
    return ( kolvo );
    }

///����� ������ �� ����������� ��� ������ ��������� �������� ��������.
int mileage_output( struct CBinaryNode *tree)
    {
    if ( tree != NULL )    // ���� ������ �� ������
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
        mileage_output ( tree -> left );  //����������� ������� ������ ������ ���������
        mileage_output ( tree -> right ); //����������� ������� ������ ������� ���������
        }
    return ( kolvo );
    }

///��/���
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

///������� ��� ������
void SetColor (int Text, int Fon)
     {
        SetConsoleTextAttribute(h, (Fon << 4) + Text);
     }

///������ ������
void privet()
    {
    char S[N]={""}; //� S ����� ����������� ������
    ifstream f("input/privet.txt"); //������� ���� ��� ������
    while (!f.eof()) //����� ������ ���������� ���� �� ������ �� ����� �����
        {
        f.getline(S,N); //���������� ���������� ���������� � S
        cout<<S<<endl; //����� ��������� ������ �� �����
        }
    f.close();  //������� �������� ����
}

///��������� ����
void TITUL()
    {
    char S[N]={""}; //� S ����� ����������� ������
    ifstream f("input/titul.txt"); //������� ���� ��� ������
    while (!f.eof()) //����� ������ ���������� ���� �� ������ �� ����� �����
        {
        f.getline(S,N); //���������� ���������� ���������� � S
        cout<<S<<endl; //����� ��������� ������ �� �����
        }
    f.close();  //������� �������� ����
    getch();
    system("cls");      //clearscreen

}

///����
int menu ()
    {
    char S[N]={""}; //� S ����� ����������� ������
    ifstream f("input/menu.txt"); //������� ���� ��� ������
    while (!f.eof()) //����� ������ ���������� ���� �� ������ �� ����� �����
        {
        f.getline(S,N); //���������� ���������� ���������� � S
        cout<<S<<endl; //����� ��������� ������ �� �����
        }
    f.close();  //������� �������� ����
    cout<<"����: "<<endl;
    x=num_check(N);
    return (x);
    }

///����� ������
void errors (int err_x)
    {
        SetColor(12, 15);
        switch (err_x)
         {
         case 1:
                cout<<"\n\t������! ���� �������� �������� ����������. ��������� �������..."<<endl;
                SetColor(0, 15);
                break;
         case 2:
                cout<<"\n\t������! ������ �������� �� ����������. ���������� ��� ���..."<<endl;
                SetColor(0, 15);
                break;
         case 3:
                cout<<"\n\t������! �� ����� ������������ ��������. �������� ����� �� ������������.."<<endl;
                SetColor(0, 15);
                break;
         case 4:
                cout<<"\n\t������! ���� �������� �����, �������� ����������. ��������� �������..."<<endl;
                SetColor(0, 15);
                break;
         case 5:
                cout<<"\n\t������! ���� � ������� ����... ���������� ������ [Y/N]?"<<endl;
                SetColor(0, 15);
                break;
         case 6:
                cout<<"\n\t������� 'Y' - ��� ������������� �������� ��� 'N' - ��� ������. "<<endl;
                SetColor(0, 15);
                break;
         case 7:
                cout<<"\n\t������! ���������� ������� ����."<<endl;
                SetColor(0, 15);
                break;
         case 8:
                cout<<"\n\t������! �� ����� ������� ������� ��������."<<endl;
                SetColor(0, 15);
                break;
         case 9:
                cout<<"����-��� ���� �� ��� ������ �� ���� �������"<<endl;
                SetColor(0, 15);
                break;
         }
    }

///���������
void header()
    {
                     cout<<setw( 80 ) << right << "������ �����������:\n"
                         <<"============================================================================================================================\n"
                         <<"|"<<setw( 4 )  << left <<"�"
                         <<"|"<<setw( 20 ) << left << "������"
                         <<"|"<<setw( 14 ) << "������ (��)"
                         <<"|"<<setw( 21 ) << "�����"
                         <<"|"<<setw( 10 ) << "���"
                         <<"|"<<setw( 20 ) << "����� ��������� (��)"
                         <<"|"<<setw( 27 ) << "���� ($)"
                         <<"|\n"<<"============================================================================================================================"<<endl;
    }

///������� ���������� ������� �����
void finish (int succ_x)
    {
        SetColor(10, 15);
        switch (succ_x)
          {
         case 1:
                SetColor(0, 15);
                break;
         case 2:
                cout<<"\n\t������� ������� ��������..."<<endl;
                SetColor(0, 15);
                break;
         case 3:
                cout<<"\n\t������ �� ���� ������� �������.."<<endl;
                SetColor(0, 15);
                break;
         case 4:
                cout<<"\n\t������ �� ���� ������� ��������.."<<endl;
                SetColor(0, 15);
                break;
         case 5:
                cout<<"\n\t������ ������� ���������.."<<endl;
                SetColor(0, 15);
                break;
         case 0:
                cout<<"\n\t������� �� ������������� ���������! �� ��������!"<<endl;
                SetColor(0, 15);
                exit(0);
          }
        cout<<"������� ����� ������� ��� �����������..."<<endl;
        getch();
        system ("cls");
    }

///��� �������� ������� � ������ ���������
struct CBinaryNode *empty_check ( struct CBinaryNode *tree )
    {
        if ( tree == NULL )
            {
            errors(9);
            finish(1);
            return NULL;
            }
    }

/*����� ������� ���������� �� ������ ������� ������� - ������� ��� ������� ���������� �� ���� - � ��������� �������� ������� ������� ��� ����� �������� ��� � ������� ������������ (���� ����� �������� ������� ��������, ������������� � ������*/ ///�� ��������

///������ �� ������
struct CBinaryNode *TREE_scrl ( struct CBinaryNode *tree, int del_number )
    {
        if ( tree != NULL  )                                                //���� �� ���������� ������ ����
            {
                if ( del_number == COUNTER )
                    PTR = tree;
                COUNTER++;
                TREE_scrl ( tree -> left, del_number );                     //����������� ������� ������ ������ ���������
                TREE_scrl ( tree -> right, del_number );                    //����������� ������� ������ ������� ���������
        }
        return ( PTR );
    }


///�������� - int
int num_check (int razmer)
    {
    int bk;  //���������� ��������
    char znach[N];
    int err=0;
    do
        {
        memset(znach,'\0', sizeof (znach)); //���������� ���� ������ ������
        err=0;
        cin.getline(znach, 256);
        fflush(stdin);                      //������ ������ �����
        if ((strlen(znach)) > razmer)       //�������� �����
            {
            errors(8);
            err = 1;
            }
        if (err==0)                         //�������� �� �����
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

///�������� - float
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
        fflush(stdin);                  //������ ������
        if ((znach.length() > razmer2)) //�������� �����
            {
            errors(8);
            err = 1;
            }
        if (err==0)                     //����� �������
            {
            for ( i = 0 ; i < znach.length() ; i++ )
                if  ( (znach [i] == ',') || (znach [i] == '.') )
                    {
                    znach [i] = ',';
                    ser = i;
                    }
            if ( ser != 0 )             //�������� �� �����
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


///�������� - ������
char *str_check (int razmer3, int if_integer)
{
    char str[N];
    char *PTR = str;
    int err=0;
    if (if_integer==0)
    {
        do
        {
        memset(str,'\0', sizeof (str)); //���������� ���� ������ ������
        cin.getline(str, N);
        fflush(stdin);                  //������ ������
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

///���� ������
struct CBinaryNode *input ( struct CBinaryNode *tree )
    {

                            cout<<"������� ������: "<<endl;
                            strcpy(tree -> CAR.car_model, str_check(20, 1));
                            fflush(stdin);  //������ ������
                            cout<<"������� ������ (� ��):"<<endl;
                            tree -> CAR.mileage = float_num_check(14);
                            fflush(stdin);
                            cout<<"������� ����� �������������:"<<endl;
                            strcpy(tree -> CAR.company, str_check(23, 0));
                            fflush(stdin);
                            cout<<"������� ��� �������:"<<endl;
                            tree -> CAR.year = num_check(10);
                            fflush(stdin);
                            cout<<"������� ����� ��������� (�� ����������) :"<<endl;
                            tree -> CAR.engine_capacity = num_check(20);
                            fflush(stdin);
                            cout<<"������� ���� ($):"<<endl;
                            tree -> CAR.price = float_num_check(27);
                            fflush(stdin);
        return tree;
    }

///������������ ������ ������
void deltree_mem( struct CBinaryNode *tree)
    {
        if ( tree != NULL )                     // ���� ������ �� ������
            {
            deltree_mem(tree->left);            // ���������� ������� ����� �����
            deltree_mem(tree->right);           // ���������� ������� ������ �����
            delete (tree);                      // ������� ������
            }
    }



///Highlighted menu
#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include<string.h>
#define EXTENDED -32
#define Enter 13
#define ESC 27
#define TAB 9
#define Up 72
#define Home 71
#define Down 80
#define End 79
using namespace std;
void gotoxy( int column, int row )
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
struct Employee
{
    int SSN;
    char name[20];
    int age;
    float salary;
    float commission;
    float deduction;
    float netsalary ;
    int isdeleted;
};
void selectionSort(Employee *arr, int _size)
{
    for (int i = 0; i < ( _size- 1); ++i)
    {
        int _min = i;
        for (int j = i + 1; j < _size; ++j)
        {
            if (arr[j].SSN < arr[_min].SSN)
            {
                _min= j;
            }
        }
        if (_min != i)
        {
            Employee temp = arr[i];
            arr[i] = arr[_min];
            arr[_min] = temp;
        }
    }
}
void bubbleSort(Employee *employees, int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (employees[j].SSN > employees[j + 1].SSN)
            {
                int temp=employees[j + 1].SSN;
                employees[j + 1].SSN=employees[j].SSN;
                employees[j].SSN=temp;
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
void insertionSort(Employee *employees, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = employees[i].SSN;
        int j = i - 1;
        while (j >= 0 && employees[j].SSN > key)
        {
            employees[j + 1].SSN = employees[j].SSN;
            j = j - 1;
        }
        employees[j + 1].SSN = key;
    }
}
void merge(Employee *employees, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = employees[l + i].SSN;
    for (j = 0; j < n2; j++)
        R[j] =employees[m + 1 + j].SSN;
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            employees[k].SSN = L[i];
            i++;
        }
        else
        {
            employees[k].SSN = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        employees[k].SSN = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        employees[k].SSN = R[j];
        j++;
        k++;
    }
}
void mergeSort(Employee *employees, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(employees, l, m);
        mergeSort(employees, m + 1, r);

        merge(employees, l, m, r);
    }
}
int binarySearch(Employee *employees,int low, int high, int x)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (employees[mid].SSN == x)
            return mid;
        if (employees[mid].SSN < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
int linearSearch(Employee *employees, int N, int x)
{
    for (int i = 0; i < N; i++)
        if (employees[i].SSN == x)
            return i;
    return -1;
}

void print(Employee *employees)
{
    for (int i = 0; i < 5; i++)
    {
        if(employees[i].SSN!=0 && employees[i].isdeleted==0)
        {
            cout<<"Employee "<<i+1;
            cout<<"\n----------\n";
            cout<<"SSN      :"<<employees[i].SSN<<endl;
            cout<<"Name      :"<<employees[i].name<<endl;
            cout<<"Age       :"<<employees[i].age<<endl;
            cout<<"Salary    :"<<employees[i].salary<<endl;
            cout<<"Commission:"<<employees[i].commission<<endl;
            cout<<"Deduction :"<<employees[i].deduction<<endl;
            cout<<"Net salary:"<<employees[i].netsalary<<endl;
            cout<<endl<<"------------------------------------------"<<endl;
        }
    }
}

int main()
{
    char menu[8][30]= {"Add new Employee","Display All Employees",
                       "Sort Employee","Search for an Employee","Delete All Employees","Exit"
                      };
    int cursor=0;
    int flag=555;
    char ch;
    int index;
    int ssn_exist=0;
    int temp;
    int ssn_delete;
    int numOfSort;
    int numOfSearch;
    int SearhedSSN;
    struct Employee employees[5]= {0};

    do
    {
        //clear screen
        system("cls");
        for (int i = 0; i < 8; i++)
        {
            if(i==cursor)
            {
                textattr(4);   //R
            }
            else
            {
                textattr(7);   //W
            }
            gotoxy(15,15+i);
            cout<<menu[i];
        }
        //
        ch=_getch();  //Enter
        switch(ch)
        {
        case EXTENDED:
            ch=getch();
            switch(ch)
            {
            case Up:
                cursor--;
                if(cursor<0)
                {
                    cursor=7;
                }
                break;
            case Down:
                cursor++;
                if(cursor>7)
                {
                    cursor=0;
                }
                break;
            case Home:
                cursor=0;
                break;
            case End:
                cursor=7;
                break;
            }
            break;
        case Enter:
            switch(cursor)
            {
            case 0:
                system("cls");
                cout<<"choose index from 0 to 4 : ";
                cin>>index;
                if (index<0 || index>9 || employees[index].SSN!=0)
                {
                    cout<<"invalid index , press any key to continue...";
                    getch();
                }

                else
                {
                    system("cls");

                    do
                    {
                        system("cls");
                        ssn_exist = 0;
                        cout<<"Please enter data from employee "<<index;
                        gotoxy(5,5);
                        cout<<"SSN : ";
                        gotoxy(55,5);
                        cout<<"Name : ";
                        _flushall();
                        gotoxy(5,10);
                        cout<<"Age : ";
                        gotoxy(55,10);
                        cout<<"Salary : ";
                        gotoxy(5,15);
                        cout<<"Commission : ";
                        gotoxy(55,15);
                        cout<<"Deduction : ";

                        gotoxy(10,5);
                        cin>>temp;

                        for(int i=0; i<10; i++)
                        {
                            if(employees[i].SSN==temp)

                            {
                                ssn_exist=1;
                                system("cls");
                                cout<<"this employee already exist!!,Please enter a unique SSN";
                                getch();
                                break;

                            }

                        }
                        if(ssn_exist==0)
                        {
                            employees[index].SSN=temp;
                        }

                    }
                    while(ssn_exist==1);

                    gotoxy(61,5);
                    cin>>employees[index].name;
                    gotoxy(10,10);
                    cin>>employees[index].age;
                    gotoxy(63,10);
                    cin>>employees[index].salary;
                    gotoxy(18,15);
                    cin>>employees[index].commission;
                    gotoxy(69,15);
                    cin>>employees[index].deduction;
                    system("cls");
                    employees[index].netsalary=employees[index].salary+employees[index].commission-employees[index].deduction;                //wait to see
                    getch();
                }
                break;
            case 1:
                system("cls");
                print(employees);
                getch();
                break;
            case 2:
                system("cls");
                cout<<"1-Selection sort"<<endl;
                cout<<"2-Bubble sort"<<endl;
                cout<<"3-Insertion sort"<<endl;
                cout<<"4-Merge sort"<<endl<<endl;
                cout<<"Choose Sort Algorithm 1 , 2 , 3 or 4: "<<endl;
                cin>>numOfSort;
                system("cls");
                if(numOfSort==1)
                {
                    selectionSort(employees,5);
                }
                if(numOfSort==2)
                {
                    bubbleSort(employees,5);
                }
                if(numOfSort==3)
                {
                    insertionSort(employees,5);
                }
                if(numOfSort==4)
                {
                    mergeSort(employees,0,4);
                }
                print(employees);
                getch();
                break;
            case 3:
                system("cls");
                cout<<"1-Binary Search"<<endl;
                cout<<"2-Linear Search"<<endl<<endl;
                cout<<"Choose Search Algorithm 1 or 2 : "<<endl;
                cin>>numOfSearch;
                system("cls");
                int result;
                if(numOfSearch==1)
                {
                    cout<<"Enter the Employee's SSN "<<endl;
                    cin>>SearhedSSN;
                    result=binarySearch(employees,0,4,SearhedSSN);
                    if(result == -1) cout << "Employee is not found in array";
                    else
                    {
                        cout <<"Employee is found in array"<<endl;
                        cout<<"Employee "<<endl;
                        cout<<"\n----------\n";
                        cout<<"SSN      :"<<employees[result].SSN<<endl;
                        cout<<"Name      :"<<employees[result].name<<endl;
                        cout<<"Age       :"<<employees[result].age<<endl;
                        cout<<"Salary    :"<<employees[result].salary<<endl;
                        cout<<"Commission:"<<employees[result].commission<<endl;
                        cout<<"Deduction :"<<employees[result].deduction<<endl;
                        cout<<"Net salary:"<<employees[result].netsalary<<endl;
                        cout<<endl<<"------------------------------------------"<<endl;
                    }
                }
                if(numOfSearch==2){
                    result=linearSearch(employees,5,12);
                     if(result == -1) cout << "Employee is not found in array";
                      else
                    {
                        cout << "Employee is found in array"<<endl;
                        cout<<"Employee "<<endl;
                        cout<<"\n----------\n";
                        cout<<"SSN      :"<<employees[result].SSN<<endl;
                        cout<<"Name      :"<<employees[result].name<<endl;
                        cout<<"Age       :"<<employees[result].age<<endl;
                        cout<<"Salary    :"<<employees[result].salary<<endl;
                        cout<<"Commission:"<<employees[result].commission<<endl;
                        cout<<"Deduction :"<<employees[result].deduction<<endl;
                        cout<<"Net salary:"<<employees[result].netsalary<<endl;
                        cout<<endl<<"------------------------------------------"<<endl;
                    }
                }
                getch();
                break;

            case 4:
                for(int i=0; i<5; i++)
                {
                    employees[i].SSN=0;
                    strcpy(employees[i].name,"Empty");
                    employees[i].age=0;
                    employees[i].commission=0;
                    employees[i].deduction=0;
                    employees[i].netsalary=0;

                }
                system("cls");
                printf("all employees are deleted !!");
                getch();
                break;
            case 5:

                flag=0;
                break;
            }
            break;
        case ESC:
            flag=0;
            break;
        case TAB:
            cursor++;
            if(cursor>7)
            {
                cursor=0;
            }
            break;
        }

    }
    while(flag==555);


    return 0;
}

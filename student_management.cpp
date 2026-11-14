
#include <bits/stdc++.h>
using namespace std;
const int SUBJECTS = 5;
const int PASS_MARK = 40;
const string FILE_NAME = "students.txt";
string sub[SUBJECTS] = {"Subject 1","Subject 2","Subject 3","Subject 4","Subject 5"};

struct Student
{
    int rollNo;
    string name;
    int marks[SUBJECTS];
};

int totalMarks(Student &s)
{
    int sum = 0;

    for(int i=0;i<SUBJECTS;i++)
    {
        sum += s.marks[i];
    }

    return sum;
}

double average(Student &s)
{
    return (double)totalMarks(s)/SUBJECTS;
}

char grade(Student &s)
{
    double avg = average(s);

    if(avg>=90) return 'O';
    if(avg>=80) return 'A';
    if(avg>=70) return 'B';
    if(avg>=60) return 'C';
    if(avg>=50) return 'D';

    return 'F';
}

bool hasPassed(Student &s)
{
    for(int i=0;i<SUBJECTS;i++)
    {
        if(s.marks[i]<PASS_MARK)
        {
            return false;
        }
    }

    return true;
}

int readInt(string msg,int low,int high)
{
    int x;

    while(true)
    {
        cout<<msg;

        if(cin>>x && x>=low && x<=high)
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return x;
        }

        cout<<"Invalid input!\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

string readName(string msg)
{
    string name;

    do
    {
        cout<<msg;
        getline(cin,name);
    }
    while(name.empty());

    for(int i=0;i<name.size();i++)
    {
        if(name[i]==' ')
        {
            name[i]='_';
        }
    }

    return name;
}

string toLower(string s)
{
    for(int i=0;i<s.size();i++)
    {
        s[i] = tolower((unsigned char)s[i]);
    }

    return s;
}

int findIndex(vector<Student> &v,int roll)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i].rollNo==roll)
        {
            return i;
        }
    }

    return -1;
}

string displayName(string name)
{
    for(int i=0;i<name.size();i++)
    {
        if(name[i]=='_')
        {
            name[i]=' ';
        }
    }

    return name;
}

void saveToFile(vector<Student> &v)
{
    ofstream fout(FILE_NAME);

    for(int i=0;i<v.size();i++)
    {
        fout<<v[i].rollNo<<" "<<v[i].name;

        for(int j=0;j<SUBJECTS;j++)
        {
            fout<<" "<<v[i].marks[j];
        }

        fout<<"\n";
    }

    fout.close();
}

void loadFromFile(vector<Student> &v)
{
    ifstream fin(FILE_NAME);

    Student s;

    while(fin>>s.rollNo>>s.name)
    {
        bool valid = true;

        for(int i=0;i<SUBJECTS;i++)
        {
            if(!(fin>>s.marks[i]))
            {
                valid = false;
                break;
            }
        }

        if(valid)
        {
            v.push_back(s);
        }
        else
        {
            break;
        }
    }

    fin.close();
}

void printHeader(bool rank = false)
{
    if(rank)
    {
        cout<<left<<setw(6)<<"Rank";
    }

    cout<<left<<setw(8)<<"Roll"
        <<setw(20)<<"Name"
        <<setw(8)<<"Total"
        <<setw(10)<<"Average"
        <<setw(7)<<"Grade"
        <<"Result\n";

    cout<<string(rank?65:59,'-')<<"\n";
}

void printRow(Student &s,int rank = 0)
{
    if(rank>0)
    {
        cout<<left<<setw(6)<<rank;
    }

    cout<<left<<setw(8)<<s.rollNo
        <<setw(20)<<displayName(s.name)
        <<setw(8)<<totalMarks(s)
        <<setw(10)<<fixed<<setprecision(2)<<average(s)
        <<setw(7)<<grade(s)
        <<(hasPassed(s)?"PASS":"FAIL")<<"\n";
}

void readMarks(Student &s)
{
    for(int i=0;i<SUBJECTS;i++)
    {
        s.marks[i] = readInt("Marks in "+sub[i]+": ",0,100);
    }
}

void addStudent(vector<Student> &v)
{
    Student s;

    s.rollNo = readInt("Roll number: ",1,999999);

    if(findIndex(v,s.rollNo)!=-1)
    {
        cout<<"Roll number already exists!\n";
        return;
    }

    s.name = readName("Name: ");

    readMarks(s);

    v.push_back(s);

    saveToFile(v);

    cout<<"Record added successfully!\n";
}

void viewAll(vector<Student> &v)
{
    if(v.empty())
    {
        cout<<"No records found!\n";
        return;
    }

    printHeader();

    for(int i=0;i<v.size();i++)
    {
        printRow(v[i]);
    }
}

void viewOne(vector<Student> &v)
{
    int roll = readInt("Enter roll number: ",1,999999);

    int idx = findIndex(v,roll);

    if(idx==-1)
    {
        cout<<"Record not found!\n";
        return;
    }

    Student s = v[idx];

    cout<<"\n--------- Report Card ---------\n";

    cout<<"Roll No : "<<s.rollNo<<"\n";
    cout<<"Name    : "<<displayName(s.name)<<"\n";

    for(int i=0;i<SUBJECTS;i++)
    {
        cout<<left<<setw(10)<<sub[i]<<": "<<s.marks[i];

        if(s.marks[i]<PASS_MARK)
        {
            cout<<" (Below pass mark)";
        }

        cout<<"\n";
    }

    cout<<"Total   : "<<totalMarks(s)<<"\n";
    cout<<"Average : "<<fixed<<setprecision(2)<<average(s)<<"\n";
    cout<<"Grade   : "<<grade(s)<<"\n";
    cout<<"Result  : "<<(hasPassed(s)?"PASS":"FAIL")<<"\n";
}

void updateStudent(vector<Student> &v)
{
    int roll = readInt("Enter roll number: ",1,999999);

    int idx = findIndex(v,roll);

    if(idx==-1)
    {
        cout<<"Record not found!\n";
        return;
    }

    cout<<"Updating student details...\n";

    v[idx].name = readName("New name: ");

    readMarks(v[idx]);

    saveToFile(v);

    cout<<"Record updated successfully!\n";
}

void deleteStudent(vector<Student> &v)
{
    int roll = readInt("Enter roll number: ",1,999999);

    int idx = findIndex(v,roll);

    if(idx==-1)
    {
        cout<<"Record not found!\n";
        return;
    }

    cout<<"Delete "<<displayName(v[idx].name)<<"?\n";

    int confirm = readInt("1 - Yes, 0 - No: ",0,1);

    if(confirm==1)
    {
        v.erase(v.begin()+idx);

        saveToFile(v);

        cout<<"Record deleted!\n";
    }
    else
    {
        cout<<"Delete cancelled!\n";
    }
}

void searchByName(vector<Student> &v)
{
    string key;

    cout<<"Enter name: ";
    getline(cin,key);

    key = toLower(key);

    for(int i=0;i<key.size();i++)
    {
        if(key[i]==' ')
        {
            key[i]='_';
        }
    }

    bool found = false;

    for(int i=0;i<v.size();i++)
    {
        if(toLower(v[i].name).find(key)!=string::npos)
        {
            if(!found)
            {
                printHeader();
            }

            printRow(v[i]);

            found = true;
        }
    }

    if(!found)
    {
        cout<<"No matching students!\n";
    }
}

void showRankList(vector<Student> &v)
{
    if(v.empty())
    {
        cout<<"No records found!\n";
        return;
    }

    vector<Student> temp = v;

    sort(temp.begin(),temp.end(),[](Student &a,Student &b)
    {
        return totalMarks(a)>totalMarks(b);
    });

    printHeader(true);

    int rank = 1;

    for(int i=0;i<temp.size();i++)
    {
        if(i>0 && totalMarks(temp[i])<totalMarks(temp[i-1]))
        {
            rank = i+1;
        }

        printRow(temp[i],rank);
    }
}

void showStatistics(vector<Student> &v)
{
    if(v.empty())
    {
        cout<<"No records found!\n";
        return;
    }

    int n = v.size();

    int sum = 0;
    int pass = 0;

    int high = totalMarks(v[0]);
    int low = totalMarks(v[0]);

    int hi = 0;
    int lo = 0;

    int cnt[6] = {0};

    string grades = "OABCDF";

    for(int i=0;i<n;i++)
    {
        int t = totalMarks(v[i]);

        sum += t;

        if(hasPassed(v[i]))
        {
            pass++;
        }

        if(t>high)
        {
            high = t;
            hi = i;
        }

        if(t<low)
        {
            low = t;
            lo = i;
        }

        for(int j=0;j<6;j++)
        {
            if(grade(v[i])==grades[j])
            {
                cnt[j]++;
                break;
            }
        }
    }

    cout<<"\n------ Class Statistics ------\n";

    cout<<"Total students : "<<n<<"\n";

    cout<<"Class average  : "
        <<fixed<<setprecision(2)
        <<(double)sum/(n*SUBJECTS)<<"\n";

    cout<<"Highest total  : "<<high
        <<" ("<<displayName(v[hi].name)<<")\n";

    cout<<"Lowest total   : "<<low
        <<" ("<<displayName(v[lo].name)<<")\n";

    cout<<"Passed         : "<<pass<<" / "<<n<<"\n";

    cout<<"Pass percentage: "
        <<(double)pass*100/n<<"%\n";

    cout<<"Grade count    : ";

    for(int i=0;i<6;i++)
    {
        cout<<grades[i]<<"="<<cnt[i]<<"  ";
    }

    cout<<"\n";
}

void showSubjectToppers(vector<Student> &v)
{
    if(v.empty())
    {
        cout<<"No records found!\n";
        return;
    }

    cout<<"\n------ Subject-wise Toppers ------\n";

    for(int i=0;i<SUBJECTS;i++)
    {
        int best = 0;

        for(int j=1;j<v.size();j++)
        {
            if(v[j].marks[i]>v[best].marks[i])
            {
                best = j;
            }
        }

        cout<<left<<setw(10)<<sub[i]<<": "
            <<displayName(v[best].name)
            <<" ("<<v[best].marks[i]<<")\n";
    }
}

int main()
{
    vector<Student> v;

    loadFromFile(v);

    int choice;

    do
    {
        cout<<"\n===== Student Result Management System =====\n";

        cout<<"1. Add student\n";
        cout<<"2. View all students\n";
        cout<<"3. Search by roll number\n";
        cout<<"4. Update student\n";
        cout<<"5. Delete student\n";
        cout<<"6. Search by name\n";
        cout<<"7. Rank list\n";
        cout<<"8. Class statistics\n";
        cout<<"9. Subject-wise toppers\n";
        cout<<"10. Exit\n";

        choice = readInt("Enter your choice: ",1,10);

        switch(choice)
        {
            case 1:
                addStudent(v);
                break;

            case 2:
                viewAll(v);
                break;

            case 3:
                viewOne(v);
                break;

            case 4:
                updateStudent(v);
                break;

            case 5:
                deleteStudent(v);
                break;

            case 6:
                searchByName(v);
                break;

            case 7:
                showRankList(v);
                break;

            case 8:
                showStatistics(v);
                break;

            case 9:
                showSubjectToppers(v);
                break;

            case 10:
                cout<<"Goodbye!\n";
                break;
        }

    }while(choice!=10);

    return 0;
}

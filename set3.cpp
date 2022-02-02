/*بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيم*/

#include <bits/stdc++.h>
using namespace std;




class Mentor
{
public:
    int class_number;
    string student_name;
    string subjects; //  math, english, bangla
    double avg_marks = 0;
    int Total_days_taught = 0;
    int Total_Earnings = 0;
    Mentor(): avg_marks(0.0), Total_days_taught(0), Total_Earnings(0) {}
    Mentor (int x, string s, string sub, double avg, int days, int Earnings) : class_number(x), student_name(s), subjects(sub), avg_marks(avg), Total_days_taught(days), Total_Earnings(Earnings) {}

};

class Calculation : public Mentor
{
public:
    vector<Mentor> info;
    const int sz = 3;
    vector<int> individual_days_each_class = vector<int>(sz);//8,9,10
    vector<int> individual_earning_each_class = vector<int>(sz);//8,9,10
    vector<int> individual_earning_each_subject = vector<int>(sz);//math,english,bangla

    map<int, string> mp_str;
    void init()
    {
        mp_str[0] = "Math";
        mp_str[1] = "English";
        mp_str[2] = "Bangla";
    }

    void set_Total_days_taught(int id, int x, int class_number)
    {
        info[id].Total_days_taught += x;

        string str = info[id].subjects;
        for (int i = 0; i < (int)str.size(); i++)
        {
            if (str[i] == '1')
            {
                individual_earning_each_subject[i] += x;
                individual_earning_each_class[class_number - 8] += x;
                info[id].Total_Earnings += x;
            }
        }
    }

    void showing_details(int id)
    {
        cout << "Name : " << info[id].student_name << "\n";
        cout << "Class :" << info[id].class_number << "\n";
        cout << "Subjects : ";
        for (int i = 0; i < 3; i++)
        {
            if (info[id].subjects[i] == '1')
            {
                cout << "\t" << i + 1 << ". " << mp_str[i] << " ";
            }
        }
        cout << "\n";
        cout << "Average Marks: " << info[id].avg_marks << "\n";
        cout << "Total Days Taught: " << info[id].Total_days_taught << "\n";
        cout << "Total Earnings: " << info[id].Total_Earnings << "\n";
    }
};

// Calculation misir;

class Functionalities : public Mentor, public Calculation
{
public:

    void print() {
        cout << "\n--------------------------*********************---------------------------------\n\n";

    }
    void add_student()
    {
        while (true)
        {
            print();
            cout << "Enter Class name (8,9 or 10) or Enter 0 for Home: ";
            int class_number;
            cin >> class_number;

            if (class_number != 8 and class_number != 9 and class_number != 10)
            {
                if (class_number == 0) return;
                cout << "Please Input Valid Class.\n";
                // print();
                continue;
            }
            cout << "Student Name: ";
            string name;
            cin >> name;
            cout << "subject list in booleans (Math, English, Bangla input three length 0/1 character.):\n";
            string sub;
            cin >> sub;
            info.push_back(Mentor(class_number, name, sub, 0, 0, 0));
            cout << "Student Added successfully!!\n";
            // print();
        }
    }

    void Edit_Student()
    {

        while (true)
        {
            print();
            cout << "Which Class student you want to Edit (8,9, or 10) or Enter 0 for Home: ";
            int class_number;
            cin >> class_number;

            if (class_number != 8 and class_number != 9 and class_number != 10)
            {
                if (class_number == 0) return;
                cout << "Please Input Valid Class.\n";
                continue;
            }

            // firstly we can show the present how many student are there in that class
            bool flag = false;
            for (int i = 0; i < (int) info.size(); i++)
            {
                if (info[i].class_number != class_number)continue;
                flag = true; break;
            }
            if (!flag)
            {
                cout << "There are no students in this class !!";
                continue;
            }
            while (true) {
                bool flag = false;
                for (int i = 0; i < (int) info.size(); i++)
                {
                    if (info[i].class_number != class_number)continue;
                    if (!flag)
                    {
                        flag = true;
                        cout << "ID\tStudnet Name\tTotal Days\tAvg. Marks\n\n";
                    }
                    cout << i << "\t" << info[i].student_name << "\t\t\t" << info[i].Total_days_taught << "\t" << info[i].avg_marks << "\n";
                }
                cout << "Select the student ID or Select -1 for previous step or -9 for Home\n";
                int student_id;
                cin >> student_id;
                if (student_id == -1)break;
                else if (student_id == -9) return;
                while (true) {
                    print();
                    cout << "Select the Criteria or Select -1 for previous step or 0 for Home\n";
                    cout << "1. Adding days to the number of days taught.\n";
                    cout << "2. Adding marks in exam s/he gets as an integer from 0 to 100\n";// These marks will change the average.
                    int op;
                    cin >> op;
                    if (op == -1)break;
                    else if (op == 0) return;
                    else if (op == 1)
                    {
                        cout << "Enter number of days: ";
                        int x;
                        cin >> x;
                        set_Total_days_taught(student_id, x, class_number);

                        individual_days_each_class[class_number - 8] += x;

                    }
                    else
                    {
                        string str = info[student_id].subjects;
                        while (true) {
                            cout << "Select Subject or Enter -1 for previous step or -9 for Home\n\n";

                            int cnt = 0;
                            for (int i = 0; i < (int)str.size(); i++)
                            {
                                if (str[i] == '1')
                                {
                                    cnt++;
                                    cout << i << ". " << mp_str[i] << "\n";
                                }
                            }
                            int sub_select;
                            cin >> sub_select;
                            if (sub_select == -1)break;
                            else if (sub_select == -9) return;
                            else if (sub_select > 2 or str[sub_select] == '0') {
                                cout << "Plase! select Valid Subject number\n";
                                continue;
                            }
                            cout << "Enter " << mp_str[sub_select] << "  Marks: (0 - 100): ";
                            double marks;
                            cin >> marks;

                            // here we assume a student will exam a subject only once
                            double tot = info[student_id].avg_marks * cnt * 1.0;
                            tot += marks;
                            info[student_id].avg_marks = (1.0 * tot) / (1.0 * cnt);
                        }
                    }
                }
            }
        }
    }

    void Delete_student()
    {
        while (true)
        {
            print();
            cout << "Which Class student you want to Delete (8,9, or 10) or Enter 0 for Home: ";
            int class_number;
            cin >> class_number;
            if (class_number != 8 and class_number != 9 and class_number != 10)
            {
                if (class_number == 0) return;
                cout << "Please Input Valid Class.\n";
                continue;
            }

            // firstly we can show the present how many student are there in that class (ID & student Name)
            bool flag = false;
            for (int i = 0; i < (int) info.size(); i++)
            {
                if (info[i].class_number != class_number)continue;
                if (!flag)
                {
                    flag = true;
                    cout << "ID\t\tStudnet Name\n\n";
                }
                cout << i << "\t" << info[i].student_name << "\n";
            }
            if (!flag)
            {
                cout << "There are no students in this class !!!\n";
                continue;
            }
            while (true) {
                cout << "Select the student ID or Enter -1 for previous step or -9 for Home ";
                int student_id;
                cin >> student_id;
                if (student_id == -1)break;
                else if (student_id == -9)return;
                if (student_id >= (int)info.size() or student_id < 0) {
                    cout << "Please Select Valid student ID\n";
                    continue;
                }
                info.erase(info.begin() + student_id);
            }
            /*
            When a student is deleted, it will not show in the list but
            the earnings added because of him/her will still be there in
            total earning.
            */
        }
    }

    void Show()
    {
        while (true)
        {
            print();
            cout << "1. specific class Details\n";
            cout << "2. Individual Details\n";
            cout << "OR -1 for previous step OR 0 for Home\n\n";
            int op;
            cin >> op;
            if (op == -1)break;
            else if (op == 0) return;
            if (op == 1)
            {
                cout << "Select Secific Class Number (8,9 or 10): ";
                int cls_no;
                cin >> cls_no;
                // showing specific class history


                bool flag = false;
                for (int i = 0; i < (int) info.size(); i++)
                {
                    if (info[i].class_number != cls_no)continue;
                    if (!flag)
                    {
                        flag = true;
                        cout << "ID\tName\tTotal Earnings\tAverage Marks\n\n";
                    }
                    cout << i << "\t" << info[i].student_name << "\t\t" << info[i].Total_Earnings << "\t" << info[i].avg_marks << "\n";
                }
                if (!flag)
                {
                    cout << "There are no students in this class !!";
                    return;
                }
            }
            else if (op == 2)
            {
                // firstly we can show the present how many student are there in that class (ID & student Name)
                cout << "ID\tName\tClass\n\n";
                for (int i = 0; i < (int)info.size(); i++)
                {
                    cout << i << "\t" << info[i].student_name << "\t\t" << info[i].class_number << "\n";
                }
                cout << "Select the student ID: ";
                int student_id;
                cin >> student_id;
                /// showing these student details:
                showing_details(student_id);
            }
            else return;
        }
    }

    void Overall()
    {
        while (true)
        {
            print();
            cout << "1. The total days taught across all classes\n";
            cout << "2. Individual days taught in each class\n";
            cout << "3. Total earnings\n";
            cout << "4. Individual earnings of each class\n";
            cout << "5. Individual earnings of each subject\n";
            cout << "6. Average marks of all students\n";
            cout << "0. HOME\n\n";
            int op;
            cin >> op;
            if (op == 1)
            {
                int Total_days = 0;
                for (int i = 0; i < 3; i++)
                {
                    Total_days += individual_days_each_class[i];
                }
                cout << "Total Days: " << Total_days << "\n";
            }
            else if (op == 2)
            {
                cout << "Class\tNo. of Days\n\n";
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 8 << "\t" << individual_days_each_class[i] << "\n";
                }
            }
            else if (op == 3)
            {
                int Total_Earnings = 0;
                for (int i = 0; i < 3; i++)
                {
                    Total_Earnings += individual_earning_each_class[i];
                }
                cout << "TOTAL EARNINGS: " << Total_Earnings << "\n";
            }
            else if (op == 4)
            {
                cout << "Class\tEarnings\n\n";
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 8 << "\t" << individual_earning_each_class[i] << "\n";
                }
            }
            else if (op == 5)
            {
                cout << "Subjects\tTotal Earnings\n\n";
                for (int i = 0; i < 3; i++)
                {
                    cout << mp_str[i] << "\t" << individual_earning_each_subject[i] << "\n";
                }
            }
            else if (op == 6)
            {
                cout << "AVG. MARKS OF ALL STUDENTS:  ";
                double avg = 0;
                int cnt = 0;
                for (int i = 0; i < (int) info.size(); i++)
                {
                    int tt = 0;
                    string str = info[i].subjects;
                    for (int j = 0; j < 3; j++) tt += (str[j] == '1');
                    avg += info[i].avg_marks * 1.0 * tt;
                    cnt += tt;
                }
                avg = (1.0 * avg) / (1.0 * cnt);
                cout << avg << "\n";
            }
            else return;
        }
    }
};




int main()
{
    //misir.init();

    Functionalities obj;
    obj.init();
    while (true)
    {
        //system("cls");
         system("clear");
        obj.print();
        cout << "\tHOME PAGE\n\n";
        cout << "1. Add a stdent\n";
        cout << "2. Edit a stdent\n";
        cout << "3. Delete a stdent\n";
        cout << "4. See the list of students individually\n";
        cout << "5. See overall info\n";
        cout << "Q/q. quit\n";
        int ty;
        cin >> ty;
        if (ty == 1)  // add student
        {
            obj.add_student();
        }
        else if (ty == 2)   // edit student
        {

            obj.Edit_Student();
        }
        else if (ty == 3)  // delete student
        {
            obj.Delete_student();
        }
        else if (ty == 4)   //See the list of students individually
        {
            obj.Show();
        }
        else if (ty == 5)  //See overall info
        {
            obj.Overall();
        }
        else exit(0);
    }
}

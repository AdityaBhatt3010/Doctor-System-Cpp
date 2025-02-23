#include <iostream>
#include <iomanip>
using namespace std;

// Templated function to display information about various objects
template <typename T>
void displayInfo(const T& obj) {
    cout << setw(15) << left << "Object Info:" << obj << endl;
}

class VirtualBase {
public:
    virtual void virtualFunction() const = 0; // Declare a pure virtual function
};

class doctor : public VirtualBase { // Inherit from VirtualBase
public:
    int id;
    string name;

    doctor()//default constructor
    {
        id = 0;
        name = "abc";
    }

    ~doctor()
    {
        cout << " " << endl;
    }

    void displayinfo()
    {
        cout << "Enter name:";
        cin >> name;
        cout << "Welcome Dr. " << name << endl;
    }

    inline void displayID()
    {
        cout << "Doctor ID: " << id << endl;
    }

    static void staticFunction()
    {
        cout << "This is a static member function." << endl;
    }

    bool operator==(const doctor& other) const {
        return (id == other.id);
    }

    void virtualFunction() const override { // Implement the pure virtual function
        cout << "This is a virtual function in doctor class." << endl;
    }
};

template <typename T>
void displayDoctorInfo(const T& d)
{
    cout << setw(15) << left << "Doctor ID:" << d.id << endl;
    cout << setw(15) << left << "Doctor Name:" << d.name << endl;
}

class Cardio : public doctor
{
protected:
    int numpatient;
    int timings;
    char day;

public:
    Cardio(int numpatient, int timings, char day)//paramatrized constructor
    {
        this->numpatient = numpatient;//this keyword
        this->timings = timings;
        this->day = day;
    }

    void displayapp()
    {
        cout << "You have 56 appointments for cardio in total" << endl;
        cout << "Enter number of appointments suitable for you today: ";
        cin >> numpatient;
        cout << "Enter your free time slot: ";
        cin >> timings;
        cout << "Enter another free day for remaining patients: "<<endl;
        cin >> day;
    }

    void pateintage()
    {
        float patage;  // Changed the data type to float
        cout << "Hello patient! Enter your age please: " << endl;
        cin >> patage;

        int age = static_cast<int>(patage); // Type cast from float to int

        if (age <= 3)
        {
            cout << "Your toddler must have 98-140 bpm heart beat" << endl;
        }
        else if (age <= 12)
        {
            cout << "Your child must have 75-118 bpm heart beat." << endl;
        }
        else
        {
            cout << "You must have 60-100 bpm heart beat" << endl;
        }

        cout << "If there is not much difference in your heart beat, then your heart is properly working my patient. But if there is an issue, fix a meeting in my portal" << endl;
    }

    void virtualFunction() const override { // Implement the pure virtual function
        cout << "This is a virtual function in Cardio class." << endl;
    }
};

class dentist : public doctor
{
protected:
    int num;
    int nchocolates;

public:
    dentist(int num, int nchocolates)
    {
        this->num = num;
        this->nchocolates = nchocolates;
    }

    dentist(const dentist &d)//copy constructor
    {
        num = d.num;
        nchocolates = d.nchocolates;
    }

    void toothdecay()
    {
        cout << "Enter num of years or time when you had replaced your tooth: ";
        cin >> num;
        cout << "Enter num of chocolates you eat per day: ";
        cin >> nchocolates;
    }

    void virtualFunction() const override { // Implement the pure virtual function
        cout << "This is a virtual function in dentist class." << endl;
    }
};

class Surgeon : public Cardio, public dentist
{
public:
    Surgeon(int numpatient, int timings, char day, int num, int nchocolates)
        : Cardio(numpatient, timings, day), dentist(num, nchocolates) {}

    void performSurgery()
    {
        cout << "Surgery performed!" << endl;
    }

    void virtualFunction() const override { // Implement the pure virtual function
        cout << "This is a virtual function in Surgeon class." << endl;
    }

    void displayinfo()
    {
        Cardio::displayinfo();  // Using Cardio's version of displayinfo
    }

    void toothdecay()
    {
        dentist::toothdecay();  // Using dentist's version of toothdecay
    }
};

int main()
{
    int arraySize;
    cout << "Enter the size of the array: ";
    cin >> arraySize;

    VirtualBase* virtualBaseArray[arraySize]; // Array of pointers to VirtualBase

    int id;
    while (true)
    {
        cout << "Enter id (0 to quit): ";
        cin >> id;

        if (id == 0)
            break;

        if (id <= arraySize && id > 0)
        {
            doctor* d = new doctor();//new
            d->virtualFunction(); // Call virtual function

            virtualBaseArray[id - 1] = d; // Store pointer to VirtualBase
            virtualBaseArray[id - 1]->virtualFunction(); // Call virtual function through pointer

            d->displayinfo();

            int numpatient;
            int timings;
            char day;

            cout << "Enter number of appointments suitable for you today: ";
            cin >> numpatient;
            cout << "Enter your free time slot: ";
            cin >> timings;
            cout << "Enter another free day for remaining patients: ";
            cin >> day;

            Cardio c1(numpatient, timings, day);

            c1.pateintage();

            // Using the friend function
            displayDoctorInfo(*d);

            // Using the overloaded operator
            doctor d2;
            d2.id = 1;
            d2.name = "xyz";
            if (*d == d2) {
                cout << "Doctors are the same." << endl;
            } else {
                cout << "Doctors are different." << endl;
            }

            delete d; // Clean up dynamically allocated memory
        }
        else if (id == 10)
        {
            Surgeon s(0, 0, 'M', 0, 0);
            s.displayinfo();  
            s.toothdecay();   
            s.pateintage();   
            s.performSurgery(); 

            // Resolving ambiguity: Treating s as a Cardio
            virtualBaseArray[id - 1] = static_cast<Cardio*>(&s); 
            virtualBaseArray[id - 1]->virtualFunction(); // Call virtual function through pointer
        }
        else
        {
            cout << "Enter id from 1 to " << arraySize << " pls";
        }
    }

    for (int i = 0; i < arraySize; ++i) {
        delete virtualBaseArray[i]; // Clean up dynamically allocated memory
    }

    return 0;
}

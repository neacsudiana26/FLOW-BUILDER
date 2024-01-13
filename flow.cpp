#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

class Step
{
private:
    string name;

public:
    virtual ~Step() = default;
    void set_name(string x)
    {
        this->name = x;
    }
    string get_name() const
    {
        return this->name;
    }
    virtual void execute() {}
    virtual void set_param() {}
    virtual string file() {}
};

class TitleStep : public Step
{
private:
    string title, subtitle;

public:
    void set_param() override
    {
        string t, s;
        cout << "Please enter the title: ";
        cin >> t;
        cout << "Please enter the subtitle: ";
        cin >> s;
        title = t;
        subtitle = s;
    }
    void execute() override
    {
        cout << "Step " << get_name() << " has the title: " << title << " and the subtitle: " << subtitle << endl;
        ;
    }
    string file()
    {
        string a = "Step" + get_name() + "has the title " + title + " and subtitle: " + subtitle;
        return a;
    }
};

class TextStep : public Step
{
private:
    string title, copy;

public:
    void set_param() override
    {
        string t, c;
        cout << "Please enter the title of the text: ";
        cin >> t;
        cout << "Please enter the copy: ";
        cin >> c;
        title = t;
        copy = c;
    }
    void execute() override
    {
        cout << "Step " << get_name() << "has the title: " << title << " and the copy: " << copy << endl;
    }
    string file()
    {
        string a = "Step" + get_name() + "has the title " + title + " and copy: " + copy;
        return a;
    }
};

class TextInput : public Step
{
private:
    string description, input;

public:
    void set_param() override
    {
        string d;
        cout << "Please enter the description of the text: ";
        cin >> d;
        description = d;
    }
    void execute() override
    {
        string i;
        //    cout << description;
        cin >> i;
        input = i;
        cout << "Step " << get_name() << " has the description: " << description << " and the text input: " << input << endl;
    }
    string file()
    {
        string a = "Step" + get_name() + "has the description " + description + " and text input " + input;
        return a;
    }
};

class Operation
{
public:
    float add(float a, float b)
    {
        return a + b;
    }

    float sub(float a, float b)
    {
        return a - b;
    }

    float mul(float a, float b)
    {
        return a * b;
    }

    float div(float a, float b)
    {
        if (b == 0)
        {
            cout << "Division By Zero" << endl;
            return 0;
        }
        else
        {
            return a / b;
        }
    }

    float mini(float a, float b)
    {
        if (a < b)
            return a;
        return b;
    }

    float maxi(float a, float b)
    {
        if (a > b)
            return a;
        return b;
    }
};

class NumberInput : public Step
{
private:
    int number;
    string description;

public:
    void set_param()
    {
        string d;
        cout << "Please enter the description of the numberinput text: ";
        cin >> d;
        description = d;
    }
    void execute()
    {
        int n;
        cout << description << ":";
        cin >> n;
        number = n;
        cout << "Step " << get_name() << " with the description: " << description << " and the number input: " << number << endl;
    }
    float get_val()
    {
        return number;
    }
    string file()
    {
        string a = "Step" + get_name() + "with the description " + description + " and number input " + to_string(number);
        return a;
    }
};
class Calculus : public Step
{
private:
    vector<int> v;
    string operation;
    float result;
    vector<Step *> x;

public:
    Calculus(vector<Step *> b)
    {
        x = b;
    }
    void set_param()
    {
    }
    void execute()
    {
        string op;
        vector<int> steps;
        int number;
        cout << "Enter the number of steps you want to add  ";
        do
        {
            cin >> number;
        } while (number < 0);

        for (int i = 0; i < number; i++)
        {
            int step;
            cout << "Please enter step number: " << i + 1 << ": ";
            do
            {
                cin >> step;
                if (step >= x.size() || x[step]->get_name() != "NumberInput")
                    cout << "Step is not valid. Please enter NumbetInput step" << endl;
            } while (step >= x.size() || x[step]->get_name() != "NumberInput");
            steps.push_back(step);
        }
        cout << "Please enter the operation";
        do
        {
            cin >> op;
        } while (op != "+" && op != "-" && op != "/" && op != "*" && op != "min" && op != "max");
        operation = op;
        v = steps;
        int n = v.size();
        float numberInputs[n];

        for (int i = 0; i < n; i++)
        {
            int step = v[i];
            NumberInput *numStep = dynamic_cast<NumberInput *>(x[step]);
            numberInputs[i] = numStep->get_val();
        }

        Operation c;
        if (operation == "+")
        {
            float re;
            re = numberInputs[0];
            for (int j = 1; j < v.size(); j++)
                re = c.add(numberInputs[j], re);
            result = re;
            cout << re << endl;
        }

        if (operation == "-")
        {
            float re;
            re = numberInputs[0];
            for (int j = 1; j < v.size(); j++)
                re = c.sub(numberInputs[j], re);
            result = re;
            cout << re << endl;
        }
        if (operation == "*")
        {
            float re;
            re = numberInputs[0];
            for (int j = 1; j < v.size(); j++)
                re = c.mul(numberInputs[j], re);
            result = re;
            cout << re << endl;
        }

        if (operation == "/")
        {
            float re;
            re = numberInputs[0];
            for (int j = 1; j < v.size(); j++)
                re = c.div(numberInputs[j], re);
            result = re;
            cout << re << endl;
        }

        if (operation == "min")
        {
            float re;
            re = numberInputs[0];
            for (int j = 1; j < v.size(); j++)
                re = c.mini(numberInputs[j], re);
            result = re;
            cout << re << endl;
        }

        if (operation == "max")
        {
            float re;
            re = numberInputs[0];
            for (int j = 1; j < v.size(); j++)
                re = c.maxi(numberInputs[j], re);
            result = re;
            cout << re << endl;
        }
    }
    string file()
    {
        string a = "Step " + get_name() + " with steps ";
        for (int i = 0; i < v.size(); i++)
        {
            a += to_string(v[i]);
            a += " ";
        }
        a += "and operation ";
        a += operation;
        return a;
    }
};

class TextFile : public Step
{
private:
    string description, file_name;

public:
    void set_param() override
    {
        string d;
        cout << "Please enter the description of the text file: ";
        cin >> d;
        description = d;
    }
    void execute() override
    {
        string fn;
        cout << "What is the name of the file?" << endl;
        cin >> fn;
        file_name = fn;
        cout << "Step " << get_name() << " has the text file name " << file_name << " and the description " << description << " was added" << endl;
    }
    string file()
    {
        string a = "Step " + get_name() + " has the description " + description + " and txt file name" + file_name;
        return a;
    }
    string get_txt_name()
    {
        return file_name;
    }
};

class CsvFile : public Step
{
private:
    string description, file_name;

public:
    void set_param() override
    {
        string d;
        cout << "Please enter the description of the CSV file: ";
        cin >> d;
        description = d;
    }
    void execute() override
    {
        string fn;
        cout << "What is the name of the file?" << endl;
        cin >> fn;
        file_name = fn;
        cout << "Step " << get_name() << " has the CSV file name " << file_name << " and the description " << description << " was added" << endl;
    }
    string file()
    {
        string a = "Step " + get_name() + " has the description " + description + " and CSV file name" + file_name;
        return a;
    }
    string get_csv_name()
    {
        return file_name;
    }
};

class Output : public Step
{
private:
    vector<int> s;
    string file_name, title, description;
    vector<Step *> x;

public:
    Output(vector<Step *> b)
    {
        x = b;
    }
    void set_param() override
    {
        string fn, t, d;
        cout << "Please enter the file name: ";
        cin >> fn;
        cout << "Please enter the title: ";
        cin >> t;
        cout << "Please enter the description: ";
        cin >> d;
        file_name = fn;
        title = t;
        description = d;
    }
    void execute() override
    {
        vector<int> steps;
        int a;
        cout << "Please enter the number of steps: ";
        cin >> a;
        for (int i = 0; i < a; i++)
        {
            int step;
            cout << "Please enter step number " << i + 1 << " ";
            do
            {
                cin >> step;
                if (step >= x.size())
                    cout << "Step is not valid" << endl;
            } while (step >= x.size());
            steps.push_back(step);
        }
        s = steps;
        ofstream f;
        f.open(file_name, ios::app);
        f << title << endl;
        f << description << endl;
        for (int i = 0; i < s.size(); i++)
            f << x[s[i]]->file() << endl;
        f << "***" << endl;
        f.close();
    }
    string file()
    {
        string a = "Step " + get_name() + " wrote steps:";
        for (int i = 0; i < s.size(); i++)
        {
            a = a + to_string(s[i]);
            a = a + " ";
        }
        return a;
    }
};

class Display : public Step
{
private:
    int step;
    vector<Step *> x;

public:
    Display(vector<Step *> b)
    {
        x = b;
    }
    void set_param()
    {
    }
    void execute()
    {
        int s;
        cout << "Please enter the file step to open: ";
        do
        {
            cin >> s;
            cout << x[s]->get_name() << endl;
            if (s >= x.size() || (x[s]->get_name() != "CSVFile" && x[s]->get_name() != "TextFile"))
                cout << "Invalid file step. Please enter another step: ";
        } while (s >= x.size() || (x[s]->get_name() != "CSVFile" && x[s]->get_name() != "TextFile"));

        step = s;
        if (x[step]->get_name() == "CSVFile")
        {
            CsvFile *CsvStep = dynamic_cast<CsvFile *>(x[step]);
            ifstream inputfile(CsvStep->get_csv_name());
            string a;
            while (getline(inputfile, a))
            {
                cout << a << endl;
            }
        }
        else
        {
            TextFile *TextStep = dynamic_cast<TextFile *>(x[step]);
            ifstream inputfile(TextStep->get_txt_name());
            string a;
            while (getline(inputfile, a))
            {
                cout << a << endl;
            }
        }
    }
};

class EndStep : public Step
{
public:
    void execute()
    {
        cout << "This is the final step. Your flow is now in our database!" << endl;
    }
    string file()
    {
        return "EndStep";
    }
};

class Builder
{
private:
    vector<Step *> steps;

public:
    void add_Step(Step *step)
    {
        steps.push_back(step);
    }
    void execute_Step() const
    {
        for (const auto &step : steps)
        {
            step->execute();
        }
    }
    Step *get_Step(int i)
    {
        return steps[i];
    }
    vector<Step *> returnare()
    {
        return steps;
    }
};

void CreateFlowinterface();
void interface();
void ExistingFlow();
void DeleteFlow();
void CreateFlow();

void interface()
{
    int option;

    cout << "*************************************************************\n";
    cout << "*                                                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                Welcome to our company!                    *\n";
    cout << "*        We are here to create a process builder            *\n";
    cout << "*        that can help you make your own flow               *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                                                           *\n";
    cout << "*  1. I want to build a flow using existing predefined steps*\n";
    cout << "*  2. I want to see a flow that I have created              *\n";
    cout << "*  3. I want to delete a flow                               *\n";
    cout << "*  4. Maybe next time :)                                    *\n";
    cout << "*                                                           *\n";
    cout << "*  Your option is ___                                       *\n";
    cout << "*                                                           *\n";
    cout << "*************************************************************\n";

    cin >> option;

    switch (option)
    {

    case 1:
        CreateFlowinterface();
        break;
    case 2:
        ExistingFlow();
        break;
    case 3:
        DeleteFlow();
        break;
    case 4:
        return;
    }
}

void ExistingFlow()
{

    ifstream file("Output.txt");

    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
    }

    // Read the search string from the user
    string searchString;
    cout << "Enter the search string: ";
    cin >> searchString;

    // Construct the regular expression pattern
    string patternString = searchString + "[\\s\\S]*?\\*\\*\\*";
    regex pattern(patternString);

    // Read the entire file into a single string
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Search for matches
    sregex_iterator iter(content.begin(), content.end(), pattern);
    sregex_iterator end;

    // Iterate over matches and print them
    for (; iter != end; ++iter)
    {
        cout << "Found: " << iter->str() << endl;
    }

    // Close the file
    file.close();
    cout << "You have seen your flow! What to do next?" << endl;
    interface();
}

void CreateFlowinterface()
{
    int option;

    cout << "****************************************************************************************\n";
    cout << "*   There are the types of steps you need to have in your flow                         *\n";
    cout << "*                                                                                      *\n";
    cout << "*   1.	TITLE step: title (string), subtitle (string)                                   *\n";
    cout << "*   2.	TEXT step: title (string), copy (string)                                        *\n";
    cout << "*   3.	TEXT INPUT step: description (string), text input (string)                      *\n";
    cout << "*   4.	NUMBER INPUT step: description (string), number input (float)                   *\n";
    cout << "*   5.	CALCULUS step: steps (int), operation (string)                                  *\n";
    cout << "*   6.	DISPLAY steps: step (int)                                                       *\n";
    cout << "*   7.	TEXT FILE input step: description, file_name                                    *\n";
    cout << "*   8.	CSV FILE input step: description, file_name                                     *\n";
    cout << "*   9. OUTPUT step: step (int), name of file (string),title (text),description (text)  *\n";
    cout << "*  10.END step                                                                         *\n";
    cout << "*                                                                                      *\n";
    cout << "*   Do you want to create a new flow?  (yes-1/no-2)                                    *\n";
    cout << "*                                                                                      *\n";
    cout << "****************************************************************************************\n";

    cin >> option;

    switch (option)
    {
    case 1:
        CreateFlow();
        break;
    case 2:
        interface();
        break;
    }
}

void DeleteFlow()
{
    // Open the input file
    ifstream inputFile("Output.txt");

    if (!inputFile.is_open())
    {
        cout << "Unable to open the input file." << endl;
    }

    // Read the entire content of the file into a string
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Close the input file
    inputFile.close();

    // Read the search string from the user
    string searchString;
    cout << "Enter the search string: ";
    cin >> searchString;

    // Escape special characters in the search string
    string escapedSearchString = regex_replace(searchString, regex("([.*+?^=!:${}()|[\\]/\\\\])"), "\\$1");

    // Construct the regular expression pattern
    string patternString = escapedSearchString + "[\\s\\S]*?\\*\\*\\*";
    regex pattern(patternString);

    // Use a temporary file for writing the modified content
    ofstream tempFile("temp.txt");

    if (!tempFile.is_open())
    {
        cout << "Unable to create the temporary file." << endl;
    }

    // Search for matches and write non-matching lines to the temporary file
    sregex_iterator iter(content.begin(), content.end(), pattern);
    sregex_iterator end;

    size_t lastPos = 0;

    for (; iter != end; ++iter)
    {
        size_t matchPos = iter->position();
        tempFile << content.substr(lastPos, matchPos - lastPos);
        lastPos = matchPos + iter->length();
    }

    tempFile << content.substr(lastPos);

    // Close the temporary file
    tempFile.close();

    // Remove the original file
    remove("Output.txt");

    // Rename the temporary file to the original file name
    rename("temp.txt", "Output.txt");

    cout << "You have deleted your flow! What to do next?" << endl;
    interface();
}

void CreateFlow()
{
    string option;
    int i = 0;
    Builder builder;
    vector<Step *> la;
    vector<Step *> la1;
    vector<Step *> la2;

    TitleStep *a = new TitleStep;
    TextStep *b = new TextStep;
    TextInput *c = new TextInput;
    NumberInput *d = new NumberInput;
    TextFile *g = new TextFile;
    CsvFile *h = new CsvFile;
    EndStep *j = new EndStep;

    cout << "Do you want to have a titlestep? (yes/no)" << endl;
    cin >> option;
    if (option == "yes")
    {
        a->set_param();
        a->set_name("TitleStep");
        builder.add_Step(a);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the titlestep!" << endl;
    }

    cout << "Do you want to have a textstep? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        b->set_param();
        b->set_name("TextStep");
        builder.add_Step(b);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the textstep!" << endl;
    }

    cout << "Do you want to have a textinput? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        c->set_param();
        c->set_name("TextInput");
        builder.add_Step(c);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the textinput!" << endl;
    }

    cout << "Do you want to have a numberinput? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        d->set_param();
        d->set_name("NumberInput");
        builder.add_Step(d);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the numberinput!" << endl;
    }

    cout << "Do you want to have a calculus step? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        la2 = builder.returnare();
        Calculus *e = new Calculus(la2);
        e->set_param();
        e->set_name("CalculusStep");
        builder.add_Step(e);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the calculus step!" << endl;
    }

    cout << "Do you want to have a textfile? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        g->set_param();
        g->set_name("TextFile");
        builder.add_Step(g);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the textfile!" << endl;
    }

    cout << "Do you want to have a csvfile? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        h->set_param();
        h->set_name("CSVFile");
        builder.add_Step(h);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the csvfile!" << endl;
    }

    cout << "Do you want to have a display step? (yes/no)";
    cin >> option;
    if (option == "yes")
    {
        la1 = builder.returnare();
        Display *f = new Display(la1);
        f->set_param();
        f->set_name("DisplayStep");
        builder.add_Step(f);
        builder.get_Step(i)->execute();
        cout << "This step has the number " << i << endl;
        i++;
    }
    else
    {
        cout << "You have skipped the display step!" << endl;
    }

    la = builder.returnare();
    Output *k = new Output(la);
    k->set_param();
    k->set_name("OutputStep");
    builder.add_Step(k);
    builder.get_Step(i)->execute();
    i++;

    j->set_param();
    j->set_name("EndStep");
    builder.add_Step(j);
    builder.get_Step(i)->execute();

    interface();
}

int main()
{
    interface();

    return 0;
}
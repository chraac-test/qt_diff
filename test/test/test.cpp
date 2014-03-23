
#include "diffLibrary.h"
using namespace DiffLibrary;
using namespace std;


void StringDiff(const string &left, const string &right)
{
    cout << "left: " << left.c_str() << endl;
    cout << "right: " << right.c_str() << endl;

    Diff<string::value_type, string> d(left, right);
    d.Compose();
    d.GetSes().Serialize(cout);

    cout << endl;
}


int main(int argc, char *argv[])
{
    StringDiff("abcdef", "acbfedg");
    StringDiff("acbfedg", "abcdef");
    StringDiff("acbfedg", "dawedawdwa");
    StringDiff("dawedawdwa", "abcdef");
    return 0;
}

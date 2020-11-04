#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Object
{
    Object(int x): x(x)
    {
        cout << "init construct " << this << endl;
    }
    Object(const Object& obj): x(obj.x)
    {
        cout << "copy construct " << this << endl;
    };
    Object(Object&& obj): x(obj.x)
    {
        cout << "move construct " << this << endl;
    };
    ~Object()
    {
        cout << "destruct "  << this << endl;
    }
    Object& operator=(const Object& obj) = default;
    int x;
};

int main()
{
    // call a copy construct function
    cout << "init vector v" << endl;
    Object obj(1);
    vector<Object> v1;
    cout << "start to push_back"<< endl;
    v1.push_back(obj);
    vector<Object> v2;
    cout << "start to emrace_back" << endl;
    v2.emplace_back(obj);
    // call init construct onece
    vector<Object> v3;
    cout << "start to emplace_back a temp obj" << endl;
    v3.emplace_back(1);
    return 0;
}

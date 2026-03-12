
### What is the output of this C++ code?

```
#include <cstdint>
using namespace std;

void main(void)
{
    int a = 10;
    int b = a;
    int& c = b;
    int* d = &a;

    for (int i = 0; i < a; i++)
    {
        a -= 1;
        c += 3;
    }

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "*d = " << *d << endl;
}
```

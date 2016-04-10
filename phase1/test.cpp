#include <map>
#include <array>
#include <iostream>

using namespace std;

int main(){
    map <string, array<int, 3>> intArrMap = {
        {"Bobby Jay",    {{67,  445, 208}} },
        {"Bobby Tables", {{999, -12, 34}} }
    };
    cout << (intArrMap["Bobby Jay"])[0];
}

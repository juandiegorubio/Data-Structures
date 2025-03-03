#include <iostream>
using namespace std;



void print_array(int* list, int size) {
    cout << '[';
    for(int i=0; i < size; ++i) {
        cout << list[i];
        if(i == size-1) cout << ']';
        else cout << ", ";
    }
}

struct Range {
    int left;
    int right;
};

/* ----- BINARY SEARCH -----
    Returns the range where the value can be found
    - If the value is in the list, left and right are the same
    - If the value is NOT in the list, left is bigger than right        */
Range binary_search(int* list, int l, int r, int value) {
    if(r < l) return {l, r};
    int m = l + (r-l)/2;
    if(list[m] == value) return {m, m};
    if(list[m] > value) return binary_search(list, l, m-1, value);
    else return binary_search(list, m+1, r, value);
}





int main() {
    int list_size; 
    list_size = 4;
    // cin >> list_size; 
    // for(int i=0; i < list_size; ++i) cin >> list[i];
    int list[list_size] = {1, 4, 8, 12};

    cout << "Result array: ";
    print_array(list, list_size);
    cout << endl;

    int value;
    cin >> value;
    Range test = binary_search(list, 0, list_size, value);
    cout << "Result: [" << test.left << ", " << test.right << ']' << endl;

    return 0;
}
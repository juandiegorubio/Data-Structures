

/* ----- BINARY SEARCH ----- */
int binary_search(int* list, int l, int r, int value) {
    if(r < l) return -1;
    int m = l + (r-l)/2;
    if(list[m] == value) return m;
    if(list[m] > value) return binary_search(list, l, m-1, value);
    else return binary_search(list, m+1, r, value);
}
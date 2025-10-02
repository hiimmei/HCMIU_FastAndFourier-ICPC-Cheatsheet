//t[v] la tong cac phan tu tu chi so l toi r
void build(int v, int l, int r){
    if(l == r){
        t[v] = a[l];//leaf
    }
    else{
        int m = (l + r)/2;
        build(2 * v, l, m);
        build(2 * v + 1,m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
}
 
int sum(int v, int tl, int tr, int l, int r){
    if(l == tl && r == tr){
        return t[v];
    }
    else{
        int tm = (tl + tr)/2;
        return sum(2 * v, tl, tm, l, min(tm, r)) + sum(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
    }
}
 
void update(int v, int l, int r, int pos, int val){
    if(l == r){
        t[pos] = val;
    }
    else{
        int m = (l + r)/2;
        if(pos <= m){
            update(2 * v + 1, m + 1, r, pos, val);
        }
        else{
            update(2 * v + 1, m + 1, r, pos, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

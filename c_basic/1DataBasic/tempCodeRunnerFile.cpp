int abssum(int x, int y){
    x = x > 0 ? x : -x;
    y = y > 0 ? y : -y;
    return x+y;
}
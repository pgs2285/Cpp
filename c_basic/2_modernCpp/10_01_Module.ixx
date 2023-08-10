export module 10_01_Module;

export void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
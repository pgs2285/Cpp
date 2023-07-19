mplate<typename T>
struct remove_pointer<T*>
{
    using type = T;
};
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

//void CoutOutput();

template <typename T>
class OutWrap
{
    T value;
public:
    OutWrap() : value{} {}
    OutWrap(T const& value) : value{ value } {}

    operator T& ()
    {
        return value;
    }

    operator T const& () const
    {
        return value;
    }

    T& Value()
    {
        return value;
    }
};

template <typename T>
std::istream& operator>>(std::istream& in, OutWrap<T>& wrap)
{
    in.read(reinterpret_cast<char*>(&static_cast<T&>(wrap)), sizeof(T));
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, OutWrap<T> const& wrap)
{
    out.write(reinterpret_cast<char const*>(&static_cast<T const&>(wrap)), sizeof(T));
    return out;
}

class User
{
    std::string name = "";
    int age = 0;
public:
    User() {}
    User(std::string name, int age)
        : name{ name }, age{ age } {};

    void Print()
    {
        std::cout << name << " " << age << "\n";
    }
};

int main()
{
    int arr[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::ofstream fout("array.dat");
    std::copy(arr, arr + 9, std::ostream_iterator<OutWrap<int>>(fout));
    //fout << OutWrap<User>(User("Bobby", 25));
    fout.close();

    /*std::ifstream fin("array.dat");
    User user;
    OutWrap<User> wrap(user);
    fin >> wrap;
    user = wrap.Value();
    fin.close();

    user.Print();*/
}

//void CoutOutput()
//{
//    std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//
//    for (auto item : v1)
//        std::cout << item << " ";
//    std::cout << "\n";
//
//    std::for_each(v1.begin(), v1.end(), [](auto item)
//        {
//            std::cout << item << " ";
//        });
//    std::cout << "\n";
//
//    std::copy(v1.begin(),
//        v1.end(),
//        std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";
//}

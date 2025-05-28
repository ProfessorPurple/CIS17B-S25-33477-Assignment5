#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

template<typename T>
class Package {
private:
    T item;
public:
    Package(T i) : item(i) {}
    void label() {
        std::cout << "Generic package containing: " << typeid(T).name() << "\n";
    }
};

// Specialization for std::string
template<>
class Package<std::string> {
private:
    std::string item;
public:
    Package(std::string i) : item(i) {}
    void label() {
        std::cout << "Book package: \"" << item << "\"\n";
    }
};

// Partial specialization for pointers
template<typename T>
class Package<T*> {
private:
    T* item;
public:
    Package(T* i) : item(i) {}
    void label() {
        std::cout << "Fragile package for pointer to type: " << typeid(T).name() << "\n";
    }
};

template<typename T, int Size>
class Box {
private:
    std::array<T, Size> items;
    int count = 0;
public:
    bool addItem(const T& item) {
        if (count < Size) {
            items[count++] = item;
            std::cout << "Added item to box: \"" << item << "\"\n";
            return true;
        }
        return false;
    }

    void printItems() const {
        std::cout << "Box contents:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << " - " << items[i] << "\n";
        }
    }
};

template<typename T>
std::string getTypeName() {
    if (std::is_same<T, std::string>::value) return "string";
    if (std::is_same<T, int>::value) return "int";
    if (std::is_same<T, double>::value) return "double";
    return typeid(T).name(); // Fallback for unknown types
}

template<typename T>
void shipItem(const T& item) {
    std::cout << "Shipping item of type: " << getTypeName<T>() << "\n";
}

template<>
void shipItem(const double& item) {
    std::cout << "Shipping temperature-controlled item: " << item << "°C\n";
}

int main()
{
    Package<int> intPackage(22);
    Package<std::string> stringPackage("House of Leaves by Mark Danielewski");
    double doubleItem = 12.34;
    Package<double*> pointerPackage(&doubleItem);

    std::cout << "Class label calls:\n";
    intPackage.label();
    stringPackage.label();
    pointerPackage.label();

    std::cout << "\nBox some books:\n";
    Box<std::string, 3> boxOfBooks;

    boxOfBooks.addItem("The Shining (by) Stephen King");
    boxOfBooks.addItem("The Count of Monte Cristo (by) Alexander Dumas");
    boxOfBooks.addItem("We Need To Do Something (by) Sean King O'Grady");
    std::cout << "\nPrint Some Books:\n";
    boxOfBooks.printItems();

    int intItem = 44;
    std::string stringItem = "The Only One Left (by) Riley Sager";
    double doubleItem2 = 33.56;

    std::cout << "\nShip some items:\n";
    shipItem(intItem);
    shipItem(stringItem);
    shipItem(doubleItem2);


    return 0;
}
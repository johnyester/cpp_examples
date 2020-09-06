#include <iostream>

/** Notes
Class object
 static int global_class_var; // static - class level variable 

Instance objects
 If your variable is an instance variable and not a class variable 
   you must initialize it in the constructor or other method.
*/

namespace jly_tutorials
{

    using namespace std;

    // Base class
    class Shape {
    public:
        Shape() :
            // the initializer list
            // const variables and references must in included in the list
            width(0), height(0)
        { /* housekeeping */
        }

        void setWidth(int w) {
            width = w;
        }
        void setHeight(int h) {
            height = h;
        }

    protected:
        int width;
        int height;
    };

    // Derived class
    class Rectangle : public Shape { // class derived-class: access-specifier base-class https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
    public:
        int getArea() {
            return (width * height);
        }
    };

    int main_classes() {
        Rectangle Rect;

        Rect.setWidth(5);
        Rect.setHeight(7);

        // Print the area of the object.
        cout << "Total area: " << Rect.getArea() << endl;

        return 0;
    }
}
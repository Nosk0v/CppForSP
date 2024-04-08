#include <iostream>
  
class Point
{
public:
    Point(int x, int y)
    {
        this->x = x; 
        this->y = y;
    }
    void showCoords() 
    {
        std::cout << "Point x: " << this->x << "\t y: " << y << std::endl;
    }
    Point* move(int x, int y)
    {
        this->x += x;
        this->y += y;
        return this;
    }
private:
    int x;
    int y;
};
  
int main()
{
    Point p1{20, 50};
    p1.showCoords();    // Point x: 20  y: 50
    p1.move(10, 5)->move(10, 10)->move(10, 15);
    p1.showCoords();    // Point x: 50  y: 80
}

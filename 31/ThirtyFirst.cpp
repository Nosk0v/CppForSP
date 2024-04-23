#include <iostream>
#include <string>

class Transport
{
public:
    virtual void printInfo() const = 0;
    virtual double getPayload() const = 0;
};

class Car : public Transport
{
private:
    std::string brand;
    std::string number;
    double speed;
    double payload;

public:
    Car(const std::string &_brand, const std::string &_number, double _speed, double _payload)
        : brand(_brand), number(_number), speed(_speed), payload(_payload) {}

    virtual void printInfo() const override
    {
        std::cout << "Car: Brand - " << brand << ", Number - " << number
                  << ", Speed - " << speed << ", Payload - " << payload << std::endl;
    }

    virtual double getPayload() const override
    {
        return payload;
    }
};

class Motorbike : public Transport
{
private:
    std::string brand;
    std::string number;
    double speed;
    double payload;
    bool hasSidecar;

public:
    Motorbike(const std::string &_brand, const std::string &_number, double _speed, double _payload, bool _hasSidecar)
        : brand(_brand), number(_number), speed(_speed), payload(_payload), hasSidecar(_hasSidecar) {}

    virtual void printInfo() const override
    {
        std::cout << "Motorbike: Brand - " << brand << ", Number - " << number
                  << ", Speed - " << speed << ", Payload - " << payload;
        if (hasSidecar)
            std::cout << ", Sidecar: Yes";
        else
            std::cout << ", Sidecar: No";
        std::cout << std::endl;
    }

    virtual double getPayload() const override
    {
        return hasSidecar ? 0 : payload;
    }
};

class Truck : public Transport
{
private:
    std::string brand;
    std::string number;
    double speed;
    double payload;
    bool hasTrailer;

public:
    Truck(const std::string &_brand, const std::string &_number, double _speed, double _payload, bool _hasTrailer)
        : brand(_brand), number(_number), speed(_speed), payload(_payload), hasTrailer(_hasTrailer) {}

    virtual void printInfo() const override
    {
        std::cout << "Truck: Brand - " << brand << ", Number - " << number
                  << ", Speed - " << speed << ", Payload - " << payload;
        if (hasTrailer)
            std::cout << ", Trailer: Yes";
        else
            std::cout << ", Trailer: No";
        std::cout << std::endl;
    }

    virtual double getPayload() const override
    {
        return hasTrailer ? 2 * payload : payload;
    }
};

int main()
{
    Car car("Toyota", "A123BC", 120.0, 500.0);
    car.printInfo();

    Motorbike motorbike("Harley-Davidson", "B456DE", 150.0, 100.0, true);
    motorbike.printInfo();

    Truck truck("Volvo", "C789FG", 80.0, 2000.0, true);
    truck.printInfo();

    return 0;
}
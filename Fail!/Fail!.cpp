#include <iostream>
#include <vector>
#include <memory>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

   
    auto circle = std::make_unique<Circle>(1.0f);
    circle->SetRadius(3.0f);
    shapes.push_back(std::move(circle));

   
    shapes.push_back(std::make_unique<Rectangle>(4.0f, 5.0f));

    
    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->Area();

        
        if (auto* circlePtr = dynamic_cast<Circle*>(shape.get())) {
            std::cout << " (Radius: " << circlePtr->GetRadius() << ")";
        }
        std::cout << std::endl;
    }

    return 0;
}
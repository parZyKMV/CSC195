
#include <iostream>

class Robot {
private:
    int x, y;
    bool hasItem;
public:
    Robot() : x(0), y(0), hasItem(false){}

    void Forward(int steps) {
        y += steps;
        std::cout << "Moved forward to (" << x << ", " << y << ")\n";
    }

    void Reverse(int steps) {
        y -= steps;
        std::cout << "Moved backward to (" << x << ", " << y << ")\n";
    }

    void TurnLeft(float angle) {
        std::cout << "Turned left " << angle << " degrees\n";
    }

    void TurnRight(float angle) {
        std::cout << "Turned right " << angle << " degrees\n";
    }

    void PickUpItem() {
        hasItem = true;
        std::cout << "Picked up the green ball.\n";
    }

    void DropItem() {
        if (hasItem) {
            hasItem = false;
            std::cout << "Dropped the green ball.\n";
        }
        else {
            std::cout << "No item to drop.\n";
        }
    }

    bool hasGreenBall() {
        return hasItem;
    }
};

int main() {
    Robot robot;

   
    robot.Forward(3);
    robot.TurnRight(90);
    robot.Forward(2);
    robot.PickUpItem(); 


    robot.TurnLeft(90);
    robot.Forward(4);
    robot.TurnRight(90);
    robot.Forward(2);

    if (robot.hasGreenBall()) {
        std::cout << "Successfully exited the maze with the green ball!\n";
    }

    return 0;
}

/*************************************************************
 * 1. Name:
 *      Joshua Sooaemalelagi and Jacob Briggs
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      Probably verifying our math and coordinating a time.
 * 5. How long did it take for you to complete the assignment?
 *      It took us about an hour to complete.
 **************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
#define PI 3.14159265358979323846 //pi

/***************************************************
* COMPUTE DISTANCE
* Apply inertia to compute a new position using the distance equation.
* The equation is:
*     s = s + v t + 1/2 a t^2
* INPUT
*     s : original position, in meters
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     s : new position, in meters
**************************************************/
double computeDistance(double originalPosition, double velocity, double acceleration, double time)
{
    double newPosition = originalPosition + velocity * time + 0.50 * acceleration * pow(time, 2);
    return newPosition;
}

/**************************************************
* COMPUTE ACCELERATION
* Find the acceleration given a thrust and mass.
* This will be done using Newton's second law of motion:
*     f = m * a
    f/m = a
* INPUT
*     f : force, in Newtons (kg * m / s^2)
*     m : mass, in kilograms
* OUTPUT
*     a : acceleration, in meters/second^2
***************************************************/
double computeAcceleration(double force, double mass)
{
    double acceleration = force / mass;
    return acceleration;
}

/***********************************************
* COMPUTE VELOCITY
* Starting with a given velocity, find the new
* velocity once acceleration is applied. This is
* called the Kinematics equation. The
* equation is:
*     v = v + a t

* INPUT
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     v : new velocity, in meters/second
***********************************************/
double computeVelocity(double givenVelocity, double acceleration, double time)
{
    double newVelocity = givenVelocity + acceleration * time;
    return newVelocity;
}

/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double computeVerticalComponent(double angle, double total){
    double verticalComponent = cos(angle) * total;
    return verticalComponent;
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the Horizontal component of the total
***********************************************/
double computeHorizontalComponent(double angle, double total){
double horizontalComponent = total * sin(angle);
return horizontalComponent;
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double computeTotalComponent(double horizontalComponent, double verticalComponent) {
double totalComponentSquared = (pow(horizontalComponent, 2) + pow(verticalComponent, 2));
      
return sqrt(totalComponentSquared);
}

/*************************************************
* RADIANS FROM DEGEES
* Convert degrees to radians:
*     radians / 2pi = degrees / 360
* INPUT
*     d : degrees from 0 to 360
* OUTPUT
*     r : radians from 0 to 2pi
**************************************************/
double radiansFromDeg(double degrees) {
    double radians = ((degrees / 360.0) * (2 * PI));
    return radians;
}
      
/**************************************************
* PROMPT
* A generic function to prompt the user for a double
* INPUT
*      message : the message to display to the user
* OUTPUT
*      response : the user's response
***************************************************/
double prompt(string message) 
{
    double response;
    cout << message << endl;
    cin >> response;
    return response;
}

/****************************************************************
* MAIN
* Prompt for input, compute new position, and display output
****************************************************************/
int main()
{
    // User Input
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double x = 0; // Initial horizontal position is set to 0
    double t = 1.0; // Time interval is set to 1 second initially
    int seconds = 1; // Initialize seconds

    // Initial angle input
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)?");
    double aRadians = radiansFromDeg(aDegrees);
    cout << endl;

    for (int i = 0; i < 5; i++)
    {
        // Calculate thrust components
        double ddxThrust = computeHorizontalComponent(aRadians, THRUST);
        double ddyThrust = computeVerticalComponent(aRadians, THRUST);

        // Calculate total acceleration components
        double ddy = computeAcceleration(ddyThrust, WEIGHT) + GRAVITY;
        double ddx = computeAcceleration(ddxThrust, WEIGHT);

        // Update velocity
        dy = computeVelocity(dy, ddy, t);
        dx = computeVelocity(dx, ddx, t);

        // Update position
        y = computeDistance(y, dy, ddy, t);
        x = computeDistance(x, dx, ddx, t);

        // Calculate total velocity
        double v = computeTotalComponent(dx, dy);

        // Output for each time unit
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << seconds << "s - ";
        cout << "x,y: (" << x << ", " << y << ")m ";
        cout << "dx, dy: (" << dx << ", " << dy << ")m/s ";
        cout << "speed: " << v << "m/s ";
        cout << "angle: " << aDegrees << "deg" << endl;

        // Increment time
        seconds++;
    }

    // User input to rotate the LM
    cout << endl;
    double newAngleDegrees = prompt("What is the new angle of the LM where 0 is up (degrees)?");
    double newAngleRadians = radiansFromDeg(newAngleDegrees);
    cout << endl;

    for (int i = 0; i < 5; i++) {
        // Update thrust components with the new angle
        double newDdxThrust = computeHorizontalComponent(newAngleRadians, THRUST);
        double newDdyThrust = computeVerticalComponent(newAngleRadians, THRUST);

        // Calculate total acceleration components with the new angle
        double newDdx = computeAcceleration(newDdxThrust, WEIGHT);
        double newDdy = computeAcceleration(newDdyThrust, WEIGHT) + GRAVITY;

        // Update velocity
        dy = computeVelocity(dy, newDdy, t);
        dx = computeVelocity(dx, newDdx, t);

        // Update position
        x = computeDistance(x, dx, newDdx, t);
        y = computeDistance(y, dy, newDdy, t);

        // Calculate total velocity
        double v = computeTotalComponent(dx, dy);

        // Output for each time unit
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << seconds << "s - ";
        cout << "x,y: (" << x << ", " << y << ")m ";
        cout << "dx, dy: (" << dx << ", " << dy << ")m/s ";
        cout << "speed: " << v << "m/s ";
        cout << "angle: " << newAngleDegrees << "deg" << endl;
        cout << endl;
        // Increment time
        seconds++;
    }

    return 0;
}
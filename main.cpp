#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <stdexcept>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu() {
    const vector<string> menuItems =
    {
        "Addition", "Subtraction", "Multiplication", "Division",
        "Modulo", "Power", "Euler's Power", "2 to the Power",
        "Square Root", "Cube Root", "Reciprocal Value", "Sine",
        "Cosine", "Tangent", "Cotangent", "Natural Logarithm",
        "Logarithm Base 10", "Logarithm Base 2", "Factorial",
        "Clear Result", "Get Current Result"
    };

    cout << "\nCalculator Menu: " << endl;
    for (int i = 0; i < menuItems.size(); ++i) {
        cout << i + 1 << ". " << menuItems[i] << endl;
    }
    cout << "Exit" << endl;
}

double getValidNumber(const string& prompt) {
    string input;
    while(true) {
        cout << prompt;
        getline(cin >> ws, input);

        try {
            size_t pos;
            double number = stod(input, &pos);
            if (pos == input.length()) {
                return number;
            }
        }
        catch (...) {

        }

        cout << "Invalid input. Please enter a valid number." << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}

class Calculator {
protected:
    double currentResult;
public:
    Calculator() {
        currentResult = 0;
    }

    double addition(double a, double b) {
        currentResult = a + b;
        return currentResult;
    }

    double subtraction(double a, double b) {
        currentResult = a - b;
        return currentResult;
    }

    double multiplication(double a, double b) {
        currentResult = a * b;
        return currentResult;
    }

    double division(double a, double b) {
        if (b == 0) throw logic_error("Division by 0 is not possible.");
        currentResult = a / b;
        return currentResult;
    }

    double modulo(double a, double b) {
        if (b == 0) throw logic_error("Division by 0 is not possible.");
        currentResult = fmod(a, b);
        return currentResult;
    }

    void clearCurrentResult() {
        currentResult = 0;
    }

    double getCurrentResult() {
        return currentResult;
    }
};

class ScientificCalculator : public Calculator {
private:
    static constexpr double pi = 3.14159265359;
    static constexpr double euler = 2.71828;
    static constexpr double halfCircle = 180.0;
    static constexpr double rightAngle = 90.0;
    static constexpr double epsilon = 1e-9;
public:
    ScientificCalculator() {
        currentResult = 0;
    }
    double power(double base, double exp) {
        currentResult = pow(base, exp);
        return currentResult;
    }

    double eulerPower(double exp) {
        currentResult = pow(euler, exp);
        return currentResult;
    }

    double twoPower(double exp) {
        currentResult = pow(2, exp);
        return currentResult;
    }

    double squareRoot(double number) {
        if (number < 0) throw logic_error("Cannot calculate sqrt of a negative number.");
        currentResult = sqrt(number);
        return currentResult;
    }

    double cubeRoot(double number) {
        currentResult = cbrt(number);
        return currentResult;
    }

    double reciprocalValue(double number) {
        if (number == 0) throw logic_error("0 does not have a reciprocal value.");
        currentResult = 1 / number;
        return currentResult;
    }

    bool isTanUndefined(double angle) {
        return (fmod(angle, halfCircle) == rightAngle);
    }

    bool isCotUndefined(double angle) {
        return (fmod(angle, halfCircle) == 0.0);
    }

    double toRad(double angle) {
        return angle * (pi / halfCircle);
    }

    double toAng(double rad) {
        return rad * (halfCircle / pi);
    }

    double sinFunc(double angle) {
        double rad = toRad(angle);
        currentResult = sin(rad);
        return currentResult;
    }

    double cosFunc(double angle) {
        double rad = toRad(angle);
        currentResult = cos(rad);
        return currentResult;
    }

    double tanFunc(double angle) {
        if (isTanUndefined(angle))
        {
            throw logic_error("The value of tan " + to_string(angle) + " degrees is undefined.");
        }
        if (isCotUndefined(angle)) {
            currentResult = 0.0;
            return currentResult;
        }
        else
        {
            double rad = toRad(angle);
            currentResult = tan(rad);
            return currentResult;
        }
    }

    double cotFunc(double angle) {
        if (isCotUndefined(angle))
        {
            throw logic_error("The value of cot " + to_string(angle) + " degrees is undefined.");
        }
        if (isTanUndefined(angle))
        {
            currentResult = 0.0;
            return currentResult;
        }
        else
        {
            currentResult = 1 / tanFunc(angle);
            return currentResult;
        }
    }

    double naturalLog(double number) {
        if (number <= 0) throw logic_error("Cannot calculate log of a non-positive number.");
        currentResult = log(number);
        return currentResult;
    }

    double log10Func(double number) {
        if (number <= 0) throw logic_error("Cannot calculate log of a non-positive number.");
        currentResult = log10(number);
        return currentResult;
    }

    double log2Func(double number) {
        if (number <= 0) throw logic_error("Cannot calculate log of a non-positive number.");
        currentResult = log2(number);
        return currentResult;
    }

    long long factorial(int n) {
        if (n < 0) throw logic_error("Cannot calculate factorial of a negative number.");
        if (n == 0 || n == 1) {
            currentResult = 1;
            return currentResult;
        }
        currentResult = 1;
        for (int i = 2; i <= n; i++) {
            currentResult *= i;
        }
        return currentResult; // return n * factorial(n - 1);
    }
};

int main()
{
    ScientificCalculator sc;
    int choice;
    double a, b;
    bool flag = true;

    do {
        clearScreen();
        displayMenu();
        cout << "> ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                a = getValidNumber("Enter the first number: ");
                b = getValidNumber("Enter the second number: ");
                cout << "Result: " << sc.addition(a, b) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 2:
                clearScreen();
                a = getValidNumber("Enter the first number: ");
                b = getValidNumber("Enter the second number: ");
                cout << "Result: " << sc.subtraction(a, b) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 3:
                clearScreen();
                a = getValidNumber("Enter the first number: ");
                b = getValidNumber("Enter the second number: ");
                cout << "Result: " << sc.multiplication(a, b) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 4:
                clearScreen();
                cout << "Enter the first number: ";
                cin >> a;
                a = getValidNumber("Enter the first number: ");
                b = getValidNumber("Enter the second number: ");
                try {
                    cout << "Result: " << sc.division(a, b) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 5:
                clearScreen();
                a = getValidNumber("Enter the first number: ");
                b = getValidNumber("Enter the second number: ");
                try {
                    cout << "Result: " << sc.modulo(a, b) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 6:
                clearScreen();
                a = getValidNumber("Enter the base: ");
                b = getValidNumber("Enter the exponent: ");
                cout << "Result: " << sc.power(a, b) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 7:
                clearScreen();
                a = getValidNumber("Enter the exponent: ");
                cout << "Result: " << sc.eulerPower(a) << endl;
                break;
            case 8:
                clearScreen();
                a = getValidNumber("Enter the exponent: ");
                cout << "Result: " << sc.twoPower(a) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 9:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                try {
                    cout << "Result: " << sc.squareRoot(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 10:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                cout << "Result: " << sc.cubeRoot(a) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 11:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                try {
                    cout << "Result: " << sc.reciprocalValue(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 12:
                clearScreen();
                a = getValidNumber("Enter the angle: ");
                cout << "Result: " << sc.sinFunc(a) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 13:
                clearScreen();
                a = getValidNumber("Enter the angle: ");
                cout << "Result: " << sc.cosFunc(a) << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 14:
                clearScreen();
                a = getValidNumber("Enter the angle: ");
                try {
                    cout << "Result: " << sc.tanFunc(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 15:
                clearScreen();
                a = getValidNumber("Enter the angle: ");
                try {
                    cout << "Result: " << sc.cotFunc(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 16:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                try {
                    cout << "Result: " << sc.naturalLog(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 17:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                try {
                    cout << "Result: " << sc.log10Func(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 18:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                try {
                    cout << "Result: " << sc.log2Func(a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 19:
                clearScreen();
                a = getValidNumber("Enter the number: ");
                try {
                    cout << "Result: " << sc.factorial((int)a) << endl;
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 20:
                clearScreen();
                sc.clearCurrentResult();
                cout << "The current result is now 0." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 21:
                clearScreen();
                cout << "This is the current result: " << sc.getCurrentResult() << " ." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                break;
            case 0:
                cout << "Goodbye.";
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                flag = false;
                break;
            default:
                cout << "Invalid option.";
                this_thread::sleep_for(chrono::seconds(2));
                flag = false;
                break;
        }
    } while (flag);
}

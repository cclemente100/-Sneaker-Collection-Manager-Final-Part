#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

// ============================================================
// Constants
// ============================================================

const int MAX_SNEAKERS = 20;

// ============================================================
// Enums
// ============================================================

enum class SneakerBrand
{
    Nike = 1,
    Jordan,
    Adidas,
    NewBalance,
    Puma,
    Converse,
    Other
};

enum class SneakerCondition
{
    New = 1,
    Excellent,
    Good,
    Fair,
    Poor
};

// ============================================================
// Struct
// ============================================================

struct Sneaker
{
    string model;
    SneakerBrand brand;
    double size;
    SneakerCondition condition;
    double purchasePrice;
    double estimatedValue;
};

// ============================================================
// Function Prototypes
// ============================================================

void displayMenu();

void displayBrandMenu();
void displayConditionMenu();

string brandToString(SneakerBrand brand);
string conditionToString(SneakerCondition condition);

void addSneaker(Sneaker collection[], int& sneakerCount);

void displayCollection(const Sneaker collection[], int sneakerCount);

void searchCollection(const Sneaker collection[], int sneakerCount);
void searchByBrand(const Sneaker collection[], int sneakerCount);
void searchByModel(const Sneaker collection[], int sneakerCount);

void sortCollection(Sneaker collection[], int sneakerCount);
void sortByBrand(Sneaker collection[], int sneakerCount);
void sortByModel(Sneaker collection[], int sneakerCount);
void sortByValue(Sneaker collection[], int sneakerCount);

void displaySummary(const Sneaker collection[], int sneakerCount);

// ============================================================
// Main
// ============================================================

int main()
{
    Sneaker collection[MAX_SNEAKERS];
    int sneakerCount = 0;
    int choice;

    do
    {
        displayMenu();

        cout << "Enter selection: ";
        cin >> choice;

        // Handle invalid non-numeric input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid input. Please enter a number from 1-6.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << endl;

        switch (choice)
        {
            case 1:
                addSneaker(collection, sneakerCount);
                break;

            case 2:
                displayCollection(collection, sneakerCount);
                break;

            case 3:
                searchCollection(collection, sneakerCount);
                break;

            case 4:
                sortCollection(collection, sneakerCount);
                break;

            case 5:
                displaySummary(collection, sneakerCount);
                break;

            case 6:
                cout << "Exiting Sneaker Collection Manager...\n";
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid selection. Please choose 1-6.\n";
        }

        cout << endl;

    } while (choice != 6);

    return 0;
}

// ============================================================
// Display Main Menu
// ============================================================

void displayMenu()
{
    cout << "========================================\n";
    cout << "       SNEAKER COLLECTION MANAGER\n";
    cout << "========================================\n";
    cout << "\n";
    cout << "  1. Add Sneaker\n";
    cout << "  2. Display Collection\n";
    cout << "  3. Search Collection\n";
    cout << "  4. Sort Collection\n";
    cout << "  5. Collection Summary\n";
    cout << "  6. Exit\n";
    cout << "\n";
    cout << "----------------------------------------\n";
}

// ============================================================
// Brand Menu
// ============================================================

void displayBrandMenu()
{
    cout << "\nSELECT BRAND\n";
    cout << "----------------------------\n";
    cout << "1. Nike\n";
    cout << "2. Jordan\n";
    cout << "3. Adidas\n";
    cout << "4. New Balance\n";
    cout << "5. Puma\n";
    cout << "6. Converse\n";
    cout << "7. Other\n";
}

// ============================================================
// Condition Menu
// ============================================================

void displayConditionMenu()
{
    cout << "\nSELECT CONDITION\n";
    cout << "----------------------------\n";
    cout << "1. New\n";
    cout << "2. Excellent\n";
    cout << "3. Good\n";
    cout << "4. Fair\n";
    cout << "5. Poor\n";
}

// ============================================================
// Convert Brand Enum to String
// ============================================================

string brandToString(SneakerBrand brand)
{
    switch (brand)
    {
        case SneakerBrand::Nike:
            return "Nike";

        case SneakerBrand::Jordan:
            return "Jordan";

        case SneakerBrand::Adidas:
            return "Adidas";

        case SneakerBrand::NewBalance:
            return "New Balance";

        case SneakerBrand::Puma:
            return "Puma";

        case SneakerBrand::Converse:
            return "Converse";

        case SneakerBrand::Other:
            return "Other";

        default:
            return "Unknown";
    }
}

// ============================================================
// Convert Condition Enum to String
// ============================================================

string conditionToString(SneakerCondition condition)
{
    switch (condition)
    {
        case SneakerCondition::New:
            return "New";

        case SneakerCondition::Excellent:
            return "Excellent";

        case SneakerCondition::Good:
            return "Good";

        case SneakerCondition::Fair:
            return "Fair";

        case SneakerCondition::Poor:
            return "Poor";

        default:
            return "Unknown";
    }
}

// ============================================================
// Add Sneaker
// ============================================================

void addSneaker(Sneaker collection[], int& sneakerCount)
{
    if (sneakerCount >= MAX_SNEAKERS)
    {
        cout << "The collection is full.\n";
        cout << "You cannot add more than "
             << MAX_SNEAKERS << " sneakers.\n";
        return;
    }

    Sneaker newSneaker;

    cout << "ADD SNEAKER\n";
    cout << "========================================\n";

    // Brand
    displayBrandMenu();

    int brandChoice;
    cout << "Enter brand: ";
    cin >> brandChoice;

    while (brandChoice < 1 || brandChoice > 7 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Invalid choice. Enter a number from 1-7: ";
        cin >> brandChoice;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    newSneaker.brand = static_cast<SneakerBrand>(brandChoice);

    // Model
    cout << "Enter model: ";
    getline(cin, newSneaker.model);

    // Size
    cout << "Enter size: ";
    cin >> newSneaker.size;

    while (cin.fail() || newSneaker.size <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid size. Enter a positive number: ";
        cin >> newSneaker.size;
    }

    // Condition
    displayConditionMenu();

    int conditionChoice;
    cout << "Enter condition: ";
    cin >> conditionChoice;

    while (conditionChoice < 1 ||
           conditionChoice > 5 ||
           cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Invalid choice. Enter a number from 1-5: ";
        cin >> conditionChoice;
    }

    newSneaker.condition =
        static_cast<SneakerCondition>(conditionChoice);

    // Purchase price
    cout << "Enter purchase price: $";
    cin >> newSneaker.purchasePrice;

    while (cin.fail() || newSneaker.purchasePrice < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid price. Enter a non-negative value: $";
        cin >> newSneaker.purchasePrice;
    }

    // Estimated value
    cout << "Enter estimated value: $";
    cin >> newSneaker.estimatedValue;

    while (cin.fail() || newSneaker.estimatedValue < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid value. Enter a non-negative value: $";
        cin >> newSneaker.estimatedValue;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Store sneaker in next available array position
    collection[sneakerCount] = newSneaker;
    sneakerCount++;

    cout << "\nSneaker added successfully!\n";
}

// ============================================================
// Display Collection
// ============================================================

void displayCollection(const Sneaker collection[], int sneakerCount)
{
    if (sneakerCount == 0)
    {
        cout << "The collection is currently empty.\n";
        return;
    }

    cout << "SNEAKER COLLECTION\n";
    cout << "==========================================================================\n";

    cout << left
         << setw(4) << "#"
         << setw(14) << "Brand"
         << setw(24) << "Model"
         << setw(8) << "Size"
         << setw(12) << "Condition"
         << right
         << setw(12) << "Paid"
         << setw(12) << "Value"
         << endl;

    cout << "--------------------------------------------------------------------------\n";

    cout << fixed << setprecision(2);

    for (int i = 0; i < sneakerCount; i++)
    {
        cout << left
             << setw(4) << i + 1
             << setw(14) << brandToString(collection[i].brand)
             << setw(24) << collection[i].model
             << setw(8) << collection[i].size
             << setw(12) << conditionToString(collection[i].condition)
             << right
             << "$" << setw(11) << collection[i].purchasePrice
             << "$" << setw(11) << collection[i].estimatedValue
             << endl;
    }

    cout << "==========================================================================\n";
}

// ============================================================
// Search Collection Menu
// ============================================================

void searchCollection(const Sneaker collection[], int sneakerCount)
{
    if (sneakerCount == 0)
    {
        cout << "The collection is currently empty.\n";
        return;
    }

    int choice;

    do
    {
        cout << "SEARCH COLLECTION\n";
        cout << "----------------------------\n";
        cout << "1. Search by Brand\n";
        cout << "2. Search by Model\n";
        cout << "3. Return to Main Menu\n";
        cout << "\n";
        cout << "Enter selection: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                searchByBrand(collection, sneakerCount);
                break;

            case 2:
                searchByModel(collection, sneakerCount);
                break;

            case 3:
                break;

            default:
                cout << "Invalid selection.\n";
        }

        cout << endl;

    } while (choice != 3);
}

// ============================================================
// Search by Brand
// ============================================================

void searchByBrand(const Sneaker collection[], int sneakerCount)
{
    displayBrandMenu();

    int brandChoice;
    cout << "Enter brand: ";
    cin >> brandChoice;

    if (cin.fail() || brandChoice < 1 || brandChoice > 7)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid brand selection.\n";
        return;
    }

    SneakerBrand selectedBrand =
        static_cast<SneakerBrand>(brandChoice);

    bool found = false;

    cout << "\nSEARCH RESULTS\n";
    cout << "========================================\n";

    for (int i = 0; i < sneakerCount; i++)
    {
        if (collection[i].brand == selectedBrand)
        {
            found = true;

            cout << "\nSneaker #" << i + 1 << endl;
            cout << "Brand: " << brandToString(collection[i].brand) << endl;
            cout << "Model: " << collection[i].model << endl;
            cout << "Size: " << collection[i].size << endl;
            cout << "Condition: "
                 << conditionToString(collection[i].condition) << endl;
            cout << fixed << setprecision(2);
            cout << "Purchase Price: $"
                 << collection[i].purchasePrice << endl;
            cout << "Estimated Value: $"
                 << collection[i].estimatedValue << endl;
        }
    }

    if (!found)
    {
        cout << "No sneakers found for that brand.\n";
    }
}

// ============================================================
// Search by Model
// ============================================================

void searchByModel(const Sneaker collection[], int sneakerCount)
{
    string searchTerm;

    cout << "Enter model to search for: ";
    getline(cin, searchTerm);

    bool found = false;

    cout << "\nSEARCH RESULTS\n";
    cout << "========================================\n";

    for (int i = 0; i < sneakerCount; i++)
    {
        if (collection[i].model == searchTerm)
        {
            found = true;

            cout << "\nSneaker #" << i + 1 << endl;
            cout << "Brand: " << brandToString(collection[i].brand) << endl;
            cout << "Model: " << collection[i].model << endl;
            cout << "Size: " << collection[i].size << endl;
            cout << "Condition: "
                 << conditionToString(collection[i].condition) << endl;

            cout << fixed << setprecision(2);
            cout << "Purchase Price: $"
                 << collection[i].purchasePrice << endl;
            cout << "Estimated Value: $"
                 << collection[i].estimatedValue << endl;
        }
    }

    if (!found)
    {
        cout << "No sneakers found with that model.\n";
    }
}

// ============================================================
// Sort Collection Menu
// ============================================================

void sortCollection(Sneaker collection[], int sneakerCount)
{
    if (sneakerCount == 0)
    {
        cout << "The collection is currently empty.\n";
        return;
    }

    int choice;

    do
    {
        cout << "SORT COLLECTION\n";
        cout << "----------------------------\n";
        cout << "1. Sort by Brand\n";
        cout << "2. Sort by Model\n";
        cout << "3. Sort by Estimated Value\n";
        cout << "4. Return to Main Menu\n";
        cout << "\n";
        cout << "Enter selection: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                sortByBrand(collection, sneakerCount);
                cout << "Collection sorted by brand.\n";
                break;

            case 2:
                sortByModel(collection, sneakerCount);
                cout << "Collection sorted by model.\n";
                break;

            case 3:
                sortByValue(collection, sneakerCount);
                cout << "Collection sorted by estimated value.\n";
                break;

            case 4:
                break;

            default:
                cout << "Invalid selection.\n";
        }

        cout << endl;

    } while (choice != 4);
}

// ============================================================
// Sort by Brand - Bubble Sort
// ============================================================

void sortByBrand(Sneaker collection[], int sneakerCount)
{
    for (int pass = 0; pass < sneakerCount - 1; pass++)
    {
        for (int i = 0; i < sneakerCount - 1 - pass; i++)
        {
            if (static_cast<int>(collection[i].brand) >
                static_cast<int>(collection[i + 1].brand))
            {
                Sneaker temp = collection[i];
                collection[i] = collection[i + 1];
                collection[i + 1] = temp;
            }
        }
    }
}

// ============================================================
// Sort by Model - Bubble Sort
// ============================================================

void sortByModel(Sneaker collection[], int sneakerCount)
{
    for (int pass = 0; pass < sneakerCount - 1; pass++)
    {
        for (int i = 0; i < sneakerCount - 1 - pass; i++)
        {
            if (collection[i].model > collection[i + 1].model)
            {
                Sneaker temp = collection[i];
                collection[i] = collection[i + 1];
                collection[i + 1] = temp;
            }
        }
    }
}

// ============================================================
// Sort by Estimated Value - Bubble Sort
// ============================================================

void sortByValue(Sneaker collection[], int sneakerCount)
{
    for (int pass = 0; pass < sneakerCount - 1; pass++)
    {
        for (int i = 0; i < sneakerCount - 1 - pass; i++)
        {
            if (collection[i].estimatedValue >
                collection[i + 1].estimatedValue)
            {
                Sneaker temp = collection[i];
                collection[i] = collection[i + 1];
                collection[i + 1] = temp;
            }
        }
    }
}

// ============================================================
// Collection Summary
// ============================================================

void displaySummary(const Sneaker collection[], int sneakerCount)
{
    double totalPurchase = 0.0;
    double totalValue = 0.0;

    for (int i = 0; i < sneakerCount; i++)
    {
        totalPurchase += collection[i].purchasePrice;
        totalValue += collection[i].estimatedValue;
    }

    double gainLoss = totalValue - totalPurchase;

    cout << "COLLECTION SUMMARY\n";
    cout << "========================================\n";
    cout << "\n";

    cout << "Sneakers in Collection: " << sneakerCount << "\n\n";

    cout << fixed << setprecision(2);

    cout << "Total Purchase Cost:   $"
         << totalPurchase << endl;

    cout << "Total Estimated Value:  $"
         << totalValue << endl;

    cout << "                         ---------\n";

    cout << "Total Gain/Loss:        $"
         << gainLoss << endl;

    cout << "\n";

    if (gainLoss > 0)
    {
        cout << "Collection Status: INCREASED IN VALUE\n";
    }
    else if (gainLoss < 0)
    {
        cout << "Collection Status: DECREASED IN VALUE\n";
    }
    else
    {
        cout << "Collection Status: REMAINED THE SAME\n";
    }

    cout << "========================================\n";
}

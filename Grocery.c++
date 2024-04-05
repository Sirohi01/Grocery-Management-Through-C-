#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Product structure
struct Product
{
    string id;
    string name;
    int quantity;
    float price;
};

class StoreManagementSystem
{
private:
    string itemID, itemName;
    int itemQuantity, itemPrice;
    fstream file, file1;
    int totalAmount, Quantity, itemRate;
    string search;
    char _choice;

public:
    void addProduct();
    void viewProducts();
    void editProduct();
    void buyProduct();
    void addBilling();
};

void StoreManagementSystem::addProduct()
{
    cout << "Enter Product ID: ";
    cin >> itemID;
    cout << "Enter Product Name: ";
    cin >> itemName;
    cout << "Enter Product Quantity: ";
    cin >> itemQuantity;
    cout << "Enter Product Price: ";
    cin >> itemPrice;
    file.open("products.txt", ios::out | ios::app);
    file << itemID << " " << itemName << " " << itemQuantity << " " << itemPrice << endl;
    file.close();
}

void StoreManagementSystem::viewProducts()
{
    ifstream file("products.txt");
    Product product;

    cout << "===== Products =====" << endl;
    cout << "ID\tName\tQuantity\tPrice" << endl;
    while (file >> product.id >> product.name >> product.quantity >> product.price)
    {
        cout << product.id << "\t" << product.name << "\t" << product.quantity << "\t\t$" << fixed << setprecision(2) << product.price << endl;
    }
    file.close();
}

void StoreManagementSystem::editProduct()
{
    string id;
    cout << "Enter product ID to edit: ";
    cin >> id;

    fstream file("products.txt");
    Product product;
    bool found = false;

    while (file >> product.id >> product.name >> product.quantity >> product.price)
    {
        if (product.id == id)
        {
            found = true;
            cout << "Enter new product name: ";
            cin >> product.name;
            cout << "Enter new quantity: ";
            cin >> product.quantity;
            cout << "Enter new price: ";
            cin >> product.price;

            file << product.id << " " << product.name << " " << product.quantity << " " << product.price << endl;
            cout << "Product updated successfully!" << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Product not found!" << endl;
    }

    file.close();
}

void StoreManagementSystem::buyProduct()
{
    _choice = 'y';

    while (_choice == 'y')
    {
        file.open("products.txt", ios::in);
        file1.open("temp.txt", ios::out | ios::app);
        Product product;
        file >> product.id >> product.name >> product.quantity >> product.price;
        cout << "Enter Product ID: ";
        cin >> search;
        cout << "Enter Quantity: ";
        cin >> Quantity;

        while (!file.eof())
        {
            if (product.id == search)
            {
                product.quantity = product.quantity - Quantity;
                file1 << product.id << " " << product.name << " " << product.quantity << " " << product.price << endl;

                itemRate = Quantity * product.price;
                totalAmount = totalAmount + itemRate;
                cout << "-----------PayBill----------------" << endl;
                cout << "Total amount: " << totalAmount << endl;
                cout << "---------------------------------\n";
            }
            else
            {
                file1 << product.id << " " << product.name << " " << product.quantity << " " << product.price << endl;
            }
            file >> product.id >> product.name >> product.quantity >> product.price;
        }
        file.close();
        file1.close();
        remove("products.txt");
        rename("temp.txt", "products.txt");

        addBilling();

        cout << "\nContinue Shopping (y/n): ";
        cin >> _choice;
    }
}

void StoreManagementSystem::addBilling()
{
    ofstream bill("billing.txt", ios::out | ios::app);
    bill << "Total amount: $" << totalAmount << endl;
    bill.close();
}

int main()
{
    StoreManagementSystem obj;
    int choice;
    do
    {
        cout << "===== Store Management System =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. View Products" << endl;
        cout << "3. Edit Product" << endl;
        cout << "4. Buy Product" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj.addProduct();
            break;
        case 2:
            obj.viewProducts();
            break;
        case 3:
            obj.editProduct();
            break;
        case 4:
            obj.buyProduct();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}
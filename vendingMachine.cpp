#include <iostream>
#include <map>
#include <string>

using namespace std;

// Product class
class Product {
private:
    string name;
    double price;
    int quantity;

public:
    /*Default constructor for the product code that contains the product code , price and quantity

    the code will represent where the product is located that will help use locate it and select the right product
    */
    Product() : name(""), price(0.0), quantity(0) {}

    // this  constructor will define the product params
    Product(string name, double price, int quantity) : name(name), price(price), quantity(quantity) {}

    string getName() { return name; }
    double getPrice() { return price; }
    bool isAvailable() { return quantity > 0; }

    void dispense() {
        if (quantity > 0) quantity--;
    }

    void restock(int amount) {
        quantity += amount;
    }
};

/* PaymentHandler class that will handle all payment options 
to make sure the price and charges are acurate
this will handle inserting coing into the maching and swiping a card that will use external api to authonticate
the the machine will match the payment with the price if its equal then it will go through and if not it will return the coins
then run the balance of the cost of the purchase iterms 
*/
class PaymentHandler {
private:
    double balance;

public:
    PaymentHandler() : balance(0) {}

    void insertCoin(double amount) {
        balance += amount;
        cout << "Current balance: $" << balance << endl;
    }

    bool swipeCard(double amount) {
        cout << "Credit card charged: $" << amount << endl;
        return true;
    }

    bool validatePayment(double price) {
        if (balance >= price) {
            balance -= price;
            return true;
        }
        return false;
    }

    void refund() {
        cout << "Refunded: $" << balance << endl;
        balance = 0;
    }

    double getBalance() {
        return balance;
    }
};

/* VendingMachine class contains all atributes that will make the machine function as intents
*/ 
class VendingMachine {
private:
    map<string, Product> inventory;
    PaymentHandler paymentHandler;

public:
//this attribute will help add a product which will set product id , name, price and quantity
    void addProduct(string id, Product product) {
        inventory[id] = product;
    }
// this will add or update the proctuct counts
    void restockProduct(string id, int amount) {
        if (inventory.find(id) != inventory.end()) {
            inventory[id].restock(amount);
            cout << "Restocked " << inventory[id].getName() << " by " << amount << endl;
        }
    }
// this will show the available products contained in the machine by looping through the list of products
    void showProducts() {
        cout << "Available Products:" << endl;
        for (auto &item : inventory) {
            Product product = item.second;
            cout << item.first << ": " << product.getName() << " - $" << product.getPrice()
                 << " (Stock: " << (product.isAvailable() ? "Available" : "Out of stock") << ")" << endl;
        }
    }
// this will get the product id and match it with product then go through paymenthandler to validate if yes then depense the product if its available
    void purchaseProduct(string id) {
        if (inventory.find(id) == inventory.end()) {
            cout << "Product not found." << endl;
            return;
        }

        Product &product = inventory[id];

        if (!product.isAvailable()) {
            cout << "Error: Product is out of stock." << endl;
            return;
        }

        if (paymentHandler.validatePayment(product.getPrice())) {
            product.dispense();
            cout << "Dispensed: " << product.getName() << endl;
        } else {
            cout << "Insufficient funds. Please add more money." << endl;
        }
    }
// validate the coins amounts
    void insertCoin(double amount) {
        paymentHandler.insertCoin(amount);
    }
// validates the amount from the card
    void swipeCard(string id) {
        if (inventory.find(id) == inventory.end()) {
            cout << "Product not found." << endl;
            return;
        }

        Product &product = inventory[id];

        if (!product.isAvailable()) {
            cout << "Error: Product is out of stock." << endl;
            return;
        }

        if (paymentHandler.swipeCard(product.getPrice())) {
            product.dispense();
            cout << "Dispensed: " << product.getName() << endl;
        }
    }
//this will return the funds if product not available of funds insaffient
    void refund() {
        paymentHandler.refund();
    }
};

// Main function for simulation
int main() {
    VendingMachine vendingMachine;

    // Add products
    vendingMachine.addProduct("P1", Product("Soda", 1.50, 10));
    vendingMachine.addProduct("P2", Product("Chips", 2.00, 5));
    vendingMachine.addProduct("P3", Product("Candy", 1.00, 0)); // Out of stock

    // Show products
    vendingMachine.showProducts();

    // Customer interactions
    cout << "\nCustomer selects Soda and inserts coins:" << endl;
    vendingMachine.insertCoin(1.00);
    vendingMachine.insertCoin(0.50);
    vendingMachine.purchaseProduct("P1");

    cout << "\nCustomer selects Chips and swipes credit card:" << endl;
    vendingMachine.swipeCard("P2");

    cout << "\nCustomer selects Candy (out of stock):" << endl;
    vendingMachine.purchaseProduct("P3");

    cout << "\nOperator restocks Candy:" << endl;
    vendingMachine.restockProduct("P3", 10);

    cout << "\nUpdated Product List:" << endl;
    vendingMachine.showProducts();

    return 0;
}

#include <iostream>
using namespace std;
int main() {

    const int max_cars = 100;
    const int model_length = 50;
    const int name_length = 50;
    const int phone_length = 20;

    int ids[max_cars];
    double prices[max_cars];
    bool available[max_cars];

    char models[max_cars * model_length] = { 0 };
    char customerNames[max_cars * name_length] = { 0 };
    char customerPhones[max_cars * phone_length] = { 0 };

    int carCount = 0;
    double totalEarnings = 0.0;
    int totalDays = 0;
    int choice;
    char tempInput[50];

    do 
    {
        cout << "\n==============================\n";
        cout << "      CAR RENTAL SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Owner view\n";
        cout << "2. Customer view\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";

        
        while (true) {
            if (!(cin >> choice)) {
                cout << "Invalid. Enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (choice <= 0) {
                cout << "Enter a positive number: ";
            }
            else 
            {
                break;
            }
        }

        if (choice == 1)
        {
            int i = 1;
            while (i == 1) 
            {
                cout << "\n--- OWNER PANEL ---\n";
                cout << "1. View Reports\n";
                cout << "2. Add New Car\n";
                cout << "3. Remove Car\n";
                cout << "4. Edit Car Details\n";
                cout << "5. Edit Rented Customer Details\n";
                cout << "6. Exit\n";
                cout << "Enter Choice: ";

             
                while (true) {
                    if (!(cin >> choice)) {
                        cout << "Invalid. Enter a number: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    else if (choice <= 0) {
                        cout << "Enter a positive number: ";
                    }
                    else {
                        break;
                    }
                }
                

                if (choice == 1) {
                    cout << "\n--- FLEET STATUS ---\n";
                    cout << "Total Earnings: $" << totalEarnings << endl;

                    if (carCount == 0) cout << "No cars in system.\n";

                    for (int j = 0; j < carCount; j++) {
                        cout << "ID: " << ids[j] << " | ";
                        int start = j * model_length;
                        int k = 0;
                        while (models[start + k] != '\0') {
                            cout << models[start + k];
                            k++;
                        }
                        cout << " | ";
                        if (available[j]) {
                            cout << "Available\n";
                        }
                        else {
                            cout << "RENTED by ";
                            int cStart = j * name_length;
                            k = 0;
                            while (customerNames[cStart + k] != '\0') {
                                cout << customerNames[cStart + k];
                                k++;
                            }
                            cout << endl;
                        }
                    }
                }

                else if (choice == 2) {
                    if (carCount < max_cars) {
                        cout << "Enter ID: ";
                        while (true) {
                            int inputID;
                            if (!(cin >> inputID)) {
                                cout << "Invalid. Enter Number: ";
                                cin.clear(); cin.ignore(1000, '\n');
                            }
                            else if (inputID <= 0) {
                                cout << "ID must be > 0. Enter ID: ";
                            }
                            else {
                                bool exists = false;
                                for (int x = 0; x < carCount; x++) {
                                    if (ids[x] == inputID) { exists = true; break; }
                                }

                                if (exists) {
                                    cout << "ID already exists! Enter unique ID: ";
                                }
                                else {
                                    ids[carCount] = inputID;
                                    break;
                                }
                            }
                        }

                        cout << "Enter Model (Letters only): ";
                        cin.ignore();
                        while (true) {
                            cin.getline(tempInput, 50);
                            bool valid = true;
                            if (tempInput[0] == '\0') valid = false;
                            int k = 0;
                            while (tempInput[k] != '\0') {
                                char c = tempInput[k];
                                if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
                                    valid = false;
                                    break;
                                }
                                k++;
                            }
                            if (valid) break;
                            cout << "Invalid. Letters/Spaces only: ";
                        }

                        int start = carCount * model_length;
                        int k = 0;
                        while (tempInput[k] != '\0') {
                            models[start + k] = tempInput[k];
                            k++;
                        }
                        models[start + k] = '\0';

                        cout << "Enter Price: $";
                        while (true) {
                            if (!(cin >> prices[carCount])) {
                                cout << "Invalid number. Enter Price: $";
                                cin.clear(); cin.ignore(1000, '\n');
                            }
                            else if (prices[carCount] <= 0) {
                                cout << "Price must be > 0. Enter Price: $";
                            }
                            else {
                                break;
                            }
                        }

                        available[carCount] = true;
                        carCount++;
                        cout << "Car Added.\n";
                    }
                    else {
                        cout << "Fleet full!\n";
                    }
                }

                else if (choice == 3) {
                    if (carCount == 0) cout << "No cars to remove.\n";
                    else {
                        int removeID;
                        cout << "Enter ID to remove: ";
                        cin >> removeID;

                        int idx = -1;
                        for (int j = 0; j < carCount; j++) {
                            if (ids[j] == removeID) { idx = j; break; }
                        }

                        if (idx == -1) cout << "ID not found.\n";
                        else {
                            for (int j = idx; j < carCount - 1; j++) {
                                ids[j] = ids[j + 1];
                                prices[j] = prices[j + 1];
                                available[j] = available[j + 1];
                                for (int k = 0; k < model_length; k++) models[j * model_length + k] = models[(j + 1) * model_length + k];
                                for (int k = 0; k < name_length; k++) customerNames[j * name_length + k] = customerNames[(j + 1) * name_length + k];
                                for (int k = 0; k < phone_length; k++) customerPhones[j * phone_length + k] = customerPhones[(j + 1) * phone_length + k];
                            }
                            carCount--;
                            cout << "Removed.\n";
                        }
                    }
                }

                else if (choice == 4) {
                    int editID;
                    cout << "Enter ID to edit: ";
                    cin >> editID;

                    int idx = -1;
                    for (int j = 0; j < carCount; j++) {
                        if (ids[j] == editID) { idx = j; break; }
                    }

                    if (idx == -1) cout << "ID not found.\n";
                    else {
                        cout << "Enter New Model (Letters): ";
                        cin.ignore();
                        while (true) {
                            cin.getline(tempInput, 50);
                            bool valid = true;
                            if (tempInput[0] == '\0') valid = false;
                            int k = 0;
                            while (tempInput[k] != '\0') {
                                char c = tempInput[k];
                                if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
                                    valid = false;
                                    break;
                                }
                                k++;
                            }
                            if (valid) break;
                            cout << "Invalid. Letters/Spaces only: ";
                        }

                        int start = idx * model_length;                       
                        for (int z = 0; z < model_length; z++)
                        {
                            models[start + z] = '\0';
                        }

                       
                        int k = 0;
                        while (tempInput[k] != '\0')
                        {
                            models[start + k] = tempInput[k];
                            k++;
                        }
                        models[start + k] = '\0';


                        cout << "Enter New Price: $";
                        while (true) {
                            if (!(cin >> prices[idx])) {
                                cout << "Invalid number. Enter Price: $";
                                cin.clear(); cin.ignore(1000, '\n');
                            }
                            else if (prices[idx] <= 0) {
                                cout << "Price must be > 0. Enter Price: $";
                            }
                            else {
                                break;
                            }
                        }

                        cout << "Enter Status (1=Avail, 0=Rented): ";
                        cin >> available[idx];

                        if (!available[idx]) {
                            cin.ignore();
                            cout << "Status set to Rented. Enter Customer Name: ";
                            cin.getline(tempInput, 50);

                            int nStart = idx * name_length;
                            for (int z = 0; z < name_length; z++) customerNames[nStart + z] = '\0';
                            k = 0;
                            while (tempInput[k] != '\0') { customerNames[nStart + k] = tempInput[k]; k++; }
                            customerNames[nStart + k] = '\0';

                            cout << "Enter Customer Phone: ";
                            cin.getline(tempInput, 50);
                            int pStart = idx * phone_length;
                            for (int z = 0; z < phone_length; z++) customerPhones[pStart + z] = '\0';
                            k = 0;
                            while (tempInput[k] != '\0') { customerPhones[pStart + k] = tempInput[k]; k++; }
                            customerPhones[pStart + k] = '\0';
                        }
                        else {
                            int nStart = idx * name_length;
                            int pStart = idx * phone_length;
                            for (int z = 0; z < name_length; z++) customerNames[nStart + z] = '\0';
                            for (int z = 0; z < phone_length; z++) customerPhones[pStart + z] = '\0';
                        }

                        cout << "Updated.\n";
                    }
                }

                else if (choice == 5) {
                    cin.ignore();
                    cout << "Enter Customer Name to search: ";
                    cin.getline(tempInput, 50);

                    int idx = -1;
                    for (int j = 0; j < carCount; j++) {
                        if (!available[j]) {
                            bool match = true;
                            int start = j * name_length;
                            int k = 0;
                            while (customerNames[start + k] != '\0' || tempInput[k] != '\0') {
                                if (customerNames[start + k] != tempInput[k]) { match = false; break; }
                                k++;
                            }
                            if (match) { idx = j; break; }
                        }
                    }

                    if (idx != -1) {
                        cout << "Found in Car ID: " << ids[idx] << endl;

                        cout << "Enter New Name (Letters): ";
                        while (true) {
                            cin.getline(tempInput, 50);
                            bool valid = true;
                            if (tempInput[0] == '\0') valid = false;
                            int k = 0;
                            while (tempInput[k] != '\0') {
                                char c = tempInput[k];
                                if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) { valid = false; break; }
                                k++;
                            }
                            if (valid) break;
                            cout << "Letters only: ";
                        }
                        int start = idx * name_length;
                        for (int z = 0; z < name_length; z++) customerNames[start + z] = '\0';
                        int k = 0;
                        while (tempInput[k] != '\0') { customerNames[start + k] = tempInput[k]; k++; }
                        customerNames[start + k] = '\0';

                        cout << "Enter New Phone (11 digits): ";
                        while (true) {
                            cin.getline(tempInput, 50);
                            bool valid = true;
                            int len = 0;
                            while (tempInput[len] != '\0') {
                                if (tempInput[len] < '0' || tempInput[len] > '9') valid = false;
                                len++;
                            }
                            if (!valid) { cout << "Digits only: "; continue; }
                            if (len != 11) { cout << "Must be 11 digits: "; continue; }
                            break;
                        }
                        start = idx * phone_length;
                        for (int z = 0; z < phone_length; z++) customerPhones[start + z] = '\0';
                        k = 0;
                        while (tempInput[k] != '\0') { customerPhones[start + k] = tempInput[k]; k++; }
                        customerPhones[start + k] = '\0';

                        cout << "Customer Updated.\n";
                    }
                    else {
                        cout << "Customer not found.\n";
                    }
                }

                else if (choice == 6) break;
            }
        }

        else if (choice == 2) {
			cout << "\n--- CUSTOMER PANEL ---\n";
            cout << "1. Rent\n2. Back\nChoice: ";

            
            while (true) {
                if (!(cin >> choice)) {
                    cout << "Invalid. Enter a number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else if (choice <= 0) {
                    cout << "Enter a positive number: ";
                }
                else {
                    break;
                }
            }
            

            if (choice == 1) {
				cout << "\n--- RENT A CAR ---\n";
                if (carCount == 0) cout << "No cars.\n";
                else {
                    cout << "\n--- AVAILABLE CARS ---\n";
                    for (int j = 0; j < carCount; j++) {
                        if (available[j]) {
                            cout << "ID: " << ids[j] << " | ";
                            int start = j * model_length;
                            int k = 0;
                            while (models[start + k] != '\0') { cout << models[start + k]; k++; }
                            cout << " | $" << prices[j] << endl;
                        }
                    }

                    int rentID;
                    cout << "Enter ID: ";
                    cin >> rentID;

                    int idx = -1;
                    for (int j = 0; j < carCount; j++) {
                        if (ids[j] == rentID) { idx = j; break; }
                    }

                    if (idx != -1 && available[idx]) {
                        cin.ignore();

                        cout << "Enter Name (Letters): ";
                        while (true) {
                            cin.getline(tempInput, 50);
                            bool valid = true;
                            if (tempInput[0] == '\0') valid = false;
                            int k = 0;
                            while (tempInput[k] != '\0') {
                                char c = tempInput[k];
                                if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) { valid = false; break; }
                                k++;
                            }
                            if (valid) break;
                            cout << "Letters only: ";
                        }
                        int start = idx * name_length;
                        int k = 0;
                        while (tempInput[k] != '\0') { customerNames[start + k] = tempInput[k]; k++; }
                        customerNames[start + k] = '\0';

                        cout << "Enter Phone (11 digits): ";
                        while (true) {
                            cin.getline(tempInput, 50);
                            bool valid = true;
                            int len = 0;
                            while (tempInput[len] != '\0') {
                                if (tempInput[len] < '0' || tempInput[len] > '9') valid = false;
                                len++;
                            }
                            if (!valid) { cout << "Digits only: "; continue; }
                            if (len != 11) { cout << "Must be 11 digits: "; continue; }
                            break;
                        }
                        start = idx * phone_length;
                        k = 0;
                        while (tempInput[k] != '\0') { customerPhones[start + k] = tempInput[k]; k++; }
                        customerPhones[start + k] = '\0';

                        int days;
                        cout << "Days: ";
                        while (true) {
                            if (!(cin >> days)) { cout << "Invalid. Enter days: "; cin.clear(); cin.ignore(1000, '\n'); }
                            else if (days <= 0) cout << "Must be > 0. Enter days: ";
                            else break;
                        }

                        char ins;
                        double insCost = 0;
                        cout << "Insurance ($20)? (y/n): ";
                        while (true) {
                            cin >> ins;
                            if (ins == 'y' || ins == 'Y' || ins == 'n' || ins == 'N') break;
                            cout << "Enter y or n: "; cin.clear(); cin.ignore(1000, '\n');
                        }
                        if (ins == 'y' || ins == 'Y') insCost = 20;

                        double total = prices[idx] * days;
                        bool discount = false;
                        if (days > 7) { total *= 0.90; discount = true; }
                        total += insCost;

                        available[idx] = false;
                        totalEarnings += total;
                        totalDays += days;

                        cout << "\n** INVOICE **\n";
                        cout << "Car: ";
                        start = idx * model_length;
                        k = 0;
                        while (models[start + k] != '\0') { cout << models[start + k]; k++; }
                        cout << endl;
                        cout << "Customer: ";
                        start = idx * name_length;
                        k = 0;
                        while (customerNames[start + k] != '\0') { cout << customerNames[start + k]; k++; }
                        cout << endl;
                        cout << "Total: $" << total << endl;
                    }
                    else {
                        cout << "Error: Not found or rented.\n";
                    }
                }
            }
        }

        else if (choice == 3) {
            cout << "\n--- FINAL REPORT ---\n";
            cout << "Cars Rented Today:\n";
            bool any = false;
            for (int j = 0; j < carCount; j++) {
                if (!available[j]) {
                    any = true;
                    cout << "ID: " << ids[j] << " | ";
                    int start = j * model_length;
                    int k = 0;
                    while (models[start + k] != '\0') { cout << models[start + k]; k++; }
                    cout << endl;
                }
            }
            if (!any) cout << "None.\n";
            cout << "Exiting...\n";
            break;
        }

    } while (choice != 0);

    return 0;
}
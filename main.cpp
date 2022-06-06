#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int returnToMenu = 0; // INCREMENTED ONLY TO END PROGRAM

class Client {
  public:
    void ListInfo();
    void OptionSelect();
    void AddEntry();
    void ChangeEntry();

  private:
    ifstream clientIFS;
    ofstream clientOFS;
    ofstream changeClient;
    ifstream makeVector;
    string newClient;
    string userInput;
    string tempString;
    string addInput;
    string clientInfo;
    int counter = 0;
    int userChoice;
    vector<string> clientList;
    vector<string> changeList;
    unsigned int i;
    
}; 
// MEMBER FUNCTIONS COPIED FOR ALL CLASSES (excluding main menu) -------
void Client::ListInfo() {
  clientIFS.open("client.txt");
  if(!clientIFS.is_open()) { 
    cout << "Could not open client.txt" << endl;
    abort();
    }

  while (!clientIFS.fail()) { //takes info from file and populates vector to be manipulated later
    getline(clientIFS, clientInfo);
    clientList.push_back(clientInfo);

    if (clientIFS.eof()) {break;}
  }
  
  clientIFS.close();
  cout << endl;

  //one form of manipulation is for formatting menus that contain data
  for (i = 0; i < clientList.size(); ++i) {
    ++counter;
    cout << counter << ": " << clientList.at(i) << " sales to date." << endl;
  }
  counter = 0;
  clientList.clear();
}

void Client::OptionSelect() {
  cout << "\nWhat would you like to do with these clients?" << endl;
  cout << "   1: Add a new client. \n   2: Update client info." << endl;
  cout << "You can also enter 0 to go back to the start! \n" << endl;
  cin >> userChoice;

  if ((userChoice > 2) || (userChoice < 0)) { //creates loop so program does not end abruptly
    cout << "INVALID ENTRY: Please enter a number between 0 and 2." << endl;
    OptionSelect();
  } 
  switch (userChoice) {
    case 0:
    break;

    case 1:
    AddEntry();
    break;
    
    case 2:
    ChangeEntry();
    break;
  }
  userChoice = 9999;
}

void Client::AddEntry() {
  clientOFS.open("client.txt", ios::app);
  if (!clientOFS.is_open()) {
    cout << "Unable to open client.txt." << endl;
    abort();
  }

  cout << "Please enter the new client information you would like to add. \nPress enter when finished.\n" << endl;

  //as user inputs info, string newClient is added onto and formatted for text file/database
  
  cout << "Enter LAST NAME" << endl;
  cin >> newClient;

  cout << "Enter FIRST NAME" << endl;
  cin >> userInput;
  newClient += " " + userInput;

  cout << "Enter SHORT ADDRESS (ex. 1234 Internet Street)" << endl;
  cin.ignore();
  getline(cin, userInput);
  newClient += " " + userInput;

  cout << "Enter SALES TO DATE (ex. 55)" << endl;
  cin >> userInput;
  newClient += " " + userInput;
  
  clientOFS << endl << newClient;
  clientOFS.close();

  ListInfo();
  OptionSelect();
}

void Client::ChangeEntry() {
  makeVector.open("client.txt");
  if (!makeVector.is_open()) {
    cout << "Failed opening client.txt" << endl;
  }

  while(!makeVector.fail()) {
    (getline(makeVector, tempString));
    
   changeList.push_back(tempString);

    if (makeVector.eof()) {
      break;
      }
    }
  
  makeVector.close();

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << " sales to date." << endl;
  }
  counter = 0;

  cout << "Which client would you like to edit?" << endl;
  cout << "Please enter the number of the user." << endl;

  while (counter == 0) { //another loop in case of user error
    cin >> userChoice;
    if ((userChoice > changeList.size()) || (userChoice < 1)) {
      cout << "Please enter a valid client number.   ";
      continue;
    }


    //same strategy used in AddEntry to format user input in pieces
    cout << "\nEnter LAST NAME" << endl;
    cin >> tempString;
  
    cout << "Enter FIRST NAME" << endl;
    cin >> addInput;
    tempString += " " + addInput;
  
    cout << "Enter SHORT ADDRESS (ex. 1234 Internet Street)" << endl;
    cin.ignore();
    getline(cin, addInput);
    tempString += " " + addInput;
  
    cout << "Enter SALES TO DATE (ex. 55)" << endl;
    cin >> addInput;
    tempString += " " + addInput;
    cout << endl;
    
   changeList.at(userChoice - 1) = tempString;
    userChoice = 9999;

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << " sales to date." << endl;
  }
  counter = 0;

    cout << "Would you like to edit another client? \n   1: Yes\n   2: No\nNOTE: Changes will ONLY fully save to database when finished editing (By pressing 2 here.)" << endl;
    //this is because even though the user is shown updates to the database in the form of the vector, the database is not updated until the end
    cin >> userChoice;

    switch (userChoice) {
      default:
      cout << "Please enter a valid number." << endl;
      cin >> userChoice;
      

      case 1:
      ChangeEntry();
      break;

      case 2:
      //RETURN TO MENU
      ++counter;
      break;
    }
  }
  //as mentioned above, here is where the database is finally updated, all changes update at one time
  changeClient.open("client.txt");
  if (!changeClient.is_open()) {
    cout << "Failed opening client.txt" << endl;
  }
  counter = 0;
  for (i = 0; i < changeList.size(); ++i) {
    if (counter == 0) {
      changeClient << changeList.at(i);
      ++counter;
    }
    else { changeClient << endl << changeList.at(i); }
  }
  changeClient.close();
  changeList.clear();
  cout << endl << endl;
}
// MEMBER FUNCTIONS COPIED FOR ALL CLASSES (excluding main menu) -------




class SalesRep {
  public:
    void ListInfo();
    void OptionSelect();
    void AddEntry();
    void ChangeEntry();
    void SalesBonus();

  private:
    ifstream salesrepIFS;
    ofstream salesrepOFS;
    ofstream changeSalesRep;
    ifstream makeVector;
    string newSalesRep;
    string userInput;
    string tempString;
    string addInput;
    string salesrepInfo;
    int counter = 0;
    int userChoice;
    vector<string> salesrepList;
    vector<string> changeList;
    unsigned int i;
    vector<int>calcBonus;
    vector<int>finalBonus;
    string loadTotal;
    int addTotal;
    char checkTotal;
    string dummy;
    
};
void SalesRep::ListInfo() {
  salesrepIFS.open("salesrep.txt");
  if(!salesrepIFS.is_open()) { 
    cout << "Could not open salesrep.txt" << endl;
    abort();
    }

  while (!salesrepIFS.fail()) {
    getline(salesrepIFS, salesrepInfo);
    salesrepList.push_back(salesrepInfo);

    if (salesrepIFS.eof()) {break;}
  }
  
  salesrepIFS.close();
  cout << endl;
  for (i = 0; i < salesrepList.size(); ++i) {
    ++counter;
    cout << counter << ": " << salesrepList.at(i) << " sales to date." << endl;
  }
  counter = 0;
  salesrepList.clear();
}

void SalesRep::OptionSelect() {
  cout << "\nWhat would you like to do with these Sales Representatives?" << endl;
  cout << "   1: Add a new Sales Rep. \n   2: Update Sales Rep info. \n   3: View Sales Bonus" << endl;
  cout << "You can also enter 0 to go back to the start! \n" << endl;
  cin >> userChoice;

  if ((userChoice > 3) || (userChoice < 0)) {
    cout << "INVALID ENTRY: Please enter a number between 0 and 2." << endl;
    OptionSelect();
  } 
  switch (userChoice) {
    case 0:
    break;

    case 1:
    AddEntry();
    break;
    
    case 2:
    ChangeEntry();
    break;

    case 3:
    SalesBonus();
    break;
  }
  userChoice = 9999;
}

void SalesRep::AddEntry() {
  salesrepOFS.open("salesrep.txt", ios::app);
  if (!salesrepOFS.is_open()) {
    cout << "Unable to open salesrep.txt." << endl;
    abort();
  }

  cout << "Please enter the new salesrep information you would like to add. \nPress enter when finished.\n" << endl;
  
  cout << "Enter LAST NAME" << endl;
  cin >> newSalesRep;

  cout << "Enter FIRST NAME" << endl;
  cin >> userInput;
  newSalesRep += " " + userInput;

  cout << "Enter SHORT ADDRESS (ex. 1234 Internet Street)" << endl;
  cin.ignore();
  getline(cin, userInput);
  newSalesRep += " " + userInput;

  cout << "Enter SALES TO DATE (ex. 55)" << endl;
  cin >> userInput;
  newSalesRep += " " + userInput;
  
  salesrepOFS << endl << newSalesRep;
  salesrepOFS.close();

  ListInfo();
  OptionSelect();
}

void SalesRep::ChangeEntry() {
  makeVector.open("salesrep.txt");
  if (!makeVector.is_open()) {
    cout << "Failed opening salesrep.txt" << endl;
  }

  while(!makeVector.fail()) {
    (getline(makeVector, tempString));
    
   changeList.push_back(tempString);

    if (makeVector.eof()) {
      break;
      }
    }
  
  makeVector.close();

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << " sales to date." << endl;
  }
  counter = 0;

  cout << "Which Sales Representative would you like to edit?" << endl;
  cout << "Please enter the number of the user." << endl;

  while (counter == 0) {
    cin >> userChoice;
    if ((userChoice > changeList.size()) || (userChoice < 1)) {
      cout << "Please enter a valid salesrep number.   ";
      continue;
    }
    
    cout << "\nEnter LAST NAME" << endl;
    cin >> tempString;
  
    cout << "Enter FIRST NAME" << endl;
    cin >> addInput;
    tempString += " " + addInput;
  
    cout << "Enter SHORT ADDRESS (ex. 1234 Internet Street)" << endl;
    cin.ignore();
    getline(cin, addInput);
    tempString += " " + addInput;
  
    cout << "Enter SALES TO DATE (ex. 55)" << endl;
    cin >> addInput;
    tempString += " " + addInput;
    cout << endl;
    
   changeList.at(userChoice - 1) = tempString;
    userChoice = 9999;

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << " sales to date." << endl;
  }
  counter = 0;

    cout << "Would you like to edit another Sales Representative? \n   1: Yes\n   2: No\nNOTE: Changes will ONLY fully save to database when finished editing (By pressing 2 here.)" << endl;
    cin >> userChoice;

    switch (userChoice) {
      default:
      cout << "Please enter a valid number." << endl;
      cin >> userChoice;
      

      case 1:
      ChangeEntry();
      break;

      case 2:
      //RETURN TO MENU
      ++counter;
      break;
    }
  }

  changeSalesRep.open("salesrep.txt");
  if (!changeSalesRep.is_open()) {
    cout << "Failed opening salesrep.txt" << endl;
  }
  counter = 0;
  for (i = 0; i < changeList.size(); ++i) {
    if (counter == 0) {
      changeSalesRep << changeList.at(i);
      ++counter;
    }
    else { changeSalesRep << endl << changeList.at(i); }
  }
  changeSalesRep.close();
  changeList.clear();
  cout << endl << endl;
}

void SalesRep::SalesBonus() {
  //produces a bonus for sales representatives
  salesrepIFS.open("salesrep.txt");
  if(!salesrepIFS.is_open()) { 
    cout << "Could not open salesrep.txt" << endl;
    abort();
    }

  while (!salesrepIFS.fail()) {
    getline(salesrepIFS, salesrepInfo);
    salesrepList.push_back(salesrepInfo);
    if (salesrepIFS.eof()) {break;}
  }
  salesrepIFS.close();

  salesrepIFS.open("salesrep.txt");
  if(!salesrepIFS.is_open()) { 
    cout << "Could not open salesrep.txt" << endl;
    abort();
    }
  while (!salesrepIFS.fail()) { //sorts numerical values from non numerical values by checking the first character of each element
    salesrepIFS >> loadTotal;
    checkTotal = loadTotal.at(0);
    if (isdigit(checkTotal)) {
      addTotal = stoi(loadTotal); //converts sorted numbers from string to integer for manipulation
      calcBonus.push_back(addTotal);
    }
    if (salesrepIFS.eof()) {break;}
  }
  
  salesrepIFS.close();
  cout << endl;

  for (i = 0; i < calcBonus.size(); ++i){ //for simplicity, bonus is sales*2
    if (calcBonus.at(i) < 1000) {
    calcBonus.at(i) = calcBonus.at(i) * 2;
    finalBonus.push_back(calcBonus.at(i));
    }
  }
  cout << endl;
  
  for (i = 0; i < salesrepList.size(); ++i) {
    ++counter;
    cout << counter << ": " << salesrepList.at(i) << " sales to date." << "$" << finalBonus.at(i) << ".00 BONUS PAY. \n" << endl;
  }
  counter = 0;
  salesrepList.clear();
  calcBonus.clear();
  cout << "Press enter to continue" << endl;
  cin.ignore();
  getline(cin, dummy); //used so program waits for enter
  
  ListInfo();
  OptionSelect();
}







class Products {
  public:
    void ListInfo();
    void OptionSelect();
    void AddEntry();
    void ChangeEntry();
    void SalesReport();

  private:
    ifstream productIFS;
    ofstream productOFS;
    ofstream changeProducts;
    ifstream makeVector;
    string newProducts;
    string userInput;
    string tempString;
    string addInput;
    string productInfo;
    int counter = 0;
    int userChoice;
    vector<string> productList;
    vector<string> changeList;
    unsigned int i;
    string rawProduct;
    int convertProduct;
    char checkProduct;
    vector<int> productPrices;
    vector<string> tempVector;
    string productName;
    vector<string> nameList;
    ifstream saleIFS;
    string loadTotal;
    char checkTotal;
    int addTotal;
    vector<int> calcTotal;
    int salesReport;
    string dummy;
    
};
void Products::ListInfo() {
  productIFS.open("product.txt");
  if(!productIFS.is_open()) { 
    cout << "Could not open product.txt" << endl;
    abort();
    }

  while (!productIFS.fail()) {
    getline(productIFS, productInfo);
    productList.push_back(productInfo);

    if (productIFS.eof()) {break;}
  }
  
  productIFS.close();
  cout << endl;
  for (i = 0; i < productList.size(); ++i) {
    ++counter;
    cout << counter << ": " << productList.at(i) << "." << endl;
  }
  counter = 0;
  productList.clear();
}

void Products::OptionSelect() {
  cout << "\nWhat would you like to do with these products?" << endl;
  cout << "   1: Add a new product. \n   2: Update product info. \n   3: View Sales Report." << endl;
  cout << "You can also enter 0 to go back to the start! \n" << endl;
  cin >> userChoice;

  if ((userChoice > 3) || (userChoice < 0)) {
    cout << "INVALID ENTRY: Please enter a number between 0 and 2." << endl;
    OptionSelect();
  } 
  switch (userChoice) {
    case 0:
    break;

    case 1:
    AddEntry();
    break;
    
    case 2:
    ChangeEntry();
    break;

    case 3:
    SalesReport();
    break;
  }
  userChoice = 9999;
}

void Products::AddEntry() {
  productOFS.open("product.txt", ios::app);
  if (!productOFS.is_open()) {
    cout << "Unable to open product.txt." << endl;
    abort();
  }

  cout << "Please enter the new product information you would like to add. \nPress enter when finished.\n" << endl;
    
  cout << "Enter PRODUCT NAME" << endl;
  cin.ignore();
  getline(cin, newProducts);

  cout << "Enter PRODUCT PRICE in dollar amount (ex. 55)" << endl;
  cin >> userInput;
  newProducts += " $" + userInput + ".00";
  
  productOFS << endl << newProducts;
  productOFS.close();

  ListInfo();
  OptionSelect();
}

void Products::ChangeEntry() {
  makeVector.open("product.txt");
  if (!makeVector.is_open()) {
    cout << "Failed opening product.txt" << endl;
  }

  while(!makeVector.fail()) {
    (getline(makeVector, tempString));
    
   changeList.push_back(tempString);

    if (makeVector.eof()) {
      break;
      }
    }
  
  makeVector.close();

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << "." << endl;
  }
  counter = 0;
  
  cout << "Which product would you like to edit?" << endl;
  cout << "Please enter the number of the product." << endl;

  while (counter == 0) {
    cin >> userChoice;
    if ((userChoice > changeList.size()) || (userChoice < 1)) {
      cout << "Please enter a valid product number.   ";
      continue;
    }
    
    cout << "Enter PRODUCT NAME" << endl;
    cin.ignore();
    getline(cin, tempString);
  
    cout << "Enter PRODUCT PRICE in dollar amount (ex. 55)" << endl;
    cin >> addInput;
    tempString += " " + addInput;
    cout << endl;
    
   changeList.at(userChoice - 1) = tempString;
    userChoice = 9999;

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << "." << endl;
  }
  counter = 0;

    cout << "Would you like to edit another product? \n   1: Yes\n   2: No\nNOTE: Changes will ONLY fully save to database when finished editing (By pressing 2 here.)" << endl;
    cin >> userChoice;

    switch (userChoice) {
      default:
      cout << "Please enter a valid number." << endl;
      cin >> userChoice;
      

      case 1:
      ChangeEntry();
      break;

      case 2:
      //RETURN TO MENU
      ++counter;
      break;
    }
  }
  
  changeProducts.open("product.txt");
  if (!changeProducts.is_open()) {
    cout << "Failed opening product.txt" << endl;
  }
  counter = 0;
  for (i = 0; i < changeList.size(); ++i) {
    if (counter == 0) {
      changeProducts << changeList.at(i);
      ++counter;
    }
    else { changeProducts << endl << changeList.at(i); }
  }
  changeProducts.close();
  changeList.clear();
  cout << endl << endl;
}

void Products::SalesReport() {
  //multiplies number of items sold by price of item for total profit
    saleIFS.open("sale.txt");
  if(!saleIFS.is_open()) { 
    cout << "Could not open sale.txt" << endl;
    abort();
  }

  while (!saleIFS.fail()) {
    saleIFS >> loadTotal;
    checkTotal = loadTotal.at(0);
    if (isdigit(checkTotal)) {
      addTotal = stoi(loadTotal);
      calcTotal.push_back(addTotal);
    }
    if (saleIFS.eof()) {break;}
  }
  
  productIFS.open("product.txt");
  if(!productIFS.is_open()) { 
    cout << "Could not open product.txt" << endl;
    abort();
  }
  while (!productIFS.fail()) {
    getline(productIFS, productInfo);
    productList.push_back(productInfo);
    if (productIFS.eof()) {
      break;
    }
  }
  productIFS.close();

  productIFS.open("product.txt");
  if(!productIFS.is_open()) {
    cout << "Could not open product.txt" << endl;
    abort();
  }
  
  while (!productIFS.fail()) {
    getline(productIFS, productName); //brute force to remove all digits and periods not needed for display
    productName.erase(remove(productName.begin(), productName.end(), '0'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '1'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '2'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '3'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '4'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '5'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '6'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '7'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '8'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '9'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '$'), productName.end());
    productName.erase(remove(productName.begin(), productName.end(), '.'), productName.end());
    nameList.push_back(productName);
    if (productIFS.eof()) {
      break;
    }
  }
  productIFS.close();

  productIFS.open("product.txt");
  if(!productIFS.is_open()) { 
    cout << "Could not open product.txt" << endl;
    abort();
    }
  while (!productIFS.fail()) { //used to further clean up file info for display
    productIFS >> rawProduct;
    checkProduct = rawProduct.at(0);
    if (checkProduct == '$') {
      rawProduct.erase(0,1);
      rawProduct.erase(rawProduct.size() - 3, rawProduct.size() - 1);
      tempVector.push_back(rawProduct);
    }
    
    if (productIFS.eof()) {break;}
  }
  
  for (i = 0; i < tempVector.size() - 1; ++i) { //strategy used earlier to sort data between numerical and alphabetic
    tempString = tempVector.at(i);
    checkProduct = tempString.at(0);
    if (isdigit(checkProduct)) {
      convertProduct = stoi(tempString);
      productPrices.push_back(convertProduct);
    }
  }
  if (isdigit(checkProduct)) { 
      convertProduct = stoi(rawProduct);
      productPrices.push_back(convertProduct);
    }
  cout << "Total Sales Report: " << endl;
  
  for (i = 0; i < calcTotal.size(); ++i) { //after sorting, multiplies vector containing price with vector containing number sold
    ++counter;
    salesReport = calcTotal.at(i) * productPrices.at(i);
    cout << counter << ": $" << salesReport << ".00 net income for " << nameList.at(i) << endl;
  }

  productPrices.clear();
  tempVector.clear();
  nameList.clear();
  
  
  cout << "Press enter to continue" << endl;
  cin.ignore();
  getline(cin, dummy);
  
  ListInfo();
  OptionSelect();
}





class Sale {
  public:
    void ListInfo();
    void OptionSelect();
    void AddEntry();
    void ChangeEntry();
    void ClientPurchase();

  private:
    ifstream saleIFS;
    ofstream saleOFS;
    ofstream changeSale;
    ifstream makeVector;
    string newSale;
    string userInput;
    string tempString;
    string addInput;
    string saleInfo;
    int counter = 0;
    int userChoice;
    string loadTotal;
    int addTotal;
    char checkTotal;
    vector<string> saleList;
    vector<int> calcTotal;
    vector<string> changeList;
    unsigned int i;
    ifstream clientIFS; 
    ofstream clientOFS;
    vector<string> clientList;
    vector<int> clientNum;
    vector<int> saleNum;
    string tempString2;
    int convertString;
    char tempChar;
    int tempInt;
    int clientChoice;
    int productChoice;
    int numPurchased;
    string purchasedString;
    string dummy;
    
};
void Sale::ListInfo() {
  saleIFS.open("sale.txt");
  if(!saleIFS.is_open()) { 
    cout << "Could not open sale.txt" << endl;
    abort();
    }

  while (!saleIFS.fail()) {
    getline(saleIFS, saleInfo);
    saleList.push_back(saleInfo);
    if (saleIFS.eof()) {break;}
  }
  saleIFS.close();

  saleIFS.open("sale.txt");
  if(!saleIFS.is_open()) { 
    cout << "Could not open sale.txt" << endl;
    abort();
    }
  while (!saleIFS.fail()) {
    saleIFS >> loadTotal;
    checkTotal = loadTotal.at(0);
    if (isdigit(checkTotal)) {
      addTotal = stoi(loadTotal);
      calcTotal.push_back(addTotal);
    }
    if (saleIFS.eof()) {break;}
  }
  
  saleIFS.close();
  cout << endl;

  addTotal = 0;
  for (i = 0; i < calcTotal.size(); ++i){
    addTotal += calcTotal.at(i);
  }
  
  for (i = 0; i < saleList.size(); ++i) {
    ++counter;
    cout << counter << ": " << saleList.at(i) << " sale to date." << endl;
  }
  cout << "Total Sales: " << addTotal << endl;
  counter = 0;
  saleList.clear();
  calcTotal.clear();
}

void Sale::OptionSelect() {
  cout << "\nWhat would you like to do with these sales?" << endl;
  cout << "   1: Add a new sale. \n   2: Update sale info. \n   3: Make a purchase for a client." << endl;
  cout << "You can also enter 0 to go back to the start! \n" << endl;
  cin >> userChoice;

  if ((userChoice > 3) || (userChoice < 0)) {
    cout << "INVALID ENTRY: Please enter a number between 0 and 3." << endl;
    OptionSelect();
  } 
  switch (userChoice) {
    case 0:
    break;

    case 1:
    AddEntry();
    break;
    
    case 2:
    ChangeEntry();
    break;

    case 3:
    ClientPurchase();
    break;
  }
  userChoice = 9999;
}

void Sale::AddEntry() {
  saleOFS.open("sale.txt", ios::app);
  if (!saleOFS.is_open()) {
    cout << "Unable to open sale.txt." << endl;
    abort();
  }

  cout << "Please enter the new sale information you would like to add. \nPress enter when finished.\n" << endl;
  
  cout << "Enter PRODUCT NAME" << endl;
  cin.ignore();
  getline(cin, newSale);

  cout << "Enter SALES TO DATE (ex. 55)" << endl;
  cin >> userInput;
  newSale += " $" + userInput + ".00";
  
  saleOFS << endl << newSale;
  saleOFS.close();

  ListInfo();
  OptionSelect();
}

void Sale::ChangeEntry() {
  makeVector.open("sale.txt");
  if (!makeVector.is_open()) {
    cout << "Failed opening sale.txt" << endl;
  }

  while(!makeVector.fail()) {
    (getline(makeVector, tempString));
    
   changeList.push_back(tempString);

    if (makeVector.eof()) {
      break;
      }
    }
  
  makeVector.close();

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << " sale to date." << endl;
  }
  counter = 0;
  cout << "Which sale would you like to edit?" << endl;
  cout << "Please enter the number of the user." << endl;

  while (counter == 0) {
    cin >> userChoice;
    if ((userChoice > changeList.size()) || (userChoice < 1)) {
      cout << "Please enter a valid sale number.   ";
      continue;
    }
    
    cout << "Enter PRODUCT NAME" << endl;
    cin.ignore();
    getline(cin, tempString);
  
    cout << "Enter SALES TO DATE (ex. 55)" << endl;
    cin >> addInput;
    tempString += " " + addInput;
    cout << endl;
    
   changeList.at(userChoice - 1) = tempString;
    userChoice = 9999;

  for (i = 0; i < changeList.size(); ++i) {
    ++counter;
    cout << counter << ": " << changeList.at(i) << " sale to date." << endl;
  }
  counter = 0;

    cout << "Would you like to edit another sale? \n   1: Yes\n   2: No\nNOTE: Changes will ONLY fully save to database when finished editing (By pressing 2 here.)" << endl;
    cin >> userChoice;

    switch (userChoice) {
      default:
      cout << "Please enter a valid number." << endl;
      cin >> userChoice;
      

      case 1:
      ChangeEntry();
      break;

      case 2:
      //RETURN TO MENU
      ++counter;
      break;
    }
  }
  changeSale.open("sale.txt");
  if (!changeSale.is_open()) {
    cout << "Failed opening sale.txt" << endl;
  }
  counter = 0;
  for (i = 0; i < changeList.size(); ++i) {
    if (counter == 0) {
      changeSale << changeList.at(i);
      ++counter;
    }
    else { changeSale << endl << changeList.at(i); }
  }
  changeSale.close();
  changeList.clear();
  cout << endl << endl;
}

void Sale::ClientPurchase() {
  //opens multiple files in order to purchase any number of items on behalf of a client
  clientIFS.open("client.txt");
  if (!clientIFS.is_open()) {
    cout << "Could not open client.txt" << endl;
    abort();
  }

  while (!clientIFS.fail()) { //sortng numerical from alphabetic elements
    getline(clientIFS, tempString);
    tempChar = tempString.back();
    while (isdigit(tempChar)) {
      tempString.pop_back();
      tempChar = tempString.back();
    }
    
    clientList.push_back(tempString);

    if (clientIFS.eof()) {
      break;
    }
  }
  
  clientIFS.close();
  //----------------------------------------------------
  cout << "Which client you would like to make a purchase for?" << endl;
  counter = 0;
  for (i = 0; i < clientList.size(); ++i) {
    ++counter;
    cout << "   " << counter << ": " << clientList.at(i) << endl;
  }
  cout << "Enter the corresponding number of the client." << endl;
  //----------------------------------------------------
  counter = 0;
  while (counter == 0) {
    cin >> clientChoice;
    if ((clientChoice > clientList.size()) || (clientChoice < 1)) {
      cout << "Please enter a valid client number.";
      continue;
    }
    ++counter;
  }//client is chosen, but nothing is done with this value yet
  
  
  saleIFS.open("sale.txt");
  if (!saleIFS.is_open()) {
    cout << "Could not open sale.txt" << endl;
    abort();
  }

  while (!saleIFS.fail()) {
    getline(saleIFS, tempString);
    tempChar = tempString.back();
    while (isdigit(tempChar)) {
      tempString.pop_back();
      tempChar = tempString.back();
    }
    
    saleList.push_back(tempString);

    if (saleIFS.eof()) {
      break;
    }
  }

  saleIFS.close();
  //----------------------------------------------------
  cout << "\nWhich product would client #" << clientChoice <<" like to purchase?" << endl;
  counter = 0;
  for (i = 0; i < clientList.size(); ++i) {
    ++counter;
    cout << "   " << counter << ": " << saleList.at(i) << endl;
  }
  cout << "Enter the corresponding number of the product." << endl;
  //----------------------------------------------------
  counter = 0;
  while (counter == 0) {
    cin >> productChoice;
    if ((productChoice > saleList.size()) || (productChoice < 1)) {
      cout << "Please enter a valid product number.";
      continue;
    }
    --productChoice; //product value needs to be decremented to account for display being different from vector position
    ++counter;
  }
  
  cout << "\nHow many " << saleList.at(productChoice) << "would client #" << clientChoice << " purchase?" << endl;
  ++productChoice;
  
  counter = 0;
  while (counter == 0) {
    cin >> numPurchased;
    if (numPurchased < 0) {
      cout << "Please enter a positive number." << endl;
      continue;
    }
    ++counter;
  }

  clientList.clear();

  clientIFS.open("client.txt"); 
  if (!clientIFS.is_open()) {
    cout << "Could not open client.txt" << endl;
    abort();
  }
  while (!clientIFS.fail()) {
    getline(clientIFS, tempString);
    clientList.push_back(tempString);

    if (clientIFS.eof()) {
      break;
    }
  }
  
  clientIFS.close();
  
  clientIFS.open("client.txt");
  if (!clientIFS.is_open()) {
    cout << "Could not open client.txt" << endl;
      abort();
  }
  while (!clientIFS.fail()) {
    clientIFS >> tempString;
    tempChar = tempString.at(0);
    if (isdigit(tempChar)) { //used to extract numbers that are not addresses (program assumes all addresses will be 4 digits and not begin with 0)
      convertString = stoi(tempString);
      if (convertString < 1000) {
        clientNum.push_back(convertString);
      }
    }
    if (clientIFS.eof()) {
      break;
    }
  }

  clientIFS.close();

  saleIFS.open("sale.txt");
  if (!saleIFS.is_open()) {
    cout << "Could not open sale.txt" << endl;
    abort();
  }
  while(!saleIFS.fail()) {
    saleIFS >> tempString;
    tempChar = tempString.at(0);
    if (isdigit(tempChar)) {
      convertString = stoi(tempString);
      saleNum.push_back(convertString);
    }
    if (saleIFS.eof()) {
      break;
    }
  }

  saleIFS.close();
  cout << "Here are the updated databases:\n\nClient Database:\n" << endl;
  
  for (i = 0; i < clientList.size(); ++i) { 
    if (i == clientChoice - 1) {    
      tempString = clientList.at(i);
      tempChar = tempString.back();
      while (isdigit(tempChar)) {
        tempString.pop_back();
        tempChar = tempString.back();
      }
      tempInt = numPurchased;
      tempInt += clientNum.at(i);
      purchasedString = to_string(tempInt);
      tempString += purchasedString; 

      cout << tempString << " sales to date."<< endl;
      clientList.at(i) = tempString;
    }
    if (i == productChoice - 1) {
      tempInt = numPurchased;
      saleNum.at(i) += tempInt;
    }
    if (i != clientChoice - 1) {
      cout << clientList.at(i) << " sales to date."<< endl;
    }
  }
  cout << "\nSales Database:\n" << endl;
  for (i = 0; i < saleList.size(); ++i) {
    tempString = saleList.at(i);
    tempString2 = to_string(saleNum.at(i));

    tempString += tempString2;

    saleList.at(i) = tempString;

    cout << saleList.at(i) << " sales to date." << endl;
  }

  clientOFS.open("client.txt");
  if (!clientOFS.is_open()) {
    cout << "Could not open client.txt" << endl;
    abort();
  }
  for (i = 0; i < clientList.size(); ++i) {
    clientOFS << clientList.at(i);
    if (i < clientList.size() - 1) {
      clientOFS << endl;
    }
  }
  clientOFS.close();
  
  saleOFS.open("sale.txt");
  if (!saleOFS.is_open()) {
    cout << "Could not open sale.txt" << endl;
    abort();
  }
  for (i = 0; i < saleList.size(); ++i) {
    saleOFS << saleList.at(i);
    if (i < saleList.size() - 1) {
      saleOFS << endl;
    }
  }
  saleOFS.close();
  clientList.clear();
  saleList.clear();
  clientNum.clear();
  saleNum.clear();

  cout << "Press enter to continue" << endl;
  cin.ignore();
  getline(cin, dummy);
  
  ListInfo();
  OptionSelect();
}





class MainMenu {
public:
  void TitleScreen();

private:
  int userChoice = 9999;

};

//The beginning screen for all choices.
void MainMenu::TitleScreen() {
  Client AccessClient;
  SalesRep AccessSalesRep;
  Products AccessProducts;
  Sale AccessSale;
  
  cout << "Welcome to the \"Bath, Bath, and Bath\" Database! \n \nEnter the number of the item you would like to view:" << endl;
  cout << "   1: Clients \n   2: Sales Representatives \n   3: Products and Services \n   4: Sales" << endl;
  cout << "You can also enter 0 to end the program!" << endl;
  cin >> userChoice;

  if ((userChoice < 0) || (userChoice > 4)) {
    cout << "INVALID ENTRY: Please enter a number between 0 and 4. \n" << endl;
    MainMenu();
  }
  switch (userChoice) {
    case 0:
    cout << "Thank you for viewing my project." << endl;
    ++returnToMenu;
    break;

    case 1:
    AccessClient.ListInfo();
    AccessClient.OptionSelect();
    break;

    case 2:
    AccessSalesRep.ListInfo();
    AccessSalesRep.OptionSelect();
    break;
    
    case 3:
    AccessProducts.ListInfo();
    AccessProducts.OptionSelect();
    break;
    
    case 4:
    AccessSale.ListInfo();
    AccessSale.OptionSelect();
    break;
  }
  userChoice = 9999;
}

//Initializes program and contains check to end program (returnToMenu).
int main() {
  MainMenu Access;

  while (returnToMenu == 0) {
    Access.TitleScreen();
  }

  cout << "\nPROGRAM ENDED." << endl;
  
  
  return 0;
}
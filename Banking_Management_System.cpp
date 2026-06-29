#include <iostream>
#include <string>

using namespace std;

const int max_customer = 100;
const int max_transactions = 50;

int main() {

    int customer_IDS[max_customer];
    string customer_Names[max_customer];
    int account_Numbers[max_customer];
    double account_Balances[max_customer];

    string transaction_History[max_customer][max_transactions];
    int transaction_Counts[max_customer] = {0};

    int total_Customer = 0;
    int nextCustomerID = 101;
    int nextAccountNumber = 5001;

    int choice;

    cout << "=== Banking Management System ===\n";

    do {

        cout << "\n==== MAIN MENU ====\n";
        cout << "1. Create New Customer and Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Details\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;


        switch(choice) {

        case 1:
        {
            if(total_Customer >= max_customer)
            {
                cout<<"Database Full\n";
                break;
            }

            string name;
            double initialDeposit;

            cin.ignore();

            cout<<"Enter Name: ";
            getline(cin,name);

            cout<<"Enter Initial Deposit: ";
            cin>>initialDeposit;

            customer_IDS[total_Customer] = nextCustomerID++;
            customer_Names[total_Customer] = name;
            account_Numbers[total_Customer] = nextAccountNumber++;
            account_Balances[total_Customer] = initialDeposit;

            transaction_History[total_Customer][0] =
            "Deposit: $" + to_string(initialDeposit);
            transaction_Counts[total_Customer]++;
            cout<<"\nAccount Created!\n";
            cout<<"Customer ID: "<<customer_IDS[total_Customer]<<endl;
            cout<<"Account No: "<<account_Numbers[total_Customer]<<endl;
            total_Customer++;

            break;
        }

        case 2:
        {
            int acc;
            double amount;

            cout<<"Enter Account Number: ";
            cin>>acc;
            
            int index=-1;
            for(int i=0;i<total_Customer;i++)
            {
                if(account_Numbers[i]==acc)
                {
                    index=i;
                    break;
                }
            }
            if(index==-1)
            {
                cout<<"Account not found\n";
                break;
            }
            cout<<"Deposit Amount: ";
            cin>>amount;
            if(amount>0)
            {
                account_Balances[index]+=amount;
                int t=transaction_Counts[index];
                transaction_History[index][t]="Deposit: $"+to_string(amount);
                transaction_Counts[index]++;
                cout<<"Deposit Successful\n";
            }
            else
                cout<<"Invalid Amount\n";
            break;
        }



        case 3:
        {
            int acc;
            double amount;

            cout<<"Enter Account Number: ";
            cin>>acc;

            int index=-1;
            for(int i=0;i<total_Customer;i++)
            {
                if(account_Numbers[i]==acc)
                {
                    index=i;
                    break;
                }
            }
            if(index==-1)
            {
                cout<<"Account not found\n";
                break;
            }
            cout<<"Withdraw Amount: ";
            cin>>amount;
            if(amount>0 && amount<=account_Balances[index])
            {
                account_Balances[index]-=amount;
                int t=transaction_Counts[index];
                transaction_History[index][t]="Withdrawal: $"+to_string(amount);
                transaction_Counts[index]++;
                cout<<"Withdrawal Successful\n";
            }
            else
                cout<<"Insufficient Balance\n";
            break;
        }
        
        case 4:
        {
            int sender, receiver;
            double amount;

            cout<<"Your Account: ";
            cin>>sender;
            cout<<"Receiver Account: ";
            cin>>receiver;
            cout<<"Amount: ";
            cin>>amount;

            int senderIndex=-1;
            int receiverIndex=-1;
            for(int i=0;i<total_Customer;i++)
            {
                if(account_Numbers[i]==sender)
                    senderIndex=i;
                if(account_Numbers[i]==receiver)
                    receiverIndex=i;
            }
            if(senderIndex!=-1 && receiverIndex!=-1)
            {
                if(amount>0 && amount<=account_Balances[senderIndex])
                {
                    account_Balances[senderIndex]-=amount;
                    account_Balances[receiverIndex]+=amount;

                    transaction_History[senderIndex][transaction_Counts[senderIndex]]
                    ="Transfer Out: $"+to_string(amount);
                    transaction_Counts[senderIndex]++;
                    transaction_History[receiverIndex][transaction_Counts[receiverIndex]]
                    ="Transfer In: $"+to_string(amount);
                    transaction_Counts[receiverIndex]++;

                    cout<<"Transfer Successful\n";
                }
                else
                    cout<<"Invalid Amount\n";
            }
            else
                cout<<"Account not found\n";
            break;
        }

        case 5:
        {
            int acc;
            cout<<"Enter Account Number: ";
            cin>>acc;

            int index=-1;
            for(int i=0;i<total_Customer;i++)
            {
                if(account_Numbers[i]==acc)
                {
                    index=i;
                    break;
                }
            }
            if(index!=-1)
            {
                cout<<"\nCustomer Name: "<<customer_Names[index];
                cout<<"\nCustomer ID: "<<customer_IDS[index];
                cout<<"\nAccount Number: "<<account_Numbers[index];
                cout<<"\nBalance: $"<<account_Balances[index]<<endl;
            }

            else
                cout<<"Account not found\n";
            break;
        }

        case 6:
        {
            int acc;
            cout<<"Enter Account Number: ";
            cin>>acc;
            
            int index=-1;
            for(int i=0;i<total_Customer;i++)
            {
                if(account_Numbers[i]==acc)
                {
                    index=i;
                    break;
                }
            }
            if(index!=-1)
            {
                for(int j=0;j<transaction_Counts[index];j++)
                {
                    cout<<j+1<<". "
                    <<transaction_History[index][j]<<endl;
                }
            }
            else
                cout<<"Account not found\n";
            break;
        }

        case 7:
            cout<<"Exiting System...\n";
            break;
        default:
            cout<<"Invalid Choice\n";
        }
    }while(choice!=7);

    return 0;
}

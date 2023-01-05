#include <iostream>
using namespace std;
class Item{
private:
    int ID;
    int Quantity;
    string Name;
    double Price;
public:
    /*defult constructor to initialize private members(name,quantity,price)*/
    Item()
    {
        Name="";
        Quantity=0;
        Price=0;
    }

    /* parameterized constructor which take the value of name and quantity and price as parameters and intialize private data with them */
    Item(int quan,string n,double p)
    {
        Quantity=quan;
        Name=n;
        Price=p;
    }

    /*copy constructor to make a copy from an objevt of this class as it copy all its private data into the new obj*/
    Item( const Item & cpy)
    {
        Quantity=cpy.Quantity;
        Name=cpy.Name;
        Price=cpy.Price;
    }

    /* Setters to set the name with the value passed by user */
    void set_name(string n)
    {
        Name=n;
    }

    /*setter to set the quantity of the item with the value passed by user */
    void set_quantity(int q)
    {
        Quantity=q;
    }

    /*setter to set the price of the item with the value passed by user */
    void set_price(double p)
    {
        Price=p;
    }

    /*setter to set the id of each item  */
    void Set_ID(int id)
    {
        ID=id;
    }
    /*getter to return the name of the item*/
    string get_name()
    {
        return Name;
    }

     /*getter to return the quantity of the item*/
    int get_quantity()
    {
        return Quantity;
    }

    /*getter to return the price of the item*/
    double get_price()
    {
        return Price;
    }

    /*getter to return the ID of the item*/
    int Get_ID()
    {
        return ID;
    }

    /*overloading operator prototybes*/
    bool operator ==(const Item &);
    Item operator +=(const Item &);
    Item operator -=(int);
    friend ostream& operator<<(ostream& os, const Item & ob);
    friend istream& operator>>(istream& is,  Item & ob);
    friend class Seller;    //making class seller as a friend to access private data

};

/*overloading operator == so it can compare the name of each item -->return trur if they equal and false otherwise*/
bool Item :: operator == (const Item & right)
{
    bool ok;
    if(Name==right.Name)
    {
        ok = true;
    }
    else ok = false;

    return ok;
}

/*overloading operator += so it can add quantity of item object to quantity other item object */
Item Item :: operator += (const Item & right)
{
    Item temp;
    temp.Quantity = Quantity + right.Quantity;
    return temp;
}


/*overloading operator -= so it can subtract quantity of item object  */
Item Item :: operator-= ( int num)
{
    Quantity -= num;
    return *this;
}

/*overloading operator << so we can use cout with object items */
ostream& operator<<  (ostream& os,const Item& ob)
{
    os<<endl<<"ID: "<<ob.ID<<endl
      <<"NAME: "<<ob.Name<<endl
      <<"Quantity: "<<ob.Quantity<<endl
      <<"Price: "<<ob.Price<<endl;
}

/*overloading operator << so we can use cin with object items */
istream& operator>> (istream& is, Item& obj)
{
    is >> obj.Name>> obj.Quantity>> obj.Price;
    return is;

}


class Seller
{
private:
    string name,email;
    Item * item;
    int maxItems;
    static int itemsCounter;
public:
    /* parameterized constructor which take the value of name and quantity and price as parameters and intialize private data with them */
    Seller(string name=" ",string email=" ",int maxItems=0)
    {
        this->maxItems=maxItems;
        item=new Item[maxItems];
        this->name=name;
        this->email=email;
    }

     /* Setters to set the max capicity of items with the value passed by user */
    void setMax(int m)
    {
        maxItems=m;
    }

    /*overloading operator [] so we can use index with array of objects  */
    Item & operator[](const int index)
    {
        return item[index];
    }

    /*boolean fun to return true if the user add item to the function wheter
    it was exist so it increase is amount or add it and
    return false it the capacity of items is full and the item
    is not exist so we cannot add it*/
    bool addItem (Item &thing)
    {
        for(int i=0;i<itemsCounter;i++)
        {
            if(item[i].Name==thing.Name)
            {
                item[i]+=thing;
                return true;
            }
        }
        if(itemsCounter>=maxItems)
        {
            return false;
        }
        else
        {
            item[itemsCounter]=thing;
            item[itemsCounter].Set_ID(++itemsCounter);   //setting the id with the count of items which is static variable
            return true;
        }

    }

   /*boolean fun to return true if the user subtract quantity of item less than
    its existing quantity so it can be subtracted (selled) false otherwise*/
    bool sellItem(string Name,int quantity)
    {
        for(int i=0;i<itemsCounter;i++)
        {
            if(item[i].get_name()==Name)
            {
                if(item[i].get_quantity()>=quantity)
                {
                    item[i]-=quantity;
                    return true;
                }
                else
                {
                    cout<<endl<<"There is only{ "<<item[i].get_quantity()<< " }left for this item"<<endl;
                    return false;
                }
            }
        }
        return false;

    }

   /*function to print the data of items using >> operator*/
    void printItems ()
    {
        for(int i=0;i<itemsCounter;i++)
        {
            cout<<item[i]<<endl;
        }
    }

    /* function to return the element with specific id*/
    Item searchItem (int id)
    {
        for(int i=0;i<itemsCounter;i++)
        {
            if(item[i].ID==id)
            {
                return item[i];
            }
        }

    }

   /* destructor*/
    ~Seller()
    {
        delete [] item;
    }

    friend ostream& operator<<(ostream & out,const Seller &s);

};

int Seller :: itemsCounter=0;


ostream& operator<<(ostream & out,const Seller &s)
{
    out<<"Seller name is : "<<s.name<<endl
       <<"Seller email is : "<<s.email<<endl;
    return out;
}

///////////////////////////////////////////////
int main ()
{
    cout<<"Enter the store capacity (Max Number Of Items)"<<endl;
    int maxCap;
    cin>>maxCap;
    cout<<"Enter the INFO of the seller (Name & Email)"<<endl;
    string n,e;
    cin>>n>>e;
    Seller S(n,e,maxCap);
    cout<<"1. Print My Info."<<endl;
    cout<<"2. Add An Item."<<endl;
    cout<<"3. Sell An Item."<<endl;
    cout<<"4. Print Items."<<endl;
    cout<<"5. Find an Item by ID."<<endl;
    cout<<"6. Exit."<<endl;
    int choice;
    while(cin>>choice)
    {
        if(choice==1)
        {
            cout<<S;

            cout<<"------------------------"<<endl;
            cout<<"1. Print My Info."<<endl;
            cout<<"2. Add An Item."<<endl;
            cout<<"3. Sell An Item."<<endl;
            cout<<"4. Print Items."<<endl;
            cout<<"5. Find an Item by ID."<<endl;
            cout<<"6. Exit."<<endl;
        }
        else if (choice==2)
        {
            cout<<"Enter item name,quantity and price"<<endl;
            Item i;
            cin>>i;
            S.addItem(i);
            cout<<"Item Added successfully"<<endl;

            cout<<"------------------------"<<endl;
            cout<<"1. Print My Info."<<endl;
            cout<<"2. Add An Item."<<endl;
            cout<<"3. Sell An Item."<<endl;
            cout<<"4. Print Items."<<endl;
            cout<<"5. Find an Item by ID."<<endl;
            cout<<"6. Exit."<<endl;

        }
        else if(choice==3)
        {
            cout<<"Enter item name and quantity"<<endl;
            string n;
            int q;
            cin>>n>>q;
            S.sellItem(n,q);

            cout<<"------------------------"<<endl;
            cout<<"1. Print My Info."<<endl;
            cout<<"2. Add An Item."<<endl;
            cout<<"3. Sell An Item."<<endl;
            cout<<"4. Print Items."<<endl;
            cout<<"5. Find an Item by ID."<<endl;
            cout<<"6. Exit."<<endl;

        }
        else if(choice==4)
        {
            S.printItems();

            cout<<"------------------------"<<endl;
            cout<<"1. Print My Info."<<endl;
            cout<<"2. Add An Item."<<endl;
            cout<<"3. Sell An Item."<<endl;
            cout<<"4. Print Items."<<endl;
            cout<<"5. Find an Item by ID."<<endl;
            cout<<"6. Exit."<<endl;
        }
        else if(choice==5)
        {
            cout<<"Enter ID "<<endl;
            int id; cin>>id;
            cout<<S.searchItem(id);

            cout<<"------------------------"<<endl;
            cout<<"1. Print My Info."<<endl;
            cout<<"2. Add An Item."<<endl;
            cout<<"3. Sell An Item."<<endl;
            cout<<"4. Print Items."<<endl;
            cout<<"5. Find an Item by ID."<<endl;
            cout<<"6. Exit."<<endl;

        } else break;
    }

    return 0;
}

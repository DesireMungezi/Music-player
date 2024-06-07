#include<iostream>
#include<string>
using namespace std;

//create a node
class Chain
{
public:
    std::string music;
    Chain* next;

    //create a constructor
    Chain(std::string song) :music(song), next(nullptr)
    {}
};
//create a settings class
class Settings
{
public:
    //prototypes
    void addAtFront(Chain** head, std::string newSong);
    void addAtEnd(Chain** head, std::string newSong);
    void addAfter(Chain** head, std::string newSong, int previous);
    void removeSong(Chain** head, int songNum);
};
void Settings::addAtFront(Chain** head, std::string newSong)
{
    //Create a new chain
    Chain* newChain = new Chain(newSong);
    //link it with the next chain
    newChain->next = *head;
    //make new chain as a head chain or node
    *head = newChain;
}
void Settings::addAtEnd(Chain** head, std::string newSong)
{
    //create a new chain
    Chain* newChain = new Chain(newSong);
    //since it will be the last, i doesn't have a next chain
    newChain->next = NULL;

    if(*head == nullptr)
    {
        //it means its the only chain and as no value
        *head = newChain;
    }
    //to iterate we create another new chain
    //we need to find the last chain
    Chain* theLast = *head;
    while(theLast->next != nullptr)
    {
        //if i find the last chain the loop will endl;
        theLast = theLast->next;
    }
    //make the new chain a last node
    theLast->next = newChain;
}
void Settings::addAfter(Chain**head, std::string newSong, int num)
{
    //num can not be zero or less than zero
    if(num <= 0)
    {
        std::cout<<"\nYou can't add before 1 with this option"<<endl;
        return;
    }
    //create new chain
    Chain* newChain = new Chain(newSong);
    //previous chain
    Chain* previous = *head;

    //begin at 1 to count matching the numbering
    int i = 1;
    while(previous != nullptr && i < num)
    {
        previous = previous->next;
        i++;
    }

    if(previous == nullptr)
    {
        std::cout<<"\nSorry the number was not found"<<endl;
    }
    else
    {
        //link the next chain before breaking
        newChain->next = previous->next;
        //break link
        previous->next = newChain;
    }
}
void Settings::removeSong(Chain** head, int num)
{
    //Search for the number or song number
    Chain* removeSong = *head;
    Chain* previous = *head;
    int i = 1;
    while(removeSong != nullptr && i != num)
    {
        previous = removeSong;
        removeSong = removeSong->next;
        i++;
    }
    //if you want to remove the first song
    if(removeSong == nullptr)
    {
        std::cout<<"Sorry the number song not found"<<std::endl;
        std::cout<<"Make sure you enter the correct song number"<<std::endl;
        return;
    }
    //Cutting and reconnecting the chain
    if(previous == removeSong)
    {
        //this means its a head so make the second as a head
        *head = removeSong->next;
    }
    else
    {
        previous->next = removeSong->next;
    }
    //Deallocate the memory
    delete removeSong;
}
void display(Chain* head)
{
    std::cout<<"\tMUSIC\n"<<std::endl;
    //check if there is any songs
    if(head == NULL)
    {
        std::cout<<"No songs are added yet"<<std::endl;
    }
    //if we have songs then display them
    //count them as we iterate
    int count = 0;
    while(head != nullptr)
    {
        count++;
        std::cout<<count<<". ";
        std::cout<<head->music<<std::endl;
        head = head->next;
    }
}
using namespace std;

int main()
{

    Chain* head = nullptr; //null by default
    //Declare an object for settings
    Settings set;
    int choice;
    do
    {
        display(head);
        std::cout<<"\n1.Settings"<<std::endl;
        std::cout<<"2.Exit app"<<std::endl;
        std::cout<<"\n: ";
        std::cin>>choice;
        if(choice == 1)
        {    //settings
            int option;
            do
            {
            std::cout<<"\nAdd songs at the:"<<std::endl;
            std::cout<<"1.Beginning"<<std::endl;
            std::cout<<"2.End of the songs"<<std::endl;
            std::cout<<"3.After a certain song"<<std::endl;
            std::cout<<"4.Delete a song"<<std::endl;
            std::cout<<"5.Return to the songs"<<std::endl;
            std::cout<<"\nEnter :";
            std::cin>>option;
            std::string song;
            if (option == 1)
            {
                std::cout<<"\nName of the song :";
                std::cin>>song;
                set.addAtFront(&head, song);
            }
            else if (option == 2)
            {
                std::cout<<"\nName of the song :";
                std::cin>>song;
                set.addAtEnd(&head, song);
            }
            else if (option == 3)
            {
                std::cout<<"\nAdd after number? :";
                int num;
                std::cin>>num;
                std::cout<<"Name of the song :";
                std::cin>>song;
                set.addAfter(&head, song, num);
            }
            else if (option == 4)
            {
                int songNum;
                std::cout<<"Enter song number :";
                std::cin>>songNum;
                set.removeSong(&head, songNum);
            }
            else if (option == 5)
            {
                //leave some space
                std::cout<<std::endl;
                break;
            }
            else
            {
                std::cout<<"Invalid Input\n"<<std::endl;
            }
            }while(option != 5);
        }
        else if(choice != 1 && choice != 2)
        {
            std::cout<<"Invalid input!"<<std::endl;
        }
    }while(choice != 2);
    return 0;
}

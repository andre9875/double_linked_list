#include <iostream>

template <class T>
struct node 
{ 
    // Pointer to the next node. 
    struct node* next; 
    // Pointer to the previous node.
    struct node* prev;
    T data;
};

template <class T>
class double_linked_list
{
public:
    double_linked_list():
    head ( nullptr ),
    tail ( nullptr )
    {}

    ~double_linked_list() {};

    void add_node( T value )
    {
        node<T>* new_node;
        try
        {
            new_node = new node<T>();
        }
        catch ( std::bad_alloc& ba )
        {
            // sake of example
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            return;
        }
        // the place for more validations of T value

        if ( head )
        {
            tail->next = new_node; 
            new_node->prev = tail;
            new_node->next = nullptr;
            tail = new_node;
        }
        else
        {
            head = new_node;
            tail = new_node;
            new_node->next = nullptr; 
            new_node->prev = nullptr;
        }
        new_node->data = value;
    }

    void remove_node( const T value )
    {
        if ( !head ) return;
        
        node<T>* tmp;
        node<T>* node =  head;

        while ( node ) 
        {
            if ( value == node->data )
            {   
                tmp = node;
                if ( tmp->prev && tmp->next )
                {
                    // remove between
                    node->prev->next = tmp->next;
                    node->next->prev = tmp->prev;
                }
                else if ( tmp->prev == nullptr )
                {
                    //remove head
                    head = tmp->next;
                    node->next->prev = nullptr;
                }
                else if ( tmp->next == nullptr )
                {
                    // remove tail
                    node->prev->next = nullptr;
                    tail = tmp->prev;
                }
            }
            node = node->next;
        }
        // release memory
        if ( tmp ) delete tmp;
    }

    void forward() const
    {
        if ( !head ) return;
        node<T>* node = head;
        while ( node->next ) 
        { 
            std::cout<< node->data << " ";
            node = node->next;
        }
        std::cout<< node->data << "\n";
    }

    void backward() const
    {
        if ( !tail ) return;

        node<T>* node = tail;
        while ( node->prev ) 
        { 
            std::cout<< node->data << " ";
            node = node->prev;
        }
        std::cout<< node->data << "\n"; 
    }

    bool test_node( const T value )
    {
        if ( !head ) return true;

        node<T>* node =  head;
        while ( node ) 
        {
            if ( value == node->data )  
                return true;
            node = node->next;
            
        }
        return false;
    }

private:
    node<T>* head;
    node<T>* tail;
};

int main()
{
    double_linked_list<int> dll;
    dll.add_node(5);
    dll.add_node(15);
    dll.add_node(25);
    dll.add_node(50);

    dll.forward();
    dll.backward();

    dll.remove_node(5);
    dll.forward();

   if ( !dll.test_node( 5 ) )
        std::cout<< "Remove value  5 is passed\n";
   else
        std::cout<< "Remove value  5 is failed\n";

   dll.remove_node(50);
   if ( !dll.test_node( 50 ) )
        std::cout<< "Remove value 50 is passed\n"; 
   else
        std::cout<< "Remove value 50 is failed\n";

   dll.add_node(45);
   if ( dll.test_node( 45 ) )
        std::cout<< "Add    value 45 is passed\n";
   else
        std::cout<< "Remove value 45 is failed\n";

   dll.remove_node(25);
   if ( !dll.test_node( 25 ) )
        std::cout<< "Remove value 25 is passed\n"; 
   else
        std::cout<< "Remove value 25 is failed\n";    
    
   if ( !dll.test_node( 35 ) )
        std::cout<< "Search value 35 is passed\n"; 
   else
        std::cout<< "Search value 35 is failed\n";

   return 0;
}
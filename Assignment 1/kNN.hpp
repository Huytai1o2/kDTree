#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual void printSub(int start, int end) const = 0;
    virtual void Arr(T *arr) const = 0;
};

template<typename T>
class Image : public List<T> {
    protected :
        class Node
        {
            public :
                T data;
                Node *next;
                Node(T data, Node *next = nullptr)
                { 
                    this -> data = data;
                    this -> next = next;
                }

                ~Node() = default;
        };
    protected :
        Node *head;
        Node *tail;
        int count = 0;
    
    public :
        Image();
        ~Image();
        void push_back(T value);
        void push_front(T value);
        void insert(int index, T value);
        void remove(int index);
        T& get(int index) const;
        int length() const;
        void clear();
        void reverse();
        void printSub(int start, int end) const
        {
            if (start < 0 || start > count || end < 0 || end > count || start > end)
            {
                return;
            }

            Node *temp = head;
            for (int i = 0; i < start; i++)
            {
                temp = temp -> next;
            }

            for (int i = start; i < end; i++)
            {
                if (i == end - 1)
                {
                    cout << temp -> data;
                    return;
                }
                cout << temp -> data << " ";
                temp = temp -> next;

                if (temp == nullptr)
                {
                    return;
                }

                if (temp -> next == nullptr)
                {
                    cout << temp -> data;
                    return;
                }
            }
        };
        void print() const
        {
            if (count == 0)
            {
                return;
            }

            Node *temp = head;
            for (int i = 0; i < count; i++)
            {
                if (i == count - 1)
                {
                    cout << temp -> data;
                }
                else
                {
                    cout << temp -> data << " ";
                    temp = temp -> next;
                }
            }
        };
        
        void Arr(T *arr) const;
};

class Dataset {
private:
    List<List<int>*>* data;
    List<string> *columnNames;
    //You may need to define more
public:
    Dataset()
    {
        this -> data = new Image<List<int>*>();
        this -> columnNames = new Image<string>();
    };
    ~Dataset()
    {
        for (int i = 0; i < this -> data -> length(); i++)
        {
            this -> data -> get(i) ->clear();
        }

        for (int i = 0; i < this -> data -> length(); i++)
        {
            delete this -> data -> get(i);
        }

        delete data;
        delete columnNames;
    };
    Dataset(const Dataset& other)
    {
        this -> data = new Image<List<int>*>();
        this -> columnNames = new Image<string>();

        int rowOfdata, colOfdata;
        other.getShape(rowOfdata, colOfdata);

        string *columnNamesArr = new string[other.columnNames ->length()];
        other.columnNames -> Arr(columnNamesArr);

        int **dataArr = new int*[rowOfdata];
        for (int i = 0; i < rowOfdata; i++)
        {
            dataArr[i] = new int[colOfdata];
        }

        other. convert2D(dataArr);

        for (int i = 0; i < other.columnNames ->length(); i++)
        {
            this -> columnNames -> push_back(columnNamesArr[i]);
        }

        delete[] columnNamesArr;

        for (int i = 0; i < rowOfdata; i++)
        {
            List<int> *row = new Image<int>();
            for (int j = 0; j < colOfdata; j++)
            {
                row -> push_back(dataArr[i][j]);
            }

            this -> data -> push_back(row);
        }

        for (int i = 0; i < rowOfdata; i++)
        {
            delete[] dataArr[i];
        }
        delete[] dataArr;
    }
    ;
    Dataset& operator=(const Dataset& other)
    {
        if (this == &other)
        {
            return *this;
        }

        for (int i = 0; i < this -> data -> length(); i++)
        {
            this -> data -> get(i) ->clear();
        }

        for (int i = 0; i < this -> data -> length(); i++)
        {
            delete this -> data -> get(i);
        }

        delete this -> data;
        delete this -> columnNames;

        this -> data = new Image<List<int>*>();
        this -> columnNames = new Image<string>();

        int rowOfdata, colOfdata;
        other.getShape(rowOfdata, colOfdata);

        string *columnNamesArr = new string[other.columnNames ->length()];
        other.columnNames -> Arr(columnNamesArr);

        for (int i = 0; i < other.columnNames ->length(); i++)
        {
            this -> columnNames -> push_back(columnNamesArr[i]);
        }

        delete[] columnNamesArr;

        for (int i = 0; i < rowOfdata; i++)
        {
            List<int>* row = new Image<int>();
            int *feature = new int[colOfdata];
            other.data -> get(i) -> Arr(feature);

            for (int j = 0; j < colOfdata; j++)
            {
                row -> push_back(feature[j]);
            }
            this -> data -> push_back(row);

            delete[] feature;
        }

        return *this;
    };
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const
    ;

    void convert2D(int **arr) const
    {
        int nRows, nCols;
        this -> getShape(nRows, nCols);
        List<int> **row = new List<int>*[this -> data -> length()];
        this -> data ->Arr(row);
        for (int i = 0; i < this -> data -> length(); i++)
        {
            int *feature = new int[nCols];
            row[i] -> Arr(feature);
            for (int j = 0; j < nCols; j++)
            {
                arr[i][j] = feature[j];
            }
            delete[] feature;
        }
        delete[] row;
    };
    
    void printTail(int nRows = 5, int nCols = 5) const
    ;
    void getShape(int& nRows, int& nCols) const;
    void columns() const
    ;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    double distanceEuclidean(const List<int>* Image1, const List<int>* Image2) const;

    List<List<int>*>* getData() const
    {
        return this -> data;
    }

    ///////////////////////////  Additional Functions  ///////////////////////////
    Dataset predict(const Dataset& X_train, const Dataset& y_train, const int k) const;
    double score(const Dataset& y_pred) const;
};

class kNN {
private:
    int k;
    //You may need to define more
    Dataset X_train;
    Dataset Y_train;
public:
    kNN(int k = 5)
    {
        this -> k = k;
    };
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test)
    {
        return X_test.predict(this -> X_train, this -> Y_train, this -> k);
    };
    double score(const Dataset& y_test, const Dataset& y_pred)
    {
        return y_test.score(y_pred);
    };
};

class dataOfDistance
{
    protected:
        double distance;
        int label;

    public:
        dataOfDistance()
        {
            distance = 0;
            label = 0;
        };
        ~dataOfDistance() {};
        double getDistance() const
        {
            return distance;
        };
        int getIndex() const
        {
            return label;
        };

        void setDistance(double distance)
        {
            this -> distance = distance;
        };
        void setIndex(int label)
        {
            this -> label = label;
        };
};

//////////////////////////////////Data of Image//////////////////////////////////

template<typename T>
Image<T>::Image()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<typename T>
Image<T>::~Image()
{
    this -> clear();
}

template<typename T>
void Image<T>::push_back(T value)
{
    Node *newNode = new Node(value);

    if (count == 0)
    {
        head = tail = newNode;
        count ++;
    }
    else
    {
        tail -> next = newNode;
        tail = newNode;
        count ++;
    }
}

template<typename T>
void Image<T>::push_front(T value)
{
    if (count == 0)
    {
        head = tail = new Node(value);
        count ++;
    }
    else
    {
        Node *newNode = new Node(value);
        newNode -> next = head;
        head = newNode;
        count ++;
    }
}

template<typename T>
void Image<T>::insert(int index, T value)
{
    if (index < 0 || index > count) {return;}
    else 
    {

        if (index == 0) this -> push_front(value);
        else if (index == count) this -> push_back(value);
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp -> next;
            }

            Node *newNode = new Node(value);
            newNode -> next = temp -> next;
            temp -> next = newNode;
            count ++;
        }
        return;
    }
}

template<typename T>
void Image<T>::remove(int index)
{
    if (index < 0 || index >= count) {return;}

    else
    {
        Node *temp = head;
        Node *prev = nullptr;

        if (index == 0)
        {
            head = temp -> next;
            count--;
            delete temp;
            return;
        }

        else 
        {
            for (int i = 0; i < index; i++)
            {
                prev = temp;
                temp = temp -> next;
            }
            prev -> next = temp -> next;

            if (tail == temp) ///////////DELETE LAST////////////
            {
                tail = prev;
            }
            count--;
            delete temp;
            return;
        }
    }
}

template<typename T>
T& Image<T>::get(int index) const
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("get(): Out of range");
    }

    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp -> next;
    }

    return temp -> data;
}

template<typename T>
int Image<T>::length() const
{
    return count;
}

template<typename T>
void Image<T>::clear()
{
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current; 
        current = next;
    }
    head = tail = nullptr; 
    count = 0;
}

template <typename T>
void Image<T>::reverse()
{
    if (head == nullptr)
    {
        return;
    }

    if (head -> next == nullptr)
    {
        return;
    }

    Node *prev = nullptr;
    Node *next = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }

    this -> tail = this -> head;
    this -> head = prev;
}

template <typename T>
void Image<T>::Arr(T *arr) const
{
    Node *temp = head;
    for (int i = 0; i < count; i++)
    {
        arr[i] = temp -> data;
        temp = temp -> next;
    }
}

// //////////////////////////////////Data of Image//////////////////////////////////

void train_test_split(Dataset& X, Dataset& Y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test);
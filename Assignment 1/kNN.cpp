#include "kNN.hpp"

bool Dataset::loadFromCSV(const char* fileName)
{
    ifstream file(fileName);
        if(file.is_open())
        {
            string nameCol;
            int dataCol;

            file >> nameCol;
            for (int i = 0; i < nameCol.length(); i++) {
                if (nameCol[i] == ',') nameCol[i] = ' ';
            }
            stringstream ss(nameCol);
            while(ss >> nameCol) columnNames->push_back(nameCol);

            while(file >> nameCol)
            {
                for (int i = 0; i < nameCol.length(); i++) {
                    if (nameCol[i] == ',') nameCol[i] = ' ';
                }
                stringstream ss(nameCol);
                List<int>* temp = new Image<int>();
                while(ss >> dataCol) temp->push_back(dataCol);
                data->push_back(temp); 
            }
            return true;
        }
        return false;
}

void Dataset::printHead(int nRows, int nCols) const
{

    if (nRows <= 0 || nCols <= 0) //|| this -> data -> length() == 0
    {
        return;
    }

    else
    {
        int rowsOfdata, colsOfdata;
        this -> getShape(rowsOfdata, colsOfdata);

        if (this -> data -> length() != 0)
        {
            if (this -> data -> get(0) -> length() == 0)
            {
                return;
            }
        }
        /////////////////////////// Print column names ///////////////////////////

        if (nCols <= this -> columnNames -> length())
        {
            this -> columnNames -> printSub(0, nCols);
            if (this -> data ->length() != 0)cout << endl;
        }

        else
        {
            this -> columnNames -> printSub(0, this -> columnNames -> length());
            if (this -> data ->length() != 0) cout << endl;
        }

        /////////////////////////// Print data ///////////////////////////

        if (this -> data -> length() == 0)
        {
            return;
        }

        if (nRows <= this -> data -> length())
        {
            for (int i = 0; i < nRows; i++)
            {
                if (nCols <= colsOfdata)
                {
                    this -> data -> get(i) -> printSub(0, nCols);
                }
                else
                {
                    this -> data -> get(i) -> printSub(0, colsOfdata);
                }
                if (i != nRows - 1)cout << endl;
            }
        }

        else
        {
            for (int i = 0; i < this -> data -> length(); i++)
            {
                if (nCols <= colsOfdata)
                {
                    this -> data -> get(i) -> printSub(0, nCols);
                }
                else
                {
                    this -> data -> get(i) -> printSub(0, colsOfdata);
                }
                if (i != this -> data -> length() - 1  && this -> data -> length()) 
                {
                    cout << endl;
                }
            }
        }

        return;
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    if (nRows <=0 || nCols <= 0)  // || this -> data -> length() == 0
    {
        return;
    }

    else
    {
        if (this -> data -> length() != 0)
        {
            if (this -> data -> get(0) -> length() == 0)
            {
                return;
            }
        }

        /////////////////////////// Print column names ///////////////////////////
        int rowsOfdata, colsOfdata;
        this -> getShape(rowsOfdata, colsOfdata);

        if (nCols <= this -> columnNames -> length())
        {
            this -> columnNames -> printSub(this -> columnNames -> length()-nCols, this -> columnNames -> length());
            if (this -> data ->length() != 0) cout << endl;
        }

        else
        {
            this -> columnNames -> printSub(0, this -> columnNames -> length());
            if (this -> data ->length() != 0) cout << endl;
        }

        /////////////////////////// Print data ///////////////////////////

        if (this -> data -> length() == 0)
        {
            return;
        }

        if (nRows <= this -> data -> length())
        {
            for (int i = this -> data -> length()-nRows; i < this -> data -> length(); i++)
            {
                if (nCols <= colsOfdata)
                {
                    this -> data -> get(i) -> printSub(colsOfdata - nCols, colsOfdata);
                }
                else
                {
                    this -> data -> get(i) -> printSub(0, colsOfdata);
                }
                if (i != this -> data -> length() - 1)cout << endl;
            }
        }

        else
        {
            for (int i = 0; i < this -> data -> length(); i++)
            {
                
                if (nCols <= colsOfdata)
                {
                    this -> data -> get(i) -> printSub(colsOfdata - nCols, colsOfdata);
                }
                else
                {
                    this -> data -> get(i) -> printSub(0, colsOfdata);
                }
                if (i != this -> data -> length() - 1  && this -> data -> length()) cout << endl;
            }
        }
        return;
    }
}

void Dataset::getShape(int& nRows, int& nCols) const
{
    nRows = this -> data -> length();
    if (nRows == 0)
    {
        nCols = 0;
        return;
    }
    
    else
    {
        nCols = this -> data -> get(0) -> length();
        return;
    }
}

void Dataset::columns() const
{
    this -> columnNames -> print();
    return;
}

bool Dataset::drop(int axis, int index, std::string columns)
{
    if (axis != 0 && axis != 1) //  && this -> data -> length() == 0)
    {
        return false;
    }

    else
    {
        if (this -> data -> length() == 0)
        {
            if (axis == 0)
            {
                return false;
            }

            else
            {
                if (axis == 1)
                {
                    for (int i = 0; i < this -> columnNames -> length(); i++)
                    {
                        if (this -> columnNames -> get(i) == columns)
                        {
                            this -> columnNames -> remove(i);
                            return true;
                        }
                    }
                    return false;
                }
            }
        }
        
        if (axis == 0)
        {
            if (index < 0 || index >= this -> data -> length())
            {
                return false;
            }

            else
            {
                this -> data -> get (index) -> clear();
                delete this -> data -> get(index);
                this -> data -> remove(index);
                return true;
            }
        }

        else
        {
            if (axis == 1)
            {
                for (int i = 0; i < this -> columnNames -> length(); i++)
                {
                    if (this -> columnNames -> get(i) == columns)
                    {
                        this -> columnNames -> remove(i);
                        for (int j = 0; j < this -> data -> length(); j++)
                        {
                            this -> data -> get(j) -> remove(i);
                        }

                        if (this -> data -> get(0) -> length() == 0)
                        {
                            this -> data -> clear();
                            return true;
                        }

                        if(this -> columnNames ->length() != this -> data -> get(0) -> length())
                        {
                            this -> columnNames -> insert(i, "\0");
                        }

                        int nRows, nCols;
                        this -> getShape(nRows, nCols);

                        if (nCols == 0 || nRows == 0)
                        {
                            this -> ~Dataset();
                            return true;
                        }

                        return true;
                    }
                }
                return false;
            }
        }
    }
    return false;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset result ;

    if (startRow < 0 || startCol < 0 || (endRow < 0 && endRow != -1) || (endCol < 0 && endCol != -1))
    {
        throw std::out_of_range("get(): Out of range");
        return result;
    }

    else
    {
        if ((endRow != -1 && endRow < startRow) || (endCol != -1 && endCol <startCol))
        {
            throw std::out_of_range("get(): Out of range");
            return result;
        }

        else if(startRow >= this -> data -> length() || startCol >= this -> columnNames -> length())
        {
            return result;
        }

        else
        {
            int rowsOfdata, colsOfdata;
            this -> getShape(rowsOfdata, colsOfdata);
            string *columnNamesArr = new string[this -> columnNames ->length()];
            this -> columnNames -> Arr(columnNamesArr);

            int **dataOfImage = new int*[rowsOfdata];
            for (int i = 0; i < rowsOfdata; i++)
            {
                dataOfImage[i] = new int[colsOfdata];
            }

            this -> convert2D(dataOfImage);

            if (endRow == -1)
            {
                if (endCol == -1)
                {

                    for (int i = startCol; i < this -> columnNames -> length(); i++)
                    {
                        result. columnNames -> push_back(columnNamesArr[i]);
                    }

                    for (int i = startRow; i < rowsOfdata; i++)
                    {

                        List<int>* row = new Image<int>();
                        for (int j = startCol; j < colsOfdata; j++)
                        {
                            row -> push_back(dataOfImage[i][j]);
                        }
                        result. data -> push_back(row);
                    }
                    for (int i = 0; i < rowsOfdata; i++)
                    {
                        delete [] dataOfImage[i];
                    }
                    delete[] dataOfImage;
                    delete [] columnNamesArr;
                    return result;
                }

                else
                {

                    if (endCol >= this -> columnNames -> length())
                    {
                        endCol = this -> columnNames -> length() - 1;
                    }

                    for (int i = startCol; i <= endCol; i++)
                    {
                        result. columnNames -> push_back(columnNamesArr[i]);
                    }

                    for (int i = startRow; i < rowsOfdata; i++)
                    {

                        List<int>* row = new Image<int>();
                        for (int j = startCol; j <= endCol; j++)
                        {
                            row -> push_back(dataOfImage[i][j]);
                        }
                        result. data -> push_back(row);
                    }
                    for (int i = 0; i < rowsOfdata; i++)
                    {
                        delete [] dataOfImage[i];
                    }
                    delete[] dataOfImage;
                    delete [] columnNamesArr;
                    return result;
                }
            }

            else if (endCol == -1)
            {
                {
                    if (endRow >= this -> data -> length())
                    {
                        endRow = this -> data -> length() - 1;
                    }

                    for (int i = startRow; i <= endRow; i++)
                    {

                        List<int>* row = new Image<int>();
                        for (int j = startCol; j < colsOfdata; j++)
                        {
                            row -> push_back(dataOfImage[i][j]);
                        }
                        result. data -> push_back(row);
                    }

                    for (int i = startCol; i < this -> columnNames -> length(); i++)
                    {
                        result. columnNames -> push_back(columnNamesArr[i]);
                    }

                    for (int i = 0; i < rowsOfdata; i++)
                    {
                        delete [] dataOfImage[i];
                    }
                    delete[] dataOfImage;
                    delete [] columnNamesArr;
                    return result;
                }
            }

            else
            {
                if (endRow >= this -> data -> length())
                {
                    endRow = this -> data -> length() - 1;
                }

                if (endCol >= this -> columnNames -> length())
                {
                    endCol = this -> columnNames -> length() - 1;
                }

                for (int i = startCol; i <= endCol; i++)
                {
                    result. columnNames -> push_back(columnNamesArr[i]);
                }

                for (int i = startRow; i <= endRow; i++)
                {

                    List<int>* row = new Image<int>();
                    for (int j = startCol; j <= endCol; j++)
                    {
                        row -> push_back(dataOfImage[i][j]);
                    }
                    result. data -> push_back(row);
                }
                
                for (int i = 0; i < rowsOfdata; i++)
                    {
                        delete [] dataOfImage[i];
                    }
                delete[] dataOfImage;
                delete [] columnNamesArr;
                return result;
            }
        }
    }
}

double Dataset::distanceEuclidean(const List<int>* Image1, const List<int>* Image2) const
{
    int maxlength = max (Image1 -> length(), Image2 -> length());
    double sum = 0;

    int *dataOfImage1 = new int [maxlength];
    int *dataOfImage2 = new int [maxlength];

    // ///////////////////////Initialize dataOfImage1 and dataOfImage2///////////////////////

    Image1 -> Arr(dataOfImage1);
    Image2 -> Arr(dataOfImage2);

    // ///////////////////////Calculate sum///////////////////////

    for (int i = 0; i < maxlength; i++)
    {
        if (i < Image1 -> length() && i < Image2 -> length())
        {
            sum += pow(dataOfImage1[i] - dataOfImage2[i], 2);

        }

        else
        {
            if (i < Image1 -> length())
            {
                sum += pow(dataOfImage1[i], 2);
            }

            else
            {
                sum += pow(dataOfImage2[i], 2);
            }
        }
    }

    double result = sqrt(sum);
    delete [] dataOfImage1;
    delete [] dataOfImage2;
    return result;
}

//////////////////////////////Split dataset//////////////////////////////

void train_test_split(Dataset& X, Dataset& Y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test)
{
    if (test_size <= 0 || test_size >= 1)
    {
        return;
    }

    int nRows = 0, nCols = 0;
    int nRowsY = 0, nColsY = 0;


    X.getShape(nRows, nCols);
    Y.getShape(nRowsY, nColsY);

    if (nCols == 0 && nColsY == 0)
    {
        X_train = Dataset();
        X_test = Dataset();
        Y_train = Dataset();
        Y_test = Dataset();
        return;
    }

    if (nCols == 0 && nColsY == 0)
    {
        X_train = Dataset();
        X_test = Dataset();
        Y_train = Dataset();
        Y_test = Dataset();
        return;
    }

    if (nRows != nRowsY)
    {
        return;
    }

    int endRowX_train = (nRows *  (1 - test_size) * 1.00000001) - 1;
    int endRowY_train = (nRows *  (1 - test_size) * 1.00000001) - 1;
    
    int startRowX_test = nRows *  (1 - test_size) * 1.00000001;
    int startRowY_test = nRowsY *  (1 - test_size) * 1.00000001;

    X_train = X.extract(0, endRowX_train, 0, -1);
    Y_train = Y.extract(0, endRowY_train, 0, 0);

    X_test = X.extract(startRowX_test, nRows, 0, -1);
    Y_test = Y.extract(startRowY_test, nRowsY, 0, 0);

    return;
}

void kNN::fit(const Dataset& X_train, const Dataset& Y_train)
{
    this -> X_train = X_train;
    this -> Y_train = Y_train;
    return;
}

/////////////////////////////////////////Merge sort//////////////////////////////////////////

void merge(dataOfDistance *arr, int const left, int const middle, int const right)
{
    int const subArrayOne = middle - left + 1;
    int const subArrayTwo = right - middle;

    dataOfDistance *leftArr = new dataOfDistance[subArrayOne];
    dataOfDistance *rightArr = new dataOfDistance[subArrayTwo];

    for (int i = 0; i < subArrayOne; i++)
    {
        leftArr[i] = arr[left + i];
    }

    for (int i = 0; i < subArrayTwo; i++)
    {
        rightArr[i] = arr[middle + 1 + i];
    }

    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArr[indexOfSubArrayOne].getDistance() <= rightArr[indexOfSubArrayTwo].getDistance())
        {
            arr[indexOfMergedArray] = leftArr[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }

        else
        {
            arr[indexOfMergedArray] = rightArr[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne)
    {
        arr[indexOfMergedArray] = leftArr[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo)
    {
        arr[indexOfMergedArray] = rightArr[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete [] leftArr;
    delete [] rightArr;
}

void mergeSort(dataOfDistance* arr, int const begin, int const end)
{
    if (begin >= end)
    {
        return;
    }

    int middle = begin + (end - begin) / 2;
    mergeSort(arr, begin, middle);
    mergeSort(arr, middle + 1, end);
    // merge(arr, begin, middle, end);


    ///////////////////////////////////////////Optimization//////////////////////////////////////////
    if(arr[middle].getDistance() > arr[middle + 1].getDistance())
    {
        merge(arr, begin, middle, end);
    }
}

/////////////////////////////////////////Merge sort//////////////////////////////////////////


Dataset Dataset::predict(const Dataset& X_train, const Dataset& Y_train, const int k) const
{
    int length = X_train.data -> length();

    if (length == 0)
    {
        return Dataset();
    }

    Dataset result;
    dataOfDistance *arrdistance = new dataOfDistance[length];

    result.columnNames -> push_back("label");

    for (int i = 0; i < this -> data -> length(); i++)
    {
        for (int j = 0; j < length; j++)
        {
            List<int>* Image1 = this -> data -> get(i);
            List<int>* Image2 = X_train.data -> get(j);

            double dis = distanceEuclidean(Image1, Image2);
            arrdistance[j].setDistance(dis);
            arrdistance[j].setIndex(Y_train.data -> get(j) -> get(0));
        }
        
        mergeSort(arrdistance, 0, length - 1);

        int *count = new int[10];
        for (int j = 0; j < 10; j++)
        {
            count[j] = 0;
        }

        if (X_train.data -> length() < k)
        {
            for (int j = 0; j < X_train.data -> length(); j++)
            {
                count[arrdistance[j].getIndex()]++;
            }
        }

        else
        {
            for (int j = 0; j < k; j++)
            {
                count[arrdistance[j].getIndex()]++;
            }
        }

        int max = 0;
        int resultIndex = 0;
        for (int j = 0; j < 10; j++)
        {
            if (count[j] > max)
            {
                max = count[j];
                resultIndex = j;
            }
        }

        delete [] count;

        List<int>* row = new Image<int>();
        row -> push_back(resultIndex);
        result.data -> push_back(row);
    }
    delete [] arrdistance;
    return result;
}

double Dataset::score(const Dataset& Y_pred) const
{
    if (this -> data -> length() != Y_pred.data -> length())
    {
        return -1;
    }

    else
    {
        if (this -> data -> length() == 0)
        {
            return -1;
        }

        int count = 0;

        int rowsOfY_pred, colsOfY_pred;
        Y_pred.getShape(rowsOfY_pred, colsOfY_pred);

        int rowsOfY, colsOfY;
        this -> getShape(rowsOfY, colsOfY);

        int **dataOfY_pred = new int*[rowsOfY_pred];
        int **dataOfY = new int*[rowsOfY];
        for (int i = 0; i < rowsOfY_pred; i++)
        {
            dataOfY_pred[i] = new int[colsOfY_pred];
        }

        for (int i = 0; i < rowsOfY; i++)
        {
            dataOfY[i] = new int[colsOfY];
        }

        Y_pred.convert2D(dataOfY_pred);
        this -> convert2D(dataOfY);
        for (int i = 0; i < rowsOfY; i++)
        {
            if (dataOfY[i][0] == dataOfY_pred[i][0])
            {
                count++;
            }
        }

        for (int i = 0; i < rowsOfY; i++)
        {
            delete [] dataOfY[i];
        }

        for (int i = 0; i < rowsOfY_pred; i++)
        {
            delete [] dataOfY_pred[i];
        }
        
        delete[] dataOfY;
        delete[] dataOfY_pred;

        return (double)count / this -> data -> length();
    }
}
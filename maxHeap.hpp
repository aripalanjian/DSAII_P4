#ifndef MAXHEAP_CPP
#define MAXHEAP_CPP

template <typename T>
class MaxHeap{
    T* array;
    int size;
public:
    MaxHeap(T arr[], int size);
    ~MaxHeap(){delete[] array;}
    T pop();
    T peek();
    void heapify(int index);
    T get(int index){return array[index];}
    T* getArray(){return array;}
    void swap(int a, int b);
    void resize();
    void print();
};

#endif

template <typename T>
MaxHeap<T>::MaxHeap(T arr[], int size){
    this->array = new T[size];
    this->size = size;
    for (int i = 0; i < size; i++){
        this->array[i] = arr[i];
    }
    for (int i = (size - 1) / 2; i >= 0; i--) {
        heapify(i);
    }
}

template <typename T>
void MaxHeap<T>::resize(){
    T tmpArr[size-1];
    for(int i = 0; i < size - 1; i++){
        tmpArr[i] = array[i+1];
    }
    delete [] array;
    size--;
    array = new T[size];
    for(int i = 0; i < size; i++){
        array[i] = tmpArr[i];
    }
}

template <typename T>
T MaxHeap<T>::pop(){
    T tmp = array[0];

    resize();    

    for (int i = (size - 1) / 2; i >= 0; i--) {
        heapify(i);
    }
    return tmp;
}

template <typename T>
T MaxHeap<T>::peek(){
    T tmp = array[0];
    return tmp;
}

template <typename T>
void MaxHeap<T>::swap(int a, int b){
    T tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

template <typename T>
void MaxHeap<T>::heapify(int index) {
    int max = index;           
    int left = 2 * index + 1;      
    int right = 2 * index + 2;     
    
    if (left < size && array[left] > array[max])
        max = left;
    
    if (right < size && array[right] > array[max])
        max = right;
    
    if (max != index) {
        swap(index, max);  
        heapify(max);               
    }
}

template <typename T>
void MaxHeap<T>::print(){
    for (int i = 0; i < size; i++){
        std::cout << array[i] << " ";
    }    
    std::cout << "\n";
}
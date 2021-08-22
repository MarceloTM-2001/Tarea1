#include <iostream>
#include <fstream>

using namespace std;

class QuickSort{
public:
    //swap cambia las variables en caso de ser menor que el pivot
    void swap(int*a,int*b){
        int t = *a;
        *a=*b;
        *b=t;
    }
    // se encarga de hacer la partición y el ordenamiento en base al pivot
    // (se decidió que el pivot fuera el último elemento del arreglo)
    int partition(int arr[],int low, int high){
        int pivot=arr[high];
        int i =(low-1);
        for (int j=low;j <=high-1;j++){
            if(arr[j]<pivot){
                i++;
                swap(&arr[i],&arr[j]);
            }
        }
        swap(&arr[i+1],&arr[high]);
        return(i+1);
    }
    //Maneja el ordenamiento
    void quicksort(int arr[],int low, int high){
        if(low<high){
            int pi = partition(arr,low,high);

            quicksort(arr,low,pi-1);
            quicksort(arr,pi+1,high);
        }
    }
    static void printarray(int arr[], int size){
        int i;
        for (i=0;i<size;i++){
            cout <<arr[i]<< " ";
            cout<< std::endl;
        }
    }
    QuickSort(int arr[],int low,int high){
        quicksort(arr,low,high);
        }

};
class Page{
public:
    int arr[256];
    int use=1000000;
    int number;
    //Cada página registra si fue usada o no
    void used(int usada){
        use=use/10;
        if (usada==1){

            use+=10000000;
        }
    }


};

int main() {
    int arr[6]={5,2,4,7,9};
    int n = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr,0,n-1);
    QuickSort::printarray(arr,n);

    return 0;
}

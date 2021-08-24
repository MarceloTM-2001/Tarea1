#include <iostream>
#include <fstream>
#include <string>

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
    int arr[256];//almacenamiento de 1kb de enteros
    int index;
    int use=1000000;//registro de uso de cada página
    //Cada página registra si fue usada o no

    void used(bool usada){
        use= round(use/10);
        if (usada==1){
            use+=10000000;
        }
    }
};


class MemoryManager{
public:
  Page Pages[6];
  int size=0;
  void writePage(Page page){
      int begg=256*(page.index-1);
      int final=256*(page.index);
  }
  int* readPage(int number){


  }

  int Pagedarray(int index){
      float dif=index/256;//encontrar la página necesaria
      int page = round(dif);//redondeo ya que la pagina es un entero

      for(int i=0;i<6;i++){//Revisar memoria por la página deseada
          Page checkPage = Pages[i];

          if(checkPage.index==page){ //La pagina está en memoria
              return checkPage.arr[index-(256*page)];//devolver el índice correspondiente
          }
          int PageFault(page);//La página no está en memoria

      }

  }
  int PageFault(int page){
      int exchange=searchexchange();// busca la página menos usada



  }
  int searchexchange(){
      int leastused= Pages[0].use;
      int i;
      for( i=1;i<6;i++){
          if(Pages[i].use<leastused){
              leastused=Pages[i].use;
              continue;
          }
      }
      return i;
  }

  void filesize(){
      fstream OldFile;
      OldFile.open("C:\\Users\\Lenovo\\CLionProjects\\untitled1\\PruebaT1.txt",ios::in);
      char number;
      char lim[2] ="," ;
      while (OldFile.get(number)){
          if (number==*lim){
              size+=1;
          }
      }
      OldFile.close();
  }
};

int main() {
    int arr[6]={5,2,4,7,9};
    int n = sizeof(arr)/sizeof(arr[0]);
    MemoryManager MMU;
    return 0;
}

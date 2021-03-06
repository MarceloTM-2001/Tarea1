#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class Page{
public:
    int arr[256];//almacenamiento de 1kb de enteros
    int index;//Número de página registrada
    int use=1000000;//registro de uso de cada página

    //Cada página registra si fue usada o no
    void used(bool usada){
        use= round(use/10);
        if (usada== true){
            use+=10000000;
        }
    }
};


//Clase que se encarga de llevar y traer páginas al archivo y encontrar el
// dato que se le pida dentro del archivo
class MemoryManager{
public:
    string File;
    Page Pages[6];//Memoria
    int size=0;//Cantidad total de números

  //Escribe una página de vuelta al archivo
  void writePage(Page page){
      string before= filecopier(256*(page.index), true);
      string middle= writepageaux(page);
      string after=filecopier(256*(page.index+1), false);
      fstream newFile;
      newFile.open("archivo_resultado.txt",ios::out);
      newFile<<before<<middle<<after<<endl;
  }

  //copia lo que se encuentra antes y después de un bloque del archivo
  string filecopier(int marca,bool antes){
      string resultado;
      fstream newFile;
      newFile.open("archivo_resultado.txt",ios::in);
      char charcopy;
      char limit[2]=",";
      int pointer=0;
      while(newFile.get(charcopy)){
          if(antes==true){
              if(pointer<marca){
                  resultado+=charcopy;
                  if(charcopy==*limit){
                      pointer+=1;
                  }
              }else {
                  break;
              }
          }else{
              if(marca<=pointer){
                  resultado+=charcopy;
              }else{
                  if(charcopy==*limit){
                      pointer+=1;
                  }
              }
          }
      }
      return resultado;
  }


  //crea un string con los enteros a copiar en el archivo
  string writepageaux(Page page){
      string newints;
      for(int i=0;i<256;i++){
          newints+=to_string(page.arr[i]);
          newints+=",";
      }
      return newints;
  }


  //Lee una página del archivo y la añade a la memoria
  Page readPage(int index){
      int begg=256*(index);//inicio de la página
      int final=256*(index+1);//Final de la página
      int pointer=0;//entero por el que va del archivo
      int indice =0;//Enteros escribiendose en la pçagina
      string entero;
      Page newpage;
      newpage.index=index;
      char copy;
      char limit[2]=",";
      fstream File;
      File.open("archivo_resultado.txt",ios::in);
      while(File.get(copy)){//Busqueda de la página en el archivo
          if (pointer==final){
              File.close();
              break;
          }else if(begg<=pointer){//Estamos en la página
              if(copy==*limit){
                  pointer+=1;
                  newpage.arr[indice]=atoi(entero.c_str());
                  indice+=1;
                  entero="";
              }else{
                  entero+=copy;
              }
          }else{//No estamos en la página
              if(copy==*limit){
                  pointer+=1;
              }
          }

      }
      return newpage;
  }

  //Busca un elemento del archivo dentro de los archivos en memoria
  int *Pagedarray(int index){
      float dif=index/256;//encontrar la página necesaria
      int page = round(dif);//redondeo ya que la pagina es un entero

      for(int i=0;i<6;i++){//Revisar memoria por la página deseada
          if(Pages[i].index==page){ //La pagina está en memoria
              Pages[i].used(true);//Registra que la página se usó
              return &Pages[i].arr[index-(256*page)];//devolver el índice correspondiente
          }
          Pages[i].used(false); //Registra que la página no se usó
      }
      Page position=PageFault(page);//La página no está en memoria
      for(int i=0;i<6;i++){
          if(Pages[i].index==page){
              return &Pages[i].arr[index-(256*page)];//devolver el índice correspondiente
          }
      }
  }


  //Se utiliza cuando se requiere una página que no está en memoria
  Page PageFault(int page){
      int exchange=searchexchange();// busca la página menos usada
      writePage(Pages[exchange]);
      Page newPage=readPage(page);
      Pages[exchange]=newPage;
      return newPage;
  }


  //Busca la página menos usadad de la memoria
  int searchexchange(){
      int leastused= Pages[0].use;
      int leastusedindex=0;
      int i;
      for( i=1;i<6;i++){
          if(Pages[i].use<=leastused){
              leastused=Pages[i].use;
              leastusedindex=i;
              continue;
          }
      }
      return leastusedindex;
  }

  //LLena las primeras páginas del array
  void Fillarray(){
      fstream File;
      File.open("archivo_resultado.txt",ios::in);
      for(int i=0;i<6;i++){
          Page page=readPage(i);
          Pages[i]=page;
      }
  }

  //Cantidad de enteros del archivo completo
  void filesize(){
      fstream OldFile;
      OldFile.open("archivo_resultado.txt",ios::in);
      char number;
      char lim[2] ="," ;
      while (OldFile.get(number)){
          if (number==*lim){
              size+=1;
          }
      }
      OldFile.close();
  }

  //Copia el archivo en uno nuevo que se ordenará
  void copyfile(){
      fstream OldFile;
      fstream Newfile;
      OldFile.open(this->File,ios::in);
      Newfile.open("archivo_resultado.txt",ios::out);
      string archivo;
      while(getline(OldFile,archivo)){
          Newfile<<archivo<<endl;
      }
      Newfile.close();
      OldFile.close();
  }

  //Copia las páginas ya ordenadas que quedan en memoria
  void CopyFinal(){
      for(int i=0;i<6;i++){
          writePage(this->Pages[i]);
      }
  }
};

//Clase que incluye el quick sort
class QuickSort{
public:
    MemoryManager MMU;
    string File;

    //swap cambia las variables en caso de ser menor que el pivot
    void swap(int*a,int*b){
        int t = *a;
        *a=*b;
        *b=t;
    }


    // se encarga de hacer la partición y el ordenamiento en base al pivot
    // (se decidió que el pivot fuera el último elemento del arreglo)
    int partition(int low, int high){
        int pivot;
        pivot=*MMU.Pagedarray(high);
        int i =(low-1);
        for (int j=low;j <=high-1;j++){
            if(*MMU.Pagedarray(j)<pivot){
                i++;
                swap(MMU.Pagedarray(i),MMU.Pagedarray(j));
            }
        }
        swap(MMU.Pagedarray(i+1),MMU.Pagedarray(high));
        return(i+1);
    }

    //Maneja el ordenamiento
    void quicksort(int low, int high){
        if(low<high){
            int pi = partition(low,high);

            quicksort(low,pi-1);
            quicksort(pi+1,high);
        }
    }

    //Imprime un arreglo en consola
    static void printarray(int arr[], int size){
        int i;
        for (i=0;i<size;i++){
            cout <<arr[i]<< " ";
            cout<< std::endl;
        }
    }


    //Builder que corre el algoritmo automáticamente
    QuickSort(MemoryManager MMU,int low,int high){
        this->MMU=MMU;
        quicksort(low,high);
        this->MMU.CopyFinal();
    }

};


int main() {
    string File;
    cout<<"Escriba la dirección del archivo a ordenar: "<<endl;
    cin>>File;
    MemoryManager MMU;
    MMU.File=File;
    MMU.filesize();
    MMU.copyfile();
    MMU.Fillarray();
    QuickSort QS(MMU,0,MMU.size-1);
}


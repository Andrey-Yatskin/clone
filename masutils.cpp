#include <iostream>

using namespace std;

int AverageMas(int *source, int size)
{
int sum=0;
for(int i=0; i < size; i++)
{
sum+=*source++;
}

return (double)sum/size;
}
int main()
{
int siz;
std::cin>>siz;
int sour[siz];
for(int i=0; i<siz; i++)
{
sour[i]=i;

}

std::cout<< AverageMas(sour, siz) << endl;


std::cout<<endl;
system("PAUSE");
}

#include <iostream>
 
using namespace std;

int  AverageMas(int *source, int size)
{
  int sum=0;
  for(int i=0; i<size; i++)
  {
    sum+=*source++;
  }
 
  return (double)sum/size;
}
int testAverageMas(){
	int sizze = 5;
	int arr[]{0,1,2,3,4};
	int num = AverageMas(arr, 5);
	if (num == 2)
	return 0;
	else 
	return -1;
}
int main()
{ 
  int siz = 5;
  int sour[siz];
  for(int i=0; i<siz; i++)
  {
   sour[i]=i;
   
  }
 testAverageMas();
 if (testAverageMas() == 0)
    cout<<"Correct";
    else 
    cout<<"Fail";
 

  cout<<endl;
  system("PAUSE");
}





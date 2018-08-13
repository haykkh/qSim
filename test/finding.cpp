#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main ()
{
   vector <int> v;

   v.push_back (50);
   v.push_back (2991);
   v.push_back (23);
   v.push_back (9999);

   vector <int>::iterator i = v.begin ();


   i = find (v.begin (),v.end (), 2991);

   if (i != v.end ())
   {
       int nPosition = distance (v.begin (), i);
       cout << "Value "<< *i;
       cout << " found in the vector at position: " << nPosition << endl;
   }

   return 0;
}
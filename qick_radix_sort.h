#ifndef QICK_RAD_SOR
#define QICK_RAD_SOR 1
#include <cstddef>


#define UNLIKELY(x) __builtin_expect((bool)(x),0)//we tell the compiler this if is improvable

     /*
     recomend compile g++ GNU
     needs
     the class need to have the next operator overload:
     - bool=obj_arr & T;
     - bool=obj_arr > obj_arr;
     - void=obj_arr =obj_arr;
     we need to define class T ex T=size_t;
     if we do a custom class T we need the next operator overload:
     - T=T{1}
     - T=T<< size_t
    //standard call mode leixor::qick_radix_sort(pointer,size of the arr); 
    //call mode leixor::<class of the pointer,the type of value>qick_radix_sort(pointer,size of the arr);
       - ex:leixor::<unsigned long long int,unsigned long long int>qick_radix_sort(pointer,size of the arr);
     */
namespace leixor {
    //is in excess on purpose
    template<class obj_arr,class T>
    size_t logb2(obj_arr* num) {

        if (num == nullptr) return -1;
        for (size_t i = sizeof(T)*8; i < size_t(-1); --i)
            if (UNLIKELY(*num & T{1} << i))//this will be true only one time so is worth
                return i;
        return -1;
    }

    template<class obj_arr>
    obj_arr* get_max(obj_arr* start, obj_arr* end) {
        if (start == nullptr || end == nullptr) return nullptr;
        if (start >end)return nullptr;
        obj_arr* aux= start;
        --end;
        while (start<end){
            ++start;
            aux = (*start > *aux) ? start : aux;//we pass a pointer is more faster that pass the object it self
        }
        return aux;
    }

    template<class obj_arr,class T>
    void two2_rad(obj_arr*const  start, obj_arr*const finish,const size_t depth) {

        if (finish <start + 2)//if is one elemente or non is alredy sort
            return;

        obj_arr auxiliar;

        if (finish == start + 2) { //is more faster to do a comparetion bettewn 2 elements than risck a recursive inter ex: 1000 1001, if we do the recusive we will call this funtion 8 times again 
            if (*start > *(start + 1)) {
                auxiliar = *start;
                *start = *(start + 1);
                *(start + 1) = auxiliar;
            }
            return;
        }

        obj_arr* s = start, * f = finish - 1;
        while (s<f){
            if (*s & T{1} << depth){
                
                while(*f & T{1} << depth && f>s){//we supose the array is partialy sorted
                    --f;
                }
                if (f<=s)
                    break;
                //less swaps more fast
                auxiliar = *s;
                *s = *f;
                *f = auxiliar;
                --f;
            }
            ++s;//we supose the array is partialy sorted
        }
        if (!(*s & T{1} << depth))
            ++s;
        // is more faster do this than s+=!(*s & 1 << depth);

        if (depth == 0) return;

        two2_rad<obj_arr,T>(start, s, depth-1);
        two2_rad<obj_arr,T>(s, finish, depth-1);
    }

    template<class obj_arr,class T=size_t>
    bool qick_radix_sort(obj_arr* arr, size_t size) {

        if (arr == nullptr || size < 2)
            return false;
        size_t depth= logb2<obj_arr,T>(get_max(arr, arr+size));
        if (depth == size_t(-1))//the max number will be not 2^(2^32-1) i expect...
            return false;
        two2_rad<obj_arr,T>(arr,arr+size, depth);
        return true;
    }
}
#endif
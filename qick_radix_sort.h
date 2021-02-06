#pragma once
namespace leixor {
		//fast log in power of 2 we are using size so we can't use bit_width
	static size_t& logb2(size_t num) {
		size_t aux = 1;
		if (num == 0) return (aux = -1);
		while (0 < (num >>= 1))
			aux++;
		return aux;
	}
	//------------------------obj version---------------------------
	//custom get_max because i don't wanna add lib,and normaly we will use this in a custom class
	template<class obj_arr>
	static size_t& get_max(obj_arr*& arr, const size_t& size) {
		
		size_t i = size%2, aux = arr[0].get_size_t(), aux2=-1;
		if (size == 0)return aux2;
		for (; i < size; i += 2) {
			aux2 = arr[i].get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
			aux2 = arr[i + 1].get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
		}
		return aux;
	}
	//----------------------------pointer obj version---------------------
	template<class obj_arr>
	static size_t& get_max(obj_arr**& arr, const size_t& size) {
		
		size_t i = size%2, aux = arr[0]->get_size_t(), aux2=-1;
		if (size == 0)return aux2;
		for (; i < size; i += 2) {
			aux2 = arr[i]->get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
			aux2 = arr[i + 1]->get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
		}
		return aux;
	}



	//---------------------------------------------------------------------
	//-----------------object orientedversion---------
	template<class obj_arr>
	void two_rad(obj_arr*& arr, size_t start, size_t finish, size_t depth) {
		depth--;
		static size_t s, f;
		static bool mod_cal;
		static obj_arr auxiliar;

		f = finish - 1; s = start;
		while (s < f) {
			auxiliar = arr[s];
			if ((auxiliar.get_size_t() >> depth) % 2) {
				arr[s] = arr[f];
				arr[f] = auxiliar;
				f--;
			}
			else
				s++;
		}
		size_t mid = s + !((arr[s].get_size_t() >> depth) % 2);
		if (depth > 0) {
			if (mid - start > 2)
				two_rad(arr, start, mid, depth);
			else if (mid - start > 1) {
				mod_cal = arr[start].get_size_t() > arr[start + 1].get_size_t();

				auxiliar = arr[start];
				arr[start] = arr[start + mod_cal];
				arr[start + mod_cal] = auxiliar;
			}
			if (finish - mid > 2)
				two_rad(arr, mid, finish, depth);
			else if (finish - mid > 1) {
				mod_cal = arr[mid].get_size_t() > arr[mid + 1].get_size_t();
				auxiliar = arr[mid];
				arr[mid] = arr[mid + mod_cal];
				arr[mid + mod_cal] = auxiliar;
			}
		}

	}
	template<class obj_arr>
	bool qick_radix_sort(obj_arr* arr, size_t size) {
		if (arr == nullptr || size < 2)
			return false;
		two_rad(arr, 0, size, logb2(get_max(arr, size)));
		return true;
	}
	//-----------------pointer orientedversion---------
	template<class obj_arr>
	void two_rad(obj_arr**& arr, size_t start, size_t finish, size_t depth) {
		depth--;
		static size_t s, f;
		static bool mod_cal;
		static obj_arr* auxiliar;
		
		f = finish - 1; s = start;
		while (s < f) {
			auxiliar = arr[s];
			if ((auxiliar->get_size_t() >> depth) % 2) {
				arr[s] = arr[f];
				arr[f] = auxiliar;
				f--;
			}else
				s++;
		}
		size_t mid =s+ !((arr[s]->get_size_t() >> depth)%2);
		if (depth>0){
			if (mid-start>2)
				two_rad(arr,start,mid,depth);
			else if (mid - start > 1) {
				mod_cal = arr[start]->get_size_t() > arr[start + 1]->get_size_t();
				
				auxiliar = arr[start];
				arr[start] = arr[start + mod_cal];
				arr[start + mod_cal] = auxiliar;
			}
			if (finish - mid > 2)
				two_rad(arr,mid,finish,depth);
			else if (finish - mid > 1) {
				mod_cal = arr[mid]->get_size_t() > arr[mid + 1]->get_size_t();
				auxiliar = arr[mid];
				arr[mid] = arr[mid + mod_cal];
				arr[mid + mod_cal] = auxiliar;
			}
		}

	}
	template<class obj_arr>
	bool qick_radix_sort(obj_arr** arr, size_t size) {
		if (arr == nullptr || size < 2)
			return false;
		two_rad(arr, 0, size, logb2(get_max(arr, size)));
		return true;
	}
}
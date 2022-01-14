#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <utility>

//****************************************************************************************
template <typename pooltype, typename node, typename T>
class class_iterator {
   private:		
	pooltype* pool;
	node current;

   public:
	using value_type = T;
	using reference = value_type&;
	

	explicit class_iterator(pooltype* p, node x)  : pool{p}, current{x} {}

	reference operator*() const  { return (*pool)[current - 1].value; }

	
	class_iterator operator++(int) {
		auto tmp = *this;
		++(*this);
		return tmp;
	}
	
	class_iterator& operator++() {
		current = (*pool)[current - 1].next;
		return *this;
	}

	friend bool operator==(const class_iterator& x, const class_iterator& y) {
		return x.current == y.current;
	}

	friend bool operator!=(const class_iterator& x, const class_iterator& y) { return !(x == y); }
};
//*********************************************************************
using namespace std;
template<typename T, typename N=size_t>
class list_pool{
    private:
    
       typedef T value_type;
       typedef N list_type;

    struct node_t{
        value_type value;
        list_type next;
    };
    vector<node_t> pool;
   
    using size_type = typename vector<node_t>::size_type;

    list_type free_node_list=end();
    list_type index=1;

    node_t& node(list_type x) 
    { 
    	return pool[x-1]; 
    }
    const node_t& node(list_type x) const  
    { 
    return pool[x-1]; 
    }

    public:

    list_pool()=default;

    explicit list_pool(size_type n)
    {   
        pool.reserve(n);
    }

 //****************************************************
   list_type push_front(const T& val, list_type head)
	 { 
		return _push_front(val, head); 
		}
	list_type push_front(T&& val, list_type head)
	{ 
		return _push_front(move(val), head);
		 }		
	
	list_type _push_front(T&& val, list_type head){
		
		node_t Node{val, head};

		if(free_node_list == 0)
		{
			pool.push_back(Node);	
		}
		else
		{
			auto head_new = free_node_list;
			free_node_list = next(free_node_list);
			value(head_new) = forward<value_type>(val);
		}
		return pool.size();
	}

//******************************************************************
   list_type push_back(const T& val, list_type head)
	{ 
		return _push_back(val, head); 
		}
	list_type push_back(T&& val, list_type head)
	{ 
		return _push_back(move(val), head);
		 }
    
	list_type _push_back(T&& val, list_type head){

		if (head==0) {
			return push_front(forward<T>(val), head);
		}
		else{      	
				auto tmp1=1,tmp2 = free_node_list,tmp3 = 0;
				while(next(tmp1) != 0){
					tmp1 = next(tmp1);
				}
				node_t Node{val, 0};
				if(free_node_list == 0){
					pool.push_back(Node);	
					tmp3 = pool.size();
				}else{
				free_node_list = next(free_node_list);
				pool[tmp2 - 1] = Node;
				tmp3 = tmp2;
			}
		     next(head) = tmp3;
		}	
		return head;
	}
	
    
//**********************************************************
	using iterator = class_iterator<vector<node_t>, list_type, value_type>;
	using const_iterator = class_iterator<vector<node_t>, list_type, const value_type>;


	iterator begin(list_type x) 
	{
	 return iterator(&pool, x); 
	 }
	
	iterator end(list_type ) 
	{ 
	return iterator(&pool, end()); 
	}

	const_iterator begin(list_type x) const 
	{
	 return const_iterator(&pool, x); 
	}
	const_iterator end(list_type ) const 
	{
	return const_iterator(&pool, end()); 
	}
	const_iterator cbegin(list_type x) const 
	{ 
	return const_iterator(&pool, x); 
	}
	const_iterator cend(list_type ) const 
	{ 
	return const_iterator(&pool, end()); 
	}
        void reserve(size_type n) { pool.reserve(n); }

	size_type capacity() const 
	{ 
	return pool.capacity(); 
	}
        size_type size() const 
        { 
        return pool.size(); 
        }

    T& value(list_type x)
    {
    	return node(x).value;
    }
   
    list_type& next(list_type x)
    {
     	return node(x).next;
    }

    list_type end() const  
    { 
        return 0; 
    }

    list_type new_list()
    { 
    	return end(); 
    }

    bool is_empty(list_type x) const
    {
      return x==end();
    }
    
 
    
//**************************************************************
    list_type free(list_type x) 
    {
        if(x!=0){
	auto temp=node(x).next;
        return temp;	
	}
	else{
	return x;
    	}
     }
  
  list_type free_list(list_type temp)
  {
	if(free_node_list !=0)
	{
		 while (node(temp).next){
   			temp = node(temp).next;
	   	}
   
    	return temp;
	}
	else{
	free_node_list=temp;
	}
	
       return end();
  }     
};


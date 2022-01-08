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
		return (*x.pool)[x.current-1].value == (*y.pool)[y.current-1].value;
	}

	friend bool operator!=(const class_iterator& x, const class_iterator& y) { return !(x == y); }
};
//*********************************************************************
using namespace std;
template<typename T, typename N=size_t>
class list_pool{
    public:
    
       typedef T value_type;
       typedef N list_type;
       
 
    struct node_t{
        value_type value;
        list_type next;
    };
    vector<node_t> pool;

  //  using list_type = N;
   // using value_type = T;
   
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
    list_type push_front(value_type&& val, list_type head){
         if(free_node_list==0)
         { 
            value(index)=forward<value_type>(val);
            return index;
        }
        else
        {
        auto  temp = free_node_list;
        free_node_list=next(free_node_list);
        value(temp)=forward<value_type>(val);     
        next(temp)=head;     
        return temp;
            
        }
    }

//******************************************************************
    list_type push_back(value_type&& val, list_type head)
    {
       list_type temp{head};
        if(head == 0)
        {   
        
        value(index)=val;
        return index;
        
        }
        while(next(temp)!=0)
        {
            temp=next(temp);
        }
        if(free_node_list==0)
        {
         
         index++;
         next(temp)=index;
         value(index)=forward<value_type>(val);
         next(index)=end();
         
         return head;
        }
        else
        {
            return head;
        }
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
        if(x!=end())
        {
        	auto temp=node(x).next;
                return temp;
        	
	}
	else
	{
       		return x;
    	}
    }
    
  list_type free_list(list_type temp)
  {
	if(free_node_list)
	{
		 while (node(temp).next)	
   	   	{
   			temp = node(temp).next;
	   	}
   
    	return temp;
	}
	else
	{
		free_node_list=temp;
	}
	
        return end();
  } 
  
 
    
};

